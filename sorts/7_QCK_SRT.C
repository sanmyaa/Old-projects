/**
* C PROGRAM TO PERFORM QUICK SORT
**/

#include <stdio.h>
#define  swap(a, m, n) (a[m] = (long) a[m] + a[n] - (a[n] = a[m]))

int partition (int a[], int n)
	{
	int P = *a, 
	    i = 1,
	    j = n - 1;
	
	while ((i <= j && a[i] <= P && ++i) | (a[j] > P && j--) ||
	       i < j && swap (a, i, j) | 1);
		   
	swap (a, 0, j);

	return j;
	}

void quick_srt (int a[], int n)
	{
	if (n > 1)
		{
		int x = partition (a, n);

		quick_srt (a, x);
		quick_srt (a + x + 1, n - x - 1);
		}
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	quick_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}