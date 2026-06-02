#include <iostream>
#include "Character.h"
#include "Station.h"
#include "SimulationEngine.h"
#include "WorldLoader.h"
#include "ReportGenerator.h"

using namespace std;

int main() {
    /*WorldLoader worldLoader;
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
    return 0;*/

    try {
        Station* station = WorldLoader::loadStation(
            "rooms.txt",
            "items.txt",
            "threats.txt"
        );

        Character* character = new Character("Player", 100, 100, 10);
        SimulationEngine* engine = new SimulationEngine(station, character, 50, 4);
        engine->run();

        ReportGenerator::generateReport(engine->getSummary(), "final_report.txt");

        delete engine;
        delete character;
        delete station;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}