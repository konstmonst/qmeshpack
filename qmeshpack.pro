TEMPLATE = app
QT += opengl
CONFIG += thread qt exceptions
QMAKE_CXXFLAGS += -march=core2 -fopenmp
QMAKE_LFLAGS += -fopenmp
SOURCES += main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    Exception.cpp \
    util.cpp \
    image.cpp \
    meshlistview.cpp \
    vectorinputdialog.cpp \
    MeshFilesModel.cpp \
    MeshPacker.cpp \
    GLView.cpp \
    Node.cpp \
    ModelView.cpp
HEADERS += mainwindow.h \
    mesh.h \
    Exception.h \
    util.h \
    image.h \
    meshlistview.h \
    vectorinputdialog.h \
    MeshFilesModel.h \
    MeshPacker.h \
    GLView.h \
    Node.h \
    ModelView.h \
    config.h
RESOURCES += \
    icons.qrc

OTHER_FILES += \
    README.txt