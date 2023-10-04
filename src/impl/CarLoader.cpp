#include "CarLoader.h"

#include <fstream>
#include <iostream>
#include <random>

#include <util/Constants.h>

namespace {
	std::string generateCarNumber() {
		static constexpr auto regLen = 7u;
		std::string builder; // TODO: change
		for (auto i = 0u; i < regLen; i++) {
			
		}
		return builder;
	}
}


namespace sbd::impl::carloader {
	std::unique_ptr<CarTape> fromFile(const std::string& filename){
		return std::make_unique<CarTape>(constants::MAIN_TAPE_NAME, std::ios::in);
	}

	std::unique_ptr<CarTape> fromCli(){
		auto tape = std::make_unique<CarTape>(constants::MAIN_TAPE_NAME, std::ios::out);
		bool end{ false };

		while (!end) {
			std::string carNumber;

			std::cout << "car number (type exit to end input): ";
			std::cin >> carNumber;
			std::cout << std::endl;

			if (carNumber == "exit") {
				end = true;
				continue;
			}
			tape->addRecord(CarRecord(carNumber));
		}
		return tape;
	}

	std::unique_ptr<CarTape> fromGenerator(uint64_t n){
		srand(0); // deterministic for now
		auto tape = std::make_unique<CarTape>(constants::MAIN_TAPE_NAME, std::ios::out);
		for (auto i = 0u; i < n; i++) {
			tape->addRecord(CarRecord(generateCarNumber()));
		}
		return tape;
	}
}
