//
// Created by Jose on 30/5/2026.
//

#include "ReportGenerator.h"
#include <fstream>
#include <stdexcept>
#include "SimulationEngine.h"

void ReportGenerator::generateReport(const SimulationSummary& summary, const std::string& outputPath) {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open report output file: " + outputPath);
    }

    out << "FINAL REPORT" << std::endl;
    out << "------uwu-------" << std::endl;
    out << "Turns taken: " << summary.turnsTaken << std::endl;
    out << "Success: " << (summary.success ? "Yes" : "No") << std::endl;
    out << "Final state: " << summary.finalState << std::endl;
}
