/**
* C PROGRAM TO PERFORM SHELL SORT
**/

#include <stdio.h>

void shell_srt (int a[], int n)
	{
	int x = n >> 1,
	    i = n - x - 1,
	    T = a[i],
	    j = i;

	while (j < n - x && T > a[j + x] && (a[j] = a[j + x], j += x) ||
	      (a[j] = T, --i) >= 0 && (T = a[j = i], 1) ||
	      (x >>= 1) && (T = a[i = j = n - x - 1], 1));
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	shell_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}