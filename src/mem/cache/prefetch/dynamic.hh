#ifndef __MEM_CACHE_PREFETCH_DYNAMIC_HH__
#define __MEM_CACHE_PREFETCH_DYNAMIC_HH__

#include <cstdint>
#include "mem/cache/prefetch/base.hh"
#include "params/DynamicPrefetcher.hh"

typedef uint32_t inst_t; // data type for instructions

class DynamicPrefetcher : public BasePrefetcher
{
private:
		int instructionInterval;
		int instructionIndex;
		int matchThreshold;
		int matchCounter;
		char prefetchBlocks; // 0b000 <= prefetchBlocks <= 0b111
		inst_t storedInstruction;

		/**
		 * If prefetchBlocks < 0b111, increment prefetchBlocks.
		 */
		void incrementPrefetchBlocks();

		/**
		 * If prefetchBlocks > 0b000, decrement prefetchBlocks.
		 */
		void decrementPrefetchBlocks();

		/**
		 * If matchCounter >= matchThreshold, call incrementPrefetchBlocks().
		 * Else, call decrementPrefetchBlocks().
		 * Call storeCurrentInstruction().
		 * Set instructionIndex to 0.
		 * Set matchCounter to 0.
		 */
		void endInterval();

		

public:
	DynamicPrefetcher(const DynamicPrefetcherParams *p);
	~DynamicPrefetcher();
	/**
		 * Store instruction to storedInstruction.
		 */
		void storeInstruction(inst_t instruction);

		/**
		 * Call storeInstruction(currentInst),
		 * where currentInst is the current instruction
		 * retrieved from the parent DynamicPrefetcher object.
		 */
		void storeCurrentInstruction();

		/**
		 * Compare an instruction on the stored instruction.
		 * In the case of a match, increment matchCounter.
		 * Increment instructionIndex.
		 * If instructionIndex >= instructionInterval, call endInterval().
		 */
		void compareInstruction(inst_t instruction);

		/**
		 * Return the number of blocks to prefetch (in
		 * addition to the required block) on a cache miss.
		 * This is equal to the two most significant bits
		 * of prefetchBlocks, or (prefetchBlocks >> 1).
		 */
		char getPrefetchBlocks(); // return prefetchBlocks >> 1;
};

#endif //__MEM_CACHE_PREFETCH_BASE_HH__
