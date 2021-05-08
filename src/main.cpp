#include "mainwindow.h"
#include "communication.h"
#include "worker.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]){

    Communication Comm;
    Worker *Wrk = new Worker;
    Wrk->SetCommunication(&Comm);
    QApplication App(argc, argv);
    MainWindow *Window = new MainWindow();
    Window->SetThreadCommunication(&Comm);
    // thread does logic part of the program and communicates with microcontroller
    QThread *LogicThread = new QThread;
    Wrk->moveToThread(LogicThread);
    Wrk->SendStartSig();
    QAbstractEventDispatcher *Dispatch = LogicThread->eventDispatcher();
    qDebug() << Dispatch;
    LogicThread->start();
    Dispatch = LogicThread->eventDispatcher();
    qDebug() << Dispatch;
    Window->show();
    // value to be returned
    int RetVal = App.exec();

    //LogicThread->wait();

    return RetVal;
}
