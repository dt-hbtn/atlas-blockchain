#include "hblk_crypto.h"

int
ec_verify(const EC_KEY *key, uint8_t const *msg, size_t msglen,
	sig_t const *sig)
{
	int verify_result;

	if (!key || !msg || !sig)
		return (0);

	verify_result = ECDSA_verify(
		0,
		msg,
		msglen,
		sig->sig,
		(int)sig->len,
		(EC_KEY *)key
	);

	return (verify_result == 1 ? 1 : 0);
}
