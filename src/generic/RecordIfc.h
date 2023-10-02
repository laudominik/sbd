#pragma once

#include <cstdint>
#include <array>
#include <vector>

namespace sbd::basic {
	class RecordIfc {
	public:
		virtual std::vector<uint8_t> serialize() { return {}; };
		virtual RecordIfc deserialize() { return {}; };
	};
}