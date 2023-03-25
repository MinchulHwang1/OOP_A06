//driver.cpp

/* -- this is a FILEHEADER COMMENT --
	NAME	: driver
	PURPOSE : This program takes the contents entered into the object and initializes it with Constructor.
			  The constructor has confirmed that it can be overloaded, and outputs accordingly.
			  User can get information from printed screen, and set the preset in radio.
			  If the input data member is out of the specified range, an appropriate value is output,
			  and the memory allocated by the destructor is deleted when the file loading is finished.
*/
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include <iostream>
#include "PioneerAM.h"
#include "PioneerWorld.h"

//template <class T>

PioneerCarRadio *createRadio(char *arg);
int main(int argc, char *argv[]) {

	char* arg = NULL;
	arg = argv[1];
	int num = kZeroValue;
	char getChar;
	PioneerCarRadio *pRadio = NULL;
	
	try {
		if (strcmp(arg, "-car") == 0 || strcmp(arg, "-am") == 0 || strcmp(arg, "-world") == 0) {
			pRadio = createRadio(arg);
		}
		else
			throw 1;
	}
	catch (int num) {
		printf("Error\n");
	}
	while (1) {
		pRadio->CurrentStatus();
		getChar = getch();
		pRadio->ProcessUserKeyStroke(getChar);
	}

	/*
	// 클래스 이름저장 완료햇고, 그걸로 접근해서 polymorphism 사용해서 해보자
	// Polymorphism 다시 만들기
	// 
	// World일때 저장하고 버튼누르면 그 주파수로 안감 <-- 이거부터 해결해야함
	// FM일때 world, AM의 출력에서 FM은 없다
	if (pRadio != NULL) {
		while (kBreakValue) {

			
			pRadio->CurrentStatus();
			getChar = getch();
			
			if (getChar == 'c') {
				strncpy(arg, "-car",sizeof("-car"));
				pRadio = createRadio(arg);
			}
			else if (getChar == 'a') {
				strncpy(arg, "-am", sizeof("-am"));
				pRadio = createRadio(arg);
			}
			else if (getChar == 'w') {
				strncpy(arg, "-world", sizeof("-world"));
				pRadio = createRadio(arg);
			}
			else if (getChar == 'x') {
				pRadio->SetExit(true);
			}
			else {

				pRadio->ProcessUserKeyStroke(getChar);
			}

			if (pRadio->GetExit() == true)
				break;
		}
	}
	
	delete pRadio;
	*/
	return 0;
}

PioneerCarRadio* createRadio(char* arg) {
	// 여기서 if 문 try catch throw 로 바꾸기

   /*
   try {
	   if (strcmp(arg, "-car") == 0 || strcmp(arg, "c") == 0 || strcmp(arg, "C") == 0) {
		   throw 1;
	   }
	   else if (strcmp(arg, "-am") == 0 || strcmp(arg, "a") == 0 || strcmp(arg, "A") == 0) {
		   throw 2;
	   }
	   else if (strcmp(arg, "-world") == 0 || strcmp(arg, "w") == 0 || strcmp(arg, "W") == 0) {
		   throw 3;
	   }
   }
   catch (int num) {
	   if (num == 1) {
		   PioneerCarRadio* pValue = new PioneerCarRadio(false);
		   return pValue;
	   }
	   else if (num == 2) {
		   PioneerAM* pValue = new PioneerAM(false);
		   return pValue;
	   }
	   else if (num == 3) {
		   PioneerWorld* pValue = new PioneerWorld(false);
		   return pValue;
	   }
   }*/


	// 성공하면 바꿔야함

	if (strcmp(arg, "-car") == 0) {
		PioneerCarRadio* pValue = NULL;
		try {
			 pValue = new PioneerCarRadio(false);
		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return 0;
		}
		return pValue;
	}
	else if (strcmp(arg, "-am") == 0) {
		PioneerAM* pValue = NULL;
		try {
			pValue = new PioneerAM(false);
		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return 0;
		}
		return pValue;
	}
	else if (strcmp(arg, "-world") == 0 ) {
		PioneerWorld* pValue = NULL;
		try {
			pValue = new PioneerWorld(false);
		}
		catch (bad_alloc& e) {
			printf("Radio is not made\n");
			return 0;
		}
		return pValue;
	}


}