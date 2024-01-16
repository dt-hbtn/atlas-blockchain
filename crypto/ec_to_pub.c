#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts raw public key from EC key pair
 * @key: key pair
 * @pub: buffer for raw public key
 *
 * Return: pointer to pub (NULL if extraction fails)
 */
uint8_t
*ec_to_pub(const EC_KEY *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *point = NULL;

	if (!key || !pub)
		return (NULL);

	point = EC_KEY_get0_public_key(key);

	if (EC_POINT_point2oct(
		EC_KEY_get0_group(key),
		point,
		POINT_CONVERSION_UNCOMPRESSED,
		pub,
		EC_PUB_LEN,
		NULL
	) != EC_PUB_LEN)
	{
		return (NULL);
	}

	return (pub);
}
