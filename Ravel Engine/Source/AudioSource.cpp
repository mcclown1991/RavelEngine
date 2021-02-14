#include "AudioSource.h"

AudioSource::AudioSource() : RavelBehaviour(), _Clip(nullptr), _Mixer(nullptr) {
}

AudioSource::~AudioSource() {
}

void AudioSource::LoadFromFile(std::string const & filename) {
}

void AudioSource::OnDestory() {
	this->~AudioSource();
}