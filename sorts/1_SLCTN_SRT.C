/**
* C PROGRAM TO PERFORM SELECTION SORT
**/

#include <stdio.h>
#define  swap(a, m, n) (a[m] ^= a[n] ^= a[m] ^= a[n])

void selection_srt (int a[], int n)
	{
	for (int i = 0, j = 1, p = 0;
	         j < n || (p ^ i && swap (a, i, p), j = (p = ++i) + 1) < n;
	         j++)
	    a[j] < a[p] && (p = j);
	} 

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	selection_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}
