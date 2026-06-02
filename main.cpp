#include <iostream>
#include "Character.h"
#include "Station.h"
#include "SimulationEngine.h"
#include "WorldLoader.h"
#include "ReportGenerator.h"

using namespace std;

int main() {
    WorldLoader worldLoader;
    ReportGenerator reportGenerator;
    auto station= new Station("Space Program Debugger");
    auto* character= new Character("Player", 100, 100, 10);
    int escapeRoomId = 3;
    auto* engine = new SimulationEngine(station, character, 10, escapeRoomId);
    engine->run();
    reportGenerator.generateReport(engine->getSummary(), "final_report.txt");
    delete engine;
    delete character;
    delete station;
    return 0;
}