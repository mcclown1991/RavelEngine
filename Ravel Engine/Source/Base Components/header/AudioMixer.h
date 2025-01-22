#pragma once
#include <vector>
#include "RavelBehaviour.h"
#include "AudioManager.h"
#include "AudioClip.h"
#include "AudioSource.h"
#include <fmod.hpp>

class AudioMixer : public RavelBehaviour {
public:
	AudioMixer();
	virtual ~AudioMixer();
	virtual AudioMixer* Clone() {
		return Memory()->alloc<AudioMixer>();
	}

	virtual void LoadFromFile(std::string const& filename);
	virtual void OnDestory();

	unsigned CreateGroup(std::string const& name);
private:
	FMOD::ChannelGroup* _Master;
	std::vector<FMOD::ChannelGroup*> _Channels;
};