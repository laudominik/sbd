#pragma once

#include <utility>

#include <generic/Tape.h>
#include <util/Constants.h>

namespace {
	template<typename RECORD_T>
	void distribute(sbd::basic::Tape<RECORD_T>& tape, sbd::basic::Tape<RECORD_T>& temp1, sbd::basic::Tape<RECORD_T>& temp2) {
		tape.reset(std::ios::in);
		temp1.reset(std::ios::out);
		temp2.reset(std::ios::out);
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
	}

	// @returns true if it's a single serie
	template<typename RECORD_T>
	bool handleEndOfRun(sbd::basic::Tape<RECORD_T>& destination, sbd::basic::Tape<RECORD_T>& source, bool appendRest = false) {
		if (source.isAtEnd()) return true;
		bool singleSerie = true;
		RECORD_T lastRecord = source.currentRecord();
		while (!source.isAtEnd() && (source.currentRecord() >= lastRecord || appendRest)){
			singleSerie = singleSerie && source.currentRecord() >= lastRecord;
			lastRecord = source.currentRecord();
			destination.addRecord(source.nextRecord());
		}
		return singleSerie;
	}

	template<typename RECORD_T>
	bool merge(sbd::basic::Tape<RECORD_T>& out, sbd::basic::Tape<RECORD_T>& tape1, sbd::basic::Tape<RECORD_T>& tape2) {
		out.reset(std::ios::out);
		tape1.reset(std::ios::in);
		tape2.reset(std::ios::in);

		bool sorted{ true };

		RECORD_T lastRecord;
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
			auto record = tape1.currentRecord() < tape2.currentRecord() ? tape1.nextRecord() : tape2.nextRecord();
			if (record < lastRecord) {
				sorted = false;
			}
			out.addRecord(record);
			lastRecord = record;
		}
		// add rest of the tape that didn't finish
		if (!tape1.isAtEnd() && tape1.currentRecord() <= lastRecord) sorted = false;
		if (!tape2.isAtEnd() && tape2.currentRecord() <= lastRecord) sorted = false;
		return handleEndOfRun(out, tape1, true) && handleEndOfRun(out, tape2, true) && sorted;
	}
}

namespace sbd::sorting {
	template<typename RECORD_T>
	inline void mergesort(sbd::basic::Tape<RECORD_T>& tape) {
		sbd::basic::Tape<RECORD_T> temp1(constants::TEMP_TAPE_1_NAME, std::ios::out);
		sbd::basic::Tape<RECORD_T> temp2(constants::TEMP_TAPE_2_NAME, std::ios::out);
		bool sorted{ false };

		while (!sorted) {
			distribute(tape, temp1, temp2);
			sorted = merge(tape, temp1, temp2);
			time::phaseClock().tick();
		}
	}
}