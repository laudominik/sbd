#pragma once

#include <cstdint>

namespace sbd::time {
	class Clock {
	public:
		void tick() { counter++; };
		uint64_t get() { return counter; };
	protected:
		uint64_t counter{0u};
	};
}