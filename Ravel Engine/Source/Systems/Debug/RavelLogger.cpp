#include "RavelLogger.h"

RavelLogger* RLogger()
{
	static RavelLogger s;
	return(&s);
}

RavelLogger::RavelLogger() {

}

RavelLogger::~RavelLogger() {

}

void RavelLogger::StartLogger() {
	logWriter.open("DebugLog.log", std::ios::binary);
	logWriter << "";
	logWriter.close();
}

void RavelLogger::StopLogger() {

}

void RavelLogger::DebugLog(std::string_view log) {
	logWriter.open("DebugLog.log", std::ios::app | std::ios::binary);
	logWriter << log << std::endl;
	logWriter.close();
}