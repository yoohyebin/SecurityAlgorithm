#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
	int temp=0;
	while (b != 0) {
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}
int get_private_key(int e, int tot) {
	int k = 1;
	while ((e*k) % tot != 1)
		k += 1;
	return k;
}
int get_public_key(int tot) {
	int e = 2;
	while (e < tot && gcd(e, tot) != 1)
		e += 1;
	return e;
}
void encrypt(int e, int  n, unsigned char *plaintext, unsigned char *encrypted_msg) {
	int i;
	int temp=1;
	for (i = 0; i < strlen(plaintext); i++) {
		temp = 1;
		for(int j=0;j<e;j++)
			temp = (temp * plaintext[i])% n;
		encrypted_msg[i] = temp;
	}
	
}
void decrypt(int d, int n, unsigned char *encrypted_msg, unsigned char *decrypted_msg) {
	int i;
	int temp = 1;
	for (i = 0; i < strlen(encrypted_msg); i++) {
		temp = 1;
		for (int j = 0; j < d; j++)
			temp = (temp * encrypted_msg[i]) % n;
		decrypted_msg[i] = temp;
	}
}
int main() {
	unsigned char plainText[256] = { 0, };
	unsigned char encrypted_msg[256] = { 0, };
	unsigned char decrypted_msg[256] = { 0, };
	int p = 13, q = 23;
	int n = p * q;
	int totient = (p - 1)*(q - 1);
	int e, d;
	printf("Enter the text to be encrypted:");
	gets(plainText);
	printf("%s\n", plainText);
	printf("p: %d q:%d n=%d t=%d", p, q, n, totient);
	e = get_public_key(totient);
	d = get_private_key(e, totient);
	printf(" public_key:%d private_key;%d\n", e, d);
	encrypt(e, n, plainText, encrypted_msg);
	for(int i=0;i < strlen(plainText); i++)
		printf("%d", encrypted_msg[i]);
	decrypt(d, n, encrypted_msg, decrypted_msg);
	printf("\n%s\n", decrypted_msg);
}