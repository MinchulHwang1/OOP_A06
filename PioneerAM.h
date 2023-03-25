#pragma once

#ifndef _PIONEERAM_H
#define _PIONEERAM_H
#include"PioneerCarRadio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "AmFmRadio.h"
#include <iostream>

/*
PioneerAM behaves like PioneerCarRadio except that it operates in the AM band only!
There is no ability to change to the FM band – it shouldn’t even display the FM band
Do this by overriding the appropriate methods that are in the parent class or grandparent class.
*/
class PioneerAM : public PioneerCarRadio { //AM의 예외처리 (AM만 나옴)
private:
	char getChar;							///< To save character which is gotten from user to choose menu
	bool on;								///< To store the status of radio power
	int volume;								///< To store the volume
	float current_station;					///< To get current station
	char band[kBandName];					///< To store the band name
	bool exit;

public:
	PioneerAM(bool on);
	virtual ~PioneerAM();

	void ShowCurrentSettings(void);			///< This method can show current status.
	void CurrentStatus(void);				///< It can check current radio status
	void ProcessUserKeyStroke(char getChar);		///< This method can divide a character of keystrokes
	void ToggleBand(void);
	int GetVolume(void);
	bool GetOn(void);
	char GetChar(void);						///< Accessor - to get char from user as keystroke
	float GetCurrent_Station(void);			///< Accessor - to get current station from AmFmRadio class
	char* GetBandName(void);				///< Accessor - to get band name from AmFmRadio class

};



#endif _PIONEERAM_H