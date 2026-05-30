cmake_minimum_required(VERSION 4.2)
project(Proyectoll_Programacionll)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyectoll_Programacionll main.cpp
        Room.cpp
        Room.h
        Item.cpp
        Item.h
        Station.cpp
        Station.h
        OxygenTank.cpp
        OxygenTank.h
        RepairKit.cpp
        RepairKit.h
        KeyCard.cpp
        KeyCard.h)
