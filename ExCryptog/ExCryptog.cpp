﻿// ExCryptog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#define N 256   
 int * ppt;

void swap(unsigned char *a, unsigned char *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int KSA(int im ,char *key, unsigned char *S) {

	int len = strlen(key);
	int j = 0;

	for (int i = 0; i < N; i++)
		S[i] = i;

	for (int i = 0; i < N; i++) {
		j = (j + S[i] + im) % N;

		swap(&S[i], &S[j]);
	}

	return 0;
}

int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) {

	int i = 0;
	int j = 0;
	int rnd =0;
	for (size_t n = 0, len = strlen(plaintext); n < 2; n++) {
		i = (i + 1) % N;
		j = (j + S[i]) % N;

		swap(&S[i], &S[j]);
		rnd= S[(S[i] + S[j]) % N];
		
		//ciphertext[n] = rnd ^ plaintext[n];

	}ppt[rnd]++;

	return 0;
}

int RC4(int i,char *key, char *plaintext, unsigned char *ciphertext) {

	unsigned char S[N];
	KSA(i,key, S);
	

	PRGA(S, plaintext, ciphertext);

	return 0;
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
		printf("Usage: %s <key> <plaintext>", argv[0]);
		return -1;
	}
	int arr[256];
	ppt = arr;
	for (int i = 0; i < 256; i++) {
		arr[i] = 0;
	}
	unsigned char *ciphertext = (unsigned char *) malloc(sizeof(int) * strlen(argv[2]));
	
	for (int i =1; i < 100000; i++) {
		RC4(i,(char*)&i, argv[2], ciphertext);
		
		
	}
	int count = 0;
	for (int i = 0; i < 256; i++) {
		printf("%d  %d  ",i,arr[i]);
		count += arr[i];
		printf("\n");
	}
	printf("%d   count.", count);



	//for (size_t i = 0, len = strlen(argv[2]); i < len; i++) {

	//	printf("%02hhX ", ciphertext[i]);
	//}


	int a;
	std::cin >> a;


	return 0;
}
