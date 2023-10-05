#include <fstream>
#include <iostream>

#include <generic/RecordIfc.h>
#include <generic/Tape.h>
#include <impl/CarRecord.h>
#include <impl/CarTape.h>
#include <impl/CarLoader.h>
#include <time/DiskClocks.h>
#include <time/Measurement.h>
#include <sorting/runsort.h>

using namespace sbd;
/*
TODO:
- performance tests
- write file contents after each iter
*/

void cli();

int main(){
	cli();
}



void cli() {
	std::string command;
	auto seed = std::time(nullptr);
	std::srand(seed);
	std::cout << "File sorter v1.0" << std::endl;
	std::cout << "Dominik Lau 188697" << std::endl;
	std::cout << "[DEBUG] seed: " << seed << std::endl;
	while (true) {
		std::cout << std::endl << "input command: " << std::endl;
		std::cin >> command;
		if (command == "exit") {
			break;
		} else if (command == "manual") {
			sorting::runSort(*impl::carloader::fromCli(), std::cout);
		} else if (command == "random") {
			uint64_t records;
			std::cin >> records;
			sorting::runSort(*impl::carloader::fromGenerator(records), std::cout);
		} else if (command == "file") {
            std::string filename;
            std::cin >> filename;
            auto tape = impl::carloader::fromFile(filename);
            if(!tape) {
                std::cout << "[ERROR] file not found" << std::endl;
                continue;
            }
			sorting::runSort(*tape, std::cout);
		} else if (command == "help") {
			std::cout << "available commands:" << std::endl
				<< "manual - generate tape from user input" << std::endl
				<< "random <n> - generate tape with n random records" << std::endl
				<< "file - generate tape from file" << std::endl
				<< "exit - exit" << std::endl;
		}
		else {
			std::cout << "type help" << std::endl;
		}
	}
}
