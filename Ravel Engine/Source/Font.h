#pragma once

#include <map>
#include <iostream>
#include <iterator>
#include <fstream>

#include "System.h"

#include "Factory.h"
#include "MemoryManager.h"

class FontSystem : public System {
public:
	struct font {
		float sz, sy, x, y, l, h, _x, _y;
		size_t sampleid;
	};

private:
	
	std::map <char, font> samples;
	std::map <size_t, std::map<char, font>> fontdb;
	std::map <std::string, size_t> fonts;

public:
	FontSystem();
	virtual ~FontSystem();
	virtual void Init();
	virtual void Update();
	void Quit();

	void AddFont(std::string const& filename, std::string const& identifier);
	font FetchFont(std::string const& font, char letter);
	
};

FontSystem* GetFontManager();