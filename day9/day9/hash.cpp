#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 256

struct nlist {
	struct nlist *next;
	char *name;
	char *phone;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(const char *s)
{
	unsigned hashval = 7;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}


struct nlist* lookup(const char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}


char *str_mcopy(const char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy_s(p, strlen(s) + 1, s);
	return p;
}


struct nlist* install(const char *name, const char *phone)
{
	struct nlist *np, *find;
	unsigned hashval;

	np = (nlist *)malloc(sizeof(nlist));
	np->name = str_mcopy(name);
	np->phone = str_mcopy(phone);
	np->next = NULL;
	find = lookup(name);
	if (find == NULL)
	{
		hashval = hash(name);
		hashtab[hashval] = np;
	}
	else
	{
		find->next = np;
	}
	return np;
}

int main()
{
	const char *name[] = { "손나은","김태희","한지민",
	   "문채원","전지현","문채원" };
	const char *phone[] = { "731-1234", "567-8976", "521-5030",
	   "521-9600", "418-4165", "520-3307", "425-1024" };
	int i, n = sizeof(name) / sizeof(name[0]);
	struct nlist *head, *ptr;


	for (i = 0; i < n; i++) 
	{
		printf("%d: %s\n", hash(name[i]), name[i]);

		install(name[i], phone[i]);
	}

	printf("\nHash Table List \n");
	for (i = 0; i < HASHSIZE; i++) 
	{
		head = hashtab[i];
		for (ptr = head; ptr != NULL; ptr = ptr->next) {
			printf("%d: %s, %s\n", i, ptr->name, ptr->phone);
		}
	}

	printf("\nHash Table Search \n");
	ptr = lookup("문채원");
	for(;ptr != NULL; ptr = ptr->next)
		printf("found: %s, %s\n", ptr->name, ptr->phone);

	printf("\nPress any key to end...");
	getchar();
	return 0;
}