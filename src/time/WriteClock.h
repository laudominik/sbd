#pragma once

#include "Clock.h"

namespace sbd::time {
	inline Clock& getWriteClock() {
		static Clock clock;
		return clock;
	}
}