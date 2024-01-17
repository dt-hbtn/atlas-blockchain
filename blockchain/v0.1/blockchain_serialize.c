#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "provided/endianness.h"
#include "blockchain.h"

#define HBLK_MAGIC "\x48\x42\x4c\x4b"
#define HBLK_VERSION "0.1"
#define HBLK_HEADER_LEN 12 
#define INVALID_FD(fd) ((fd) < 0)

static int write_header(int fd, const uint32_t n_blocks)
{
	char buf[HBLK_HEADER_LEN + 1] =
		HBLK_MAGIC		/* magic bytes */ \
		HBLK_VERSION		/* 0.1 */ \
		"\x00"			/* endianness placeholder */ \
		"\x00\x00\x00\x00";	/* block-count placeholder */

	buf[7] = (char)_get_endianness();
	memcpy(buf + 8, &n_blocks, 4);

	if (write(fd, buf, HBLK_HEADER_LEN) == HBLK_HEADER_LEN)
		return (1);

	return (0);
}

static int write_block(int fd, const block_t *block)
{
	ssize_t tmp;

	/* write block info */
	tmp = write(fd, block, sizeof(block_info_t));

	if (tmp < (ssize_t)sizeof(block_info_t))
		return (0);

	/* write data length */
	tmp = write(fd, &block->data.len, 4);

	if (tmp < (ssize_t)4)
		return (0);

	/* write data */
	tmp = write(fd, block->data.buffer, block->data.len);

	if (tmp < (ssize_t)block->data.len)
		return (0);

	/* write hash */
	tmp = write(fd, block->hash, SHA256_DIGEST_LENGTH);

	if (tmp < SHA256_DIGEST_LENGTH)
		return (0);

	return (1);
}

/**
 * blockchain_serialize - Serializes blockchain in memory to a file
 * @blockchain: Pointer to blockchain_t structure
 * @path: Output file path
 *
 * Return: 0 on success, -1 on failure
*/
int blockchain_serialize(const blockchain_t *blockchain, const char *path)
{
	int fd, n_blocks, i;
	void *block_tmp = NULL;

	if (!blockchain || !path)
		return (-1);

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	if (INVALID_FD(fd))
		return (-1);

	n_blocks = llist_size(blockchain->chain);

	if (n_blocks < 1)
		return (-1);

	if (!write_header(fd, (uint32_t)n_blocks))
		return (-1);

	for (i = 0; i < n_blocks; ++i)
	{
		block_tmp = llist_get_node_at(blockchain->chain, (uint32_t)i);

		if (!block_tmp)
			return (-1);

		if (!write_block(fd, (const block_t *)block_tmp))
			return (-1);
	}

	close(fd);
	return (0);
}
