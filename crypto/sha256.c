#include "hblk_crypto.h"

/**
 * sha256 - computes SHA-256 message digest for the given data
 * @s: input data
 * @len: length of input data
 * @digest: destination buffer for message digest
 *
 * Return: pointer to digest
 */
uint8_t
*sha256(const int8_t *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!s || !digest)
		return (NULL);

	if (!SHA256((uint8_t *)s, len, digest))
		return (NULL);

	return (digest);
}
