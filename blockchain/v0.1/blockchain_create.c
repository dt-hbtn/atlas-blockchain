#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

#define GENESIS_DATA "Holberton School"
#define GENESIS_DATA_LEN UINT32_C(16)
#define GENESIS_TIMESTAMP UINT64_C(1537578000)
#define GENESIS_HASH	"\xc5\x2c\x26\xc8\xb5\x46\x16\x39"\
			"\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"\
			"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1"\
			"\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
 * blockchain_create - Creates new blockchain with genesis block
 *
 * Return: Pointer to allocated blockchain_t structure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = NULL;
	block_t *head = NULL;
	llist_t *list = NULL;

	blockchain = calloc(1, sizeof(blockchain_t));
	head = calloc(1, sizeof(block_t));
	list = llist_create(MT_SUPPORT_FALSE);

	if (!blockchain || !head || !list)
		goto create_fail;

	head->data.len = GENESIS_DATA_LEN;
	head->info.timestamp = GENESIS_TIMESTAMP;
	memcpy(head->data.buffer, GENESIS_DATA, GENESIS_DATA_LEN);
	memcpy(head->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(list, head, ADD_NODE_FRONT) == -1)
		goto create_fail;

	blockchain->chain = list;
	return (blockchain);

create_fail:
	free(blockchain);
	free(head);
	llist_destroy(list, 0, NULL);
	return (NULL);
}
