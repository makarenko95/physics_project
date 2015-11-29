#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T13:48:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = phys2
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
    src/Geometry/Box.cpp \
    src/Geometry/ComponentArray.cpp \
    src/Geometry/HVector.cpp \
    src/Geometry/Matrix.cpp \
    src/Geometry/Point.cpp \
    src/Geometry/Rotation.cpp \
    src/Geometry/Vector.cpp \
    src/Math/Constants.cpp \
    src/Math/Random.cpp \
    src/Misc/Timer.cpp \
    src/CollisionBox.cpp \
    src/Models/billiardmodel.cpp \
    src/Views/billiardview.cpp \
    src/Views/qtbilliardview.cpp \
    src/Control/billiardcontrol.cpp \
    src/Control/qtbilliardcontrol.cpp \
    src/Views/qtplot.cpp \
    src/qcustomplot.cpp \
    src/Views/qtaveragevelocityplot.cpp \
    src/Views/qtvelocityhistogram.cpp \
    src/Views/qthistogram.cpp \
    src/Views/qtdirectionhistogram.cpp \
    src/Views/qtworkplot.cpp

HEADERS  += application.h \
    src/Geometry/Box.h \
    src/Geometry/ComponentArray.h \
    src/Geometry/HitResult.h \
    src/Geometry/HVector.h \
    src/Geometry/Matrix.h \
    src/Geometry/MatrixHelperFunctions.h \
    src/Geometry/Point.h \
    src/Geometry/Ray.h \
    src/Geometry/Rotation.h \
    src/Geometry/SolidHitResult.h \
    src/Geometry/Vector.h \
    src/Math/Constants.h \
    src/Math/Math.h \
    src/Math/Random.h \
    src/Misc/Array.h \
    src/Misc/ArrayIndex.h \
    src/Misc/ChunkedArray.h \
    src/Misc/PriorityHeap.h \
    src/Misc/Timer.h \
    src/Misc/Utility.h \
    src/CollisionBox.h \
    src/Models/billiardmodel.h \
    src/Views/billiardview.h \
    src/Views/qtbilliardview.h \
    src/Control/billiardcontrol.h \
    src/Control/qtbilliardcontrol.h \
    src/Views/qtplot.h \
    src/qcustomplot.h \
    src/Views/qtaveragevelocityplot.h \
    src/Views/qtvelocityhistogram.h \
    src/Views/qthistogram.h \
    src/Views/qtdirectionhistogram.h \
    src/Views/qtworkplot.h

INCLUDEPATH += src

CONFIG += c++11


