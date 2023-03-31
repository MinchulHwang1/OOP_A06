// PioneerAM.cpp
#include "PioneerAM.h"

/*  -- Method Header Comment
	Name	: PioneerAM -- CONSTRUCTOR
	Purpose : To instantiate a new PioneerAM object - given a set of attribute values, and inherited from AmFmRadio class and PioneerCarRadio class
	Inputs	: on		bool		Bool status of power
	Outputs	: NONE
	Returns	: Nothing
*/
PioneerAM::PioneerAM(bool on) :PioneerCarRadio(false) {
	getChar = 'x';
	this->on = on;
	exit = false;
	volume = kZeroValue;
	current_station = kMinAMFreqs;
	strncpy(band, "AM", sizeof("AM"));
}

/*  -- Method Header Comment
	Name	: PioneerAM -- DESTRUCTOR
	Purpose : To destroy the PioneerAM object - free up the memory associated with the object
	Inputs	: NONE
	Outputs	: Outputs a final message from the object before being destroyed
	Returns	: Nothing
*/
PioneerAM:: ~PioneerAM() {
	//Destructor
}

/*  -- Method Header Comment
	Name	: ShowCurrentSetting
	Purpose : it prints all of information(band, volume, frequency, and preset). it is overriding method in AmFmRadio and PioneerCarRadio
	Inputs	: NONE
	Outputs	: Prints all of information(band, volume, frequency, and preset (AM)
	Returns	: Nothing
*/
void PioneerAM::ShowCurrentSettings(void) {
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
	Name	: CurrentStatus
	Purpose : it prints current radio's status, and it can get character from user to set key stroke
	Inputs	: NONE
	Outputs	: Prints radio's power status
	Returns	: Nothing
*/
void PioneerAM::CurrentStatus(void) {
	on = GetOn();
	if (on == false) {
		printf("Pioneer XS440-AM\n");
		printf("Radio is off\n\n");
	}
	else {
		printf("Pioneer XS440-AM\n");
		printf("Radio is on\n");
		ShowCurrentSettings();
		printf("\n\n");
	}
}

/*  -- Method Header Comment
	Name	: ProcessUserKeyStroke
	Purpose : it divides key stroke gotten from user. Overriding from parent class
	Inputs	: getChar		char		the character from user
	Outputs	: Nothing
	Returns	: Nothing
*/
void PioneerAM::ProcessUserKeyStroke(char getChar) {
	if (getChar == 'b') {
		ToggleFrequency();
	}
	else
		PioneerCarRadio::ProcessUserKeyStroke(getChar);
}

/*  -- Method Header Comment
	Name	: ToggleBand
	Purpose : to do not change band just stay in AM band
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void PioneerAM::ToggleFrequency(void) {
	if (strcmp(GetBandName(), "FM") == 0) {
		current_station = PioneerCarRadio::GetCurrent_Station();
		strncpy(GetBandName(), "AM", sizeof("AM"));
		PioneerCarRadio::SetCurrentStation(current_station);
	}
	else {
		current_station = PioneerCarRadio::GetCurrent_Station();
		PioneerCarRadio::SetCurrentStation(current_station);	
	}
}

/*  -- Method Header Comment
	Name	: GetVolume
	Purpose : getting volume and return current volume, it get volume from parent class
	Inputs	: NONE
	Outputs	: NONE
	Returns	: volume		int			includes current volume
*/
int PioneerAM::GetVolume(void) {
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
char PioneerAM::GetChar(void) {
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
float PioneerAM::GetCurrent_Station(void) {
	current_station = AmFmRadio::GetCurrent_Station();
	return current_station;
}

/*  -- Method Header Comment
	Name	: GetBandName
	Purpose : Get band name from parent's class(AmFmRadio.class)
	Inputs	: Nothing
	Outputs	: Nothing
	Returns	: band		char*		a pointer of band name
*/
char* PioneerAM::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	if (strcmp(band, "AM") != 0) {
		ToggleFrequency();
	}
	return band;
}

/*  -- Method Header Comment
	Name	: GetOn
	Purpose : getting on bool vaule and return current on bool vaule. it gets value from paraent class(PioneerCarRadio class)
	Inputs	: NONE
	Outputs	: NONE
	Returns	: on		bool		includes current on bool vaule
*/
bool PioneerAM::GetOn(void) {
	on = PioneerCarRadio::GetOn();
	return on;
}


