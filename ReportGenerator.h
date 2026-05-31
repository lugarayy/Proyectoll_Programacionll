//
// Created by Jose on 30/5/2026.
//

#ifndef PROYECTOLL_PROGRAMACIONLL_REPORTGENERATOR_H
#define PROYECTOLL_PROGRAMACIONLL_REPORTGENERATOR_H
#include <string>

struct SimulationSummary;
class ReportGenerator {
public:
    ReportGenerator() = default;
    ~ReportGenerator() = default;
    static void generateReport(const SimulationSummary& summary, const std::string& outputPath = "final_report.txt");
};


#endif //PROYECTOLL_PROGRAMACIONLL_REPORTGENERATOR_H