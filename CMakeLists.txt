CMake_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(runMain
        main.cpp
       	src/date.cpp
        src/task.cpp
        src/time.cpp
        src/UI.cpp
        src/debug.cpp

        # header/date.h
        # header/task.h
        # header/time.h
        # header/UI.h 
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test")

ADD_EXECUTABLE(runTest
        test/test.cpp
        src/date.cpp
        src/task.cpp
        src/time.cpp
        src/debug.cpp
        src/UI.cpp

)

TARGET_LINK_LIBRARIES(runTest gtest)
TARGET_COMPILE_DEFINITIONS(runTest PRIVATE gtest_disable_pthreads=ON)

