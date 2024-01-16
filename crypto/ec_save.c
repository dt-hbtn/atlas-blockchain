#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/pem.h>
#include "hblk_crypto.h"

static int
mkdir_if_not_exists(const char *path);

static int
write_private(EC_KEY *key, const char *dir, const size_t dir_len);

static int
write_public(EC_KEY *key, const char *dir, const size_t dir_len);

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
	size_t dir_len;

	if (!key || !folder)
		return (0);

	dir_len = strlen(folder);

	if (!dir_len)
		return (0);

	if (!mkdir_if_not_exists(folder))
		return (0);

	while (dir_len && folder[dir_len - 1] == '/')
		--dir_len;

	if (!write_private(key, folder, dir_len))
		return (0);

	if (!write_public(key, folder, dir_len))
		return (0);

	return (1);
}

static int
mkdir_if_not_exists(const char *path)
{
	struct stat stat_buf;
	int path_invalid, mkdir_failed;

	path_invalid = stat(path, &stat_buf);

	if (!path_invalid)
		return (S_ISDIR(stat_buf.st_mode));

	mkdir_failed = mkdir(path, 0777);
	return (!mkdir_failed);
}

static int
write_private(EC_KEY *key, const char *dir, const size_t dir_len)
{
	char *filepath = NULL;
	FILE *file = NULL;

	filepath = calloc(dir_len + 9, sizeof(char));

	if (!filepath)
		return (0);

	sprintf(filepath, "%.*s/" PRI_FILENAME, (int)dir_len, dir);

	file = fopen(filepath, "w");
	free(filepath);

	if (!file)
		return (0);

	if (PEM_write_ECPrivateKey(file, key, NULL, NULL, 0, NULL, NULL) != 1)
	{
		fclose(file);
		return (0);
	}

	fclose(file);
	return (1);
}

static int
write_public(EC_KEY *key, const char *dir, const size_t dir_len)
{
	char *filepath = NULL;
	FILE *file = NULL;

	filepath = calloc(dir_len + 13, sizeof(char));

	if (!filepath)
		return (0);

	sprintf(filepath, "%.*s/" PUB_FILENAME, (int)dir_len, dir);

	file = fopen(filepath, "w");
	free(filepath);

	if (!file)
		return (0);

	if (PEM_write_EC_PUBKEY(file, key) != 1)
	{
		fclose(file);
		return (0);
	}

	fclose(file);
	return (1);
}
