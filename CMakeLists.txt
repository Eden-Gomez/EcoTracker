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
        src/GUI/Menu.h
        src/Core/ActionLogger.cpp
        src/Core/ActionLogger.h
        src/Core/FoodChoice.cpp
        src/Core/FoodChoice.h
        src/Core/Achievement.cpp
        src/Core/Achievement.h
        src/Core/DailyChallenge.cpp
        src/Core/DailyChallenge.h)
add_definitions(-DUNICODE -D_UNICODE)
