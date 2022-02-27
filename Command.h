/**
 * author: jeffrey wang
 * date: october 5 2021
 * 
 * header file as an interface for the Command class
 */
#ifndef COMMAND_H
#define COMMAND_H

using namespace std;

class Command{
	private:
		string userCommand;
		string result;
		int returnCode;
	
	public:
		Command(string command);

		void execute();
		string getuserCommand();
		string getResult();
		int getreturnCode();
		void setUserInput(string command);

		~Command();
};



#endif
