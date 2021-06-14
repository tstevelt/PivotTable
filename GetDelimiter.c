
#include	"PivotTable.h"

char GetDelimiter ( char xbuffer[] )
{
	int		CommaCount, TabCount, PipeCount, ndx;
	char	Delim;

	CommaCount = TabCount = PipeCount = 0;

	for ( ndx = 0; ndx < strlen(xbuffer); ndx++ )
	{
		switch ( xbuffer[ndx] )
		{
			case ',': 
				CommaCount++; 
				break;

			case '|': 
				PipeCount++; 
				break;

			case '\t': 
				TabCount++; 
				break;

			case '\n':
			case '\r':
				xbuffer[ndx] = '\0';
				break;
		}
	}

	if ( CommaCount > PipeCount && CommaCount > TabCount )
	{
		Delim = ',';
		if ( Debug )
		{
			printf ( "Setting delimiter to comma\n" );
		}
	}
	else if ( PipeCount > CommaCount && PipeCount > TabCount )
	{
		Delim = '|';
		if ( Debug )
		{
			printf ( "Setting delimiter to pipe\n" );
		}
	}
	else if ( TabCount > CommaCount && TabCount > PipeCount )
	{
		Delim = '\t';
		if ( Debug )
		{
			printf ( "Setting delimiter to tab\n" );
		}
	}
	else
	{
		printf ( "Cannot determine delimiter\n" );
		exit ( 1 );
	}

	return ( Delim );
}
