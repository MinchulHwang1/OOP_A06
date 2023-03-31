// AmFmRadio.cpp

#include "AmFmRadio.h"

/*  -- Method Header Comment
	Name	: AmFmRadio -- CONSTRUCTOR
	Purpose : To instantiate a new AmFmRadio object - given a set of attribute values
			  It can be overloaded
	Inputs	: on		bool		Bool sttus of power
	Outputs	: NONE
	Returns	: Nothing
*/
AmFmRadio::AmFmRadio(bool on) {
	// Initialization of Bool value.

	this->on = on;

	// Initialization of array value.
	for (int i = kZeroValue; i < kNumberOfArray; ++i) {
		button[i].AMFreqs = kMinAMFreqs;
	}
	for (int j = kZeroValue; j < kNumberOfArray; ++j) {
		button[j].FMFreqs = kMinFMFreqs;
	}

	// Initialization of Current_station
	current_station = kMinAMFreqs;

	// Initialization of array of band.
	strncpy(band, "AM", sizeof("AM"));
	strncpy(bandCopy, "", sizeof(""));

	// Initialization of struct rememberStatus.
	rememberStatus.rememberVolume = volume = kMinVolume;
	strncpy(rememberStatus.rememberBand, band, sizeof(band));
	rememberStatus.AMFreqs = kMinAMFreqs;
	rememberStatus.FMFreqs = kMinFMFreqs;

	button_num = kZeroValue;
	displayOutput = false;
}

/*  -- Method Header Comment
	Name	: AmFmRadio -- CONSTRUCTOR
	Purpose : To instantiate a new AmFmRadio object - given a set of attribute values
			  It can be overloaded
	Inputs	: on							bool		Bool status of power
			  button[kNumberOfArray]		Freqs		Array of struct value
	Outputs	: NONE
	Returns	: Nothing
*/
AmFmRadio::AmFmRadio(bool on, Freqs button[kNumberOfArray]) {
	// Initialization of Bool value.
	this->on = on;

	// Initialization of array value.
	for (int i = kZeroValue; i < kNumberOfArray; ++i) {
		button[i].AMFreqs = kMinAMFreqs;
		this->button[i].AMFreqs = button[i].AMFreqs;
	}
	for (int j = kZeroValue; j < kNumberOfArray; ++j) {
		button[j].FMFreqs = kMinFMFreqs;
		this->button[j].FMFreqs = button[j].FMFreqs;
	}

	// Initialization of Current_station
	current_station = kMinAMFreqs;

	// Initialization of array of band.
	strncpy(band, "AM", sizeof("AM"));
	strncpy(bandCopy, "", sizeof(""));

	// Initialization of struct rememberStatus.
	rememberStatus.rememberVolume = volume = kMinVolume;
	strncpy(rememberStatus.rememberBand, band, sizeof(band));
	rememberStatus.AMFreqs = kMinAMFreqs;
	rememberStatus.FMFreqs = kMinFMFreqs;

	button_num = kZeroValue;
	displayOutput = false;
}

/*  -- Method Header Comment
	Name	: AmFmRadio -- DESTRUCTOR
	Purpose : To destroy the AmFmRadio object - free up the memory associated with the object
	Inputs	: NONE
	Outputs	: Outputs a final message from the object before being destroyed --> should be deleted
	Returns	: Nothing
*/
AmFmRadio::~AmFmRadio() {
	//printf("Destorying AmFmRadio\n");
}

