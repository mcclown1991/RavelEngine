#include "AudioClip.h"

AudioClip::AudioClip()
{
}

AudioClip::~AudioClip()
{
	_clip->release();
}

void AudioClip::LoadFromFile(std::string const & filename)
{
}

void AudioClip::LoadAudioClip(std::string const & file, bool loadToMemory)
{
	AudioManagement()->LoadAudioClip(file, _clip, loadToMemory);
}
