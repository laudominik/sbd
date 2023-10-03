#include <gtest/gtest.h>

#include <generic/Tape.h>
#include <impl/Measurement.h>

using namespace sbd::impl::measurement;

TEST(Perf1, testCase1){
	MeasurementReport report("test1");
	{
		Measurement meas(report);
	}

}