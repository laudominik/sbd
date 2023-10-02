#pragma once

#include <cstdint>
#include <list>
#include <string>

#include <util/Constants.h>
#include <generic/RecordIfc.h>

namespace sbd::basic {

	template<typename RECORD_T>
	class Tape {

	public:
		Tape(const std::string& filename) {
			// open file
		}

		void addRecord(const RECORD_T& record) {
			// TODO: should check for the end of the page and save the previous page if it overflows
			currentPage.push_back(record);
			savePage();
		}

		RECORD_T nextRecord() {
			// TODO: should check for the end of the page, if so, load new page 
			return currentPage[pageIndex++];
		}

		RECORD_T currentRecord() const {
			return currentPage[pageIndex];
		}

		bool isAtEnd() const {
			// TODO: should check for the EOF
			return pageIndex == currentPage.size();
		}

		~Tape() {
			// close file
		}
	private:
		std::vector<RECORD_T> currentPage;
		uint64_t pageIndex{};
		uint64_t reads{};

		void savePage() {
			// TODO: should append the current page to file
			for (const auto& record : currentPage) {
				//record.serialize();
			}
		}

		void loadPage() {
			// should load the next PAGE_SIZE bytes from file
			// if the file doesn't contain PAGE_SIZE bytes, then it should load as much as it can 
			const auto recordsCount = constants::PAGE_SIZE / constants::RECORD_SIZE;
			for (auto i = 0u; i < recordsCount; i++) {
				
			}
		}
	};
}