#pragma once

#include <cstdint>
#include <list>
#include <string>
#include <fstream>

#include <util/Constants.h>
#include <generic/RecordIfc.h>
#include <clock/ReadClock.h>
#include <clock/WriteClock.h>

namespace sbd::basic {

	template<typename RECORD_T>
	class Tape {

	public:
		Tape(const std::string& filename, std::ios_base::openmode mode):mode(mode) {
			if (mode != std::ios::in && mode != std::ios::out) {
				throw std::runtime_error("[ERROR] unsupported file mode");
			}
			file.open(filename, mode);
			if (!file.good()) {
				throw std::runtime_error("[ERROR] unable to open file");
			}
 			currentPage.reserve(recordCount);
		}

		void addRecord(const RECORD_T& record) {
			writeModeCheck();

			if (fullPage()) {
				savePage();
				nextPage();
			};

			currentPage.push_back(record);
			pageIndex++;
		}

		RECORD_T nextRecord() {
			readModeCheck();
			// TODO: should check for the end of the page, if so, load new page 
			if (pageEnd()) {
				nextPage();
				loadPage();
			}
			return currentPage[pageIndex++];
		}

		RECORD_T currentRecord() const {
			readModeCheck();
			return currentPage[pageIndex];
		}

		bool isAtEnd() const {
			return file.eof();
		}

		~Tape() {
			if (mode == std::ios::out) {
				savePage();
			}
			file.close();
		}
	private:
		std::vector<RECORD_T> currentPage;
		std::ios_base::openmode mode;
		uint64_t pageIndex{};
		std::fstream file;
		static constexpr auto recordCount = constants::PAGE_SIZE / constants::RECORD_SIZE;

		bool fullPage() {
			return pageIndex >= recordCount;
		}

		bool pageEnd() {
			return fullPage();
		}

		void writeModeCheck() const {
			if (mode != std::ios::out) {
				throw std::runtime_error("[ERROR] trying to write page in read-only mode");
			}
		}

		void readModeCheck() const {
			if (mode != std::ios::in) {
				throw std::runtime_error("[ERROR] trying to read page in write-only mode");
			}
		}

		void savePage() {
			writeModeCheck();
			if (currentPage.empty()) return;
			std::vector<uint8_t> pageSerialized;
			for (const auto& record : currentPage) {
				auto serial = record.serialize();
				pageSerialized.insert(pageSerialized.end(), serial.begin(), serial.end());
			}
			std::copy(pageSerialized.begin(), pageSerialized.end(), std::ostream_iterator<uint8_t>(file));
			time::getWriteClock().tick();
			file.flush();
		}

		void nextPage() {
			pageIndex = 0;
			currentPage.clear();
		}

		void loadPage() {
			// should load the next PAGE_SIZE bytes from file
			// if the file doesn't contain PAGE_SIZE bytes, then it should load as much as it can
			for (auto i = 0u; i < recordCount; i++) {
				
			}
		}
	};
}