cmake_minimum_required(VERSION 3.12)
project("imuldiv")

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.66.0 REQUIRED COMPONENTS program_options)

add_library(parser parser.cc parser.h)

set_source_files_properties(memuser.cc PROPERTIES COMPILE_FLAGS -Od)
add_executable(memusr memusr.cc parser.cc parser.h)

target_link_libraries(memusr PUBLIC parser)

# target_link_libraries(tcgen ${Boost_LIBRARIES})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(tcgen ${Boost_LIBRARY_DIRS})
    target_link_libraries(memusr PUBLIC ${Boost_LIBRARIES} Boost::program_options)
else()
    message(FATAL_ERROR "Boost::program options is not found. Use apt-get libboost-program-options-dev to get it.")
endif()