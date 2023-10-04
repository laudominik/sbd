#include <fstream>
#include <iostream>

#include <generic/RecordIfc.h>
#include <generic/Tape.h>
#include <impl/CarRecord.h>
#include <impl/CarTape.h>
#include <sorting/mergesort.h>
#include <impl/CarLoader.h>

using namespace sbd;
/*
TODO:
- performance tests
- write file contents after each iter
*/

void cli();

int main(){
	cli();
	//auto& tape = impl::carloader::fromCli();
	//impl::CarTape tape(constants::MAIN_TAPE_NAME, std::ios::out);
	
	//tape.addRecord(impl::CarRecord("ABI"));
	//tape.addRecord(impl::CarRecord("CHYYY"));
	//tape.addRecord(impl::CarRecord("XDD"));
	//tape.addRecord(impl::CarRecord("POGG"));
	//tape.addRecord(impl::CarRecord("UWU"));
	//tape.addRecord(impl::CarRecord("KIWI"));
	//tape.addRecord(impl::CarRecord("POMELO"));
	//tape.addRecord(impl::CarRecord("GRANAT"));
	//tape.addRecord(impl::CarRecord("GRUSZKA"));
	//tape.addRecord(impl::CarRecord("JAPKO"));
	//tape.addRecord(impl::CarRecord("JABLKO"));
	//tape.addRecord(impl::CarRecord("DYNIA"));
	//tape.addRecord(impl::CarRecord("DYNKA"));
	//sorting::mergesort(tape);	
}

void cli() {
	std::string command;
	while (true) {
		std::cout << std::endl << "input command: " << std::endl;
		std::cin >> command;
		if (command == "exit") {
			break;
		} else if (command == "manual") {
			sorting::mergesort(*impl::carloader::fromCli());
		} else if (command == "random") {
			uint64_t records;
			std::cout << "number of records to generate: ";
			std::cin >> records;
			sorting::mergesort(*impl::carloader::fromGenerator(records));
		} else if (command == "file") {
			sorting::mergesort(*impl::carloader::fromFile("aaa"));
		} else if (command == "help") {
			std::cout << "available commands:" << std::endl
				<< "manual - generate tape from user input" << std::endl
				<< "random - generate tape randomly" << std::endl
				<< "file - generate tape from file" << std::endl
				<< "exit - exit" << std::endl;
		}
		else {
			std::cout << "type help" << std::endl;
		}
	}
}
