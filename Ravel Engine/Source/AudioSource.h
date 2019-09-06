#pragma once
#include "RavelBehaviour.h"

class AudioClip;
class AudioMixer;
class AudioSource : public RavelBehaviour {
public:
	AudioSource();
	virtual ~AudioSource();
	virtual AudioSource* Clone() {
		return Memory()->alloc<AudioSource>();
	}

	virtual void LoadFromFile(std::string const& filename);
	virtual void OnDestory() { 
		Memory()->dealloc(this); 
		this->~AudioSource();
	}

	AudioClip* _Clip;
	AudioMixer* _Mixer;
};