#include "blockchain.h"

/**
 * block_hash - SHA-256 hashes a block
 * @block: Pointer to block
 * @hash_buf: >=32-byte buffer for hash
 *
 * Return: Pointer to hash_buf, NULL on failure
 */
uint8_t *block_hash(const block_t *block,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t msg_len;

	if (!block || !hash_buf)
		return (NULL);

	msg_len = sizeof(block_info_t) + block->data.len;
	return (sha256((const int8_t *)block, msg_len, hash_buf));
}
