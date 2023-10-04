#include <fstream>

#include <generic/RecordIfc.h>
#include <generic/Tape.h>
#include <impl/CarRecord.h>
#include <impl/CarTape.h>
#include <sorting/mergesort.h>

using namespace sbd;
/*
TODO:
- fix mergesort
- generation
- performance tests
- cli
*/

int main(){
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
	//tape.addRecord(impl::CarRecord("JABLKO"));
	//tape.addRecord(impl::CarRecord("DYNIA"));
	//tape.addRecord(impl::CarRecord("DYNKA"));
	sorting::mergesort(tape);
	
}
