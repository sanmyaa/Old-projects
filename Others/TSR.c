/*
 |----------|--------------------------------------------------|
 | Encipher | <prog. name> <E> <inp. file> <outp. file> <key>  |
 |----------|--------------------------------------------------|
 | Decipher | <prog. name> <D> <inp. file> <outp. file> <key>  |
 |----------|--------------------------------------------------|
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==============================================
       THE 24 PLANES AS VERTEX QUADRUPLETS
===============================================*/

short planes [24][4] =
    {
     0,  8,  9,  1,
     6, 14, 15,  7,
     2, 10, 11,  3,
     4, 12, 13,  5,

     2, 10,  8,  0,
     3, 11,  9,  1,
     4, 12, 14,  6,
     5, 13, 15,  7,

     0,  6, 14,  8,
     1,  7, 15,  9,
     2,  4, 12, 10,
     3,  5, 13, 11,

     3,  1,  7,  5,
    11,  9, 15, 13,
    10,  8, 14, 12,
     2,  0,  6,  4,

     2,  4,  5,  3,
    10, 12, 13, 11,
     8, 14, 15,  9,
     0,  6,  7,  1,

     0,  1,  3,  2,
     8,  9, 11, 10,
    14, 15, 13, 12,
     6,  7,  5,  4
    };

/*==============================================
      FIRST LEVEL INITIALIZATION USING OTP
===============================================*/

#define  OTP  "otp.txt"

short prll_quad_mtr_no,
      mpp_actual_to_tssr [4][4];

void init_otp ();
void get_tss  (char [12], char [16]);
void put_tss  (char [16], char [12]);

/*==============================================
            ROTATIONS OF THE PLANES
===============================================*/

short rot_id [] =
    {
    0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230,
    1, 11, 21, 31, 41, 51, 61, 71, 81, 91, 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 201, 211, 221, 231
    };

void rotate   (char [16], short, short);
void bin2gry  (char [16], short [4][4]);
void gry2bin  (char [16], short [4][4]);
void e_scrmbl (char [16], char*);
void d_scrmbl (char [16], char*);

/*==============================================
          SECOND LEVEL INITIALIZATION
===============================================*/

void get_blk_tss  (char  [], char* [], long);
void put_blk_tss  (char* [], char  [], long);

/*==============================================
            ROTATIONS OF THE BLOCKS
===============================================*/

void rotblk       (char* [16], short, short);
void e_blk_scrmbl (char* [],   long,  char*);
void d_blk_scrmbl (char* [],   long,  char*);

/*==============================================
     THE 'main ()' FUNCTION AS DRIVER MODULE
===============================================*/

