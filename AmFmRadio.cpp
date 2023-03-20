// AmFmRadio.cpp

#include "AmFmRadio.h"

/**
* \brief AmFmRadio -- CONSTRUCTOR
* \details <b>Details</b>
*
* To instantiate a new AmFmRadio object - given a set of attribute values
*
* It can be overloaded
*
* \param on  - <b>bool</b> - the status of radio's power
*
* \return Nothing
*
* \see ~AmFmRadio()
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

/**
* \brief AmFmRadio -- CONSTRUCTOR
* \details <b>Details</b>
*
* To instantiate a new AmFmRadio object - given a set of attribute values
*
* It can be overloaded
*
* \param on  - <b>bool</b> - the status of radio's power
* \param button[kNUmberOfArray]  - <b>Freqs</b> - Array of struct value
*
* \return Nothing
*
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

/**
* \brief AmFmRadio -- DESTRUCTOR
*
* Called upon to <i>destroy</i> a AmFmRadio object
* \details <b>Details</b>
*
* To destroy the AmFmRadio object - free up the memory associated with the object
*
* \return Nothing
*
*/
AmFmRadio::~AmFmRadio() {
	//printf("Destorying AmFmRadio\n");
}


/// \brief Method
/// \details <b>Details</b>
///
/// This method switch value of <b>on</b>
/// 
/// Also it can store current frequency and volume into struct.
///	\return Nothing
/// 
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


/// \brief Method
/// \details <b>Details</b>
///
/// This method can get value <b>on</b>
/// 
///	\return on - the status of radio's power
/// 
bool AmFmRadio::IsRadioOn(void) {
	return on;
}


/// \brief Mutator
/// \details <b>Details</b>
///
/// This method can set volume value
/// 
///	\return
/// 	kOverLowVolRet(0) - when the insert volume is lower or the same as 0.
/// 
///		kVolRet(1) - when the insert volume is between 0 ~ 100
/// 
///		kOverMaxVolRet(2) - when the insert volume is biggner or the same as 100.
/// 
/// 
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

/// \brief Mutator
/// \details <b>Details</b>
///
/// This method can set volume value
/// 
/// \param volume  - <b>int</b> - the volume to set data member(volume)
///	\return
/// 	kOverLowVolRet(0) - when the insert volume is lower or the same as 0.
/// 
///		kVolRet(1) - when the insert volume is between 0 ~ 100
/// 
///		kOverMaxVolRet(2) - when the insert volume is biggner or the same as 100.
/// 
/// 
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


/// \brief Method
/// \details <b>Details</b>
///
/// This method can switch band(AM -> FM or FM -> AN)
/// 
///	\return Nothing
/// 
void AmFmRadio::ToggleBand(void) {
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


/// \brief Method
/// \details <b>Details</b>
///
/// This method can preset current_station as user wants
/// 
/// Stores the number received as a parameter in an array with an index.
/// 
/// \param button_num  - <b>int</b> - index number which is received.
///	\return
///		kRetNullPreButton(0) - When user inserts out of range index.
/// 
/// 	kRetPresetButton(1) - When user wants to change preset in struct array

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


/// \brief Method
/// \details <b>Details</b>
///
/// This method can get current_station as user wants
/// 
/// It can change current_station value as channel from user
/// 
/// \param button_num  - <b>int</b> - index number which is received.
///	\return
///		kRetNullPreButton(0) - When user inserts out of range index.
/// 
/// 	kRetPresetButton(1) - When user wants to change preset in struct array
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
	Purpose : When user select '7', current frequeency is going up with in a range as each amount of frequency (AM : 10, FM : 0.2)
	Inputs	: NONE
	Outputs	: if displayOutput is true, display current band and frequency
	Returns	: Nothing
*/

/// \brief Method
/// \details <b>Details</b>
///
/// This method changes current frequency up within appropriate range.
/// 
/// AM - 10, FM - 0.2
/// 
///	\return Nothing
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


/// \brief Method
/// \details <b>Details</b>
///
/// This method changes current frequencu down within appropriate range.
/// 
/// AM - 10, FM - 0.2
/// 
///	\return Nothing
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


/// \brief Method
/// \details <b>Details</b>
///
/// This method shows all information of current setting status
/// 
///	\return Nothing
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

///
/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting current_station and return it.
/// 
/// \return Returns current_station which is gotten from user as float type
///
///
float AmFmRadio::GetCurrent_Station(void) {
	return current_station;
}

/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting volume and return current volume
/// 
/// \return Returns volume which is gotten from user as int type
///
///
int AmFmRadio::GetVolume(void) {
	return volume;
}


/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting on bool vaule and return current on bool vaule
/// 
/// \return Returns on which is gotten from user as bool type
///
///
bool AmFmRadio::GetOn(void) {
	return on;
}

/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting band string and return band string
/// 
/// \return Returns bandCopy which is gotten from user as char* type
///
///
char* AmFmRadio::GetBandName(void) {
	memcpy(bandCopy, band, sizeof(band));
	return bandCopy;
}


/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting display bool value and display bool value
/// 
/// \return Returns displayOutput which is gotten from user as bool type
///
bool AmFmRadio::GetDisplayOutput(void) {
	return displayOutput;
}

/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting an array which has struct
/// 
/// \return Returns button[button_num] which is gotten from user as array of struct type
///
Freqs AmFmRadio::GetButton(int button_num) {
	return button[button_num];
}


/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting struct which has information of current status to save lastest information
/// 
/// \return Returns rememberStatus which is gotten from user as struct type
///
Freqs AmFmRadio::GetRememberStatus(void) {
	return rememberStatus;
}


/// \brief Mutator
/// \details <b>Details</b>
///
/// A mutator to save current_station in private data member.
/// 
/// \return Nothing
///
void AmFmRadio::SetCurrentStation(float current_station) {
	this->current_station = current_station;
}

/// \brief Mutator
/// \details <b>Details</b>
///
/// A mutator to save displayOutput in private data member.
/// 
/// \return Nothing
///
void AmFmRadio::SetDisplayOutput(bool displayOutput) {
	this->displayOutput = displayOutput;
}