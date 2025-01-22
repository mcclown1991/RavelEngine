#pragma once
#include "RavelEngine.h"
#include "fmod.hpp"

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	void Init();
	void Update();
	void Destory();

	bool CreateGroup(std::string const& name, FMOD::ChannelGroup* channel);
	bool LoadAudioClip(std::string const& filename, FMOD::Sound* clip, bool loadToMemory = false);

private:
	FMOD::System* _system;
};

AudioManager* AudioManagement();