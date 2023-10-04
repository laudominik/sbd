#pragma once

#include <cstdint>
#include <list>
#include <string>
#include <fstream>
#include <filesystem>

#include <util/Constants.h>
#include <generic/RecordIfc.h>
#include <time/ReadClock.h>
#include <time/WriteClock.h>

namespace sbd::basic {

	template<typename RECORD_T>
	class Tape {

	public:
		Tape(const std::string& filename, std::ios_base::openmode mode):mode(mode), filename(filename) {
			if (mode != std::ios::in && mode != std::ios::out) {
				throw std::runtime_error("[ERROR] unsupported file mode");
			}
			currentPage.reserve(recordCount);
			openFile();
		}

		Tape(const Tape&) = delete;
		Tape& operator=(const Tape&) = delete;
		Tape(Tape&&) = delete;
		Tape& operator=(Tape&&) = delete;

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
			lazyLoadPage();
			if (pageEnd()) {
				resetPagePtr();
				loadPage();
			}

			return currentPage[pageIndex++];
		}

		RECORD_T currentRecord() {
			readModeCheck();
			lazyLoadPage();
			if (pageEnd()) {
				resetPagePtr();
				loadPage();
			}
			return currentPage[pageIndex];
		}

		bool isAtEnd() const {
			readModeCheck();
			//bool eof = file.eof();
			return readFileBytes == fileSizeBytes && pageEnd();
		}

		void reset(std::ios_base::openmode mode_) {
			closeFile();
			mode = mode_;
			readFileBytes = 0u;
			resetPagePtr();
			openFile();
		}

		~Tape() {
			closeFile();
		}
	private:
		std::vector<RECORD_T> currentPage;
		std::ios_base::openmode mode;
		uint64_t pageIndex{};
		std::fstream file;
		std::string filename;
		uint64_t fileSizeBytes{};
		uint64_t readFileBytes{};
		bool firstPageLoaded{ false };
		static constexpr auto recordCount = constants::PAGE_SIZE / constants::RECORD_SIZE;

		void closeFile() {
			if (mode == std::ios::out && pageIndex != 0) {
				savePage();
			}
			if (file.is_open()) {
				file.close();
			}
		}

		void lazyLoadPage() {
			if (firstPageLoaded) {
				return;
			}
			loadPage();
			firstPageLoaded = true;
		}

		void openFile() {
			file.open(filename, mode);
			if (!file.good()) {
				throw std::runtime_error("[ERROR] unable to open file");
			}
		/*	if (mode == std::ios::in) {
				loadPage();
			}*/
			fileSizeBytes = std::filesystem::file_size(filename);
		}

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
			readFileBytes += readBytes;
		}
	};
}