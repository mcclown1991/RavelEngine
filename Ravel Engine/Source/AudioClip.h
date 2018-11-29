#pragma once
#include "RavelObject.h"
#include "AudioManager.h"

class AudioClip : public RavelObject {
public:
	AudioClip();
	virtual ~AudioClip();
	virtual AudioClip* Clone() {
		return Memory()->alloc<AudioClip>();
	}

	virtual void LoadFromFile(std::string const& filename);
	virtual void OnDestory() { this->~AudioClip(); }

	void LoadAudioClip(std::string const& file, bool loadToMemory = false);

private:
	FMOD::Sound* _clip;
};