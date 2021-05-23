#include "mainwindow.h"
#include "communication.h"
#include "worker.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]){

    Communication Comm;
    Worker Wrk;
    Wrk.SetCommunication(&Comm);
    QApplication App(argc, argv);
    MainWindow *Window = new MainWindow();
    Window->SetThreadCommunication(&Comm);
    // thread does logic part of the program and communicates with microcontroller
    QThread *WorkerThread = new QThread;
    Wrk.moveToThread(WorkerThread);
    Wrk.SendStartSig();
    WorkerThread->start();
    Window->show();
    // value to be returned
    int RetVal = App.exec();
    WorkerThread->wait();
    delete Window;
    delete WorkerThread;

    return RetVal;
}
