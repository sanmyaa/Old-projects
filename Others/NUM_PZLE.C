/**
* A NUMBER PUZZLE GAME
*
* MOVE_BLANK  !=  0  MEANS THE ARROW KEYS WILL MAKE THE BLANK SQUARE MOVE ACCORDINGLY
* MOVE_BLANK  ==  0  MEANS THE THE TILES IN CLOSEST PROXIMITY WILL SLIDE INSTEAD OF THE BLANK SQUARE
*
* ALTERNATIVE CONTROL KEYS :
* --------------------------
* BACKSPACE -> UNDO/REDO LAST MOVE
* ESC       -> EXIT
* 8         -> UP
* 2         -> DOWN
* 4         -> LEFT
* 6         -> RIGHT
**/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MOVE_BLANK 1

void set(int *a, int *r, int *c)
	{
	int i, j, t;

	randomize();

	for(a[i = j = 0] = random(20) ; j < i || (!a[i] && (t = i), *a ^ 1 || (a[i = 0] = random(20)), a[j = 0, ++i] = random(20), i) < 20 ; j++)
		a[i] ^ a[j] && a[i] ^ i + 1 || (a[i] = random(20), j = -1);

	*r = t / 5;
	*c = t % 5;
	}

int chk(int *a)
	{
	int i, j;

	for(i = j = 0 ; i < 20 ; a[i] ^ i++ + 1 || ++j);
	return j;
	}

char undo(char b)
	{
	switch(b)
		{
		case 72 : case '8' : return '2';
		case 80 : case '2' : return '8';
		case 75 : case '4' : return '6';
		case 77 : case '6' : return '4';
		default : return 0;
		}
	}

char draw(int [4][5], unsigned, int, int, int);
char success(unsigned);

int play(int a[4][5], int r, int c)
	{
	unsigned m = 0, d = 0;
	char g = 0, p = 0;

	#if MOVE_BLANK
		#define LOCK_BLANK
		#define LOCK_NUMBR /##/
	#else
		#define LOCK_NUMBR
		#define LOCK_BLANK /##/
	#endif

	while(g = (d = chk(*a)) < 19 ? draw(a, m, d, r, c) : success(m), 1)
		switch(g ^ 'X' && g ^ 'x' && g ^ 8 || (g = undo(p)), g)
			{
			LOCK_NUMBR case 80 : case '2' :
			LOCK_BLANK case 72 : case '8' :
			                                r > 0 && (a[r][c] = a[r - 1][c], a[--r][c] = 0, m++, p = g);
			                                break;
			LOCK_NUMBR case 72 : case '8' :
			LOCK_BLANK case 80 : case '2' : 
			                                r < 3 && (a[r][c] = a[r + 1][c], a[++r][c] = 0, m++, p = g);
			                                break;
			LOCK_NUMBR case 77 : case '6' :
			LOCK_BLANK case 75 : case '4' : 
			                                c > 0 && (a[r][c] = a[r][c - 1], a[r][--c] = 0, m++, p = g);
			                                break;
			LOCK_NUMBR case 75 : case '4' :
			LOCK_BLANK case 77 : case '6' : 
			                                c < 4 && (a[r][c] = a[r][c + 1], a[r][++c] = 0, m++, p = g);
											break;
													  											
			case 'E' : case 'e' : case 27 : return 0;
			case 'N' : case 'n' : return 1;
			}
	}

int main(void)
	{
	int a[4][5], r, c;

	while(set(*a, &r, &c), play(a, r, c));
	return 0;
	}

#define SU(X) for(putchar(218), i = X ; i-- || !putchar(191) ; putchar(196))
#define SM(X) for(putchar(195), i = X ; i-- || !putchar(180) ; putchar(196))
#define SD(X) for(putchar(192), i = X ; i-- || !putchar(217) ; putchar(196))
#define SA(X) for(putchar(198), i = X ; i-- || !putchar(181) ; putchar(205))

#define BU        for(printf(" %c %c", 254, 201), i = 4 ; i-- || !printf("%c%c%c%c %c", 205, 205, 205, 187, 179) ; printf("%c%c%c%c", 205, 205, 205, 203))
#define BML       for(printf(" %c %c", 254, 204), i = 4 ; i-- || !printf("%c%c%c%c %c", 205, 205, 205, 185, 179) ; printf("%c%c%c%c", 205, 205, 205, 206))
#define BMN(X, Y) for(printf(" %d %c", Y, 186), i = 0 ; i < 5 || !printf(" %c", 179) ; putchar(186), i++) printf(X[i] ? X[i] / 10 ? " %d" : " %d " : "%c%c%c", X[i] ? X[i] : 32, 2, 32)
#define BD        for(printf(" %c %c", 254, 200), i = 4 ; i-- || !printf("%c%c%c%c %c", 205, 205, 205, 188, 179) ; printf("%c%c%c%c", 205, 205, 205, 202))

