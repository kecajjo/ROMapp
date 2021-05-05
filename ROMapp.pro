QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport bluetooth

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communication.cpp \
    datafordatatable.cpp \
    dataforplot.cpp \
    datatable.cpp \
    datatransform.cpp \
    graphs.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    programlogiceventloop.cpp \
    qcustomplot.cpp

HEADERS += \
    communication.h \
    datafordatatable.h \
    dataforplot.h \
    datafromstm.h \
    datatable.h \
    datatransform.h \
    graphs.h \
    mainwindow.h \
    map.h \
    programlogiceventloop.h \
    qcustomplot.h

FORMS += \
    datatable.ui \
    graphs.ui \
    mainwindow.ui \
    map.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
