#include "PioneerAM.h"
// 저장변수 가져오기
PioneerAM::PioneerAM(bool on) :PioneerCarRadio(false) {
	getChar = 'x';
	
	this->on = on;
	exit = false;
	volume = kZeroValue;
	current_station = kMinAMFreqs;
	strncpy(band, "AM", sizeof("AM"));
	
}

PioneerAM:: ~PioneerAM() {
	printf("Destroying Pioneer XS440-AM Radio\n");
}

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


void PioneerAM::ProcessUserKeyStroke(char getChar) {
	if (getChar == 'b') {
		ToggleBand();
	}
	else
		PioneerCarRadio::ProcessUserKeyStroke(getChar);
}

int PioneerAM::GetVolume(void) {
	volume = PioneerCarRadio::GetVolume();
	return volume;
}
char PioneerAM::GetChar(void) {
	getChar = getch();
	return getChar;
}

float PioneerAM::GetCurrent_Station(void) {
	current_station = AmFmRadio::GetCurrent_Station();
	return current_station;
}
char* PioneerAM::GetBandName(void) {
	memcpy(band, AmFmRadio::GetBandName(), sizeof(band));
	if (strcmp(band, "AM") != 0) {
		ToggleBand();
	}
	return band;
}

bool PioneerAM::GetOn(void) {
	on = PioneerCarRadio::GetOn();
	return on;
}


void PioneerAM::ToggleBand(void) {
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