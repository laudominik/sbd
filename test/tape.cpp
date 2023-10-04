#include <gtest/gtest.h>

#include <generic/Tape.h>
#include <impl/CarTape.h>
#include <time/ReadClock.h>
#include <time/WriteClock.h>

using namespace sbd;

void write() {
	impl::CarTape tape(constants::MAIN_TAPE_NAME, std::ios::out);
	tape.addRecord(impl::CarRecord("ABI"));
	tape.addRecord(impl::CarRecord("CHYYY"));
	tape.addRecord(impl::CarRecord("XDD"));
	tape.addRecord(impl::CarRecord("POGG"));
	tape.addRecord(impl::CarRecord("UWU"));
	tape.addRecord(impl::CarRecord("KIWI"));
	tape.addRecord(impl::CarRecord("POMELO"));
	tape.addRecord(impl::CarRecord("GRANAT"));
	tape.addRecord(impl::CarRecord("GRUSZKA"));
	tape.addRecord(impl::CarRecord("JAPKO"));
	tape.addRecord(impl::CarRecord("JABLKO"));
	tape.addRecord(impl::CarRecord("DYNIA"));
	tape.addRecord(impl::CarRecord("DYNKA"));
}

void read() {
	impl::CarTape tape(constants::MAIN_TAPE_NAME, std::ios::in);
	auto rec1 = tape.currentRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
	tape.nextRecord();
}

TEST(Tape, testWriting) {
	write();
	EXPECT_EQ(time::getWriteClock().get(), 2);
}

TEST(Tape, testReading) {
	write();
	read();
	EXPECT_EQ(time::getReadClock().get(), 2);
}

