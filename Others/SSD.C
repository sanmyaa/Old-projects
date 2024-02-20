/**
* C PROGRAM TO IMPLEMENT A SEVEN SEGMENT DISPLAY LIKE DISPLAY
**/

#include <stdio.h>
#include <conio.h>

#define  MX    8
#define  PNT   '.' - 48
#define  C(X)  switch(X){
#define  N(Y)  case Y :
#define  L(Z)  N(Z) printf(
#define  T     ); B
#define  B     break;
#define  E     }

void ssd(int l, int n)
	{
	C (n)
	N (0) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "  *  *  "    T
	      L (2)    "  *  *  "    T
	      L (3)    "  *  *  "    T
	      L (4)    "  *  *  "    T
	      L (5)    "  *  *  "    T
	      L (6)    "  ****  "    T E B

	N (1) C (l)

	      L (0)    "    *   "    T
	      L (1)    "   **   "    T
	      L (2)    "  * *   "    T
	      L (3)    "    *   "    T
	      L (4)    "    *   "    T
	      L (5)    "    *   "    T
	      L (6)    "  ****  "    T E B

	N (2) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "     *  "    T
	      L (2)    "     *  "    T
	      L (3)    "  ****  "    T
	      L (4)    "  *     "    T
	      L (5)    "  *     "    T
	      L (6)    "  ****  "    T E B

	N (3) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "     *  "    T
	      L (2)    "     *  "    T
	      L (3)    "  ****  "    T
	      L (4)    "     *  "    T
	      L (5)    "     *  "    T
	      L (6)    "  ****  "    T E B

	N (4) C (l)

	      L (0)    "     *  "    T
	      L (1)    "    **  "    T
	      L (2)    "   * *  "    T
	      L (3)    "  ****  "    T
	      L (4)    "     *  "    T
	      L (5)    "     *  "    T
	      L (6)    "     *  "    T E B

	N (5) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "  *     "    T
	      L (2)    "  *     "    T
	      L (3)    "  ***   "    T
	      L (4)    "     *  "    T
	      L (5)    "     *  "    T
	      L (6)    "  ***   "    T E B

	N (6) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "  *     "    T
	      L (2)    "  *     "    T
	      L (3)    "  ****  "    T
	      L (4)    "  *  *  "    T
	      L (5)    "  *  *  "    T
	      L (6)    "  ****  "    T E B

	N (7) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "     *  "    T
	      L (2)    "     *  "    T
	      L (3)    "     *  "    T
	      L (4)    "     *  "    T
	      L (5)    "     *  "    T
	      L (6)    "     *  "    T E B

	N (8) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "  *  *  "    T
	      L (2)    "  *  *  "    T
	      L (3)    "  ****  "    T
	      L (4)    "  *  *  "    T
	      L (5)    "  *  *  "    T
	      L (6)    "  ****  "    T E B

	N (9) C (l)

	      L (0)    "  ****  "    T
	      L (1)    "  *  *  "    T
	      L (2)    "  *  *  "    T
	      L (3)    "  ****  "    T
	      L (4)    "     *  "    T
	      L (5)    "     *  "    T
	      L (6)    "  ****  "    T E B

	N (PNT) C (l)

	      L (0)    "        "    T
	      L (1)    "        "    T
	      L (2)    "        "    T
	      L (3)    "        "    T
	      L (4)    "        "    T
	      L (5)    "        "    T
	      L (6)    "   *    "    T E E
	}

void u_intrfce()
	{
	int  i, j, k,   P;
	char a[MX + 1], c;

	for(*a = P = i = 0 ; clrscr(), printf("\n\t%*cSeven Segment Display\n\t%*c---------------------\n\n\n\tType a Number (Press ENTER to Exit) :  [%d / %d Digits]\n\n\t  %s\n\n\n\tSSD :\n\n\n\t  ", 20, ' ', 20, ' ', i, MX, a) ; a[i] = 0)
		{
		for(j = k = 0 ; k < i || (printf("\n\t  "), k = 0, ++j) <= 6 ; ssd(j, a[k++] - 48));
		switch (c = getch())
			{
			default : i < MX && (c > 47 & c < 58 || c == '.' & !P && ++P) && (a[i++] = c);
			          break;

			case 8  : i && i--, a[i] ^ '.' || P--;
			          break;

			case 13 : return;
			}
		}
	}

int main(void)
	{
	u_intrfce();
	return 0;
	}