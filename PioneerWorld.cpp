#include "PioneerWorld.h"
//처음에 모든 주파수 531
PioneerWorld::PioneerWorld(bool on) : PioneerAM(false) {
	getChar = 'x';
	
	this->on = on;
	exit = false;
	volume = kZeroValue;
	current_station = kWorldMinRange;
	current_stationCopy = kWorldMinRange;
	strncpy(band, "AM", sizeof("AM"));
	
	
}

PioneerWorld::~PioneerWorld() {
	printf("Destroying Pioneer XS440-WRLD Radio\n");
}

void PioneerWorld::CurrentStatus(void) {
	on = GetOn();

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

int PioneerWorld::GetVolume(void) {
	volume = PioneerCarRadio::GetVolume();
	return volume;
}
char PioneerWorld::GetChar(void) {
	getChar = getch();
	return getChar;
}

float PioneerWorld::GetCurrent_Station(void) {
	current_station = PioneerCarRadio::GetCurrent_Station();
	return current_station;
}

char* PioneerWorld::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	if (strcmp(band, "AM") == 0) {
		ToggleBand();
	}
	return band;
}

bool PioneerWorld::GetOn(void) {
	on = PioneerAM::GetOn();
	return on;
}

void PioneerWorld::ScanUp(void) {
	if (current_station == kWorldMaxRange) {
		current_station = kWorldMinRange;
	}
	else {
		current_station = current_station + kWorldFreqRange;	
	}
	SetCurrentStation(current_station);
}

void PioneerWorld::ScanDown(void) {
	if (current_station == kWorldMinRange) {
		current_station = kWorldMaxRange;
	}
	else {
		current_station = current_station - kWorldFreqRange;
	}
	SetCurrentStation(current_station);
}

void PioneerWorld::SetPresetButton(int button_num) {
	SetCurrentStation(kWorldMinRange);
	AmFmRadio::SetPresetButton(button_num);
}


void PioneerWorld::SetCurrentStation(float current_station) {
	PioneerCarRadio::SetCurrentStation(current_station);
	
}
