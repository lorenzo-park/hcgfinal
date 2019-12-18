HEADERS       = glwidget.h \
                BasicMaterial.h \
                CircuitBase.h \
                cursor.h \
                layertoggle.h \
                materialchoose.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                BasicMaterial.cpp \
                CircuitBase.cpp \
                cursor.cpp \
                layertoggle.cpp \
                main.cpp \
                materialchoose.cpp \
                window.cpp \
                mainwindow.cpp
QT           += widgets

LIBS += -lopengl32

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target

FORMS += \
    layertoggle.ui \
    materialchoose.ui
