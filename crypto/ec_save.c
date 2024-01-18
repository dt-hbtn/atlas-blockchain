#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/pem.h>
#include "hblk_crypto.h"
#include "_macros.h"

static char PATH_BUF[MAX_PATH_LEN] = { '\0' };

static int
mkdir_p(const char *path);

static int
write_ec_key(EC_KEY *key, const char *dir, const int private);

/**
 * ec_save - saves EC key pair to files
 * @key: EC key pair
 * @folder: directory to save keys
 *
 * Return: 1=success, 0=failure
 */
int
ec_save(EC_KEY *key, const char *folder)
{
	if (!key || !folder || !*folder)
		return (0);

	if (!mkdir_p(folder))
		return (0);

	return (write_ec_key(key, folder, 1) && write_ec_key(key, folder, 0));
}

static int
mkdir_p(const char *path)
{
	int result;
	struct stat stat_buf;

	result = stat(path, &stat_buf)
		? !mkdir(path, 0777)
		: S_ISDIR(stat_buf.st_mode);

	return (result);
}

static int
write_ec_key(EC_KEY *key, const char *dir, const int private)
{
	FILE *file = NULL;
	int result;

	JOIN_PATH(PATH_BUF, dir, private ? PRI_FILENAME : PUB_FILENAME);
	file = fopen(PATH_BUF, "w");

	if (!file)
		return (0);

	result = private
		? PEM_write_ECPrivateKey(file, key, NULL, NULL, 0, NULL, NULL)
		: PEM_write_EC_PUBKEY(file, key);

	fclose(file);
	return (result);
}
