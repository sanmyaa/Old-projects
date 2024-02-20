/**
* C PROGRAM TO PERFORM MERGE SORT
**/

#include <stdio.h>
#include <stdlib.h>

int *b;

int merge (int a[], int n)
	{
	int MID = n / 2,
	    i   = 0,
	    j   = MID,
	    t   = 0;

	while (i < MID & j < n)
		b[t++] = a[a[i] < a[j] ? i++ : j++];

	for (j -= MID - i ; i ^ MID ; a[j++] = a[i++]);

	while (t--) a[t] = b[t];
	}

void merge_srt (int a[], int n)
	{
	if (n > 1)
		{
		int x = n / 2;

		merge_srt (a, x);
		merge_srt (a + x, n - x);
		merge (a, n);
		}
	}

void main ()
	{
	int a[] = {310, 18, 18, -6, -5, 10, -99, 2, -6},
	    n   = sizeof (a) / sizeof (*a);

	b = (int*) malloc (n * sizeof (int));
	merge_srt (a, n);

	for (int i = 0 ; i < n ; i++) printf (" %d ", a[i]);
	}