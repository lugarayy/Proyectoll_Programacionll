#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Station.h"
#include "SimulationEngine.h"
#include "WorldLoader.h"
#include "ReportGenerator.h"

using namespace std;

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    try {
        Station* station = WorldLoader::loadStation(
            "rooms.txt",
            "items.txt",
            "threats.txt"
        );
        station->printMap();
        auto* character = new Character("Player", 100, 100, 10);
        auto* engine = new SimulationEngine(station, character, 50, 4);
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