/**
 * Author: Jeffrey Wang
 * Date: October 5 2021
 * 
 * This file creates the main window and properly displays everything that is executed when the execute button is pressed.
 */

#include "mainwindow.h"

/**
 * Function: MainWindow()
 * Description: contructor for the mainwindow class that sets up the GUI.
 * Parameters: QWidget
 * Returns: void
 */
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  counter = 0; //counter counts the amount of times execute was pressed
  // Create the button, make "this" the parent
  m_button = new QPushButton("Execute", this);
  m_button->setGeometry(QRect(QPoint(250, 50), QSize(100, 50)));
 
  // Connect button signal to appropriate slot
  connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);

  // create an input box
  m_textbox = new QLineEdit("",this);
  m_textbox ->setGeometry(QRect(QPoint(50,50), QSize(200,50)));
  m_textbox ->setPlaceholderText("Input Command Here");
  m_textbox ->setFocus();
    
  //create a label "output"
  outputLabel = new QLabel("Output:",this);
  outputLabel ->setGeometry(QRect(55,105,100,30));
    
  //create a textbox to display results
  m_textdisplay = new QTextEdit("", this);
  m_textdisplay -> setGeometry(QRect(QPoint(50,140), QSize(300,200)));
  m_textdisplay ->setReadOnly(true);
  m_textdisplay ->setPlaceholderText("Output will appear here");
    
  //create a label "Exit Status"
  statusLabel = new QLabel("Exit Status: ",this);
  statusLabel ->setGeometry(QRect(55, 340, 100, 30));
    
  //create a label "History"
  historyLabel = new QLabel("--------------------\nHistory: (click on entry to view past results)",this);
  historyLabel ->setGeometry(QRect(55,360, 400,30)); 
    
  //create a list widget to store and display past commands
  historyList = new QListWidget(this);
  historyList ->setGeometry(QRect(QPoint(50,405), QSize(300,200)));
  connect(historyList, &QListWidget::itemClicked, this, &MainWindow::displayItemClicked);
   

}
 
/**
 * Function: handleButton()
 * Description: This function handles the execute button press
 * Parameters: none
 * Returns: void
 */
void MainWindow::handleButton()
{
    //get input text and convert it to std::string to use with Command()
    QString text = m_textbox ->text();
    std::string textString = text.toStdString();
    Command newCommand(textString);
    newCommand.execute();

    //add objects into a vector to save them for use with the history list
    savedCommands.push_back(newCommand);
    displayResults(newCommand);
    
    //get the return code and concatenate it with a string to display
    int status = newCommand.getreturnCode();
    std::string statusString = std::to_string(status);
    counter +=1;
    std::string counterString = std::to_string(counter);
    std::string listString = counterString + ". " +textString + " (" + statusString +")";
    

    //convert listString to const char* and add item to historylist
    const char * charItem = listString.c_str();
    new QListWidgetItem(tr(charItem), historyList);

    //clear input textbox and refocus cursor on the text box
    m_textbox ->setText("");
    m_textbox ->setFocus();

}

/**
 * Function: displayItemClicked()
 * Description: redisplays past result if clicked on from historyList
 * Parameters: none
 * Returns: void
 */
void MainWindow::displayItemClicked(){
    int row = historyList->currentRow();
    QString qrow = QString::number(row);
    
    Command selectedCommand = savedCommands[row];
    displayResults(selectedCommand);
     
}

/**
 * Function: displayResults()
 * Description: this function displays the results of execute
 * Parameters: Command newCommand - command object that was executed
 * Returns: void
 */
void MainWindow::displayResults(Command newCommand){

    std::string result = newCommand.getResult();
    QString resultQ = QString::fromStdString(result);
    m_textdisplay -> setText(resultQ);

    int status = newCommand.getreturnCode();
    std::string statusString = std::to_string(status);
    std::string statusOutputString = "Exit Status: "+statusString;
    QString statusQ = QString::fromStdString(statusOutputString);
    statusLabel ->setText(statusQ);

}
