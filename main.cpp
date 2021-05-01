#include "mainwindow.h"
#include "communication.h"
#include "programlogiceventloop.h"

#include <QApplication>
#include <thread>

int main(int argc, char *argv[]){

    Communication Comm;

    QApplication App(argc, argv);
    MainWindow *Window = new MainWindow();
    Window->SetThreadCommunication(&Comm);
    Window->show();

    // thread does logic part of the program and communicates with microcontroller
    std::thread MyThread(ProgramLogicEventLoop, &Comm);

    // value to be returned
    int RetVal = App.exec();

    MyThread.join();

    return RetVal;
}
