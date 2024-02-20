/**
* C PROGRAM TO PERFORM INSERTION SORT
**/

#include <stdio.h>

void insertion_srt (int a[], int n)
	{
	int i = 1, j = 1, T = a[1];

	while (a[j - 1] >= T          && (a[j] = a[j - 1], --j) ||
	      (a[j] = T, j = ++i) < n && (T = a[i], 1));
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	insertion_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}