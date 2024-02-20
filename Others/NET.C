#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define  GETNODE ((s*)calloc(1, sizeof(s)))

typedef struct node
	{
	int no;
	struct node *lnk[4];
	}s;

void disp(s*);
s*   make(int, int);

void main()
	{
	int R = 3, C = 3;
	s *ptr = make(R, C);

	while(disp(ptr), 1)
		switch(getch())
			{
			case 75 : ptr = ptr -> lnk[0]; break;
			case 77 : ptr = ptr -> lnk[1]; break;
			case 72 : ptr = ptr -> lnk[2]; break;
			case 80 : ptr = ptr -> lnk[3]; break;

			case 32 : scanf("%d", &ptr -> no, printf("\n\tPrevious  Val  : %d\n\tEnter New Val. : ", ptr -> no)); break;
			case 13 : return;
			}
	}

s* list(int N)
	{
	s *ptr = GETNODE;

	ptr -> lnk[0] = ptr -> lnk[1] = ptr;
	ptr -> lnk[2] = ptr -> lnk[3] = ptr;

	while(--N)
		{
		s *tmp = GETNODE;

		tmp -> lnk[0] = ptr -> lnk[0], ptr -> lnk[0] = tmp;
		tmp -> lnk[1] = ptr, tmp -> lnk[0] -> lnk[1] = tmp;

		tmp -> lnk[2] = tmp -> lnk[3] = tmp;
		}

	return ptr;
	}

s* join(s *net1, s *ptr2)
	{
	s *ntp1, *tmp2;

	for(ntp1 = net1, tmp2 = ptr2 ; tmp2 != ptr2 || tmp2 -> lnk[2] == ptr2 ; ntp1 = ntp1 -> lnk[0], tmp2 = tmp2 -> lnk[0])
		{
		tmp2 -> lnk[2] = ntp1 -> lnk[2], ntp1 -> lnk[2] = tmp2;
		tmp2 -> lnk[3] = ntp1, tmp2 -> lnk[2] -> lnk[3] = tmp2;
		}

	return ptr2;
	}

s* make(int R, int C)
	{
	return R ^ 1 ? join(make(R - 1, C), list(C)) : list(C);
	}

void disp(s *ptr)
	{
	s *I = ptr, *J = ptr;

	clrscr();
	printf("\n\tThe Structure :\n\t---------------\n\n\t");

	while(printf("%4d", J -> no), J = J -> lnk[0],
		J != I || (printf("\n\t"), I = J = I -> lnk[2]) != ptr);
	}