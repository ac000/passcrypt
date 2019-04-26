/*
 * passcrypt.c
 *
 * Copyright (C) 2014, 2019	Andrew Clayton <andrew@digital-domain.net>
 *
 * Released under the GNU General Public License version 2.
 * See COPYING
 */

#define _XOPEN_SOURCE	500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
	static const char salt_chars[64] =
"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char salt[21];
	int i;

	if (argc < 4) {
		printf("Usage: passcrypt -l <256/512/md5> <password>\n");
		exit(EXIT_FAILURE);
	}

	memset(salt, 0, sizeof(salt));

	if (strcmp(argv[2], "256") == 0) {
		strcpy(salt, "$5$");
	} else if (strcmp(argv[2], "512") == 0) {
		strcpy(salt, "$6$");
	} else if (strcmp(argv[2], "md5") == 0) {
		strcpy(salt, "$1$");
	} else {
		printf("Unknown hash type.\n");
		exit(EXIT_FAILURE);
	}

	for (i = 3; i < 19; i++) {
		long r;
		struct timespec tp;

		clock_gettime(CLOCK_REALTIME, &tp);
		srandom(tp.tv_sec * tp.tv_nsec);
		r = random() % 64; /* 0 - 63 */
		salt[i] = salt_chars[r];
	}
	strcat(salt, "$");

	printf("%s\n", crypt(argv[3], salt));

	exit(EXIT_SUCCESS);
}
