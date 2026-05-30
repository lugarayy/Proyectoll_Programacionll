//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_LOGGER_H
#define PROYECTOLL_PROGRAMACIONLL_LOGGER_H
//#include "ReportGenerator.h"
#include <string>

class Logger {
public:
    void log(const  std::string& message);
    static Logger& getInstance();
private:
    Logger();
};


#endif //PROYECTOLL_PROGRAMACIONLL_LOGGER_H