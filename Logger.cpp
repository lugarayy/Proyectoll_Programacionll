//
// Created by Jose on 30/5/2026.
//
#include "Logger.h"
#include <iostream>

void Logger::log(const std::string &message) {
	if (logFile.is_open()) {
		logFile << message << std::endl;
	}
	std::cout << message << std::endl;
}

Logger & Logger::getInstance() {
	static Logger instance;
	return instance;
}

Logger::Logger() {
	logFile.open("simulation.log", std::ios::out);
	if (!logFile.is_open()) {
		std::cerr << "Warning: could not open simulation.log" << std::endl;
	}
}

Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}
