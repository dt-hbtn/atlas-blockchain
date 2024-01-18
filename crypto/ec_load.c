#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include "hblk_crypto.h"
#include "_macros.h"

static char PATH_BUF[MAX_PATH_LEN] = { '\0' };

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
	FILE *file = NULL;

	if (!folder || !*folder)
		return (NULL);

	JOIN_PATH(PATH_BUF, folder, PRI_FILENAME);
	file = fopen(PATH_BUF, "r");

	if (!file)
		return (NULL);

	key = PEM_read_ECPrivateKey(file, NULL, NULL, NULL);
	fclose(file);
	return (key);
}
