#ifndef ATLASBLOCKCHAIN_CRYPTO_MACROS_H
#define ATLASBLOCKCHAIN_CRYPTO_MACROS_H

#define MAX_PATH_LEN 4096

#define JOIN_PATH(dest, dir, file) \
	snprintf((dest), MAX_PATH_LEN - 1, "%s/%s", (dir), (file))

#endif /* ATLASBLOCKCHAIN_CRYPTO_MACROS_H */
