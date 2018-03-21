#include <string> // Temporary

#include "mem/cache/prefetch/dynamic.hh"

/*
 * DynamicPrefetcher definitions:
 */

DynamicPrefetcher::DynamicPrefetcher(const DynamicPrefetcherParams* p)
	: BasePrefetcher(p) /*
	, nextParameter(p->nextParameter)
	, etc(p->etc) */
{
}

DynamicPrefetcher::~DynamicPrefetcher(){
}





/*
 * PrefetchConfig definitions:
 */

DynamicPrefetcher::
PrefetchConfig::
PrefetchConfig(int instructionInterval, int matchThreshold)
	: instructionInterval(instructionInterval)
	, matchThreshold(matchThreshold)
{
}

DynamicPrefetcher::
PrefetchConfig::
~PrefetchConfig(){
}

void
DynamicPrefetcher::
PrefetchConfig::
incrementPrefetchBlocks(){
	if(prefetchBlocks < 0b111){
		prefetchBlocks++;
	}
}

void
DynamicPrefetcher::
PrefetchConfig::
decrementPrefetchBlocks(){
	if(prefetchBlocks > 0b000){
		prefetchBlocks--;
	}
}

void
DynamicPrefetcher::
PrefetchConfig::
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
PrefetchConfig::
storeInstruction(inst_t instruction){
	storedInstruction = instruction;
}

void
DynamicPrefetcher::
PrefetchConfig::
storeCurrentInstruction(){
	// TODO: implement function.
	throw std::string("Not implemented.");
}

void
DynamicPrefetcher::
PrefetchConfig::
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
PrefetchConfig::
getPrefetchBlocks(){
	return prefetchBlocks >> 1;
}
