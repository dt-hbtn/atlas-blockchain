#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blockchain.h"

#define TIME_ERROR(t) ((t) < (time_t)0)

/**
 * block_create - Allocates a new block_t structure
 * @prev: Pointer to previous block
 * @data: Pointer to data for new block
 * @data_len: Length of data
 *
 * Return: Pointer to allocated block_t structure
 */
block_t *block_create(const block_t *prev, const int8_t *data,
	uint32_t data_len)
{
	block_t *block = NULL;
	time_t timestamp;

	if (!prev || !data)
		return (NULL);

	timestamp = time(NULL);

	if (TIME_ERROR(timestamp))
		return (NULL);

	block = calloc(1, sizeof(block_t));

	if (!block)
		return (NULL);

	/* set block info */
	block->info.timestamp = (uint64_t)timestamp;
	block->info.index = prev->info.index + 1;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

	/* set block data */
	block->data.len = data_len > BLOCKCHAIN_DATA_MAX
		? BLOCKCHAIN_DATA_MAX
		: data_len;

	memcpy(block->data.buffer, data, block->data.len);

	return (block);
}
