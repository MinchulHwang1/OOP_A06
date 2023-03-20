// PioneerCarRadio.cpp
#include"PioneerCarRadio.h"

/**
* \brief PioneerCarRadio -- CONSTRUCTOR
* \details <b>Details</b>
*
* To instantiate a PioneerCarRadio object - given a set of attribute values.
*
* It prints nothing
*
* It is inherited from AmFmRadio Class
* \param on  - <b>bool</b> - the status of radio's power
*
*
* \return Nothing
*
* \see ~PioneerCarRadio()
*/
PioneerCarRadio::PioneerCarRadio(bool on) : AmFmRadio(false) {
	getChar = 'x';
	on = false;
	this->on = on;

	volume = kZeroValue;
	current_station = kMinAMFreqs;
	strncpy(band, "AM", sizeof("AM"));
}

/**
* \brief PioneerCarRadio -- DESTRUCTOR
*
* Called upon to <i>destroy</i> a PioneerCarRadio object
* \details <b>Details</b>
*
* To destroy the PioneerCarRadio object - free up the memory associated with the object
*
* It prints the message that object is destoried
*
* \return Nothing
*
*/
PioneerCarRadio::~PioneerCarRadio() {
	printf("PioneerCarRadio is destroyed\n");
}

/// \brief Method
/// \details <b>Details</b>
///
/// Showing all of information of object PioneerCarRadio.
///	\return Nothing
/// 
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

/// \brief Method
/// \details <b>Details</b>
/// 
/// Showing all of current information of object PioneerCarRadio.
///	\return kBreakValue(1) when user input <b>'x'</b> or <b>'X'</b> when user want to exit.
/// KZeroValue(0) when user input the character except <b>'x'</b> or <b>'X'</b>
/// 
int PioneerCarRadio::CurrentStatus(void) {

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

	GetChar();
	switch (getChar) {
	case 'x':
		return kBreakValue;

	case 'X':
		return kBreakValue;

	default:
		DivisionChar(getChar);
		return kZeroValue;
	}

}

/// \brief Method
/// \details <b>Details</b>
/// 
/// This method can divide the character as keystroke
/// 
/// 'o' : Power toggle	- This key can turn power <b>on</b> or <i>off</i>
/// 
/// '+' : Volume up		- THis key can volume <b>up</b> for 1
/// 
/// '_' : Voulume down	- This key can volume <b>down</b> for 1
/// 
/// '=' : Scan up		- This key can scan <b>up</b> for 10 in AM Frequency or 0.2 in FM Frequency
/// 
/// '-' : Scan down		- This key can scan <b>down</b> for 10 in AM Frequency or 0.2 in FM Frequency
/// 
/// 'b' : Toggle power	- This key can turn <b>switch</b> band
/// 
/// '!' : Set button 1	- This key can set current frequancy into button <b>1</b> on current band
/// 
/// '@' : Set button 2	- This key can set current frequancy into button <b>2</b> on current band
/// 
/// '#' : Set button 3	- This key can set current frequancy into button <b>3</b> on current band
/// 
/// '$' : Set button 4	- This key can set current frequancy into button <b>4</b> on current band
/// 
/// '%' : Set button 5	- This key can set current frequancy into button <b>5</b> on current band
/// 
/// 1~5 : Select preset	- This key can set current frequancy into what user want to set.
/// 
///	\return Nothing
/// 
void PioneerCarRadio::DivisionChar(char getChar) {
	switch (getChar) {
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

///
/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting character using getch() from user
/// 
/// \return Returns getChar which is gotten from user as char type
///
///
char PioneerCarRadio::GetChar(void) {
	getChar = getch();
	return getChar;
}

///
/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting current station from parent class(AmFmRadio)
/// 
/// \return Returns current_station which is gotten from user as float type
///
///
float PioneerCarRadio::GetCurrent_Station(void) {
	current_station = AmFmRadio::GetCurrent_Station();
	return current_station;
}

///
/// \brief Accessor
/// \details <b>Details</b>
///
/// Getting band from parent class(AmFmRadio)
/// 
/// \return Returns band which is gotten from user as pointer of char
///
///
char* PioneerCarRadio::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	return band;
}