/*  -- Method Header Comment
	Name	: PowerToggle
	Purpose : to turn Radio power on or off
	Inputs	: NONE
	Outputs	: NONE
	Returns	: true		when it turns on
			  false		when it turns off
*/
void AmFmRadio::PowerToggle(void) {
	if (on == false) {

		if (strcmp(band, "AM") == 0) {
			current_station = (float)rememberStatus.AMFreqs;		// To save current frequency into rememberStatus member
			volume = rememberStatus.rememberVolume;					// To save current volume into rememberStatus member
		}
		else {
			current_station = rememberStatus.FMFreqs;				// To save current frequency into rememberStatus member
			volume = rememberStatus.rememberVolume;					// To save current volume into rememberStatus member
		}
		on = true;
	}
	else {
		if (strcmp(band, "AM") == 0) {
			rememberStatus.AMFreqs = (int)current_station;			// To save current frequency into rememberStatus member
		}
		else {
			rememberStatus.FMFreqs = current_station;				// To save current frequency into rememberStatus member
		}
		volume = kMinVolume;
		on = false;
	}
}


/*  -- Method Header Comment
	Name	: IsRadioOn
	Purpose : To check radio is on or off
	Inputs	: NONE
	Outputs	: NONE
	Returns	: on
*/
bool AmFmRadio::IsRadioOn(void) {
	return on;
}


/*  -- Method Header Comment
	Name	: SetVolume
	Purpose : To set radio's volume
	Inputs	: NONE
	Outputs	: Request volume which is user wants to change.
	Returns	: kOverLowVolRet = 0	when the insert volume is lower or the same as 0.
			  kOverMaxVolRet = 2	when the insert volume is biggner or the same as 100.
			  kVolRet = 1			when the insert volume is between 0 ~ 100
*/
int AmFmRadio::SetVolume(void) {
	if (on == true) {
		char buf[kBuffer] = "";

		printf("\nEnter the volume level (0 - 100). ");
		fgets(buf, sizeof buf, stdin);
		volume = atoi(buf);

		//if user enters volume less than 0, volume = 0
		if (volume < kMinVolume) {
			volume = kMinVolume;
			rememberStatus.rememberVolume = volume;					// Save current volume into rememberStatus
			return kOverLowVolRet;
		}
		//if user enters volume greater than 100, volume = 100
		if (volume > kMaxVolume) {
			volume = kMaxVolume;
			rememberStatus.rememberVolume = volume;					// Save current volume into rememberStatus
			return kOverMaxVolRet;
		}
		rememberStatus.rememberVolume = volume;						// Save current volume into rememberStatus
		return kVolRet;
	}
}

/*  -- Method Header Comment
	Name	: SetVolume
	Purpose : To set radio's volume
	Inputs	: volume
	Outputs	: Request volume which is user wants to change.
	Returns	: kOverLowVolRet = 0	when the insert volume is lower or the same as 0.
			  kOverMaxVolRet = 2	when the insert volume is biggner or the same as 100.
			  kVolRet = 1			when the insert volume is between 0 ~ 100
*/
int AmFmRadio::SetVolume(int volume) {
	this->volume = volume;

	//if user enters volume less than 0, volume = 0
	if (this->volume < kMinVolume) {
		this->volume = kMinVolume;
		rememberStatus.rememberVolume = this->volume;				// Save current volume into rememberStatus
		return kOverLowVolRet;
	}
	//if user enters volume greater than 100, volume = 100
	if (this->volume > kMaxVolume) {
		this->volume = kMaxVolume;
		rememberStatus.rememberVolume = this->volume;				// Save current volume into rememberStatus
		return kOverMaxVolRet;
	}
	rememberStatus.rememberVolume = this->volume;					// Save current volume into rememberStatus
	return kVolRet;

}


/*  -- Method Header Comment
	Name	: ToggleBand
	Purpose : to change Band would be changed(AM -> FM or FM -> AM)
	Inputs	: NONE
	Outputs	: NONE
	Returns	: Nothing
*/
void AmFmRadio::ToggleFrequency(void) {
	if (strcmp(band, "AM") == 0) {
		strncpy(band, "FM", sizeof("FM"));
		rememberStatus.AMFreqs = current_station;
		strncpy(&rememberStatus.rememberBand[kBandName], band, sizeof(band));		// Save the string into rememberStatus struct
		current_station = rememberStatus.FMFreqs;									// Put rememberStatus data member into current_station.

	}
	else {
		strncpy(band, "AM", sizeof("AM"));
		rememberStatus.FMFreqs = current_station;
		strncpy(&rememberStatus.rememberBand[kBandName], band, sizeof(band));		// Save the string into rememberStatus struct
		current_station = (float)rememberStatus.AMFreqs;							// Put rememberStatus data member into current_station.
	}
}


