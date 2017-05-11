#include <assert.h>
#include <err.h>
#include <search.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "resh.h"

enum
{
	MULT = 5,
	SHIFT = 27,
	TBLSZ = 37,
};

struct var {
	struct var *next;
	const char *key;
	char *value;
};

struct var *vars[TBLSZ];

static size_t
hash(const char *s)
{
	size_t h = 0;

	assert(s != NULL);
	for (const char *p = s; *p != '\0'; ++p)
		h = (h<<MULT) + (((h>>SHIFT)&((1<<MULT) - 1))^*p);

	return h % TBLSZ;
}

char *
getvar(const char *name)
{
	assert(name != NULL);
	for (struct var *p = vars[hash(name)]; p != NULL; p = p->next)
		if (STREQ(name, p->key))
			return p->value;

	return NULL;
}

#include <stdio.h>
void
setvar(const char *name, const char *value)
{
	struct var *p;
	size_t h = hash(name);

	assert(name != NULL);
	assert(value != NULL);
	for (p = vars[h]; p != NULL; p = p->next) {
		if (STREQ(name, p->key)) {
			free(p->value);
			p->value = strdup(value);
			return;
		}
	}
	p = calloc(1, sizeof(*p));
	if (p == NULL)
		err(1, "Panic zero. Rebooting.\n");
	p->key = estrdup(name);
	p->value = estrdup(value);
	p->next = vars[h];
	vars[h] = p;
}

void
unsetvar(const char *name)
{
	size_t h;

	assert(name != NULL);
	h = hash(name);
	for (struct var *pp = NULL, *p = vars[h]; p != NULL; pp = p, p = p->next) {
		if (STREQ(p->key, name)) {
			if (pp != NULL)
				pp->next = p->next;
			else
				vars[h] = p->next;
			free((char *)p->key);
			free(p->value);
			free(p);
			return;
		}
	}
}
