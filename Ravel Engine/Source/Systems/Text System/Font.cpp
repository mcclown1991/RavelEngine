#include "Font.h"
#include "RavelEngine.h"

FontSystem::FontSystem() : System()
{
}

FontSystem::~FontSystem()
{
}

void FontSystem::Init()
{
}

void FontSystem::Update()
{
}

void FontSystem::Quit()
{
	samples.clear();
	fontdb.clear();
	fonts.clear();
}

void FontSystem::AddFont(std::string const & filename, std::string const& identifier)
{
	unsigned int sampleid{};
	GetGraphicsManager()->Renderer()->CreateTexture(RavelEngine::getGameDataPath().data() + filename + ".png", sampleid);
	size_t id = HASH(identifier);

	if (fonts.count(identifier) != 0) return;

	fonts[identifier] = id;
	
	//load meta data comes in id(u, v)
	std::ifstream file(RavelEngine::getGameDataPath().data() + filename + ".meta", std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Failed to open font meta file" << std::endl;
		return;
	}

	std::string size;
	size_t sz, sy;
	// file size
	getline(file, size);
	sz = std::stoi(size);
	getline(file, size);
	sy = std::stoi(size);


	std::string value;
	while (file) {
		// get char
		getline(file, value);
		std::cout << value << std::endl;
		
		// process line

		size_t pos{ 0 };
		char id{};
		font data;
		data.sampleid = sampleid;
		data.sz = sz;
		data.sy = sy;

		// find character
		pos = value.find_first_of("\"", pos);
		id = value[pos + 1];
		

		// find x
		size_t pos1{ 0 };
		pos1 = value.find_first_of(",", pos + 3);
		pos = value.find_first_of(",", pos1 + 1);
		//substr the interval
		std::string str = value.substr(pos1 + 1, pos - (pos1 + 1));
		data.x = std::stoi(str);

		// find y
		pos1 = value.find_first_of(",", ++pos);
		//substr the interval
		str = value.substr(pos, pos1 - pos);
		data.y = std::stoi(str);

		// find l
		pos = value.find_first_of(",", ++pos1);
		//substr the interval
		str = value.substr(pos1, pos - pos1);
		data.l = std::stoi(str);

		// find h
		pos1 = value.find_first_of(",", ++pos);
		//substr the interval
		str = value.substr(pos, pos1 - pos);
		data.h = std::stoi(str);

		// find _x
		pos = value.find_first_of(",", ++pos1);
		//substr the interval
		str = value.substr(pos1, pos - pos1);
		data._x = std::stoi(str);

		// find _y
		pos1 = value.find_first_of(",", ++pos);
		//substr the interval
		str = value.substr(pos, pos1 - pos);
		data._y = std::stoi(str);

		samples[id] = data;
	}
	fontdb[id] = samples;
}

FontSystem::font FontSystem::FetchFont(std::string const & font, char letter)
{
	return fontdb[HASH(font)][letter];
}

FontSystem * GetFontManager()
{
	static FontSystem s;
	return(&s);
}
