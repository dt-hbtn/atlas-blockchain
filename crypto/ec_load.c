#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include "hblk_crypto.h"

static char
*join_path(const char *dir, const char *filename);

/**
 * ec_load - loads EC key from public-/private-key files
 * @folder: key-file directory path
 *
 * Return: EC_KEY pointer
 */
EC_KEY
*ec_load(const char *folder)
{
	EC_KEY *key = NULL;
	char *filepath = NULL;
	FILE *key_file = NULL;
	int load_failed;

	if (!folder || !*folder)
		return (NULL);

	filepath = join_path(folder, PRI_FILENAME);

	if (!filepath)
	{
		free(filepath);
		return (NULL);
	}

	key_file = fopen(filepath, "r");
	free(filepath);
	filepath = NULL;

	if (!key_file)
		return (NULL);

	key = EC_KEY_new();

	if (!key)
	{
		fclose(key_file);
		return (NULL);
	}

	load_failed = !PEM_read_ECPrivateKey(key_file, &key, NULL, NULL);
	fclose(key_file);

	if (load_failed)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	return (key);
}

static char
*join_path(const char *dir, const char *filename)
{
	char *filepath = NULL;
	size_t dir_len;

	dir_len = strlen(dir);
	filepath = calloc(dir_len + strlen(filename) + 1, sizeof(char));

	if (!filepath)
		return (NULL);

	sprintf(
		filepath,
		"%s%s%s",
		dir,
		dir[dir_len - 1] == '/' ? "" : "/",
		filename
	);

	return (filepath);
}
