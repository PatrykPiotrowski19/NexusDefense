#pragma once
#include"stdafx.h"

class DeviceSource{
	ALuint buffer, source;
	ALint state;
	ALsizei size;
	ALsizei frequency;
	ALenum format;

	struct RIFF_Header {
		char chunkID[4];
		long chunkSize;//size not including chunkSize or chunkID
		char format[4];
	};

	struct WAVE_Format {
		char subChunkID[4];
		long subChunkSize;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};

	struct WAVE_Data {
		char subChunkID[4]; //should contain the word data
		long subChunk2Size; //Stores the size of the data block
	};

	bool loadWav(std::string filename);

public:

	DeviceSource(std::string filename, int type);

	void Play();

};

class SoundManage {

	DeviceSource *announcer[10];

	DeviceSource *ShacoTurrets[2];
	DeviceSource *HeimerTurrets[2];
	DeviceSource *ZyraTurrets[4];
	DeviceSource *AzirTurrets[4];

	public:

		SoundManage();
		void _Announcer_Prepare();
		void _Announcer_New_Round();
		void _Announcer_Ace();

		//Placing turrets
		void _PlaceTurret_Heimer();
		void _PlaceTurret_Shaco();
		void _PlaceTurret_Zyra();
		void _PlaceTurret_Azir();
};