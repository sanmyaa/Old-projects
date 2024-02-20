/**
* C PROGRAM TO PERFORM COMB SORT
**/

#include <stdio.h>
#define  swap(a, m, n) (a[m] ^= a[n] ^= a[m] ^= a[n])

void comb_srt (int a[], int n)
	{
	for (int x = n - 1, j = 0, c = 1;
	         j < n - x || (j = 0, x > 1 && (x /= 1.3) || !c && (c = 1));
	         j++)
	    a[j] > a[j + x] && (c = 0) & swap (a, j, j + x);
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	comb_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}