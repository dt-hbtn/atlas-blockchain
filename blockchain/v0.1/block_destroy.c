#include <stdlib.h>
#include "blockchain.h"

/**
 * block_destroy - Frees a block_t structure
 * @block: Pointer to block to free
 */
void block_destroy(block_t *block)
{
	free(block);
}
