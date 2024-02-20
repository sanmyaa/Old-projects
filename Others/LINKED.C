/**
* BASIC OPERATIONS ON DOUBLY LINEAR LINKED LISTS
**/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIR  3
#define MAX_STU  3
#define MAX_YEAR 3

typedef struct movie  // NODES
	{
	char name[20];

	int FldNum[3];
	struct movie *field[8];
	}s;

typedef struct  // HEADS
	{
	s *link;
	char name[10];
	}H;

s* MAIN = 0;
H  DIR [MAX_DIR]  = {0, "Dir 'A'" , 0, "Dir 'B'" , 0, "Dir 'C'" },
   STU [MAX_STU]  = {0, "Stu 'P'" , 0, "Stu 'Q'" , 0, "Stu 'R'" },
   YEAR[MAX_YEAR] = {0, "Year 'X'", 0, "Year 'Y'", 0, "Year 'Z'"};

int main()
	{
	s *temp;
	char ctgr[] = "(i) Main List (ii) Director (iii) Studio  (iv) Year";
	int n = 0;

	void Insert (s*);
	void Modify (s*);
	void Delete (s**, int);
	void Display(s*);

	while(clrscr(), printf("\n\tLinked List :\n\t-------------\n\n\t1. Insert\n\t2. Modify\n\t3. Delete\n\t4. Exit\n\n\n\tUP   - Previous Node \tLEFT  - Previous List\n\tDOWN - Next Node    \tRIGHT - Next List\n"), Display(temp), printf("\n\tBrowsing by : %.*s\n\tAll Fields  : %s\n", 13, n / 2 * 14 + ctgr, ctgr))

		switch(getch())
			{
			case '1' : Insert(temp = (s*) malloc(sizeof(s)));                         break;
			case '2' : Modify(temp);                                                  break;
			case '3' : Delete(&temp, n), temp || (temp = MAIN);                       break;
			case '4' : return(0);

			case 72 : MAIN  && temp -> field[n + 1] && (temp = temp -> field[n + 1]); break;
			case 80 : MAIN  && temp -> field[n]     && (temp = temp -> field[n]);     break;
			case 75 : n > 1 && (n -= 2);                                              break;
			case 77 : n < 6 && (n += 2);
			}
	}

Link_Field    (s*, int, s**);   
Del_Link_Field(s*, int, s**);  

void Input(char *b, s *temp, int k, H *F, int Max)
	{
	int i;
	for(printf("\n\n\t"), i = 0 ; i < Max || !printf("\n\n") ; printf("%d. %s  ", 1 + i++, (F + i) -> name));

	while(fflush(stdin), !scanf("%d", &temp -> FldNum[k], printf("%s", b)) | temp -> FldNum[k] < 1 ^ temp -> FldNum[k] > Max);
	Link_Field(temp, k + 1 << 1, (s**)(F + --temp -> FldNum[k]));
	}

void Insert(s *temp)
	{
	clrscr();
	printf("\n\tInsert :\n\t--------");

	fflush(stdin);
	scanf("%19[^\n]s", temp -> name, printf("\n\n\tEnter Movie Name : "));

	Link_Field(temp, 0, &MAIN);
	Input("\tEnter Director Number : ", temp, 0, DIR , MAX_DIR);
	Input("\tEnter  Studio  Number : ", temp, 1, STU , MAX_STU);
	Input("\tEnter   Year   Number : ", temp, 2, YEAR, MAX_YEAR);
	}

void Display(s *temp)
	{
	MAIN ? printf("\n\tCurrent Node Details :\n\t----------------------\n\n\t Name     :  \" %s \"\n\t Director :  %s\n\t Studio   :  %s\n\t Year     :  %s\n", strupr(temp -> name), DIR[temp -> FldNum[0]].name, STU[temp -> FldNum[1]].name, YEAR[temp -> FldNum[2]].name) :  printf("\n\n\n\n\t[  LIST  IS  EMPTY  ]\n\n\n\n");
	}

void Modify(s *temp)
	{
	while(clrscr(), printf("\n\tModify :\n\t--------\n\n\t1. Modify NAME\n\t2. Modify DIRECTOR\n\t3. Modify STUDIO\n\t4. Modify YEAR\n\t5. Back\n"), Display(temp), MAIN)

		switch(getch())
			{
			case '1' : Del_Link_Field(temp, 0, &MAIN);
			           Del_Link_Field(temp, 2, (s**)(DIR  + temp -> FldNum[0]));
			           Del_Link_Field(temp, 4, (s**)(STU  + temp -> FldNum[1]));
			           Del_Link_Field(temp, 6, (s**)(YEAR + temp -> FldNum[2]));

			           fflush(stdin);
			           scanf("%19[^\n]s", temp -> name, printf("\n\n\tEnter Movie Name : "));

			           Link_Field(temp, 0, &MAIN);
			           Link_Field(temp, 2, (s**)(DIR  + temp -> FldNum[0]));
			           Link_Field(temp, 4, (s**)(STU  + temp -> FldNum[1]));
			           Link_Field(temp, 6, (s**)(YEAR + temp -> FldNum[2]));
			           break;

			case '2' : Del_Link_Field(temp, 2, (s**)(DIR  + temp -> FldNum[0]));
			           Input("\tEnter Director Number : ", temp, 0, DIR, MAX_DIR);
			           break;

			case '3' : Del_Link_Field(temp, 4, (s**)(STU  + temp -> FldNum[1]));
			           Input("\tEnter  Studio  Number : ", temp, 1, STU, MAX_STU);
			           break;

			case '4' : Del_Link_Field(temp, 6, (s**)(YEAR + temp -> FldNum[2]));
			           Input("\tEnter   Year   Number : ", temp, 2, YEAR, MAX_YEAR);
			           break;

			case '5' : return;
			}
	}

void Delete(s **temp, int NodeNo)
	{
	if(MAIN)
		{
		s *junk = *temp;

		Del_Link_Field(*temp, 0, &MAIN);
		Del_Link_Field(*temp, 2, (s**)(DIR  + (*temp) -> FldNum[0]));
		Del_Link_Field(*temp, 4, (s**)(STU  + (*temp) -> FldNum[1]));
		Del_Link_Field(*temp, 6, (s**)(YEAR + (*temp) -> FldNum[2]));

		*temp = (*temp) -> field[NodeNo + !((*temp) -> field[NodeNo])];
		free(junk);
		}
	}

Link_Field(s *temp, int Ind, s **F)
	{
	if(*F && strcmpi((*F) -> name, temp -> name) <= 0)
		{
		s *ptr;

		for(ptr = *F ; ptr -> field[Ind] && strcmpi(ptr -> field[Ind] -> name, temp -> name) <= 0 ; ptr = ptr -> field[Ind]);
		(temp -> field[Ind] = ptr -> field[Ind]) && (ptr -> field[Ind] -> field[Ind + 1] = temp);

		ptr  -> field[Ind]     = temp;
		temp -> field[Ind + 1] = ptr;
		}
	else
		{
		(temp -> field[Ind] = *F) && ((*F) -> field[Ind + 1] = temp) ;
		temp -> field[Ind + 1] = 0;

		*F = temp;
		}
	}

Del_Link_Field(s *temp, int Ind, s **F)
	{
	if(*F - temp)
		(temp -> field[Ind + 1] -> field[Ind] = temp -> field[Ind]) && (temp -> field[Ind] -> field[Ind + 1] = temp -> field[Ind + 1]);
	else
		(*F = temp -> field[Ind]) && ((*F) -> field[Ind + 1] = 0);
	}