#include "AudioClip.h"

AudioClip::AudioClip() : RavelObject(), _clip(nullptr) {
}

AudioClip::~AudioClip() {
	_clip->release();
}



void AudioClip::LoadFromFile(std::string const & filename) {
}

void AudioClip::OnDestory() {
	this->~AudioClip();
}

void AudioClip::LoadAudioClip(std::string const & file, bool loadToMemory) {
	AudioManagement()->LoadAudioClip(file, _clip, loadToMemory);
}
