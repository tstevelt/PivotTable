/*----------------------------------------------------------------------------
	Program : PivotTable.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Jun 2021
	Synopsis: Read delimited file, create and output a pivot table
	Return  : 

	MIT License
	-----------

	Copyright (c) 2021 Tom Stevelt (https://www.silverhammersoftware.com)
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
			
	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/

#define		MAIN
#include		"PivotTable.h"

static int CountDecimals ( char String[] )
{
	int		rv, ndx, len;

	if ( strchr ( String, '.' ) == NULL )
	{
		return ( 0 );
	}

	rv = len = strlen( String );
	for ( ndx = 0; ndx < len; ndx++, rv-- )
	{
		if ( String[ndx] == '.' )
		{
			rv--;
			break;
		}
	}
	return ( rv );
}

int main ( int argc, char *argv[] )
{
	char	xbuffer[1024];
	int		lineno;
	int		rv, ndx, len;
	int		ndx1, ndx2, Offset;
	long	Location;
	char	dbuf[48];
	int		Decimals = 0;

	GetArgs ( argc, argv );

	lineno = 0;
	Index1 = Index2 = -1;
	while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
	{
		lineno++;

		if ( lineno == 1 && Delimiter == '?' )
		{
			Delimiter = GetDelimiter ( xbuffer );
		}

		tokcnt = GetTokens ( xbuffer );

		if ( lineno == 1 )
		{
			GetIndex();
			Location = ftell ( ifp );
			GetDimensions ( Location );
			continue;
		}
		
		if ( Dimensions == 1 )
		{
			for ( ndx1 = 0; ndx1 < Dimension1; ndx1++ )
			{
				if ( strcmp ( Labels1[ndx1].Label, tokens[Index1] ) == 0 )
				{
					break;
				}
			}
			if ( ndx1 >= Dimension1 )
			{
				printf ( "Cannot find %s in labels\n", tokens[Index1] );
				exit ( 1 );
			}

			Offset = ndx1;

			switch ( Function )
			{
				case FUNCTION_COUNT:
					CellArray[Offset].intValue++;
					break;
				case FUNCTION_SUM:
				case FUNCTION_AVG:
					CellArray[Offset].intValue++;
					CellArray[Offset].dblValue +=  atof ( tokens[IndexMath] );
					break;
				case FUNCTION_MIN:
					if ( CellArray[Offset].intValue == 0 || CellArray[Offset].dblValue > atof ( tokens[IndexMath] ) )
					{
						CellArray[Offset].dblValue =  atof ( tokens[IndexMath] );
					}
					CellArray[Offset].intValue++;
					break;
				case FUNCTION_MAX:
					if ( CellArray[Offset].intValue == 0 || CellArray[Offset].dblValue < atof ( tokens[IndexMath] ) )
					{
						CellArray[Offset].dblValue =  atof ( tokens[IndexMath] );
					}
					CellArray[Offset].intValue++;
					break;
			}
		}
		else
		{
			for ( ndx1 = 0; ndx1 < Dimension1; ndx1++ )
			{
				if ( strcmp ( Labels1[ndx1].Label, tokens[Index1] ) == 0 )
				{
					break;
				}
			}
			if ( ndx1 >= Dimension1 )
			{
				printf ( "Cannot find %s in labels\n", tokens[Index1] );
				exit ( 1 );
			}

			for ( ndx2 = 0; ndx2 < Dimension2; ndx2++ )
			{
				if ( strcmp ( Labels2[ndx2].Label, tokens[Index2] ) == 0 )
				{
					break;
				}
			}
			if ( ndx2 >= Dimension2 )
			{
				printf ( "Cannot find %s in labels\n", tokens[Index2] );
				exit ( 1 );
			}


			Offset = ndx1 * Dimension2 + ndx2;
			if ( Debug > 1 )
			{
				printf ( "%s(%d) %s(%d) %d\n", tokens[Index1], ndx1, tokens[Index2], ndx2, Offset );
			}

			switch ( Function )
			{
				case FUNCTION_COUNT:
					CellArray[Offset].intValue++;
					break;
				case FUNCTION_SUM:
				case FUNCTION_AVG:
					CellArray[Offset].intValue++;
					CellArray[Offset].dblValue +=  atof ( tokens[IndexMath] );
					break;
				case FUNCTION_MIN:
					if ( CellArray[Offset].intValue == 0 || CellArray[Offset].dblValue > atof ( tokens[IndexMath] ) )
					{
						CellArray[Offset].dblValue =  atof ( tokens[IndexMath] );
					}
					CellArray[Offset].intValue++;
					break;
				case FUNCTION_MAX:
					if ( CellArray[Offset].intValue == 0 || CellArray[Offset].dblValue < atof ( tokens[IndexMath] ) )
					{
						CellArray[Offset].dblValue =  atof ( tokens[IndexMath] );
					}
					CellArray[Offset].intValue++;
					break;
			}
		}

		if ( HasMath == 1 )
		{
			rv = CountDecimals ( tokens[IndexMath] );
			if ( Decimals < rv )
			{
				Decimals = rv;
			}
		}
	}

	if ( Function == FUNCTION_AVG )
	{
		if ( Decimals < 2 )
		{
			Decimals = 2;
		}
	}

	if ( Dimensions == 1 )
	{
		switch ( Function )
		{
			case FUNCTION_COUNT:
				printf ( "COUNT %s\n", Column1 );
				break;
			case FUNCTION_SUM:
				printf ( "SUM %s\n", ColumnMath );
				break;
			case FUNCTION_AVG:
				printf ( "AVG %s\n", ColumnMath );
				break;
			case FUNCTION_MIN:
				printf ( "MIN %s\n", ColumnMath );
				break;
			case FUNCTION_MAX:
				printf ( "MAX %s\n", ColumnMath );
				break;
		}
		for ( ndx1 = 0; ndx1 < Dimension1; ndx1++ )
		{
			printf ( "%-*.*s", Width1, Width1, Labels1[ndx1].Label );

			Offset = ndx1;
			switch ( Function )
			{
				case FUNCTION_COUNT:
					printf ( " %8d", CellArray[Offset].intValue );
					break;
				case FUNCTION_SUM:
				case FUNCTION_MIN:
				case FUNCTION_MAX:
					printf ( " %12.*f", Decimals, CellArray[Offset].dblValue );
					break;
				case FUNCTION_AVG:
					if ( CellArray[Offset].intValue > 0 )
					{
						printf ( " %12.*f", Decimals, CellArray[Offset].dblValue / (double) CellArray[Offset].intValue );
					}
					else
					{
						printf ( " %12.*f", Decimals, 0.0 );
					}
					break;
			}

			printf ( "\n" );
		}
	}
	else
	{
		switch ( Function )
		{
			case FUNCTION_COUNT:
				printf ( "COUNT %s %s\n", Column1, Column2 );
				break;
			case FUNCTION_SUM:
				printf ( "SUM %s\n", ColumnMath );
				break;
			case FUNCTION_AVG:
				printf ( "AVG %s\n", ColumnMath );
				break;
			case FUNCTION_MIN:
				printf ( "MIN %s\n", ColumnMath );
				break;
			case FUNCTION_MAX:
				printf ( "MAX %s\n", ColumnMath );
				break;
		}
		for ( ndx = 0; ndx < Dimension1 * Dimension2; ndx++ )
		{
			switch ( Function )
			{
				case FUNCTION_COUNT:
					len = sprintf ( dbuf, "%d", CellArray[ndx].intValue );
					break;
				case FUNCTION_SUM:
				case FUNCTION_MIN:
				case FUNCTION_MAX:
				case FUNCTION_AVG:
					len = sprintf ( dbuf, "%.*f", Decimals, CellArray[ndx].dblValue );
					break;
			}
			if ( Width2 < len )
			{
				Width2 = len;
				if ( Debug )
				{
					printf ( "Increase Width2 to %d\n", Width2 );
				}
			}
		}

		printf ( "%-*.*s", Width1, Width1, " " );
		for ( ndx2 = 0; ndx2 < Dimension2; ndx2++ )
		{
			printf ( " %-*.*s", Width2, Width2, Labels2[ndx2].Label );
		}
		printf ( "\n" );

		for ( ndx1 = 0; ndx1 < Dimension1; ndx1++ )
		{
			printf ( "%-*.*s", Width1, Width1, Labels1[ndx1].Label );

			for ( ndx2 = 0; ndx2 < Dimension2; ndx2++ )
			{
				Offset = ndx1 * Dimension2 + ndx2;
				switch ( Function )
				{
					case FUNCTION_COUNT:
						printf ( " %*d", Width2, CellArray[Offset].intValue );
						break;
					case FUNCTION_SUM:
					case FUNCTION_MIN:
					case FUNCTION_MAX:
						printf ( " %*.*f", Width2, Decimals, CellArray[Offset].dblValue );
						break;
					case FUNCTION_AVG:
						if ( CellArray[Offset].intValue > 0 )
						{
							printf ( " %*.*f", Width2, Decimals, CellArray[Offset].dblValue / (double)CellArray[Offset].intValue );
						}
						else
						{
							printf ( " %*.*f", Width2, Decimals, 0.0 );
						}
						break;
				}
			}

			printf ( "\n" );
		}
	}

	return ( 0 );
}
