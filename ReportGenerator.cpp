//
// Created by Jose on 30/5/2026.
//

#include "ReportGenerator.h"
#include <fstream>
#include <stdexcept>
#include "SimulationEngine.h"
#include <ctime>

void ReportGenerator::generateReport(const SimulationSummary& summary, const std::string& outputPath) {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open report output file: " + outputPath);
    }

    const std::time_t now = std::time(nullptr);

    out << "----------------------------------------" << std::endl;
    out << "           FINAL REPORT" << std::endl;
    out << "------------------uwu-------------------" << std::endl;
    out << "\nGenerated at: " << std::asctime(std::localtime(&now));
    out << "Turns taken: " << summary.turnsTaken << std::endl;
    out << "Result: " << (summary.success ? "Success" : "Failure") << std::endl;
    out << "Final state: " << summary.finalState << std::endl;
    out << std::endl;
    out << "========================================" << std::endl;
    out << "          SIMULATION LOG" << std::endl;
    out << "========================================" << std::endl;
    for (const auto& event : summary.eventLog) {
        out << "  " << event << std::endl;
    }
    out << "========================================" << std::endl;
}
