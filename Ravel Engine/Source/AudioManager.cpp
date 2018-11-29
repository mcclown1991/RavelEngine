#include "AudioManager.h"

AudioManager * AudioManagement()
{
	static AudioManager s;
	return(&s);
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Init()
{
	FMOD_RESULT result = FMOD::System_Create(&_system);
	if (result != FMOD_OK) {
		std::cout << "FMOD error! " << result << std::endl;
		return;
	}

	result = _system->init(64, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK) {
		std::cout << "FMOD error! " << result << std::endl;
		return;
	}

	result = _system->set3DSettings(1.f, 1.f, 1.f);
	if (result != FMOD_OK) {
		std::cout << "FMOD error! " << result << std::endl;
		return;
	}

	int driver{ 0 };
	result = _system->getNumDrivers(&driver);

	if (result != FMOD_OK)
	{
		std::cout << "No sound card detected!" << result << std::endl;
	}
}

void AudioManager::Update()
{
}

void AudioManager::Destory()
{
	_system->release();
}

bool AudioManager::CreateGroup(std::string const& name, FMOD::ChannelGroup * channel)
{
	FMOD_RESULT res = _system->createChannelGroup(name.c_str(), &channel);
	if (res != FMOD_OK) {
		// throw some error
		return false;
	}
	return true;
}

bool AudioManager::LoadAudioClip(std::string const& filename, FMOD::Sound * clip, bool loadToMemory)
{
	FMOD_RESULT res;
	if (loadToMemory)
		res = _system->createSound(filename.c_str(), FMOD_HARDWARE | FMOD_3D | FMOD_LOOP_NORMAL, 0, &clip);
	else
		res = _system->createStream(filename.c_str(), FMOD_HARDWARE | FMOD_3D | FMOD_LOOP_NORMAL, 0, &clip);
	if (res != FMOD_OK) {
		return false;
	}
	return true;
}

