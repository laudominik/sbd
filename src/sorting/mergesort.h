#pragma once

#include <utility>

#include <generic/Tape.h>


namespace {
	template<typename RECORD_T>
	std::pair<sbd::basic::Tape<RECORD_T>, sbd::basic::Tape<RECORD_T>> distribute(sbd::basic::Tape<RECORD_T>& tape) {
		sbd::basic::Tape<RECORD_T> temp1("temp1");
		sbd::basic::Tape<RECORD_T> temp2("temp2");

		bool appendToTemp1{ true };
		RECORD_T lastRecord;
		while (!tape.isAtEnd()) {
			auto record = tape.nextRecord();
			if (record < lastRecord) {
				appendToTemp1 = !appendToTemp1;
			}
			if (appendToTemp1) {
				temp1.addRecord(record);
			}
			else {
				temp2.addRecord(record);
			}
			lastRecord = record;
		}

		return std::make_pair(temp1, temp2);
	}

	template<typename RECORD_T>
	void handleEndOfRun(sbd::basic::Tape<RECORD_T>& destination, sbd::basic::Tape<RECORD_T>& source, bool appendRest = false) {
		if (source.isAtEnd()) return;
		RECORD_T lastRecord = source.currentRecord();
		while (!source.isAtEnd() && (source.currentRecord() >= lastRecord || appendRest)){
			lastRecord = source.currentRecord();
			destination.addRecord(source.nextRecord());
		}
	}

	template<typename RECORD_T>
	sbd::basic::Tape<RECORD_T> merge(sbd::basic::Tape<RECORD_T>& tape1, sbd::basic::Tape<RECORD_T>& tape2) {
		sbd::basic::Tape<RECORD_T> out("out");
		RECORD_T lastRecord1, lastRecord2;
		while (!tape1.isAtEnd() && !tape2.isAtEnd()) {
			bool isRun1Finished = tape1.currentRecord() < lastRecord1;
			bool isRun2Finished = tape2.currentRecord() < lastRecord2;
			if (isRun1Finished || isRun2Finished) {
				handleEndOfRun(out, isRun1Finished ? tape2 : tape1);
				lastRecord1 = {};
				lastRecord2 = {};
				continue;
			} 
			lastRecord1 = tape1.currentRecord();
			lastRecord2 = tape2.currentRecord();
			out.addRecord(tape1.currentRecord() < tape2.currentRecord() ? tape1.nextRecord() : tape2.nextRecord());
		}
		// add rest of the tape that didn't finish
		handleEndOfRun(out, tape1, true);
		handleEndOfRun(out, tape2, true);
		return out;
	}
}

namespace sbd::sorting {
	template<typename RECORD_T>
	inline void mergesort(sbd::basic::Tape<RECORD_T>& tape) {
		bool sorted{ false };

		while (true) {
			auto [tape1, tape2] = distribute(tape);
			if (tape1.isAtEnd()) {
				tape = tape2;
				return;
			}
			if (tape2.isAtEnd()) {
				tape = tape1;
				return;
			}
			tape = merge(tape1, tape2);
		}
	}
}