cmake_minimum_required(VERSION 3.22)

project(CellularAutomata)

set(CMAKE_TOOLCHAIN_FILE
  "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(SDL2 CONFIG REQUIRED)

set(SOURCE_FILES ./Source_Files/Automata.cpp ./Source_Files/main.cpp ./Source_Files/TerminalAutomata.cpp)

add_executable(CellularAutomata ${SOURCE_FILES})
# set_target_properties(CellularAutomata PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
target_include_directories(
  CellularAutomata PUBLIC "${PROJECT_BINARY_DIR}"
                      "${PROJECT_SOURCE_DIR}/Source_Files/"
                      "${PROJECT_SOURCE_DIR}/Header_Files/")

target_link_libraries(
  CellularAutomata PRIVATE SDL2
  )
