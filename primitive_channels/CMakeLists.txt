cmake_minimum_required (VERSION 2.8)

project (SystemCTutorial)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Require SystemC
find_package( SystemC )
if(SystemC_FOUND)
    include_directories(${SystemC_INCLUDE_DIRS})
    link_directories(${SystemC_LIBRARIES})
#    link_directories("/usr/local/lib")
else()
    message( FATAL_ERROR "SystemC library not found." )
endif()

set(SOURCES main.cpp fifo_if.h fifo.h producer.h consumer.h)

add_executable(SystemCTutorial ${SOURCES})

target_link_libraries(SystemCTutorial ${SystemC_LIBRARIES})

