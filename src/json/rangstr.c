#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rangstr.h"

void rangstr_print (Rangstr *s) {
	//printf ("%.%s", s->t-s->f, s->p);
	if (s->p) fwrite (s->p+s->f, s->t-s->f, 1, stdout);
}

static const char *staticstr = NULL;

void rangstr_static (const char *s) {
	staticstr = s;
}

void rangstr_free (void *p) {
	if (p && p == staticstr)
		free (p);
}

Rangstr rangstr_new (const char *s) {
	Rangstr rs;
	rs.f = 0;
	rs.next = 1;
	rs.t = strlen (s);
	rs.p = s;
	return rs;
}

Rangstr rangstr_null() {
	Rangstr rs = {0};
	return rs;
}

int rangstr_int (Rangstr *s) {
	const int base = 10;
	int mul = 1;
	int ch, i, f, n = 0;
	if (s->p[s->f]=='-') {
		mul = -1;
		i = s->f+1;
	} else i = s->f;
	for (;i<s->t;i++) {
		ch = s->p[i];
		if (ch <'0'||ch>'9')
			break;
		n = n*base + (ch-'0');
	}
	return n * mul;
}


char *rangstr_dup (Rangstr *rs) {
	int len;
	char *p;
	if (!rs->p) return NULL;
	len = rangstr_length (rs);
	p = malloc (len+1);
	memcpy (p, rs->p+rs->f, len);
	p[len+1] = 0;
	return p;
}

Rangstr rangstr_news (const char *s, ut16 *res, int i) {
	Rangstr rs;
	rs.next = 1;
	rs.f = res[i];
	rs.t = res[i]+res[i+1];
	rs.p = s;
	return rs;
}

int rangstr_cmp (Rangstr *a, Rangstr *b) {
	int la = a->t-a->f;
	int lb = b->t-b->f;
	if (la != lb)
		return 1;
	return memcmp (a->p+a->f, b->p+b->f, la);
}
