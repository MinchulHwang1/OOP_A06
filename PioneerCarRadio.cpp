// PioneerCarRadio.cpp
#include"PioneerCarRadio.h"


/*  -- Method Header Comment
	Name	: PioneerCarRadio -- CONSTRUCTOR
	Purpose : To instantiate a new PioneerCarRadio object - given a set of attribute values, and inherited from AmFmRadio class
	Inputs	: on		bool		Bool sttus of power
	Outputs	: NONE
	Returns	: Nothing
*/
PioneerCarRadio::PioneerCarRadio(bool on) : AmFmRadio(false) {
	getChar = 'x';
	
	this->on = on;
	exit = false;
	volume = kZeroValue;
	current_station = kMinAMFreqs;
	strncpy(band, "AM", sizeof("AM"));
	displayOutput = false;
	strncpy(className, "-car", sizeof("-car"));
	strncpy(classNameCopy, "", sizeof(""));
}

/*  -- Method Header Comment
	Name	: PioneerCarRadio -- DESTRUCTOR
	Purpose : To destroy the PioneerCarRadio object - free up the memory associated with the object
	Inputs	: NONE
	Outputs	: Outputs a final message from the object before being destroyed
	Returns	: Nothing
*/
PioneerCarRadio::~PioneerCarRadio() {
	printf("PioneerCarRadio is destroyed\n");
}


/*  -- Method Header Comment
	Name	: ShowCurrentSetting
	Purpose : it prints all of information(band, volume, frequency, and preset). it is overriding method in AmFmRadio
	Inputs	: NONE
	Outputs	: Prints all of information(band, volume, frequency, and preset (both of AM and FM)
	Returns	: Nothing
*/
void PioneerCarRadio::ShowCurrentSettings(void) {
	printf("Volume: %d\n", volume);

	if (strcmp(GetBandName(), "AM") == 0) {
		printf("Current Station: %d %s\n", (int)GetCurrent_Station(), GetBandName());
	}
	else {
		printf("Current Station: %.1f %s\n", GetCurrent_Station(), GetBandName());
	}

	printf("AM Buttons:\n");
	for (int i = kZeroValue; i < kNumberOfArray - 1; ++i) {
		printf("%d) %6d,  ", i + 1, GetButton(i).AMFreqs);
	}
	printf("%d) %6d", kNumberOfArray, GetButton(kNumberOfArray - 1).AMFreqs);
	printf("\nFM Buttons:\n");
	for (int j = kZeroValue; j < kNumberOfArray - 1; ++j) {
		printf("%d) %6.1f,  ", j + 1, GetButton(j).FMFreqs);
	}
	printf("%d) %6.1f", kNumberOfArray, GetButton(kNumberOfArray - 1).FMFreqs);
}


/*  -- Method Header Comment
	Name	: CurrentStatus
	Purpose : it prints current radio's status, and it can get character from user to set key stroke
	Inputs	: NONE
	Outputs	: Prints radio's power status/
	Returns	: Nothing
*/
void PioneerCarRadio::CurrentStatus(void) {
	SetDisplayOutput(false);
	if (on == false) {
		printf("Pioneer XS440\n");
		printf("Radio is off\n\n");
	}
	else {
		printf("Pioneer XS440\n");
		printf("Radio is on\n");
		ShowCurrentSettings();
		printf("\n\n");
	}
}

/*  -- Method Header Comment
	Name	: ProcessUserKeyStroke
	Purpose : it divides key stroke gotten from user.
	Inputs	: getChar		char		the character from user
	Outputs	: Nothing
	Returns	: Nothing
*/
void PioneerCarRadio::ProcessUserKeyStroke(char getChar) {
	switch (getChar) {
	case 'x':
		exit = true;
		break;

	case 'X':
		exit = true;
		break;

	case 'o':

		PowerToggle();
		on = IsRadioOn();

		break;

	case '+':
		if (on == true) {
			volume++;
			if (volume > kMaxVolume) {
				volume = kMaxVolume;
			}
			SetVolume(volume);
		}
		else
			SetVolume(volume);
		break;

	case '_':
		if (on == true) {
			volume--;
			if (volume < kMinVolume) {
				volume = kMinVolume;
			}
			SetVolume(volume);
		}
		else
			SetVolume(volume);
		break;

	case '=':
		if (on == true) {
			ScanUp();
		}
		break;

	case '-':
		if (on == true) {
			ScanDown();
		}
		break;

	case 'b':
		if (on == true) 
			ToggleBand();
		break;
		

	case '1':
		if (on == true) {
			SelectPresetButton(kZeroIndex);
		}
		break;

	case '2':
		if (on == true) {
			SelectPresetButton(kOneIndex);
		}
		break;

	case '3':
		if (on == true) {
			SelectPresetButton(kTwoIndex);
		}
		break;

	case '4':
		if (on == true) {
			SelectPresetButton(kThreeIndex);
		}
		break;

	case '5':
		if (on == true) {
			SelectPresetButton(kFourIndex);
		}
		break;

	case '!':
		if (on == true) {
			SetPresetButton(kZeroIndex);
		}
		break;

	case '@':
		if (on == true) {
			SetPresetButton(kOneIndex);
		}
		break;

	case '#':
		if (on == true) {
			SetPresetButton(kTwoIndex);
		}
		break;

	case '$':
		if (on == true) {
			SetPresetButton(kThreeIndex);
		}
		break;

	case '%':
		if (on == true) {
			SetPresetButton(kFourIndex);
		}
		break;


	default:
		break;
	}
}


/*  -- Method Header Comment
	Name	: GetChar
	Purpose : Get characterfrom user.
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: getChar		char		a character from user
*/
char PioneerCarRadio::GetChar(void) {
	getChar = getch();
	return getChar;
}

/*  -- Method Header Comment
	Name	: GetCurrent_Station
	Purpose : Get current station of radio from it's parent's class
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: current_station		float		current station frequency
*/
float PioneerCarRadio::GetCurrent_Station(void) {
	current_station = AmFmRadio::GetCurrent_Station();
	return current_station;
}


/*  -- Method Header Comment
	Name	: GetBandName
	Purpose : Get band name from parent's class
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: band		char*		a pointer of band name
*/
char* PioneerCarRadio::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	return band;
}

bool PioneerCarRadio::GetOn(void) {
	return on;
}

/*  -- Method Header Comment
	Name	: GetExit
	Purpose : Get bool value which can finish it.
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: exit		bool		a bool value which can continue or not
*/
bool PioneerCarRadio::GetExit(void) {
	return exit;
}

void PioneerCarRadio::SetExit(bool exit) {
	this->exit = exit;
}
/*  -- Method Header Comment
	Name	: SetDisplayOutput
	Purpose : Set bool value displayOutpur which can control AmFmRadio class
	Inputs	: displayOutput		bool		the value of bool to control AmFmRadio class
	Outputs	: Nothing
	Returns	: nothing
*/
void PioneerCarRadio::SetDisplayOutput(bool displayOutput) {
	AmFmRadio::SetDisplayOutput(displayOutput);
}

char* PioneerCarRadio::GetClassName(void) {
	memcpy(classNameCopy, className, sizeof(className));
	return classNameCopy;

}
void PioneerCarRadio::SetClassName(char* className) {
	strncpy(this->className, className, sizeof(className));
}