/*  -- Method Header Comment
	Name	: SetPresetButton
	Purpose : to change the preset changed as current_station as user wants
	Inputs	: button_num				an index of struct array.
	Outputs	: NONE
	Returns	: kRetPresetButton = 1		When user wants to change preset in struct array
			  kRetNullPreButton = 0		When user inserts out of range index.
*/

int AmFmRadio::SetPresetButton(int button_num) {
	if ((button_num >= kMinRangeOfButton) && (button_num <= kMaxRangeOfButton)) {  // If the insert number is within a range
		if (strcmp("AM", band) == 0) {
			button[button_num].AMFreqs = (int)current_station;
		}
		else {
			button[button_num].FMFreqs = current_station;
		}
		return kRetPresetButton;
	}
	return kRetNullPreButton;
}


/*  -- Method Header Comment
	Name	: SelectPresetButton
	Purpose : current frequeency is changed as element which is in button array
	Inputs	: button_num				an index of struct array.
	Outputs	: NONE
	Returns	: kRetPresetButton = 1		When user wants to change preset in struct array
			  kRetNullPreButton = 0		When user inserts out of range index.
*/
int AmFmRadio::SelectPresetButton(int button_num) {
	if ((button_num >= kMinRangeOfButton) && (button_num <= kMaxRangeOfButton)) {		// If the insert number is within a range
		if (strcmp("AM", band) == 0) {
			current_station = (float)button[button_num].AMFreqs;
		}
		else {
			current_station = button[button_num].FMFreqs;
		}
		return kRetPresetButton;
	}
	return kRetNullPreButton;
}

