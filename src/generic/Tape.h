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
			if (mode == std::ios::in) {
				loadPage();
			}
		}

		void addRecord(const RECORD_T& record) {
			writeModeCheck();

			if (fullPage()) {
				savePage();
				resetPagePtr();
			};

			currentPage.push_back(record);
			pageIndex++;
		}

		RECORD_T nextRecord() {
			readModeCheck();

			if (isAtEnd()) {
				throw std::runtime_error("[ERROR] index out of file range");
			}

			if (pageEnd()) {
				resetPagePtr();
				loadPage();
			}
			return currentPage[pageIndex++];
		}

		RECORD_T currentRecord() const {
			readModeCheck();
			return currentPage[pageIndex];
		}

		bool isAtEnd() const {
			readModeCheck();
			return file.eof() && pageEnd();
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

		bool pageEnd() const {
			return pageIndex >= currentPage.size();
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

		void resetPagePtr() {
			pageIndex = 0;
			currentPage.clear();
		}

		void loadPage() {
			if (!currentPage.empty()) {
				throw std::runtime_error("[ERROR] trying to read page when the previous one wasn't unloaded");
			}
			std::vector<uint8_t> pageSerialized(constants::PAGE_SIZE);
			file.read(reinterpret_cast<char*>(pageSerialized.data()), constants::PAGE_SIZE);
			auto readBytes = file.gcount();
			time::getReadClock().tick();
			auto readRecords = std::min(recordCount, readBytes / constants::RECORD_SIZE);
			for (auto i = 0u; i < readRecords; i++) {
				currentPage.push_back(RECORD_T::deserialize(pageSerialized, i * constants::RECORD_SIZE));
			}
		}
	};
}