int main (int argc, char *argv [])
    {
    FILE *f1, *f2;
    char *x, *y, **z;
    long  sze1, sze2, sze3,
          i, tmp;

    if (argc ^ 6    ||
        argv [1][1] ||
        !(f1 = fopen (argv [2], "rb")) ||
        !(f2 = fopen (argv [3], "wb")))
            return 0;

    init_otp ();

    if (argv [1][0] == 'E' || argv [1][0] == 'e')
        {
        fseek (f1, 0, SEEK_END);
        tmp = ftell (f1);
        rewind (f1);

        sze1 = ceil (tmp / 12.0) * 12;
        x = (char*) malloc (sze1 * sizeof (char));
        sze2 = sze1 / 12 * 16;
        y = (char*) malloc (sze2 * sizeof (char));
        sze3 = sze2 / 16;
        z = (char**) malloc (sze3 * sizeof (char*));

        for (i = 0 ; i < tmp ; i++)
            fread (x + i, 1, 1, f1);
        while (i < sze1) x [i++] = ' ';

        srand (time (NULL));
        for (i = sze1 ; i ; i -= 12)
            get_tss  (x, y),
            e_scrmbl (y, argv [4]),
            x += 12, y += 16;
        y -= sze2;

        if (sze3 >= 16)
            get_blk_tss  (y, z, sze3),
            e_blk_scrmbl (z, sze3, argv [5]),
            put_blk_tss  (z, y, sze3);

        for (i = 0 ; i < sze2 ; i++)
            fwrite (y + i, 1, 1, f2);
        }
    else if (argv [1][0] == 'D' || argv [1][0] == 'd')
        {
        fseek (f1, 0, SEEK_END);
        tmp = ftell (f1);
        rewind (f1);

        sze1 = ceil (tmp / 16.0) * 16;
        y = (char*) malloc (sze1 * sizeof (char));
        sze3 = sze1 / 16;
        z = (char**) malloc (sze3 * sizeof (char*));
        sze2 = sze1 / 16 * 12;
        x = (char*) malloc (sze2 * sizeof (char));

        for (i = 0 ; i < tmp ; i++)
            fread (y + i, 1, 1, f1);
        while (i < sze1) y [i++] = ' ';

	if (sze3 >= 16)
	    get_blk_tss  (y, z, sze3),
	    d_blk_scrmbl (z, sze3, argv [5]),
	    put_blk_tss  (z, y, sze3);

        for (i = sze1 ; i ; i -= 16)
            d_scrmbl (y, argv [4]),
            put_tss  (y, x),
            y += 16, x += 12;
        x -= sze2;

        for (i = 0 ; i < sze2 ; i++)
            fwrite (x + i, 1, 1, f2);
	}

    return 0;
    }

/*==============================================
      DEFINITIONS OF THE UTILITY FUNCTIONS
===============================================*/

void init_otp ()
    {
    FILE *fp = fopen (OTP, "rt");
    int  i;

    fscanf (fp, "%hi", &prll_quad_mtr_no);
    for (i = 0 ; i < 16 ; i++)
        fscanf (fp, "%hi", mpp_actual_to_tssr [i / 4] + (i % 4));
    }

void get_tss (char inp [12], char a [16])
    {
    short *x = planes [4 * prll_quad_mtr_no],
          *y = mpp_actual_to_tssr [0],
           i, j;
    char tmp;

    for (i = 0 ; i < 4 ; i++)
    for (tmp = rand () % 256,
         j = 0 ; j < 4 ; j++)
            a [*x] = *y ^ 9999 ? tmp ^ inp [*y] : tmp,
            x++, y++;
    }

void put_tss (char a [16], char out [12])
    {
    short *x = planes [4 * prll_quad_mtr_no],
          *y = mpp_actual_to_tssr [0],
           i, j;
    char tmp;

    for (i = 0 ; i < 4 ; i++)
        {
        for (j = 0 ; y [j] ^ 9999 ; j++);
        for (tmp = a [x [j]], j = 0 ; j < 4 ; j++)
            *y ^ 9999 && (out [*y] = tmp ^ a [*x]),
            x++, y++;
        }
    }

void rotate (char a [16], short pln_no, short dir)   // dir : {0, 1}
    {
    short *T = planes [pln_no] + 3 * !dir,
           d = -dir | 1;                             // dir : 0 -> (+1) Right , 1 -> (-1) Left

    char C         = a [T [0]];
    a [T [0]]      = a [T [-d]];
    a [T [-d]]     = a [T [-d * 2]];
    a [T [-d * 2]] = a [T [-d * 3]];
    a [T [-d * 3]] = C;
    }

void bin2gry (char a [16], short pl [4][4])
    {
    int i;

    for (i = 0 ; i < 4 ; i++)
        a [pl [3][i]] ^= a [pl [2][i]],
        a [pl [2][i]] ^= a [pl [1][i]],
        a [pl [1][i]] ^= a [pl [0][i]];
    }

void gry2bin (char a [16], short pl [4][4])
    {
    int i;

    for (i = 0 ; i < 4 ; i++)
        a [pl [1][i]] ^= a [pl [0][i]],
        a [pl [2][i]] ^= a [pl [1][i]],
        a [pl [3][i]] ^= a [pl [2][i]];
    }

