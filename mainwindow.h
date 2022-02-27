/**
 * Author: Jeffrey Wang
 * Date: October 5 2021
 * 
 * This is the header file for mainwindow.cpp and contains variable and function declarations
 * used for the creation of a GUI.
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <vector>
#include "Command.h"


namespace Ui {
  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
    private slots:
        void handleButton();
        void displayItemClicked();
        void displayResults(Command);
    private:
        QPushButton *m_button;
        QLineEdit *m_textbox;
        QTextEdit *m_textdisplay;
        QLabel *outputLabel;
        QLabel *statusLabel;
        QLabel *historyLabel;
        QTextEdit *m_historybox;
        QListWidget *historyList;
        vector<Command> savedCommands;
        int counter;
};
#endif // MAINWINDOW_H
