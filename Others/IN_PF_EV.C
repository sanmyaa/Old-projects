/**
* INFIX TO POSTFIX CONVERSION AND POSTFIX EVALUATION
*
* MAX  =  MAXIMUM NUMBER OF CHARACTERS IN THE EXPRESSION
* DGT  =  MAXIMUM NUMBER OF DIGITS BEFORE AND AFTER THE DECIMAL POINT IN A FLOATING PT. NUMBER
**/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX 70
#define DGT 5

main()
	{
	char E[(MAX << 1) + 2];

	void   input    (char*);
	char*  topostf  (char*);
	double evalpostf(char*);

	input (E);
	printf("\n\n\n\t= %s  ( -ve signs replaced )", E);

	memcpy(E, topostf(E), (MAX << 1) + 2);
	printf("\n\n\n\t= %s  ( Postfix )", E);

	printf("\n\n\n\t= %g\n\n", evalpostf(E));

	getch();
	return 0;
	}

int chk(char c)
	{
	switch(c)
		{
		default  : return c > 47 & c < 58;
		case '.' : return 2;
		case '+' :
		case '-' :
		case '*' :
		case '/' :
		case '^' : return 3;
		case '(' : return 4;
		case ')' : return 5;
		case 8   : return 6;
		case 13  : return 7;
		case '~' : return 8;
		}
	}

void input(char *E)
	{
	int  i, k;
	char p, c,  *t;

	char  pushc(char*, char);
	char  popc (char*);
	char* prep (char*);

	for(*E = p = i = k = 0 ; clrscr(), printf("\n\tInfix Expression Evaluation :\n\t-----------------------------\n\n\tEnter Expression : ( %d Characters Left )\n\n\t  %s", MAX - i, E) ; p = i ? E[i - 1] : 0)
		{
		switch(chk(c = getch()))
			{
			case 1  : if(chk(strrev(E)[0]) < 3 ? strtol(E, &t, 10) : (long)(t = E), p = *t, t - E < DGT & (p ^ ')' | (strrev(E), 0) || i < MAX - 1 && pushc(E, '*') && ++i)) break; continue;
			case 2  : if(chk(strrev(E)[0]) < 3 ? strtol(E, &t, 10) : (long)(t = E), p = *t, p != '.'    & (p ^ ')' | (strrev(E), 0) || i < MAX - 1 && pushc(E, '*') && ++i)) break; continue;
                                                                                                    
			case 3  : if(p ^ '.' && (chk(p) ^ 3 && p ^ '(' && p) | c == '-') break; continue;

			case 4  : if(p ^ '.' && (chk(p) ^ 1 && p ^ ')' || i < MAX - 1 && pushc(E, '*') && ++i) && ++k) break; continue;
			case 5  : if(p ^ '.' && chk(p) ^ 3 && p ^ '(' && k > 0 && k--)                                 break; continue;

			case 6  : if(p) E[i - 1] ^ '(' || k--, E[i - 1] ^ ')' || ++k, popc(E) & i--; continue;
			case 7  : if(p && chk(p) ^ 3 && chk(p) ^ 2 && !k && prep(E)) return;

			default : continue;
			}

		i < MAX && pushc(E, c) & i++;
		}
	}

char* prep(char *a)
	{
	int i;

	for(i = strlen(a) - 1 ; i >= 0 ; i--)
		a[i] ^ '-' | (i && chk(a[i - 1]) ^ 3 && chk(a[i - 1]) ^ 4) || (a[i] = '~');

	return a;
	}
	
char* topostf(char *a)
	{
	char p[(MAX << 1) + 2], s[MAX + 1], *t;

	int  prio (char);
	char pushc(char*, char);
	char popc (char*);

	for(*p = *s = 0, pushc(a, ')'), pushc(s, '(') ; *s || !popc(p); a++)
		switch(chk(*a))
			{
			case 1 :
			case 2 : strtod (a, &t);
			         strncat(p, a, t - a);
			         pushc(p, ',');
			         a = --t;
			         break;

			case 3 : while(prio(s[strlen(s) - 1]) >= prio(*a) || !pushc(s, *a))
							pushc(p, popc(s)), pushc(p, ',');
			         break;

			case 4 : pushc(s, '(');
			         break;

			case 5 : while(s[strlen(s) - 1] ^ '(' || !popc(s))
							pushc(p, popc(s)), pushc(p, ',');
			         break;

			case 8 : pushc(s, '~');
			}

	return p;
	}

double evalpostf(char *p)
	{
	double s[(MAX >> 1) + 2];
	char   *t;

	double pushn(double*, double);
	double popn (double*);
	double oper (double B, char, double A);

	for(*s = 0, strcat(p, ",)"), t = strtok(p, ",") ; *t ^ ')' ; t = strtok(0, ","))
		switch(chk(*t))
			{
			case 1 :
			case 2 : pushn(s, atof(t)); break;

			case 3 : if(*t ^ '/' | !!s[*s] && (int)pushn(s, oper(popn(s), *t, popn(s))) | 1 ) break;

					   printf("\n\n\t'Divide by Zero Error' Encountered. Expression can't be evaluated.\n\t[ Press any key to exit ]"), getch();
			         exit(0);

			case 8 : pushn(s, -popn(s));
			}

	return popn(s);
	}

char pushc(char *a, char c)
	{
	return strncat(a, &c, 1), c;
	}

char popc(char *a)
	{
	char x = a[strlen(a) - 1];
	
	return *strrchr(a, x) = 0, x;
	}

int prio(char x)
	{
	switch(x)
		{
		default  : return 0;
		case '+' :
		case '-' : return 1;
		case '*' :
		case '/' : return 2;
		case '^' : return 3;
		case '~' : return 4;
		}
	}

double pushn(double *s, double n)
	{
	return s[++*s] = n;
	}

double popn(double *s)
	{
	return s[(*s)--];
	}

double oper(double X, char c, double Y)
	{
	switch(c)
		{
		case '+' : return X + Y;
		case '-' : return X - Y;
		case '*' : return X * Y;
		case '/' : return X / Y;
		case '^' : return pow(X, Y);
		}
	}