/*  -- Method Header Comment
	Name	: ScanUp
	Purpose : current frequeency is going up with in a range as each amount of frequency (AM : 10, FM : 0.2)
	Inputs	: NONE
	Outputs	: if displayOutput is true, display current band and frequency
	Returns	: Nothing
*/
void AmFmRadio::ScanUp(void) {
	if (strcmp("AM", band) == 0) {
		//if current_station is 1700, the current_station becomes 530
		if (current_station == kMaxAMFreqs) {
			current_station = kMinAMFreqs;
		}
		else {
			current_station = current_station + kAMRange;
		}
		rememberStatus.AMFreqs = (int)current_station;
	}
	else {
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station >= kMaxFMFreqs) {
			current_station = kMinFMFreqs;
		}
		else {
			current_station += kFMRange;
		}
		rememberStatus.FMFreqs = current_station;
	}
	if (displayOutput == true) {
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Method Header Comment
	Name	: ScanDown
	Purpose : current frequeency is going down with in a range as each amount of frequency (AM : 10, FM : 0.2)
	Inputs	: NONE
	Outputs	: if displayOutput is true, display current band and frequency
	Returns	: Nothing
*/
void AmFmRadio::ScanDown(void) {
	if (strcmp("AM", band) == 0) {
		//if current_station is 530, the current_station becomes 170
		if (current_station == kMinAMFreqs) {
			current_station = kMaxAMFreqs;
		}
		else {
			current_station = current_station - kAMRange;
		}
		rememberStatus.AMFreqs = (int)current_station;
	}
	else {
		//if the current_station is 87.9, the current_station becomes 107.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= kMinFMFreqs) {
			current_station = kMaxFMFreqs;
		}
		else {
			current_station -= kFMRange;
		}
		rememberStatus.FMFreqs = current_station;
	}
	if (displayOutput == true) {
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Method Header Comment
	Name	: ShowCurrentSetting
	Purpose : it prints all of information(band, volume, frequency, and preset)
	Inputs	: NONE
	Outputs	: Prints all of information(band, volume, frequency, and preset (both of AM and FM)
	Returns	: Nothing
*/
void AmFmRadio::ShowCurrentSettings(void) {
	if (on == true) {
		printf("\n\nRadio is on. \n");
	}
	else {
		printf("\n\nRadio is off. \n");
	}

	printf("\nRadio Band: %s\n", band);
	printf("Volume: %d\n", volume);
	printf("Current Station: %.1f %s\n", current_station, band);
	printf("AM Button Settings: ");
	for (int i = kZeroValue; i < kNumberOfArray; ++i) {
		printf("%d) %6d ", i + 1, button[i].AMFreqs);
	}
	printf("\nFM Button Settings: ");
	for (int j = kZeroValue; j < kNumberOfArray; ++j) {
		printf("%d) %6.1f ", j + 1, button[j].FMFreqs);
	}
}

/*  -- Method Header Comment
	Name	: GetCurrent_Station
	Purpose : getting current_station and return it.
	Inputs	: NONE
	Outputs	: NONE
	Returns	: current_station		float		includes current frequency
*/
float AmFmRadio::GetCurrent_Station(void) {
	return current_station;
}

/*  -- Method Header Comment
	Name	: GetVolume
	Purpose : getting volume and return current volume
	Inputs	: NONE
	Outputs	: NONE
	Returns	: volume		int			includes current volume
*/
int AmFmRadio::GetVolume(void) {
	return volume;
}


/*  -- Method Header Comment
	Name	: GetOn
	Purpose : getting on bool vaule and return current on bool vaule
	Inputs	: NONE
	Outputs	: NONE
	Returns	: on		bool		includes current on bool vaule
*/
bool AmFmRadio::GetOn(void) {
	return on;
}

/*  -- Method Header Comment
	Name	: GetBandName
	Purpose : getting band string and return band string
	Inputs	: NONE
	Outputs	: NONE
	Returns	: bandCopy		char*		string of band
*/
char* AmFmRadio::GetBandName(void) {
	memcpy(bandCopy, band, sizeof(band));
	return bandCopy;
}


/*  -- Method Header Comment
	Name	: GetDIsplyOutput
	Purpose : getting display bool value and display bool value
	Inputs	: NONE
	Outputs	: NONE
	Returns	: displayOutput			bool		display bool value
*/
bool AmFmRadio::GetDisplayOutput(void) {
	return displayOutput;
}

/*  -- Method Header Comment
	Name	: GetButton
	Purpose : return an array which has struct
	Inputs	: NONE
	Outputs	: NONE
	Returns	: button[button_num]		Freqs(struct)		an array which has struct
*/
Freqs AmFmRadio::GetButton(int button_num) {
	return button[button_num];
}


/*  -- Method Header Comment
	Name	: GetRememberStatus
	Purpose : return struct which has information of current status to save lastest information
	Inputs	: NONE
	Outputs	: NONE
	Returns	: rememberStatus		Freqs(struct)		current information
*/
Freqs AmFmRadio::GetRememberStatus(void) {
	return rememberStatus;
}


/*  -- Method Header Comment
	Name	: SetCurrentStation
	Purpose : A mutator to save current_station in private data member.
	Inputs	: current_station
	Outputs	: NONE
	Returns	: Nothing
*/
void AmFmRadio::SetCurrentStation(float current_station) {
	this->current_station = current_station;
}

/*  -- Method Header Comment
	Name	: SetDisplayOutput
	Purpose : A mutator to save displayOutput in private data member.
	Inputs	: displayOutput
	Outputs	: NONE
	Returns	: Nothing
*/
void AmFmRadio::SetDisplayOutput(bool displayOutput) {
	this->displayOutput = displayOutput;
}