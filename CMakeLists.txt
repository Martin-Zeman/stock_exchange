# How to use:
# 1) Navigate to the build directory
# 2) Run "cmake .."
# 3) Run "make build" or "cmake --build . --config Release"
# 4) Optional: Run "make runtests" to start the units tests

cmake_minimum_required (VERSION 3.10.2)

project ("Market")

set (MARKET_VERSION_MAJOR 1)
set (MARKET_VERSION_MINOR 0)

set (CONFIG "Release")
set (COMMON_INCLUDES ${PROJECT_SOURCE_DIR})
set (GOOGLE_TEST_DIR ${PROJECT_SOURCE_DIR}/ext/googletest)

set(CMAKE_CXX_STANDARD 14)

message ("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message ("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

#----GOOGLETEST BUILD----
add_subdirectory(${GOOGLE_TEST_DIR})

#----INCLUDE DIRECTORIES----
include_directories (${COMMON_INCLUDES} ${GTEST_INCLUDE_DIRS})

#----SOURCES----
file (GLOB SOURCES "*.cpp")

#----LIBRARY CREATION----
add_library (${PROJECT_NAME}_lib ${SOURCES})

#----TESTING----
# Test each module separately
enable_testing()
add_subdirectory(test)

#----CUSTOM TARGET TO TRIGGER THE BUILD WITH A CMAKE COMMAND INSTEAD OF MAKE----
add_custom_target (build
    COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --config ${CONFIG}
    #WORKING_DIRECTORY unit_tests
	COMMENT "Running the build..."
	)

#----CUSTOM TARGET TO RUN THE UNIT TESTS----
add_custom_target (runtests
    COMMAND ${CMAKE_CTEST_COMMAND} --build-config ${CONFIG} --extra-verbose
    WORKING_DIRECTORY .
	COMMENT "Starting the unit tests..."
	)