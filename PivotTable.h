

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<errno.h>

#ifdef MAIN
#define		TYPE	/* */
#else
#define		TYPE	extern
#endif

TYPE	FILE	*ifp;
TYPE	char	*Column1;
TYPE	char	*Column2;
TYPE	char	*ColumnMath;
TYPE	int		Dimensions;
TYPE	int		Debug;
TYPE	char	Delimiter;

#define		FUNCTION_COUNT	1
#define		FUNCTION_SUM	2
#define		FUNCTION_AVG	3
#define		FUNCTION_MIN	4
#define		FUNCTION_MAX	5
TYPE	int		Function;

typedef struct
{
	int		intValue;
	double	dblValue;
} CELL_RECORD;

TYPE	CELL_RECORD		*CellArray;

TYPE	int		Index1;
TYPE	int		Index2;
TYPE	int		IndexMath;
TYPE	int		HasMath;
TYPE	int		Dimension1;
TYPE	int		Dimension2;

#define		MAXLABLEN	20
typedef struct
{
	char	Label[MAXLABLEN];
} LABEL_RECORD;
TYPE	LABEL_RECORD	*Labels1;
TYPE	LABEL_RECORD	*Labels2;
TYPE	int		Width1;
TYPE	int		Width2;

#define		MAXTOKS		100
TYPE	char	*tokens[MAXTOKS];
TYPE	int		tokcnt;

/*----------------------------------------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------------------------------------*/

/* GetArgs.c */
void GetArgs ( int argc , char *argv []);

/* GetDelimiter.c */
char GetDelimiter ( char xbuffer []);

/* GetDimensions.c */
void GetDimensions ( long Location );

/* GetIndex.c */
void GetIndex ( void );

/* GetTokens.c */
int GetTokens ( char xbuffer []);

/* PivotTable.c */
int main ( int argc , char *argv []);
