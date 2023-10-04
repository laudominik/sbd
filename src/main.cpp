#include <fstream>
#include <iostream>

#include <generic/RecordIfc.h>
#include <generic/Tape.h>
#include <impl/CarRecord.h>
#include <impl/CarTape.h>
#include <sorting/mergesort.h>
#include <impl/CarLoader.h>
#include <time/DiskClocks.h>
#include <time/Measurement.h>

using namespace sbd;
/*
TODO:
- performance tests
- write file contents after each iter
- test file
*/

void cli();

int main(){
	cli();
}

void runSort(impl::CarTape& tape) {
	time::Measurement meas(std::cout);
	sorting::mergesort(tape);
}

void cli() {
	std::string command;
	auto seed = std::time(0);
	std::srand(seed);
	std::cout << "File sorter v1.0" << std::endl;
	std::cout << "Dominik Lau 188697" << std::endl;
	std::cout << "[DEBUG] seed: " << seed << std::endl;
	std::srand(std::time(0));
	while (true) {
		std::cout << std::endl << "input command: " << std::endl;
		std::cin >> command;
		if (command == "exit") {
			break;
		} else if (command == "manual") {
			runSort(*impl::carloader::fromCli());
		} else if (command == "random") {
			uint64_t records;
			std::cin >> records;
			runSort(*impl::carloader::fromGenerator(records));			
		} else if (command == "file") {
			runSort(*impl::carloader::fromFile("aaa"));
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
