cmake_minimum_required(VERSION 3.16)
project(VillageSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

file(GLOB MODEL_SRC "src/model/*.cpp")
file(GLOB VIEW_SRC "src/view/*.cpp")
file(GLOB CONTROLLER_SRC "src/controller/*.cpp")

add_executable(${PROJECT_NAME} 
    src/main.cpp ${MODEL_SRC} ${VIEW_SRC} ${CONTROLLER_SRC}
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE src/model src/view src/controller)
