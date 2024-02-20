/**
* C PROGRAM TO PERFORM RADIX SORT
**/

#include <stdio.h>
#include <stdlib.h>
#define B 10

void sub_countngSrt (int a[], int n, int x)
	{
	int i, c[2 * B - 1] = {0};
	static *b = (int*) malloc (n * sizeof(int));

	for (i = 0 ; i < n ; i++)
		c[a[i] / x % B + B - 1]++;

	for (i = 1 ; i <= B - 1 << 1 ; i++)
		c[i] += c[i - 1];

	for (i = n - 1 ; i >= 0 ; i--)
		b[c[a[i] / x % B + B - 1]-- - 1] = a[i];

	for (i = 0 ; i < n ; i++)
		a[i] = b[i];
	}

void radix_srt (int a[], int n)
	{
	int i, mx;

	for (mx = *a, i = 1 ; i < n ; i++)
		mx < a[i] && (mx = a[i]);

	for (i = 1 ; mx >= i ; i *= B)
		sub_countngSrt (a, n, i);
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	radix_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}