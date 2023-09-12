QT       += core gui #serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UDS/uds.cpp \
    adapter/systec/save_array/save_array.cpp \
    adapter/systec/save_transcriotion/save_transcriotion.cpp \
    adapter/systec/systectf.cpp \
    config.cpp \
    connection.cpp \
    adapter/systec.cpp \
    logic.cpp \
    main.cpp \
    mainwindow.cpp \
    utils.cpp

HEADERS += \
    UDS/uds.h \
    adapter/systec/i_adapter.h \
    adapter/systec/save_array/save_array.h \
    adapter/systec/save_transcriotion/save_transcriotion.h \
    adapter/systec/systectf.h \
    connection.h \
    adapter/systec.h \
    config.h \
    logic.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


INCLUDEPATH += adapter/systec/save_array/ \
                adapter/systec/systecLib/ \
                adapter/systec/save_transcriotion/ \
                adapter/systec/
LIBS += $$PWD/adapter/systec/systecLib/USBCAN64.lib


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
