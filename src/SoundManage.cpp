#include "SoundManage.h"
#include "stdafx.h"


SoundManage::SoundManage()
{
	
	announcer[0] = new DeviceSource("Data/Sound/Announcer/Start.wav",2);
	announcer[1] = new DeviceSource("Data/Sound/Announcer/Wave_Start1.wav", 2);
	announcer[2] = new DeviceSource("Data/Sound/Announcer/Wave_Start2.wav", 2);
	announcer[3] = new DeviceSource("Data/Sound/Announcer/Wave_Start3.wav", 2);
	announcer[4] = new DeviceSource("Data/Sound/Announcer/Ace.wav", 2);


	ShacoTurrets[0] = new DeviceSource("Data/Sound/PlaceTurrets/Shaco1.wav", 1);
	ShacoTurrets[1] = new DeviceSource("Data/Sound/PlaceTurrets/Shaco2.wav", 1);

	HeimerTurrets[0] = new DeviceSource("Data/Sound/PlaceTurrets/Heimer1.wav", 1);
	HeimerTurrets[1] = new DeviceSource("Data/Sound/PlaceTurrets/Heimer2.wav", 1);

	ZyraTurrets[0] = new DeviceSource("Data/Sound/PlaceTurrets/Zyra1.wav", 1);
	ZyraTurrets[1] = new DeviceSource("Data/Sound/PlaceTurrets/Zyra2.wav", 1);
	ZyraTurrets[2] = new DeviceSource("Data/Sound/PlaceTurrets/Zyra3.wav", 1);
	ZyraTurrets[3] = new DeviceSource("Data/Sound/PlaceTurrets/Zyra4.wav", 1);

	AzirTurrets[0] = new DeviceSource("Data/Sound/PlaceTurrets/Azir1.wav", 1);
	AzirTurrets[1] = new DeviceSource("Data/Sound/PlaceTurrets/Azir2.wav", 1);
	AzirTurrets[2] = new DeviceSource("Data/Sound/PlaceTurrets/Azir3.wav", 1);
	AzirTurrets[3] = new DeviceSource("Data/Sound/PlaceTurrets/Azir4.wav", 1);

}

void SoundManage::_Announcer_Prepare()
{
	announcer[0]->Play();
	//cout << "ANNOUNCER\n";
}

void SoundManage::_Announcer_New_Round()
{
	int random = (rand() % 3) + 1;

	announcer[random]->Play();

}

void SoundManage::_Announcer_Ace()
{
	announcer[4]->Play();
}


void SoundManage::_PlaceTurret_Shaco()
{
	int random = rand() % 2;

	ShacoTurrets[random]->Play();

}

void SoundManage::_PlaceTurret_Zyra()
{

	int random = rand() % 4;

	ZyraTurrets[random]->Play();
}

void SoundManage::_PlaceTurret_Azir()
{

	int random = rand() % 4;

	AzirTurrets[random]->Play();

}


void SoundManage::_PlaceTurret_Heimer()
{
	int random = rand() % 2;

	HeimerTurrets[random]->Play();

}

bool DeviceSource::loadWav(std::string filename)
{
	//Local Declarations
	FILE* soundFile = NULL;
	
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;
	/*
	&size = &wave_data.subChunk2Size;
	frequency = wave_format.sampleRate;

	if (wave_format.numChannels == 1) {
		if (wave_format.bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if (wave_format.bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
	}
	else if (wave_format.numChannels == 2) {
		if (wave_format.bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if (wave_format.bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
	}
	*/
	try {
		soundFile = fopen(filename.c_str(), "rb");
		if (!soundFile)
			throw (filename);

		// Read in the first chunk into the struct
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		//check for RIFF and WAVE tag in memeory
		if ((riff_header.chunkID[0] != 'R' ||
			riff_header.chunkID[1] != 'I' ||
			riff_header.chunkID[2] != 'F' ||
			riff_header.chunkID[3] != 'F') ||
			(riff_header.format[0] != 'W' ||
				riff_header.format[1] != 'A' ||
				riff_header.format[2] != 'V' ||
				riff_header.format[3] != 'E'))
			throw ("Invalid RIFF or WAVE Header");

		//Read in the 2nd chunk for the wave info
		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
		//check for fmt tag in memory
		if (wave_format.subChunkID[0] != 'f' ||
			wave_format.subChunkID[1] != 'm' ||
			wave_format.subChunkID[2] != 't' ||
			wave_format.subChunkID[3] != ' ')
			throw ("Invalid Wave Format");

		//check for extra parameters;
		if (wave_format.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		//Read in the the last byte of data before the sound file
		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);

		//check for data tag in memory
		if (wave_data.subChunkID[0] != 'd' ||
			wave_data.subChunkID[1] != 'a' ||
			wave_data.subChunkID[2] != 't' ||
			wave_data.subChunkID[3] != 'a')
			throw ("Invalid data header");

		//Allocate memory for data
		data = new unsigned char[wave_data.subChunk2Size];

		// Read in the sound data into the soundData variable
		if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw ("error loading WAVE data into struct!");

		//Now we set the variables that we passed in with the
		//data from the structs
		size = wave_data.subChunk2Size;
		frequency = wave_format.sampleRate;
		//The format is worked out by looking at the number of
		//channels and the bits per sample.
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8)
				format = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				format = AL_FORMAT_MONO16;
		}
		else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8)
				format = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				format = AL_FORMAT_STEREO16;
		}
		//create our openAL buffer and check for success
		alGenBuffers(2, &buffer);
		if (alGetError() != AL_NO_ERROR) {
			std::cerr << alGetError() << std::endl;
		}
		//now we put our data into the openAL buffer and
		//check for success
		alBufferData(buffer, format, (void*)data,
			size, frequency);
		if (alGetError() != AL_NO_ERROR) {
			std::cerr << alGetError() << std::endl;
		}
		//clean up and return true if successful
		fclose(soundFile);
		delete data;
		return true;
	}
	catch (const char* error) {
		//our catch statement for if we throw a string
		std::cerr << error << " : trying to load "
			<< filename << std::endl;
		//clean up memory if wave loading fails
		if (soundFile != NULL)
			fclose(soundFile);
		//return false to indicate the failure to load wave
		delete data;
		return false;
	}
}

DeviceSource::DeviceSource(std::string filename, int type)
{
	loadWav(filename);
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	//put_turrets
	if(type == 1)
		alSourcef(source, AL_GAIN, 0.3);
	//announcer
	if (type == 2)
		alSourcef(source, AL_GAIN, 0.3);
	//music
	if(type == 3)
		alSourcef(source, AL_GAIN, 0.1);
}

void DeviceSource::Play()
{
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING)
	alSourcePlay(source);
}
