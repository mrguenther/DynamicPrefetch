#include <string> // Temporary

#include "mem/cache/prefetch/dynamic.hh"

/*
 * DynamicPrefetcher definitions:
 */

DynamicPrefetcher::DynamicPrefetcher(const DynamicPrefetcherParams* p)
    : BasePrefetcher(p),
    instructionInterval(p->instruction_interval),
    matchThreshold(p->match_threshold)
{

}

DynamicPrefetcher::~DynamicPrefetcher(){

}


/*
 * PrefetchConfig definitions:
 */

void
DynamicPrefetcher::
incrementPrefetchBlocks(){
	if(prefetchBlocks < 0b111){
		prefetchBlocks++;
	}
}

void
DynamicPrefetcher::
decrementPrefetchBlocks(){
	if(prefetchBlocks > 0b000){
		prefetchBlocks--;
	}
}

void
DynamicPrefetcher::
endInterval(){
	if(matchCounter >= matchThreshold){
		incrementPrefetchBlocks();
	} else {
		decrementPrefetchBlocks();
	}
	storeCurrentInstruction();
	instructionIndex = 0;
	matchCounter = 0;
}

void
DynamicPrefetcher::
storeInstruction(inst_t instruction){
	storedInstruction = instruction;
}

void
DynamicPrefetcher::
storeCurrentInstruction(){
	// TODO: implement function.
	throw std::string("Not implemented.");
}

void
DynamicPrefetcher::
compareInstruction(inst_t instruction){
	if(instruction == storedInstruction){
		matchCounter++;
	}
	instructionIndex++;
	if(instructionIndex >= instructionInterval){
		endInterval();
	}
}

char
DynamicPrefetcher::
getPrefetchBlocks(){
	return prefetchBlocks >> 1;
}

DynamicPrefetcher*
DynamicPrefetcherParams::create()
{
    return new DynamicPrefetcher(this);
}
