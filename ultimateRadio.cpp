//ultimateRadio.cpp

/* -- this is a FILEHEADER COMMENT --
	NAME	: ultimatiRadio.cpp
	PURPOSE : This program takes the contents entered into the object and initializes it with Constructor.
			  The constructor has confirmed that it can be overloaded, and outputs accordingly.
			  User can get information from printed screen, and set the preset in radio.
			  If the input data member is out of the specified range, an appropriate value is output,
			  and the memory allocated by the destructor is deleted when the file loading is finished.
			  If user want to change radio mode, it can be changed.
			  when user what to exit program, all object is distoryed
	Function : in this file, there is one function called createRadio.
				createRadio			PioneerCarRadio*		to create new object followed by command line argument.
*/
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include <iostream>
#include "PioneerAM.h"
#include "PioneerWorld.h"
#include <new>

PioneerCarRadio *createRadio(string arg);

int main(int argc, char* argv[]) {

	string arg;
	arg = argv[1];
	int num = kZeroValue;
	char getChar;
	PioneerCarRadio* pRadio = NULL;			// Declare pointer of Radio.

	try {			//Get string from command line
		pRadio = createRadio(arg);
		while (kBreakValue) {
			pRadio->CurrentStatus();

			getChar = getch();
			if (getChar == 'x') {
				delete pRadio;
				break;
			}
			else
				pRadio->ProcessUserKeyStroke(getChar);
		}
	}
	catch (int num) {
		printf("Error in command line.\n");
	}
	
	while (kBreakValue) {
		printf("\n");
		getChar = getch();
		if (getChar == 'c') {
			arg = "-car";
			pRadio = createRadio(arg);
			while (kBreakValue) {
				pRadio->CurrentStatus();
				getChar = getch();
				if (getChar == 'x') {
					break;
				}
				else
					pRadio->ProcessUserKeyStroke(getChar);
			}
			delete pRadio;
		}
		else if (getChar == 'a') {
			arg = "-am";
			pRadio = createRadio(arg);
			while (kBreakValue) {
				printf("\n");
				pRadio->CurrentStatus();
				getChar = getch();
				if (getChar == 'x') {
					break;
				}
				else
					pRadio->ProcessUserKeyStroke(getChar);
			}
			delete pRadio;
		}
		else if (getChar == 'w') {
			arg = "-world";
			pRadio = createRadio(arg);
			while (kBreakValue) {
				pRadio->CurrentStatus();
				getChar = getch();
				if (getChar == 'x') {
					break;
				}
				else
					pRadio->ProcessUserKeyStroke(getChar);
			}
			delete pRadio;
		}
		else if (getChar == 'x') {
			break;
		}
	}
	return 0;
}

/*  -- function Header Comment
	Name	:createRadio
	Purpose : to create new object followed by command line argument.
	Inputs	: arg			char*		the string from argument in command line
	Outputs	: the message if there is no memory or fail to create object in new memory
	Returns	: pValue		object		the object is created under meaning of command line argument
*/
PioneerCarRadio* createRadio(string arg) {

	if (arg == "-car") {
		PioneerCarRadio* pValue = NULL;
		try {
			pValue = new PioneerCarRadio(false);
			pValue->SetClassName((char*)"");
			return pValue;
		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return kZeroValue;
		}
	}
	else if (arg == "-am") {
		PioneerAM* pValue = NULL;
		try {
			pValue = new PioneerAM(false);
			pValue->SetClassName((char*)"-AM");
			return pValue;

		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return kZeroValue;
		}
	}
	else if (arg == "-world") {
		PioneerWorld* pValue = NULL;
		try {
			pValue = new PioneerWorld(false);
			pValue->SetClassName((char*)"-WRLD");
			return pValue;
		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return kZeroValue;
		}
	}
	else
		throw 1;
}