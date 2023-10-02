#pragma once

#include <string>

#include <generic/RecordIfc.h>

namespace sbd::impl {
	class CarRecord : public sbd::basic::RecordIfc {
	public:
		std::string value;

		CarRecord(std::string value) :value(value) {};
		CarRecord() = default;

		virtual std::vector<uint8_t> serialize() override { return {}; };
		virtual RecordIfc deserialize() override { return {}; };
		bool operator>(const CarRecord& other) { return value > other.value; }
		bool operator>=(const CarRecord& other) { return value >= other.value; }
		bool operator==(const CarRecord& other) { return value == other.value; }
		bool operator<(const CarRecord& other) { return value < other.value; }
		bool operator<=(const CarRecord& other) { return value <= other.value; }
	};

}
