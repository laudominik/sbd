#include <gtest/gtest.h>

#include <generic/Tape.h>
#include <sorting/mergesort.h>
#include <impl/CarTape.h>

TEST(Tape, testAdd) {
	sbd::impl::CarTape tape("data/file1.bin");
	sbd::sorting::mergesort(tape);
}