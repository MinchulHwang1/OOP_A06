// AmFmRadio.h
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#ifndef _CARRADIO_H
#define _CARRADIO_H
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define kNumberOfArray		5
#define kBandName			3
#define kZeroValue			0
#define kMinRangeOfButton	0
#define kMaxRangeOfButton	4
#define kRetPresetButton	1
#define kRetNullPreButton	0
#define kMinAMFreqs			530
#define kMinFMFreqs			87.9f
#define kMaxAMFreqs			1700
#define kMaxFMFreqs			107.9f
#define kMinVolume			0
#define kMaxVolume			100
#define kBuffer				20
#define kAMRange			10
#define kFMRange			.2f
#define kOverLowVolRet		0
#define kOverMaxVolRet		2
#define kVolRet				1

/*
	-* Struct COMMENT *-
	NAME    : Freqs
	PURPOSE : This structure is a structure that stores information desired by the user.
			  Also, previous data can be stored.
*/
struct Freqs {
	int		AMFreqs;						///< it can store AM Frequency
	float	FMFreqs;						///< It can store FM Frequency
	int		rememberVolume;					///< It can store Volume
	char	rememberBand[kBandName];		///< IT can store Band
};

/*
	-* CLASS COMMENT *-
	NAME    : AmFmRadio
	PURPOSE : This class creates an object that
			  proceeds with the program according to the number pressed by the user in the menu.
			  There are 9 buttons(power, band change, scan up, scan down etc), each button follows below methods
*/
class AmFmRadio {
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
private:
	/* -------------- CONSTANTS ------------- */
	/* -------------- ATTRIBUTES ------------ */
	Freqs	button[kNumberOfArray];			///< Array with structs where user wants to store content for each frequency
	float	current_station;				///< Current frequency station
	char	band[kBandName];				///< Array to store the name "AM", and "FM"
	int		volume;							///< Int value to store volume
	bool	on;								///< Bool value to store power status(on - true, off - false)
	Freqs	rememberStatus;					///< A struct to store previous status of radio.
	bool	displayOutput;					///< Bool value to store display or not
	int		button_num;						///< Int value to save array struct's element
	char	bandCopy[kBandName];			///< Variabless for safe copying of band strings.

	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false

	/* -------------- ATTRIBUTES ------------ */
	/* ---------- METHOD PROTOTYPES --------- */
	AmFmRadio(bool on);									///< Constructor with bool parameter.
	AmFmRadio(bool on, Freqs button[kNumberOfArray]);	///< Constructor with bool parameter and struct .
	~AmFmRadio();										///< Mutatoe of AmFmRadio object.

	void PowerToggle(void);							///< Returns a true if the radio is currently powered on, and false if the radio is in the off position
	bool IsRadioOn(void);							///< Status of radio power
	int SetVolume(void);							///< Sets volume
	int SetVolume(int volume);						///< Sets volume with parameter
	virtual void ToggleBand(void);							///< Toggles frequency between AM and FM and sets current station
	int SetPresetButton(int button_num);			///< Sets button (radio preset) with current station by being passed a button number
	int SelectPresetButton(int button_num);			///< Sets current station to radio preset by being passed a button number
	virtual void ScanUp(void);								///< Changes frequency up in increments of .2 for FM, 10 for AM
	virtual void ScanDown(void);							///< Changes frequency down in increments of .2 for FM, 10 for AM
	void ShowCurrentSettings(void);					///< Shows volume, button settings, current station, AM or FM

	float GetCurrent_Station(void);					///< Accessor - current_station
	int GetVolume(void);							///< Accessor - volume
	bool GetOn(void);								///< Accessor - on
	char* GetBandName(void);						///< Accessor - band
	bool GetDisplayOutput(void);					///< Accessor - displayOutput
	Freqs GetButton(int button_num);				///< Accessor - struct of buttons
	Freqs GetRememberStatus(void);					///< Accessor - struct of previous information.

	void SetCurrentStation(float current_station);  ///< Mutator of current_station
	void SetDisplayOutput(bool displayOutput);		///< Mutator of displayOutput
};

#endif