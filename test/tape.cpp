#include <gtest/gtest.h>

#include <generic/Tape.h>

TEST(Tape, testAdd) {
	sbd::basic::CarTape tape("data/file1.bin");

	sbd::sorting::mergesort(tape);
}