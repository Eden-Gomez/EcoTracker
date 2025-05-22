cmake_minimum_required(VERSION 3.28)
project(Eco_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Eco_Project src/main.cpp
        src/Core/UserProfile.cpp
        src/Core/UserProfile.h
        src/Core/EcoAction.cpp
        src/Core/EcoAction.h
        src/Core/TransportAction.cpp
        src/Core/TransportAction.h
        src/GUI/Dashboard.cpp
        src/GUI/Dashboard.h
        src/GUI/Menu.cpp
        src/GUI/Menu.h)
add_definitions(-DUNICODE -D_UNICODE)
