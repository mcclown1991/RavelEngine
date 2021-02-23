#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

class RavelLogger {
public :
	RavelLogger();
	~RavelLogger();

	void StartLogger();
	void StopLogger();
	void DebugLog(std::string_view log);

private:
	std::ofstream logWriter;
};

RavelLogger* RLogger();