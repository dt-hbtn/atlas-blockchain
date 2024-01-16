#ifndef HOLBERTONSCHOOLBLOCKCHAIN_CRYPTO_HBLKCRYPTO_H
#define HOLBERTONSCHOOLBLOCKCHAIN_CRYPTO_HBLKCRYPTO_H

#include <stddef.h>
#include <stdint.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>

#define EC_CURVE NID_secp256k1
#define EC_PUB_LEN 65UL
#define SIG_MAX_LEN 72UL
#define PRI_FILENAME "key.pem"
#define PUB_FILENAME "key_pub.pem"

/**
 * struct sig_s - EC Signature structure
 *
 * @sig: Signature buffer. The whole space may not be used
 * @len: Actual signature size. Can't exceed SIG_MAX_LEN
 */
typedef struct sig_s
{
	/*
	 * @sig must stay first, so we can directly use the structure as
	 * an array of char
	 */
	uint8_t sig[SIG_MAX_LEN];
	uint8_t len;
} sig_t;

uint8_t
*sha256(const int8_t *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]);

EC_KEY
*ec_create(void);

uint8_t
*ec_to_pub(const EC_KEY *key, uint8_t pub[EC_PUB_LEN]);

EC_KEY
*ec_from_pub(uint8_t const pub[EC_PUB_LEN]);

int
ec_save(EC_KEY *key, const char *folder);

EC_KEY
*ec_load(const char *folder);

uint8_t
*ec_sign(const EC_KEY *key, uint8_t const *msg, size_t msglen, sig_t *sig);

int
ec_verify(const EC_KEY *key, uint8_t const *msg, size_t msglen,
	sig_t const *sig);

#endif /* HOLBERTONSCHOOLBLOCKCHAIN_CRYPTO_HBLKCRYPTO_H */
