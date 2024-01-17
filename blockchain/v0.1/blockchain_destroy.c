#include <stdlib.h>
#include "blockchain.h"

static void free_block(void *block)
{
	free(block);
}

/**
 * blockchain_destroy - Frees a blockchain_t structure
 * @blockchain: Pointer to blockchain_t structure
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, free_block);
	free(blockchain);
}