void e_scrmbl (char a [16], char *sq)
    {
    char c;

    while (c = *sq++)
        if (c >= 'a' && c <= 'x')
            rotate  (a, rot_id [c - 'a'] / 10,
                        rot_id [c - 'a'] % 10),
            bin2gry (a, (short (*)[4]) (planes + rot_id [c - 'a'] / 40 * 4));
        else if (c >= 'A' && c <= 'X')
            rotate  (a, rot_id [c - 'A' + 24] / 10,
                        rot_id [c - 'A' + 24] % 10),
            bin2gry (a, (short (*)[4]) (planes + rot_id [c - 'A' + 24] / 40 * 4));
    }

void d_scrmbl (char a [16], char *sq)
    {
    char  c;
    short i;

    for (i = 0 ; *sq ; i++, sq++);

    while (i-- && (c = *--sq))
        if (c >= 'a' && c <= 'x')
            gry2bin (a, (short (*)[4]) (planes + rot_id [c - 'a'] / 40 * 4)),
            rotate  (a, rot_id [c - 'a'] / 10,
                       !(rot_id [c - 'a'] % 10));
        else if (c >= 'A' && c <= 'X')
            gry2bin (a, (short (*)[4]) (planes + rot_id [c - 'A' + 24] / 40 * 4)),
            rotate  (a, rot_id [c - 'A' + 24] / 10,
                       !(rot_id [c - 'A' + 24] % 10));
    }

void get_blk_tss (char a [], char *z [], long len)
    {
    long i, j;

    for (i = j = 0 ; j < len ; i += 16, j++)
        z [j] = a + i;
    }

void put_blk_tss (char *z [], char a [], long len)
    {
    int  i, j;
    char *tmp = (char*) malloc (len * 16);

    for (i = 0 ; i < len ; i++)
    for (j = 0 ; j < 16 ; j++)
        tmp [i * 16 + j] = z [i][j];

    for (i = len * 16 - 1 ; i >= 0 ; i--)
        a [i] = tmp [i];
    free (tmp);
    }

void rotblk (char *z [16], short pln_no, short dir)   // dir : {0, 1}
    {
    short *T = planes [pln_no] + 3 * !dir,
           d = -dir | 1;                              // dir : 0 -> (+1) Right , 1 -> (-1) Left

    char *P        = z [T [0]];
    z [T [0]]      = z [T [-d]];
    z [T [-d]]     = z [T [-d * 2]];
    z [T [-d * 2]] = z [T [-d * 3]];
    z [T [-d * 3]] = P;
    }

void e_blk_scrmbl (char *z [], long len, char *sq)
    {
    long L = 0;
    char c;

    while (c = *sq++)
        if (c >= 'a' && c <= 'x')
            rotblk  (z + L, rot_id [c - 'a'] / 10,
                            rot_id [c - 'a'] % 10);
        else if (c >= 'A' && c <= 'X')
            rotblk  (z + L, rot_id [c - 'A' + 24] / 10,
                            rot_id [c - 'A' + 24] % 10);
        else if (c == '1') L + 23 < len && (L += 8);
        else if (c == '2') L > 7 && (L -= 8);
        else if (c == '3') ;
    }

void d_blk_scrmbl (char *z [], long len, char *sq)
    {
    long  L = 0;
    char  c;
    short i;

    for (i = 0 ; *sq ; i++, sq++)
        if      (*sq == '1') L + 23 < len ? (L += 8) : (*sq = '3');
        else if (*sq == '2') L > 7 ? (L -= 8) : (*sq = '3');

    while (i-- && (c = *--sq))
        if (c >= 'a' && c <= 'x')
            rotblk  (z + L, rot_id [c - 'a'] / 10,
                          !(rot_id [c - 'a'] % 10));
        else if (c >= 'A' && c <= 'X')
            rotblk  (z + L, rot_id [c - 'A' + 24] / 10,
                          !(rot_id [c - 'A' + 24] % 10));
        else if (c == '2') L += 8;
        else if (c == '1') L -= 8;
        else if (c == '3') ;
    }
