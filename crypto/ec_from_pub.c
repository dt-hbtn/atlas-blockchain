#include "hblk_crypto.h"

/**
 * ec_from_pub - load raw public key into new EC_KEY instance
 * @pub: raw public key
 *
 * Return: EC_KEY pointer
 */
EC_KEY
*ec_from_pub(const uint8_t pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;
	EC_POINT *point = NULL;
	EC_GROUP *group = NULL;

	if (!pub)
		return (NULL);

	group = EC_GROUP_new_by_curve_name(EC_CURVE);

	if (!group)
		return (NULL);

	point = EC_POINT_new(group);

	if (!point)
		goto error;

	if (EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL) != 1)
		goto error;

	key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (!key)
		goto error;

	if (EC_KEY_set_public_key(key, point) != 1)
		goto error;

	EC_GROUP_free(group);
	EC_POINT_free(point);
	return (key);

error:
	EC_GROUP_free(group);
	EC_POINT_free(point);
	EC_KEY_free(key);
	return (NULL);
}