char draw(int a[4][5], unsigned moves, int box, int r, int c)
	{
	int i;

	clrscr();
	printf("\n\n\n     ");

	SU(8);
	for(printf(" %c", 214), i = 0 ; i < 45 || !printf("%c ", 183) ; i++) putchar(196);
	SU(8);
	printf("\n     %c %c%c  %c%c %c %c%*c %c %c%c  %c%c %c\n     %c   %c%c   %c %c%*c%c  NUMBER   PUZZLE  %c%c%*c %c   %c%c   %c\n     %c %c%c  %c%c %c %c%*c %c %c%c  %c%c %c\n     ", 179, 219, 219, 219, 219, 179, 186, 46, 186, 179, 219, 219, 219, 219, 179, 179, 219, 219, 179, 186, 12, 4, 4, 4, 4, 12, 186, 179, 219, 219, 179, 179, 219, 219, 219, 219, 179, 186, 46, 186, 179, 219, 219, 219, 219, 179);
	SD(8);
	for(printf(" %c", 211), i = 0 ; i < 45 || !printf("%c ", 189) ; i++) putchar(196);
	SD(8);

	printf("\n\n     %c ", 178);
	SU(25);  SU(20);  SU(14);

	for(printf(" %c\n     %c %c   %c", 178, 178, 179, 254), i = 1 ; i < 6 ; i++) printf(" %d %c", i, 254);
	printf(" %c%c %c MOVES     : %-5u%c%c%*c KEYS %c%*c %c\n     %c %c", 179, 179, 219, moves, 179, 179, 4, 4, 4, 4, 179, 178, 178, 179);

	BU;  SD(20);  SA(14);
	printf(" %c\n     %c %c", 178, 178, 179);

	BMN(a[0], 1);  SU(20);
	printf("%c  %c  %c  UP    %c %c\n     %c %c", 179, 15, 30, 179, 178, 178, 179);

	BML;
	printf("%c %c SQUARES   : 20 %c %c%c  %c  %c  DOWN  %c %c\n     %c %c", 179, 5, 5, 179, 179, 15, 31, 179, 178, 178, 179);

	BMN(a[1], 2);  SM(20);
	printf("%c  %c  %c  LEFT  %c %c\n     %c %c", 179, 15, 17, 179, 178, 178, 179);

	BML;
	printf("%c %c PLACED    : %2d   %c%c  %c  %c  RIGHT %c %c\n     %c %c", 179, 1, box, 179, 179, 15, 16, 179, 178, 178, 179);

	BMN(a[2], 3);
	printf("%c %c MISPLACED : %2d   %c", 179, 1, 20 - box, 179);
	SM(14);

	printf(" %c\n     %c %c", 178, 178, 179);
	BML;  SD(20);
	printf("%c  %c  X  UNDO  %c %c\n     %c %c", 179, 4, 179, 178, 178, 179);

	BMN(a[3], 4);  SU(20);
	printf("%c  %c  N  NEW   %c %c\n     %c %c", 179, 4, 179, 178, 178, 179);

	BD;
	printf("%c %c R = %d %c C = %d %c  %c%c  %c  E  EXIT  %c %c\n     %c ", 179, 254, r + 1, 254, c + 1, 254, 179, 179, 4, 179, 178, 178);

	SD(25);  SD(20);  SD(14);
	printf(" %c\n     ", 178);

	return getch();
	}

#include <dos.h>

#define DU(W, X)  for(printf("%*c", (W) - 1, 218), i = (X) + 4 ; i-- || !printf("%c\n", 191); putchar(196));\
                  for(printf("%*c %c", (W) - 1, 179, 201), i = X ; i-- || !printf("%c %c\n", 187, 179); putchar(205))
#define DM(W, X)  printf("%*c %c%*c %c\n", (W) - 1, 179, 186, (X) + 1, 186, 179)
#define DD(W, X)  for(printf("%*c %c", (W) - 1, 179, 200), i = X ; i-- || !printf("%c %c\n", 188, 179); putchar(205));\
                  for(printf("%*c", (W) - 1, 192), i = (X) + 4 ; i-- || !printf("%c\n", 217); putchar(196))

#define MS1(X)    printf("%*c %c%*c %c %*.*s%*c %c  %c %c\n", 20, 179, 186, 4, 5, 5, 22 - (X), 21 - (X) * 2, (X) + "YOU HAVE SUCCEEDED !!", (X) + 3, 5, 5, 186, 179)
#define MS2(X, Y) printf("%*c %c%*c  %.*s", 20, 179, 186, 7, 6, X, "Total Moves : ") && X < 14 && printf("%*c%*c %c\n", 22 - (X), 6, 6, 186, 179) || printf("%5u%*c%*c %c\n", Y, 17 - (X), 6, 6, 186, 179)

char success(unsigned moves)
	{
	int R, K, i;
	char c;

	for(clrscr(), delay(200), R = 6, K = 30 ; K ; R && R-- || K--)
		{
		clrscr();

		for(i = R + 6 ; i-- ; putchar('\n'));
		DU((7 + R) * 3, (6 - R) * 6);
		for(i = 0 ; i < (6 - R) * 2 ; i++)
			switch((K <= 28) + (K <= 17) + (K <= 2) + (K == 1))
				{
				case 4  : if(i == 9 && printf("%*c %c%*c  Press  'N'  for  NEW GAME%*c %c\n", 20, 179, 186, 6, 15, 4, 186, 179)) break;
				case 3  : if(i == 8 && printf("%*c %c%*c  Press  'E'  to   EXIT%*c %c\n", 20, 179, 186, 6, 15, 8, 186, 179)) break;
				case 2  : if(i == 5 && (K > 3  ? MS2(18 - K, moves) : MS2(14, moves))) break;
				case 1  : if(i == 3 && (K > 18 ? MS1(K - 18) : MS1(0))) break;
				default : DM((7 + R) * 3, (6 - R) * 6);
				}
		DD((7 + R) * 3, (6 - R) * 6);

		delay(R ? 30 : K ^ 29 && K ^ 18 && K ^ 3 ? 25 : 100);
		}

	while(1)
		switch(c = getch()) case 'E' : case 'e' : case 27 : case 'N' : case 'n' : return c;
	}