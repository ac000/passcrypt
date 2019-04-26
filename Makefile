passcrypt: passcrypt.c
	gcc -Wall -Wextra -std=c99 -O2 -o passcrypt passcrypt.c -lcrypt

clean:
	rm -f passcrypt
