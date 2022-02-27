/**
 * author: jeffrey wang
 * date: october 5 2021
 * 
 * main function to run the program
 */

#include "mainwindow.h"
#include <QApplication>
 
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  //added by me
  //qwidget functions
  mainWindow.resize(400,654);

  return app.exec();
}
