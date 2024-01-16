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
    models/f-16.mtl \
    shaders/basicLlumShader.frag \
    shaders/basicLlumShader.vert
