QT       += core gui qml quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filedialog2.cpp \
    filepathsedit.cpp \
    filepathsource.cpp \
    filesdialog3.cpp \
    filesdialog4.cpp \
    main.cpp \
    filesdialog1.cpp

HEADERS += \
    filedialog2.h \
    filepathsedit.h \
    filepathsource.h \
    filesdialog1.h \
    filesdialog3.h \
    filesdialog4.h

FORMS += \
    filedialog2.ui \
    filepathsource.ui \
    filesdialog1.ui \
    filesdialog3.ui \
    filesdialog4.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qmlfiledialog.qml

RESOURCES += \
    qml.qrc
