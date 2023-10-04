#pragma once

#include <string>
#include <algorithm>

#include <generic/RecordIfc.h>

namespace sbd::impl {
	class CarRecord : public sbd::basic::RecordIfc<std::string> {
	public:
		std::vector<uint8_t> serialize() const override { 
			std::vector<uint8_t> bytes;
			bytes.reserve(constants::RECORD_SIZE);
			std::transform(value.begin(), value.end(), std::back_inserter(bytes), [](const char& c) {
				return static_cast<uint8_t>(c);
			});
			addPadding(bytes);
			return bytes; 
		}

		static CarRecord deserialize(std::vector<uint8_t>& bytes, uint64_t offset) {
			return CarRecord(std::string(bytes.begin() + offset, bytes.begin() + offset + constants::RECORD_SIZE));
		}
		CarRecord() :RecordIfc("") {};
		CarRecord(const std::string& value) : RecordIfc(value) {};
	private:
		void addPadding(std::vector<uint8_t>& bytes) const {
			while (bytes.size() != constants::RECORD_SIZE) {
				bytes.push_back(0);
			}
		}
	};
}
