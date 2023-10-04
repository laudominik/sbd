#pragma once

#include "Clock.h"

namespace sbd::time {
	inline Clock& getPhasesClock() {
		static Clock clock;
		return clock;
	}
}