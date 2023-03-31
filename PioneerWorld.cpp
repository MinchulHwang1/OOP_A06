// PioneerWorld.cpp
#include "PioneerWorld.h"

/*  -- Method Header Comment
	Name	: PioneerWorld-- CONSTRUCTOR
	Purpose : To instantiate a new PioneerWorld object - given a set of attribute values, and inherited from AmFmRadio class, PioneerCarRadio class, and PioneerAM class
	Inputs	: on		bool		Bool status of power
	Outputs	: NONE
	Returns	: Nothing
*/
PioneerWorld::PioneerWorld(bool on) : PioneerAM(false) {
	getChar = 'x';
	this->on = on;
	exit = false;
	volume = kZeroValue;
	current_station = kWorldMinRange;
	strncpy(band, "AM", sizeof("AM"));
}

/*  -- Method Header Comment
	Name	: PioneerWorld -- DESTRUCTOR
	Purpose : To destroy the PioneerWorld object - free up the memory associated with the object
	Inputs	: NONE
	Outputs	: Outputs a final message from the object before being destroyed
	Returns	: Nothing
*/
PioneerWorld::~PioneerWorld() {
	// Distructor
}

/*  -- Method Header Comment
	Name	: CurrentStatus
	Purpose : it prints current radio's status, and it can get character from user to set key stroke
	Inputs	: NONE
	Outputs	: Prints radio's power status
	Returns	: Nothing
*/
void PioneerWorld::CurrentStatus(void) {
	on = GetOn();

	// Set initialization of frequency
	if (PioneerCarRadio::GetCurrent_Station() == kMinAMFreqs) {
		SetCurrentStation(current_station);
		for (int i = kZeroValue; i < kNumberOfArray; i++) {
			SetPresetButton(i);
		}	
	}

	if (on == false) {
		printf("Pioneer XS440-WRLD\n");
		printf("Radio is off\n\n");
	}
	else {
		
		printf("Pioneer XS440-WRLD\n");
		printf("Radio is on\n");
		ShowCurrentSettings();
		printf("\n\n");
	}
}

/*  -- Method Header Comment
	Name	: ShowCurrentSetting
	Purpose : it prints all of information(band, volume, frequency, and preset). it is overriding method in AmFmRadio class, PioneerCarRadio class, and PioneerAM class
	Inputs	: NONE
	Outputs	: Prints all of information(band, volume, frequency, and preset (AM)
	Returns	: Nothing
*/
void PioneerWorld::ShowCurrentSettings(void) {
	printf("Volume: %d\n", GetVolume());
	if (strcmp(GetBandName(), "AM") == 0) {
		printf("Current Station: %d %s\n", (int)GetCurrent_Station(), GetBandName());
	}
	
	printf("AM Buttons:\n");
	for (int i = kZeroValue; i < kNumberOfArray - 1; ++i) {
		printf("%d) %6d,  ", i + 1, GetButton(i).AMFreqs);
	}
	printf("%d) %6d", kNumberOfArray, GetButton(kNumberOfArray - 1).AMFreqs);
}

/*  -- Method Header Comment
	Name	: ProcessUserKeyStroke
	Purpose : it divides key stroke gotten from user. Overriding from parent class
	Inputs	: getChar		char		the character from user
	Outputs	: Nothing
	Returns	: Nothing
*/
void PioneerWorld::ProcessUserKeyStroke(char getChar) {
	if (getChar == '=') {
		if (on == true) {
			ScanUp();
		}
	}
	else if (getChar == '-') {
		if (on == true) {
			ScanDown();
		}
	}
	else
		PioneerCarRadio::ProcessUserKeyStroke(getChar);
}

/*  -- Method Header Comment
	Name	: ScanUp
	Purpose : current frequeency is going up with in a range as each amount of frequency in AM band(9), this method is overriding AmFmRadio class
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void PioneerWorld::ScanUp(void) {
	if (current_station == kWorldMaxRange) {
		current_station = kWorldMinRange;
	}
	else {
		current_station = current_station + kWorldFreqRange;	
	}
	SetCurrentStation(current_station);
}

/*  -- Method Header Comment
	Name	: ScanDown
	Purpose : current frequeency is going down with in a range as each amount of frequency in AM band(9), this method is overriding AmFmRadio class
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void PioneerWorld::ScanDown(void) {
	if (current_station == kWorldMinRange) {
		current_station = kWorldMaxRange;
	}
	else {
		current_station = current_station - kWorldFreqRange;
	}
	SetCurrentStation(current_station);
}

/*  -- Method Header Comment
	Name	: GetVolume
	Purpose : getting volume and return current volume, it get volume from parent class
	Inputs	: NONE
	Outputs	: NONE
	Returns	: volume		int			includes current volume
*/
int PioneerWorld::GetVolume(void) {
	volume = PioneerCarRadio::GetVolume();
	return volume;
}

/*  -- Method Header Comment
	Name	: GetChar
	Purpose : Get characterfrom user.
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: getChar		char		a character from user
*/
char PioneerWorld::GetChar(void) {
	getChar = getch();
	return getChar;
}

/*  -- Method Header Comment
	Name	: GetCurrent_Station
	Purpose : Get current station of radio from it's parent's class(AmFmRadio class)
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: current_station		float		current station frequency
*/
float PioneerWorld::GetCurrent_Station(void) {
	current_station = PioneerCarRadio::GetCurrent_Station();
	return current_station;
}

/*  -- Method Header Comment
	Name	: GetBandName
	Purpose : Get band name from parent's class(AmFmRadio.class)
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: band		char*		a pointer of band name
*/
char* PioneerWorld::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	if (strcmp(band, "AM") == 0) {
		ToggleFrequency();
	}
	return band;
}

/*  -- Method Header Comment
	Name	: GetOn
	Purpose : getting on bool vaule and return current on bool vaule. it gets value from paraent class(AmFmRadio class)
	Inputs	: NONE
	Outputs	: NONE
	Returns	: on		bool		includes current on bool vaule
*/
bool PioneerWorld::GetOn(void) {
	on = PioneerAM::GetOn();
	return on;
}

/*  -- Method Header Comment
	Name	: SetPresetButton
	Purpose : Set all initial station in 531 KHZ using method AmFmRadio method
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void PioneerWorld::SetPresetButton(int button_num) {
	SetCurrentStation(kWorldMinRange);
	AmFmRadio::SetPresetButton(button_num);
}

/*  -- Method Header Comment
	Name	: SetCurrentStation
	Purpose : Set current station as user want to put, it is overriding PioneerCarRadio class
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void PioneerWorld::SetCurrentStation(float current_station) {
	PioneerCarRadio::SetCurrentStation(current_station);
	
}
