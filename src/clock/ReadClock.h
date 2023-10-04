#pragma once

#include "Clock.h"

namespace sbd::time {
	inline Clock& getReadClock() {
		static Clock clock;
		return clock;
	}
}