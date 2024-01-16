#include "hblk_crypto.h"

uint8_t
*ec_sign(const EC_KEY *key, uint8_t const *msg, size_t msglen, sig_t *sig)
{
	unsigned int sig_len;

	if (!key || !msg || !sig)
		return (NULL);

	if (!ECDSA_sign(0, msg, msglen, sig->sig, &sig_len, (EC_KEY *)key))
		return (NULL);

	sig->len = (uint8_t)sig_len;
	return (sig->sig);
}
