# Space Station Survival — Adventure Simulation Engine

**Course:** EIF204 - Programming II  
**University:** Universidad Nacional de Costa Rica — Escuela de Informática  
**Team:** Lucia Garay Garcia and Jose Pablo Sanchez Ramirez 
**Period:** I Ciclo 2026  
**Due date:** June 11, 2026

---

## Simulation Description

An astronaut is stranded on an abandoned space station. The player character explores a network of rooms loaded from text files, encounters defective robots and oxygen leaks, collects items, and must reach the escape pod while carrying a KeyCard — before health or oxygen runs out.

Each run generates a **different map** using a randomized spanning tree algorithm, so no two playthroughs are the same. The simulation runs fully automatically with no user input required.

**Victory:** Reach the escape room (Room ID defined in `main.cpp`) while carrying a KeyCard.  
**Defeat:** Health or oxygen drops to 0, or the maximum turn limit is reached.

---

## Compilation

Requires **CMake 3.x** and a **C++20** compatible compiler (GCC or MinGW).

```bash
# Clone the repository
git clone https://github.com/lugarayy/Proyectoll_Programacionll.git
cd Proyectoll_Programacionll

# Build with CMake
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

Or open the project in **CLion** and use the default Debug build configuration.

---

## Execution

The input files must be in the same directory as the executable (`cmake-build-debug/`):

```
cmake-build-debug/
├── rooms.txt
├── items.txt
├── threats.txt
└── Proyectoll_Programacionll.exe
```

Run the executable:

```bash
./Proyectoll_Programacionll.exe
```

Output files are generated automatically in the same directory.

---

## Input File Format

All files use `;` as a delimiter. Lines starting with `#` are treated as comments.

**rooms.txt** — `id;name;oxygen;energy`
```
# Room definitions
1;Control Room;80;100
2;Engine Bay;50;60
3;Medical Bay;70;80
4;Escape Pod;90;100
```
> Note: room connections are randomized at startup and do not need to be defined in this file.

**items.txt** — `roomId;itemId;type;name;restore_or_accessLevel`
```
# Types: OxygenTank (restore=int), RepairKit (restore=int), KeyCard (accessLevel=string)
2;1;OxygenTank;Small Tank;30
3;2;RepairKit;Basic Kit;20
1;3;KeyCard;Security Card;A
```

**threats.txt** — `roomId;threatId;type;name;damage`
```
# Types: DefectiveRobot, OxygenLeak
2;1;DefectiveRobot;Broken Sentinel;15
4;2;OxygenLeak;Cracked Pipe;10
```

---

## Output Files

| File | Description |
|------|-------------|
| `simulation.log` | Full turn-by-turn event log written during the simulation |
| `final_report.txt` | Summary with result, turns taken, and full event history |

---

## Project Structure

```
Proyectoll_Programacionll/
│
├── Entity.h                  # Base class: id, name, getType() (virtual pure)
│
├── Item.h / Item.cpp         # Abstract item: use(Character&), getType()
├── OxygenTank.h/cpp          # Restores character oxygen
├── RepairKit.h/cpp           # Restores character health
├── KeyCard.h/cpp             # Victory condition item
│
├── Threat.h                  # Abstract threat: activate(Character&), getType()
├── DefectiveRobot.h/cpp      # Deals health damage to character
├── OxygenLeak.h/cpp          # Reduces character oxygen
│
├── Inventory.h               # Generic template container with capacity limit
├── Character.h/cpp           # Player: health, oxygen, Inventory<Item*>, currentRoom
│
├── Room.h/cpp                # Room with items, threats and connections
├── Station.h/cpp             # Collection of rooms, printMap(), iterators
│
├── WorldLoader.h/cpp         # Loads world from .txt files, randomizes connections
├── SimulationEngine.h/cpp    # Core simulation loop, combat, item usage, victory check
├── Logger.h/cpp              # Singleton: writes events to simulation.log
├── ReportGenerator.h/cpp     # Generates final_report.txt from SimulationSummary
│
├── main.cpp                  # Entry point
├── CMakeLists.txt
│
└── cmake-build-debug/
    ├── rooms.txt             # Input
    ├── items.txt             # Input
    ├── threats.txt           # Input
    ├── simulation.log        # Output (generated at runtime)
    └── final_report.txt      # Output (generated at runtime)
```

---

## Course Concepts Applied

### Object-Oriented Design
- `Entity` as a base class with `id`, `name`, and `getType()` virtual pure
- `Item` and `Threat` as abstract classes with pure virtual methods (`use()`, `activate()`)
- Concrete subclasses: `OxygenTank`, `RepairKit`, `KeyCard`, `DefectiveRobot`, `OxygenLeak`
- Clear separation of responsibilities: data loading, simulation logic, entities, and output

### Inheritance and Polymorphism
- `item->use(*character)` — each item applies its effect polymorphically
- `threat->activate(*character)` — each threat damages the character differently
- `Entity` hierarchy allows `Room` to hold `Item*` and `Threat*` generically

### Memory Management
- Manual memory management with `new` / `delete`
- Destructors in `Room` and `Station` free all owned pointers
- Copy constructors deleted in `Item` and `Room` where copying is unsafe (Rule of Three)

### Generic Programming (Templates)
- `Inventory<T>` is a custom template container used as `Inventory<Item*>` in `Character`
- Enforces a maximum capacity and throws exceptions when full or item not found

### Iterators
- `Inventory<T>` exposes `begin()` / `end()` using `typename std::vector<T>::iterator`
- `Station` exposes `begin()` / `end()` for range-based iteration over rooms
- Used in `SimulationEngine` to iterate over inventory items

### Operator Overloading
- `operator<<` overloaded in `Entity`, `Item`, `Room`, `Station`, `Inventory<T>`
- `operator==` overloaded in `Room` (compares by id)
- `operator<<` in `Inventory<T>` prints size and capacity

### File Handling
- `WorldLoader` reads three `.txt` files using `ifstream` with `;` delimiter parsing
- `Logger` writes events to `simulation.log` using `ofstream`
- `ReportGenerator` writes the final summary to `final_report.txt`
- All paths are relative — no absolute paths used

### Exception Handling
- `WorldLoader` throws `std::runtime_error` if a file cannot be opened
- `WorldLoader` throws if an invalid item or threat type is found
- `Inventory<T>` throws `std::runtime_error` when full or item not found
- All exceptions are caught in `main.cpp` with `try/catch`

### Design Patterns
- **Singleton** — `Logger`: only one instance exists throughout the program, created via `Logger::getInstance()`
- **Factory methods** — `WorldLoader::createItem()` and `WorldLoader::createThreat()` centralize object creation from file data, decoupling parsing logic from instantiation

### SOLID Principles
- **SRP** — each class has a single responsibility: `WorldLoader` loads data, `SimulationEngine` runs logic, `Logger` logs, `ReportGenerator` writes the report
- **OCP** — new item or threat types can be added by creating a new subclass and registering it in `createItem()` / `createThreat()` without modifying existing classes
- **ISP** — `Item` defines `use(Character&)` and `Threat` defines `activate(Character&)` separately; no class is forced to implement methods it does not need

---

## Notes

- Room connections are randomized at every run — the map changes each time.
- The character starts in a random room, never the escape room.
- All source code and internal comments are written in English.
- The project uses relative paths only.