QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logic.cpp \
    main.cpp \
    mainwindow.cpp \
    gnss/gnss.cpp \
    connection/settings.cpp \
    connection/greyBox.cpp \
    UDS/protocol_uds.cpp \
    UDS/executer_uds.cpp \
    UDS/assembling_answer.cpp \
    connection/connection.cpp \
    UDS/dtc_diagnostictroublecodes.cpp \
    log_file.cpp

HEADERS += \
    logic.h \
    mainwindow.h \
    definitions.h \
    gnss/gnss.h \
    connection/settings.h \
    connection/greyBox.h \
    UDS/protocol_uds.h \
    UDS/executer_uds.h \
    UDS/assembling_answer.h \
    connection/connection.h \
    UDS/dtc_diagnostictroublecodes.h \
    log_file.h

FORMS += \
    mainwindow.ui

debug {
    CONFIG+=sanitizer
    CONFIG+=sanitize_address
    CONFIG+=sanitize_thread
    CONFIG+=sanitize_fuzzer_no_link
    CONFIG+=sanitize_undefined
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
