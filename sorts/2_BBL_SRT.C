/**
* C PROGRAM TO PERFORM BUBBLE SORT
**/

#include <stdio.h>
#define  swap(a, m, n) (a[m] ^= a[n] ^= a[m] ^= a[n])

void bubble_srt (int a[], int n)
	{
	for (int i = n, j = 1, c = 1;
	         j < i || (j = 1, !c && --i && (c = 1));
	         j++)
	    a[j - 1] > a[j] && (c = 0) & swap (a, j, j - 1);
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	bubble_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}