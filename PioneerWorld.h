#pragma once

#ifndef _PIONEERWORLD_H
#define _PIONEERWORLD_H
#include "PioneerAM.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "AmFmRadio.h"
#include <iostream>
#define kWorldMaxRange		1602
#define kWorldMinRange		531
#define kWorldFreqRange		9
/*
Except that the AM band range is 531 kHz to 1602 kHz (instead of the 530 kHz to 1700 kHz range)
And the interval between frequencies is 9 kHz, not 10 kHz
So scanning up from 531 would bring you to 540, then 549, etc. Wrapping from 1602 brings you to 531.
*/
class PioneerWorld : public PioneerAM {
private:
	char getChar;							///< To save character which is gotten from user to choose menu
	bool on;								///< To store the status of radio power
	int volume;								///< To store the volume
	float current_station;					///< To get current station
	float current_stationCopy;
	char band[kBandName];					///< To store the band name
	bool exit;

public :
	PioneerWorld(bool on);
	virtual ~PioneerWorld();

	// ScanUp/Down
	void ShowCurrentSettings(void);			///< This method can show current status.
	void CurrentStatus(void);				///< It can check current radio status
	void ProcessUserKeyStroke(char getChar);		///< This method can divide a character of keystrokes
	int GetVolume(void);
	bool GetOn(void);
	char GetChar(void);						///< Accessor - to get char from user as keystroke
	float GetCurrent_Station(void);			///< Accessor - to get current station from AmFmRadio class
	char* GetBandName(void);				///< Accessor - to get band name from AmFmRadio class
	void ScanUp(void);
	void ScanDown(void);
	void SetPresetButton(int button_num);
	//void SelectPresetButton(int button_num);
	void SetCurrentStation(float current_station);
};
#endif _PIONEERWORLD_H