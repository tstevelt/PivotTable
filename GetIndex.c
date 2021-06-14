
#include	"PivotTable.h"

void GetIndex ()
{
	int		ndx;

	Index1 = Index2 = IndexMath = -1;

	for ( ndx = 0; ndx < tokcnt; ndx++ )
	{
		if ( strcmp ( tokens[ndx], Column1 ) == 0 )
		{
			Index1 = ndx;
		}

		if ( Dimensions == 2 && strcmp ( tokens[ndx], Column2 ) == 0 )
		{
			Index2 = ndx;
		}

		if ( HasMath == 1 && strcmp ( tokens[ndx], ColumnMath ) == 0 )
		{
			IndexMath = ndx;
		}
	}

	if ( Dimensions == 1 )
	{
		if ( Index1 == -1 )
		{
			printf ( "Cannot find %s in header line\n", Column1 );
			exit ( 1 );
		}
	}
	else
	{
		if ( Index1 == -1 )
		{
			printf ( "Cannot find %s in header line\n", Column1 );
		}
		if ( Index2 == -1 )
		{
			printf ( "Cannot find %s in header line\n", Column2 );
		}
		if ( Index1 == -1 || Index2 == -1 )
		{
			exit ( 1 );
		}
	}

	if ( HasMath == 1 && IndexMath == -1 )
	{
		printf ( "Cannot find %s in header line\n", ColumnMath );
		exit ( 1 );
	}

	if ( Debug )
	{
		if ( Dimensions == 1 )
		{
			printf ( "%s %d\n", Column1, Index1 );
		}
		else
		{
			printf ( "%s %d, %s %d\n", Column1, Index1, Column2, Index2 );
		}

		if ( HasMath == 1 )
		{
			printf ( "%s %d\n", ColumnMath, IndexMath );
		}
	}
}
