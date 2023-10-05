#include "CarLoader.h"

#include <fstream>
#include <iostream>
#include <random>
#include <array>

#include <util/Constants.h>

namespace {
	/*
		Ask: should the generator be improved?
		for now: just 7 random characters
		proposal: 2 alphabetic + 5 alphanumeric
	*/
	std::string generateCarNumber() {
		static constexpr auto regLen = 7u;
		static const char charset[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		std::string builder;
		builder.reserve(regLen);
		for (auto i = 0u; i < regLen; i++) {
			builder += charset[std::rand() % (sizeof(charset)-1)];
		}
		return builder;
	}
}


namespace sbd::impl::carloader {
	std::unique_ptr<CarTape> fromFile(const std::string& filename){
        auto tape = std::make_unique<CarTape>(constants::MAIN_TAPE_NAME, std::ios::out);
        std::ifstream file(filename);
        if(!file.good()){
            return nullptr;
        }

        do {
            std::string carNumber;
            file >> carNumber;
            tape->addRecord(carNumber);
        } while(!file.eof());

        file.close();
		return tape;
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
		auto tape = std::make_unique<CarTape>(constants::MAIN_TAPE_NAME, std::ios::out);
		for (auto i = 0u; i < n; i++) {
			tape->addRecord(CarRecord(generateCarNumber()));
		}
		tape->reset(std::ios::in);
		return tape;
	}
}
