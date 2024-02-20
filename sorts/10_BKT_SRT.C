/**
* C PROGRAM TO PERFORM BUCKET SORT
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct
	{
	int *P,
	     n;
	}
	BKT;

void insert (BKT *B, int x)
	{
	int j;
	
	B -> P = (int*) realloc (B -> P, ++(B -> n) * sizeof(int));

	for (j = B -> n - 1 ; j && B -> P[j - 1] > x ; j--)
	    B -> P[j] = B -> P[j - 1];
	B -> P[j] = x;
	}

void concat (int a[], BKT B)
	{
	for (int i = 0 ; i < B.n ; i++) 
		a[i] = B.P[i];
	}

void bucket_srt (int a[], int n)
	{
	int   i, lw;
	float e;
	BKT   b[10] = {0};

	for (e = lw = *a, i = n ;
	     i-- || !(e = (e - lw + 1) / 10) ;
	     a[i] > e && (e = a[i], 1) || a[i] < lw && (lw = a[i]));

	for (i = 0 ; i < n ; i++)
		insert (b + (int)((a[i] - lw) / e), a[i]);

	for (int m = i = 0 ; i < n ; i += b[m++].n)
		concat (a + i, b[m]);
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	bucket_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}