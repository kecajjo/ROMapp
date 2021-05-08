QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport bluetooth

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/btcommunication.cpp \
    src/communication.cpp \
    src/datafordatatable.cpp \
    src/dataforplot.cpp \
    src/datatable.cpp \
    src/datatransform.cpp \
    src/graphs.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/map.cpp \
    src/qcustomplot.cpp \
    src/worker.cpp

HEADERS += \
    inc/btcommunication.h \
    inc/communication.h \
    inc/datafordatatable.h \
    inc/dataforplot.h \
    inc/datafromstm.h \
    inc/datatable.h \
    inc/datatransform.h \
    inc/graphs.h \
    inc/mainwindow.h \
    inc/map.h \
    inc/qcustomplot.h \
    inc/worker.h

FORMS += \
    forms/datatable.ui \
    forms/graphs.ui \
    forms/mainwindow.ui \
    forms/map.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
