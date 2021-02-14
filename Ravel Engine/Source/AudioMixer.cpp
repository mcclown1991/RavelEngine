#include "AudioMixer.h"

AudioMixer::AudioMixer() : RavelBehaviour(), _Master(nullptr), _Channels(std::vector<FMOD::ChannelGroup*>()) {
	_Master = nullptr;
	AudioManagement()->CreateGroup("Master", _Master);
}

AudioMixer::~AudioMixer() {
	_Master->release();
	if(_Channels.size() != 0)
	for (FMOD::ChannelGroup* iter : _Channels) {
		iter->release();
	}
}

void AudioMixer::LoadFromFile(std::string const & filename) {
}

void AudioMixer::OnDestory() {
	this->~AudioMixer();
}

unsigned AudioMixer::CreateGroup(std::string const& name) {
	FMOD::ChannelGroup* channel = nullptr;
	if (AudioManagement()->CreateGroup(name, channel)) {
		_Channels.push_back(channel);
		return _Channels.size() - 1;
	}
	return -1;
}
