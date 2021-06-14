
#include		"PivotTable.h"

static void MyUsage ()
{
	printf ( "USAGE: PivotTable file col1      <function [arg]>\n" );
	printf ( "USAGE: PivotTable file col1 col2 <function [arg]>\n" );
	printf ( "Functions:\n" );
	printf ( "  -count\n" );
	printf ( "  -sum column\n" );
	printf ( "  -avg column\n" );
	printf ( "  -min column\n" );
	printf ( "  -max column\n" );
	exit ( 1 );
}

void GetArgs ( int argc, char *argv[] )
{
	int		xa;

	if ( argc < 4 )
	{
		MyUsage ();
	}

	if (( ifp = fopen ( argv[1], "r" )) == NULL )
	{
		printf ( "Cannot open input file\n" );
		exit ( 0 );
	}

	Column1 = argv[2];

	if ( argv[3][0] != '-' )
	{
		Column2 = argv[3];
		Dimensions = 2;
		xa = 4;
	}
	else
	{
		Column2 = NULL;
		Dimensions = 1;
		xa = 3;
	}

	Function = 0;
	HasMath = 0;
	Delimiter = '?';
	Debug = 0;
	for ( ; xa < argc; xa++ )
	{
		if ( strcmp ( argv[xa], "-count" ) == 0 )
		{
			Function = FUNCTION_COUNT;
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-sum" ) == 0 )
		{
			Function = FUNCTION_SUM;
			HasMath = 1;
			xa++;
			ColumnMath = argv[xa];
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-avg" ) == 0 )
		{
			Function = FUNCTION_AVG;
			HasMath = 1;
			xa++;
			ColumnMath = argv[xa];
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-min" ) == 0 )
		{
			Function = FUNCTION_MIN;
			HasMath = 1;
			xa++;
			ColumnMath = argv[xa];
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-max" ) == 0 )
		{
			Function = FUNCTION_MAX;
			HasMath = 1;
			xa++;
			ColumnMath = argv[xa];
		}
		else if ( xa + 1 < argc && strcmp ( argv[xa], "-delim" ) == 0 )
		{
			xa++;
			Delimiter = argv[xa][0];
		}
		else if ( strcmp ( argv[xa], "-d" ) == 0 )
		{
			Debug = 1;
		}
		else 
		{
			MyUsage ();
		}
	}

	if ( Function == 0 )
	{
		MyUsage ();
	}
}
