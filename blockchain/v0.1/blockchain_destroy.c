#include <stdlib.h>
#include "blockchain.h"

/**
 * blockchain_destroy - Frees a blockchain_t structure
 * @blockchain: Pointer to blockchain_t structure
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, free);
	free(blockchain);
}
