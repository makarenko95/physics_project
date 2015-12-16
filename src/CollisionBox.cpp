/***********************************************************************
CollisionBox - Class to represent a rectangular box containing spheres
of a fixed radius interacting by fully elastic collisions.
Copyright (c) 2005 Oliver Kreylos
***********************************************************************/

#define COLLISIONBOX_IMPLEMENTATION

#include <Math/Math.h>

#include "CollisionBox.h"

/*****************************
Methods of class CollisionBox:
*****************************/

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queueCollisionsInCell(
    typename CollisionBox<ScalarParam, dimensionParam>::GridCell *cell,
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *particle1,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
    bool symmetric,
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *otherParticle,
    typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
	/* Calculate all intersections between two particles: */
    for (Particle *particle2 = cell->particlesHead; particle2 != 0; particle2 = particle2->cellSucc)
        if (particle2 != particle1 && particle2 != otherParticle && (symmetric || particle2 > particle1))
        {
            /* Calculate any possible intersection time between the two particles: */
            Vector d = particle1->position - particle2->position;
            d -= particle1->velocity * particle1->timeStamp;
            d += particle2->velocity * particle2->timeStamp;
            Vector vd = particle1->velocity - particle2->velocity;
            Scalar vd2 = Geometry::sqr(vd);

            if (vd2 > Scalar(0)) // Are the two particles' velocities different?
			{
                /* Solve the quadratic equation determining possible collisions: */
                Scalar ph = (d * vd) / vd2;
                Scalar q = (Geometry::sqr(d) - Scalar(4) * particleRadius2) / vd2;
                Scalar det = Math::sqr(ph) - q;

                if (det >= Scalar(0)) // Are there any solutions?
				{
                    /* Calculate the first solution (only that can be valid): */
                    Scalar collisionTime = -ph - Math::sqrt(det);

					/* If the collision is valid, i.e., occurs past the last update of both particles, queue it: */
                    if (collisionTime > particle1->timeStamp && collisionTime > particle2->timeStamp && collisionTime <= timeStep)
                    {
                        collisionQueue.insert(CollisionEvent(collisionTime, particle1, particle2));
					}
				}
			}
        }
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queueCellChanges(
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *particle,
    const typename CollisionBox<ScalarParam, dimensionParam>::Point &newPosition,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
    typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
	/* Check for crossing of any cell borders: */
    GridCell *cell = particle->cell;
    Scalar cellChangeTime = timeStep;
    int cellChangeDirection = -1;

    for (int i = 0; i < dimension; ++i)
    {
        if (newPosition[i] < cell->boundaries.min[i])
		{
            Scalar collisionTime = particle->timeStamp + (cell->boundaries.min[i] - particle->position[i]) / particle->velocity[i];

            if (cellChangeTime > collisionTime)
			{
                cellChangeTime = collisionTime;
                cellChangeDirection = 2 * i + 0;
			}
        }
        else if (newPosition[i] > cell->boundaries.max[i])
        {
            Scalar collisionTime = particle->timeStamp + (cell->boundaries.max[i] - particle->position[i]) / particle->velocity[i];

            if (cellChangeTime > collisionTime)
			{
                cellChangeTime = collisionTime;
                cellChangeDirection = 2 * i + 1;
			}
		}
	}

    if (cellChangeDirection >= 0)
    {
        collisionQueue.insert(CollisionEvent(cellChangeTime, particle, cellChangeDirection));
    }
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queueCollisions(
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *particle1,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
    bool symmetric,
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *otherParticle,
    typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
    /* Calculate the particle's position at the end of this time step: */
    Point newPosition = particle1->position + particle1->velocity * (timeStep - particle1->timeStamp);

    /* Calculate the piston's position at the end of this time step: */
    Scalar newPistonPosition = pistonPos + pistonVelocity * (timeStep - pistonTimeStamp);

	/* Check for crossing of cell borders: */
    queueCellChanges(particle1, newPosition, timeStep, collisionQueue);

	/* Check for collision with any of the collision box's walls: */
    for (int i = 0; i < dimension; ++i)
    {
        if (newPosition[i] < boundaries.min[i] + particleRadius)
        {
            Scalar collisionTime = particle1->timeStamp + (boundaries.min[i] + particleRadius - particle1->position[i]) / particle1->velocity[i];

            if (collisionTime < particle1->timeStamp)
            {
                collisionTime = particle1->timeStamp;
            }
            else if (collisionTime > timeStep)
            {
                collisionTime = timeStep;
            }

            Vector wallNormal = Vector::zero;
            wallNormal[i] = Scalar(1);
            collisionQueue.insert(CollisionEvent(collisionTime, particle1, wallNormal));
        }
        else if (newPosition[i] > boundaries.max[i] - particleRadius)
		{
            Scalar collisionTime = particle1->timeStamp + (boundaries.max[i] - particleRadius - particle1->position[i]) / particle1->velocity[i];

            if (collisionTime < particle1->timeStamp)
			{
                collisionTime = particle1->timeStamp;
			}
            else if (collisionTime > timeStep)
			{
                collisionTime = timeStep;
			}

            Vector wallNormal = Vector::zero;
            wallNormal[i] = Scalar(-1);
            collisionQueue.insert(CollisionEvent(collisionTime, particle1, wallNormal));
        }
    }

    /* Check for collision with piston */

    queuePistonCollision(particle1, timeStep, collisionQueue);

	/* Check for collision with any other particle: */
    GridCell *baseCell = particle1->cell;

    for (int i = 0; i < numNeighbors; ++i)
    {
        GridCell *cell = baseCell + neighborOffsets[i];
        queueCollisionsInCell(cell, particle1, timeStep, symmetric, otherParticle, collisionQueue);
	}
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queueCollisionsOnCellChange(
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *particle,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
    int cellChangeDirection,
    typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
	/* Calculate the particle's position at the end of this time step: */
    Point newPosition = particle->position + particle->velocity * (timeStep - particle->timeStamp);

	/* Check for crossing of cell borders: */
    queueCellChanges(particle, newPosition, timeStep, collisionQueue);

	/* Check for collision with any other particle: */
    GridCell *baseCell = particle->cell;

    for (int i = 0; i < numNeighbors; ++i)
        if (cellChangeMasks[i] & (1 << cellChangeDirection))
        {
            GridCell *cell = baseCell + neighborOffsets[i];
            queueCollisionsInCell(cell, particle, timeStep, true, 0, collisionQueue);
        }
}

template <class ScalarParam, int dimensionParam>
inline
CollisionBox<ScalarParam, dimensionParam>::CollisionBox(
    const typename CollisionBox<ScalarParam, dimensionParam>::Box &sBoundaries,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar sParticleRadius)
    : boundaries(sBoundaries),
      numNeighbors(0), neighborOffsets(0), cellChangeMasks(0),
      particleRadius(sParticleRadius), particleRadius2(Math::sqr(particleRadius)),
      attenuation(1),
      numParticles(0),
      pistonPos(0),
      pistonStart(0),
      pistonEnd(boundaries.max[0]),
      pistonVelocity(0.0),
      pistonTimeStamp(0.0),
      pistonDir(1.0),
      free_path(0),
      current_path(0),
      num_of_collisions(0)
{
	/* Calculate optimal number of cells and cell sizes: */
	Index numOuterCells;

    for (int i = 0; i < dimension; ++i)
    {
        numCells[i] = int(Math::floor(boundaries.getSize(i) / (particleRadius * Scalar(2))));
        cellSize[i] = boundaries.getSize(i) / Scalar(numCells[i]);
        numOuterCells[i] = numCells[i] + 2; // Create a layer of "ghost cells" in all directions
    }

	/* Create the cell array: */
	cells.resize(numOuterCells);

    for (Index index(0); index[0] < numOuterCells[0]; cells.preInc(index))
    {
		/* Initialize the cell: */
        Point min, max;

        for (int i = 0; i < dimension; ++i)
		{
            min[i] = boundaries.min[i] + cellSize[i] * Scalar(index[i] - 1);
            max[i] = boundaries.min[i] + cellSize[i] * Scalar(index[i] - 0);
		}

        cells(index).boundaries = Box(min, max);
        cells(index).particlesHead = 0;
        cells(index).particlesTail = 0;
    }

    /* Initialize the direct neighbor offsets: */
    for (int i = 0; i < dimension; ++i)
    {
        directNeighborOffsets[2 * i + 0] = -cells.getIncrement(i);
        directNeighborOffsets[2 * i + 1] = cells.getIncrement(i);
    }

	/* Initialize the neighbor array: */
    numNeighbors = 1;

    for (int i = 0; i < dimension; ++i)
    {
        numNeighbors *= 3;
    }

    neighborOffsets = new ssize_t[numNeighbors];
    cellChangeMasks = new int[numNeighbors];
	Index minBound;
	Index maxBound;

    for (int i = 0; i < dimension; ++i)
    {
        minBound[i] = -1;
        maxBound[i] = 2;
    }

    int neighborIndex = 0;

    for (Index index = minBound; index[0] < maxBound[0]; index.preInc(minBound, maxBound), ++neighborIndex)
    {
        neighborOffsets[neighborIndex] = 0;
        cellChangeMasks[neighborIndex] = 0x0;

        for (int i = 0; i < dimension; ++i)
		{
            neighborOffsets[neighborIndex] += cells.getIncrement(i) * index[i];

            if (index[i] == -1)
            {
                cellChangeMasks[neighborIndex] |= 1 << (2 * i + 0);
            }
            else if (index[i] == 1)
			{
                cellChangeMasks[neighborIndex] |= 1 << (2 * i + 1);
			}
		}
    }
}

template <class ScalarParam, int dimensionParam>
inline
CollisionBox<ScalarParam, dimensionParam>::~CollisionBox(
    void)
{
	delete[] neighborOffsets;
	delete[] cellChangeMasks;
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::setAttenuation(
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar newAttenuation)
{
    attenuation = newAttenuation;
}

template <class ScalarParam, int dimensionParam>
inline
bool
CollisionBox<ScalarParam, dimensionParam>::addParticle(
    const typename CollisionBox<ScalarParam, dimensionParam>::Point &newPosition,
    const typename CollisionBox<ScalarParam, dimensionParam>::Vector &newVelocity)
{
	/* Find the cell containing the new particle: */
    Point newP = newPosition;
	Index cellIndex;

    for (int i = 0; i < dimension; ++i)
    {
        if (newP[i] < boundaries.min[i] + particleRadius)
		{
            newP[i] = boundaries.min[i] + particleRadius;
        }
        else if (newP[i] > boundaries.max[i] - particleRadius)
        {
            newP[i] = boundaries.max[i] - particleRadius;
		}

        cellIndex[i] = int(Math::floor((newP[i] - boundaries.min[i]) / cellSize[i])) + 1;
    }

    GridCell *cell = cells.getAddress(cellIndex);

	/* Check if there is room to add the new particle: */
    for (int i = 0; i < numNeighbors; ++i)
    {
        GridCell *neighborCell = cell + neighborOffsets[i];

        for (Particle *pPtr = neighborCell->particlesHead; pPtr != 0; pPtr = pPtr->cellSucc)
		{
            Scalar dist2 = Geometry::sqrDist(pPtr->position, newP);

            if (dist2 <= Scalar(4)*particleRadius2)
			{
                return false;    // Could not add the particle
			}
		}
    }

	/* Add a new particle to the particle list: */
	particles.push_back(Particle());
    Particle &p = particles.back();

	/* Initialize the new particle: */
    p.position = newPosition;
    p.velocity = newVelocity;
    p.timeStamp = Scalar(0);
	cell->addParticle(&p);

	return true; // Particle succesfully added
}

template<class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queuePistonChange(
        typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
        typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
    Scalar newPos = pistonPos + pistonVelocity * (timeStep - pistonTimeStamp);
    if (pistonVelocity > 0 && newPos >= pistonEnd)
    {
        Scalar collisionTime = pistonTimeStamp + (pistonEnd - pistonPos) / pistonVelocity;
        collisionQueue.insert(CollisionEvent(collisionTime, pistonTimeStamp));
    }
    else if (pistonVelocity < 0 && newPos <= pistonStart)
    {
        Scalar collisionTime = pistonTimeStamp + (pistonStart - pistonPos) / pistonVelocity;
        collisionQueue.insert(CollisionEvent(collisionTime, pistonTimeStamp));
    }
}

template<class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queueCollisionsOnPistonChange(
        typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
        typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
    for (typename ParticleList::iterator pIt = particles.begin(); pIt != particles.end(); ++pIt)
    {
        queuePistonCollision(&(*pIt), timeStep, collisionQueue);
    }

    queuePistonChange(timeStep, collisionQueue);
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::queuePistonCollision(
    typename CollisionBox<ScalarParam, dimensionParam>::Particle *particle,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep,
    typename CollisionBox<ScalarParam, dimensionParam>::CollisionQueue &collisionQueue)
{
    if (pistonVelocity == 0 && pistonPos == 0) //it is such a wall
    {
        return;
    }

    Point newPosition = particle->position + particle->velocity * (timeStep - particle->timeStamp);
    Scalar newPistonPosition = pistonPos + pistonVelocity * (timeStep - pistonTimeStamp);

    if (newPosition[0] < newPistonPosition + particleRadius)
    {
        Scalar collisionTime = particle->timeStamp +
            (particle->position[0] - pistonPos - pistonVelocity * (particle->timeStamp - pistonTimeStamp)
            - particleRadius) /
            (pistonVelocity - particle->velocity[0]);

        if (collisionTime <= timeStep)
        {
            collisionQueue.insert(CollisionEvent(collisionTime, particle));
        }
    }
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::setPiston(
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar sPistonStart,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar sPistonEnd,
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar sPistonVelocity)
{
    pistonStart = sPistonStart;
    pistonEnd = sPistonEnd;
    pistonVelocity = sPistonVelocity;
}

template <class ScalarParam, int dimensionParam>
inline
typename CollisionBox<ScalarParam, dimensionParam>::Scalar
CollisionBox<ScalarParam, dimensionParam>::getPistonPos() const
{
    return pistonPos;
}


template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::simulate(
    typename CollisionBox<ScalarParam, dimensionParam>::Scalar timeStep)
{
    track.clear();
    updateTrack(getTrackedParticle());

    /* Initialize the collision queue: */
    CollisionQueue collisionQueue(numParticles * dimension);

    for (typename ParticleList::iterator pIt = particles.begin(); pIt != particles.end(); ++pIt)
	{
        queueCollisions(&(*pIt), timeStep, false, 0, collisionQueue);
    }

    queuePistonChange(timeStep, collisionQueue);

	/* Update all particles' positions and handle all collisions: */
    while (!collisionQueue.isEmpty())
    {
        /*if(collisionQueue.getNumElements() > 2000000)
            exit(0);
        Get the next collision from the queue: */
        CollisionEvent nc = collisionQueue.getSmallest();
		collisionQueue.removeSmallest();

		/* Handle the collision if it is still valid: */
        switch (nc.collisionType)
        {
        case CollisionEvent::CellChange:
            if (nc.particle1->timeStamp == nc.timeStamp1)
			{
                /* Let the particle cross into the next grid cell: */
                GridCell *cell = nc.particle1->cell;
                cell->removeParticle(nc.particle1);
                cell += directNeighborOffsets[nc.cellChangeDirection];
                cell->addParticle(nc.particle1);

                /* Re-calculate all the particle's collisions: */
                queueCollisionsOnCellChange(nc.particle1, timeStep, nc.cellChangeDirection, collisionQueue);
            }

            break;

        case CollisionEvent::WallCollision:
            if (nc.particle1->timeStamp == nc.timeStamp1)
            {
                Vector delta_pos = nc.particle1->velocity * (nc.collisionTime - nc.timeStamp1);
                updateFreePath(nc.particle1, delta_pos.mag());
                /* Bounce the particle off the wall: */
                nc.particle1->position += delta_pos;
                nc.particle1->timeStamp = nc.collisionTime;
                Vector dv = (Scalar(2) * (nc.wallNormal * nc.particle1->velocity)) * nc.wallNormal;
                nc.particle1->velocity -= dv;

                /* Re-calculate all the particle's collisions: */
                queueCollisions(nc.particle1, timeStep, true, 0, collisionQueue);
                updateTrack(nc.particle1);
            }

            break;

        case CollisionEvent::ParticleCollision:
            if (nc.particle1->timeStamp == nc.timeStamp1 && nc.particle2->timeStamp == nc.timeStamp2)
            {
                Vector delta_pos1 = nc.particle1->velocity * (nc.collisionTime - nc.timeStamp1);
                Vector delta_pos2 = nc.particle2->velocity * (nc.collisionTime - nc.timeStamp2);
                updateFreePath(nc.particle1, delta_pos1.mag());
                updateFreePath(nc.particle2, delta_pos2.mag());

                /* Bounce the two particles off each other: */
                nc.particle1->position += delta_pos1;
                nc.particle1->timeStamp = nc.collisionTime;
                nc.particle2->position += delta_pos2;
                nc.particle2->timeStamp = nc.collisionTime;
                Vector d = nc.particle2->position - nc.particle1->position;
                Scalar dLen2 = Geometry::sqr(d);
                Vector v1 = d * ((nc.particle1->velocity * d) / dLen2);
                Vector v2 = d * ((nc.particle2->velocity * d) / dLen2);
                Vector dv = v2 - v1;
                nc.particle1->velocity += dv;
                nc.particle2->velocity -= dv;

                /* Re-calculate all collisions of both particles: */
                queueCollisions(nc.particle1, timeStep, true, nc.particle2, collisionQueue);
                queueCollisions(nc.particle2, timeStep, true, nc.particle1, collisionQueue);
                updateTrack(nc.particle1);
                updateTrack(nc.particle2);
			}

            break;
        case CollisionEvent::PistonChangeDirection:
            if (pistonTimeStamp == nc.timeStamp1)
            {
                pistonPos += pistonVelocity * (nc.collisionTime - pistonTimeStamp);
                pistonTimeStamp = nc.collisionTime;
                pistonVelocity = -pistonVelocity;
                pistonDir = -pistonDir;

                queueCollisionsOnPistonChange(timeStep, collisionQueue);
            }

            break;

        case CollisionEvent::PistonCollision:
            if (nc.particle1->timeStamp == nc.timeStamp1)
            {
                Vector delta_pos = nc.particle1->velocity * (nc.collisionTime - nc.timeStamp1);
                updateFreePath(nc.particle1, delta_pos.mag());

                nc.particle1->position += delta_pos;
                nc.particle1->timeStamp = nc.collisionTime;
                nc.particle1->velocity[0] = 2 * pistonVelocity - nc.particle1->velocity[0];
                queueCollisions(nc.particle1, timeStep, true, 0, collisionQueue);
                updateTrack(nc.particle1);
            }

            break;
        }
    }

    /* Update all particles and piston to the end of the timestep: */
    if (attenuation != Scalar(1))
    {
        Scalar att = Math::pow(attenuation, timeStep); // Scale attenuation factor for this time step

        for (typename ParticleList::iterator pIt = particles.begin(); pIt != particles.end(); ++pIt)
		{
            pIt->position += pIt->velocity * (timeStep - pIt->timeStamp);
            pIt->velocity *= att;
            pIt->timeStamp = Scalar(0);
		}
    }
    else
    {
        for (typename ParticleList::iterator pIt = particles.begin(); pIt != particles.end(); ++pIt)
        {
            Vector delta_pos = pIt->velocity * (timeStep - pIt->timeStamp);

            if(&(*pIt) == getTrackedParticle())
                current_path += delta_pos.mag();

            pIt->position += delta_pos;
            pIt->timeStamp = Scalar(0);
		}
    }

    pistonPos += pistonVelocity * (timeStep - pistonTimeStamp);
    pistonTimeStamp = Scalar(0);

    updateTrack(getTrackedParticle());
}

template <class ScalarParam, int dimensionParam>
inline
const typename CollisionBox<ScalarParam, dimensionParam>::ParticleTrack &
CollisionBox<ScalarParam, dimensionParam>::getTrack() const
{
    return track;
}

template <class ScalarParam, int dimensionParam>
inline void
CollisionBox<ScalarParam, dimensionParam>::StopPiston()
{
    pistonVelocity = 0;
}

template <class ScalarParam, int dimensionParam>
inline void
CollisionBox<ScalarParam, dimensionParam>::StartPiston(Scalar vel)
{
    pistonVelocity = vel * pistonDir;
}
template <class ScalarParam, int dimensionParam>
inline
typename CollisionBox<ScalarParam, dimensionParam>::Scalar
CollisionBox<ScalarParam, dimensionParam>::GetEnergy() const
{
    Scalar Energy = 0;

    for(auto particle : particles)
    {
        Scalar vel = particle.getVelocity().mag();
        Energy += vel * vel;
    }

    return Energy / 2;
}

template <class ScalarParam, int dimensionParam>
typename CollisionBox<ScalarParam, dimensionParam>::Scalar
CollisionBox<ScalarParam, dimensionParam>::GetFreePath() const
{
    return free_path;
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::clearTrack()
{
    track.clear();
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::updateTrack(Particle * particle)
{
    if (particle && particle == getTrackedParticle())
    {
        track.push_back(particle->getPosition());
    }
}

template <class ScalarParam, int dimensionParam>
inline
void
CollisionBox<ScalarParam, dimensionParam>::updateFreePath(Particle * particle, Scalar delta_path)
{
    if (particle && particle == getTrackedParticle())
    {
        //free_path = current_path;
        free_path = (free_path * num_of_collisions + current_path + delta_path) / (num_of_collisions + 1);
        num_of_collisions++;
        current_path = 0;
    }
}

template <class ScalarParam, int dimensionParam>
inline
typename CollisionBox<ScalarParam, dimensionParam>::Particle *
CollisionBox<ScalarParam, dimensionParam>::getTrackedParticle()
{
    if (!particles.empty())
    {
        return &(*particles.begin());
    }

    return NULL;
}

template <class ScalarParam, int dimensionParam>
inline
typename CollisionBox<ScalarParam, dimensionParam>::Scalar
CollisionBox<ScalarParam, dimensionParam>::GetAverageVelocity() const
{
    Scalar v = 0;

    for(auto particle: particles)
    {
        v += particle.velocity.mag();
    }

    v /= particles.size();

    return v;
}
