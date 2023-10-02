#pragma once

#include <string>

#include <generic/RecordIfc.h>

namespace sbd::impl {
	class CarRecord : public sbd::basic::RecordIfc<std::string> {
	public:
		CarRecord() :RecordIfc("") {};
		CarRecord(const std::string& value) : RecordIfc(value) {};
	};
}
