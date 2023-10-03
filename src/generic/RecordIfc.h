#pragma once

#include <cstdint>
#include <array>
#include <vector>

namespace sbd::basic {
	template<typename T>
	class RecordIfc {
	public:
		RecordIfc(T t) : value(t) {}

		virtual std::vector<uint8_t> serialize() const { return {}; };
		bool operator>(const RecordIfc<T>& other) { return value > other.value; }
		bool operator>=(const RecordIfc<T>& other) { return value >= other.value; }
		bool operator==(const RecordIfc<T>& other) { return value == other.value; }
		bool operator<(const RecordIfc<T>& other) { return value < other.value; }
		bool operator<=(const RecordIfc<T>& other) { return value <= other.value; }

		T getValue() { return value; }

	protected:
		T value;
	};
}