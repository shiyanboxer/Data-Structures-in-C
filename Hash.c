// HASH.C
// Program for use with ELEC278 Lab 5 Part 2.
//
// History:
// 161106	HF	First release
// 171102	DA	Minor tweaks


#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"
#include <time.h>
#include <math.h>

typedef struct HashTable {
	LinkedList** a;
	int size;
	int collisions;
} HashTable;


HashTable* initHashTable(int s)
{
	HashTable* h = malloc(sizeof(HashTable));
	int		i;
	h->size = s;
	h->a = malloc(sizeof(LinkedList) * s);
	for(i=0;i<s;i++)
		h->a[i]= init();
	h->collisions = 0;
	return h;
}//initHashTable()


long h(char* x)
// This function computes a hash code for a given string.  Note that hash
// code is unbounded - it needs to be reduced modulo the size of the array
// used to store the data. (You will see another function hash() below that
// completes the index calculation.)
{
	long	sum=0;
	//#########################COMPLETE THIS FUNCTION##########################
	// Requirements given in lab instructions.
	// ---<SNIP>---
	int		i = 0;
	int l = strlen(x);
	while(x[i]!='\0'){
		sum+=(x[i] * (long)pow(31,l-1-i));
		i++;
		}
	// ---<SNIP>---
	return sum;
}//h()


double loadFactor(HashTable* ht)
{
	double nonempty = 0;
	int i;
	for(i=0; i<ht->size; i++)	{
		if (isEmpty(ht->a[i])==0)	nonempty++;
		}
	return nonempty/ht->size*100;
}//loadFactor()


int hash(char* x, int size)
// Index calculation. Function h() computes general hash for the string;
// this function turns the hash into a valid index, given the size of the
// array.
{
	return h(x) % size;
}


void insert(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---

	int key = hash(x, ht->size);
	if (isEmpty(ht->a[key])==0)
		ht->collisions++;
	addFront(ht->a[key],x);

	// ---<SNIP>---
}//insert()


int findInTable(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---

	int key = hash(x, ht->size);
	return (find(ht->a[key],x));
	// ---<SNIP>---
}


void printTable(HashTable *ht)
{
	int i;
	printf("----------\n");
	for (i = 0; i < ht->size; i++)	{
		printf("%d --> ", i);
		print(ht->a[i]);
		}
	printf("# of Collisions=%d\n", ht->collisions);
	printf("Load Factor %%=%.2f\n----------", loadFactor(ht));
}


int main() {
	//FILE *fp;
	//fp = fopen("words.txt","w+");
	int i=0;
	HashTable* h = initHashTable(101);

#if 0
	// Generate a set of random strings (given the way this works, everyone
	// gets the same set of random strings!) insert each into the hash table
	// and then print the table.
	for(i=0;i<100;i++){
		int x = rand()%5+1;
		char *p = malloc(sizeof(char)*x);
		int j=0;
		for(j=0;j<x;j++)
			p[j] = rand()%26 + 97;
		p[j]='\0';
		insert(h,p);
	}
#else

	FILE	*fp;
	char	*p;
	char	buff [132];
	fp = fopen ("words.txt", "r");
	while (!feof (fp))	{
		fgets (buff, 128, fp);
		p = buff;
		while (*p)	 {
			if (*p == '\n')  *p = '\0';
			p++;
			}
		printf ("Word inserted: %s\n", buff);
		insert (h, buff);
		printTable (h);
		getchar();
		}
#endif
	printTable(h);
	return 0;
}
