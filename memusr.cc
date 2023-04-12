#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <iomanip>
#include <fstream>

#include <boost/program_options.hpp>
#include "parser.h"

namespace po = boost::program_options;

const size_t DEFAULT_MEM_SIZE = 1 * 2^30; // 1GB
const size_t DEFAULT_INTERVAL = 100; // 100ns

std::default_random_engine generator;

int main(int argc, char** argv) {
    po::options_description desc("Program options");
    desc.add_options()
        ("msize", po::value<std::string>(), "Amount of memory to allocate.")
        ("interval", po::value<size_t>(), "Interval of accessing the allocated memory, in nanoseconds.")
        ("report", po::value<size_t>(), "Interval for printing progress.")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

    size_t msize = vm.count("msize") ? parse_human_readable(vm["msize"].as<std::string>()) : DEFAULT_MEM_SIZE;
    size_t time_ns = vm.count("interval") ? vm["interval"].as<size_t>() : DEFAULT_INTERVAL;
    size_t report_interval = vm.count("report") ? vm["report"].as<size_t>() : 10000;

    std::cout << "Allocating " << msize << " bytes of memory." << std::endl;

    volatile unsigned char *bytes = (unsigned char*) malloc(msize);

    std::uniform_int_distribution<size_t> address(0, msize-1);
    std::uniform_int_distribution<uint8_t> data(0, 255);

    std::cout << "Memory has been allocated, executing random memory access." << std::endl;
    std::cout.flush();
    
    unsigned long itercount = 0;

    while(true) {
        bytes[address(generator)] = data(generator);

        itercount += 1;

        if (itercount % 10000 == 0) {
            std::cout << std::setw(20) << itercount << " iterations executed." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::duration<size_t, std::nano>(time_ns));
    }
}