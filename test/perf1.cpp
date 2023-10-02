#include <gtest/gtest.h>

#include <generic/Tape.h>
#include <testutil/Measurement.h>

TEST(Perf1, testCase1){
	MeasurementReport report("test1");
	{
		Measurement meas(report);
	}

}