#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
#ifdef NET_PHYSICS_CLIENT
#undef LOGGER_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#ifdef NET_PHYSICS_SERVER
#include <iostream>
#endif /* NET_PHYSICS_SERVER */
#include <string>


enum Level {
	DEBUG_MSG,
	LOG_MSG,
	WARNING_MSG,
	ERROR_MSG,
	FATAL_MSG,
};
namespace NetPhysics {
	class Logger {
	public:

		Logger(
			Level level,
			std::string const& message,
			char const* file,
			char const* function,
			int line)
		{
			std::string levelMessage;
			switch (level) {
				case DEBUG_MSG: {
					levelMessage = "DEBUG";
					break;
				}
				case LOG_MSG: {
					levelMessage = "MESSAGE";
					break;
				}
				case WARNING_MSG: {
					levelMessage = "WARNING";
					break;
				}
				case ERROR_MSG: {
					levelMessage = "ERROR";
					break;
				}
				case FATAL_MSG: {
					levelMessage = "FATAL";
					break;
				}
			}
			std::string log = levelMessage + ": '" + message + "' | " + file + "::" + function + "::" + std::to_string(line);
#ifdef NET_PHYSICS_SERVER
			std::cout << log << std::endl;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			FString UELog = log.c_str();
			switch (level) {
				case DEBUG_MSG: {
					UE_LOG(LogTemp, Log, TEXT("%s"), *UELog);
					break;
				}
				case LOG_MSG: {
					UE_LOG(LogTemp, Log, TEXT("%s"), *UELog);
					break;
				}
				case WARNING_MSG: {
					UE_LOG(LogTemp, Warning, TEXT("%s"), *UELog);
					break;
				}
				case ERROR_MSG: {
					UE_LOG(LogTemp, Error, TEXT("%s"), *UELog);
					break;
				}
				case FATAL_MSG: {
					UE_LOG(LogTemp, Fatal, TEXT("%s"), *UELog);
					break;
				}
			}
#endif /* NET_PHYSICS_CLIENT */
		}
	};
}


#define LOG(level, string) Logger(level, string, __FILE__, __FUNCTION__, __LINE__)
#ifdef NET_PHYSICS_NDEBUG
#define DEBUG_LOG(level, string) do {} while(0);
#else
#define DEBUG_LOG LOG
#endif /* NDEBUG */
#endif /* LOGGER_H_INCLUDED */