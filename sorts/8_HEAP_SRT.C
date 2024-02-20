/**
* C PROGRAM TO PERFORM HEAP SORT
**/

#include <stdio.h>
#define ftch_root(a, i) (a[0] ^= a[i] ^= a[0] ^= a[i])

void makeheap (int a[], int l, int m)
	{
	int x = a[l];

	for (int j = l << 1;
	         j <= m && x < a[j += (j < m && a[j] < a[j + 1])];
	         j = (l = j) << 1)
	    a[l] = a[j];

	a[l] = x;
	}

void heap_srt (int a[], int n)
	{
	int i;

	for (i = n - 1 >> 1 ; i >= 0 ; i--)
		makeheap (a, i, n - 1);

	for (i = n – 1 ; i ; makeheap (a, 0, i-- - 1))
		ftch_root (a, i);
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	heap_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}