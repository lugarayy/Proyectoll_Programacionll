//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_LOGGER_H
#define PROYECTOLL_PROGRAMACIONLL_LOGGER_H
#include <string>
#include <fstream>

class Logger {
public:
    void log(const std::string& message);
    static Logger& getInstance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
private:
    Logger();
    ~Logger();

    std::ofstream logFile;
};


#endif //PROYECTOLL_PROGRAMACIONLL_LOGGER_H