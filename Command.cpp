/**
 * Author: Jeffrey Wang
 * Date: October 5 2021
 * 
 * This file contains functions relating to executing a user command and retrieving the results.
 */

#include <string>
#include <boost/process.hpp>
#include <iostream>
#include "Command.h"

using namespace boost::process;
using namespace std;

/**
 * Function: Command()
 * Description: contructor for the Command class that initializes 3 variables
 * Parameters: String command - command to be executed
 * Returns: void
 */
Command::Command(string command){ //constructor 
    userCommand = command;
	returnCode = 0;
	result = "";
}

/**
 * Function: execute()
 * Description: executes the inputted command and stores the results. Catches process_error.
 * Parameters: none
 * Returns: void
 */
void Command::execute(){
	try{
		ipstream pipe_stream;
		child c(userCommand, (std_out & std_err) > pipe_stream);//stores output and error in stream
		string line;
		while (pipe_stream && getline(pipe_stream,line) && !line.empty())	
			result = result + line + "\n"; //store the output in result string

		c.wait();	
    }
    catch (exception& e){
		returnCode = -1;
		result = "Invalid Command Error\n";
        }
	}

/**
 * Function: getuserCommand()
 * Description: returns the inputted command string
 * Parameters: none
 * Returns: string userCommand
 */
string Command::getuserCommand(){
    return userCommand;
}

/**
 * Function: getResult()
 * Description: executes the inputted command and stores the results. Catches process_error.
 * Parameters: none
 * Returns: void
 */
string Command::getResult(){
    return result;
}

/**
 * Function: getreturnCode()
 * Description: returns the exit code
 * Parameters: none
 * Returns: int returnCode
 */
int Command::getreturnCode(){
	return returnCode;
}

/**
 * Function: setUserInput()
 * Description: sets the user command
 * Parameters: string command - new command
 * Returns: void
 */
void Command::setUserInput(string command){
	userCommand = command;
}

/**
 * Deconstructor
 */
Command::~Command(){//Deconstructor
}





/*
test main
int main(){
	Command testCommandObject("ls -l");
	testCommandObject.execute();
	//testCommandObject.setUserInput("date");
	//testCommandObject.execute();
	cout << testCommandObject.getResult() <<"above is the result"<< endl;
    cout << testCommandObject.getreturnCode() <<endl;
    cout << testCommandObject.getuserCommand() <<endl;

	return 0;
}
*/

