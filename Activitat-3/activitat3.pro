TEMPLATE    = app
QT         += opengl \
    widgets

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h \
    customradiobutton.h

SOURCES += main.cpp  MyForm.cpp \
        MyGLWidget.cpp ./Model/model.cpp \
        customradiobutton.cpp

DISTFILES += \
    models/MINITUNNEL.mtl \
    models/escena_reduida.mtl \
    models/escena_reduida.obj \
    models/espelma.mtl \
    models/espelma.obj \
    models/f-16.mtl \
    models/finestres.mtl \
    models/finestres.obj \
    models/snitch.mtl \
    models/snitch.obj \
    shaders/basicLlumShader.frag \
    shaders/basicLlumShader.vert
