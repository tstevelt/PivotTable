
#include		"PivotTable.h"

void GetDimensions ( long Location )
{
	char	tfn[128];
	FILE	*tfp;
	char	xbuffer[1024];
	char	cmdline[512];
	long	rv;
	long	Size;
	int		ndx, len;

	Width1 = Width2 = 0;

	sprintf ( tfn, "PivotTable.tmp" );

	if (( tfp = fopen ( tfn, "w" )) == NULL )
	{
		printf ( "Cannot create temp file %s\n", tfn );
		exit ( 0 );
	}

	if (( rv = fseek ( ifp, Location, SEEK_SET )) == -1 )
	{
		printf ( "fseek %d %s\n", errno, strerror(errno) );
	}
		
	while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
	{
		tokcnt = GetTokens ( xbuffer );
		if ( tokcnt <= Index1 )
		{
			continue;
		}

		len = strlen(tokens[Index1]);
		if ( len >= MAXLABLEN )
		{
			printf ( "%s exceeds MAXLABLEN of %d\n", tokens[Index1], MAXLABLEN );
			exit ( 1 );
		}
		if ( Width1 < len )
		{
			Width1 = len;
		}
		fprintf ( tfp, "%s\n", tokens[Index1] );
	}

	fclose ( tfp );

	sprintf ( cmdline, "sort -u -o %s %s", tfn, tfn );
	system ( cmdline );
	tfp = fopen ( tfn, "r" );
	Dimension1 = 0;
	while ( fgets ( xbuffer, sizeof(xbuffer), tfp ) != NULL )
	{
		Dimension1++;
	}
		
	Labels1 = calloc ( Dimension1, sizeof(LABEL_RECORD) );
	rewind ( tfp );
	ndx = 0;
	while ( fgets ( xbuffer, sizeof(xbuffer), tfp ) != NULL )
	{
		len = strlen(xbuffer) - 1;
		xbuffer[len] = '\0';
		sprintf ( Labels1[ndx++].Label, "%s", xbuffer );
	}
	fclose ( tfp );

	if ( Debug )
	{
		printf ( "Dimension1 %d, Width1 %d\n", Dimension1, Width1 );
	}
	
	if ( Dimensions == 2 )
	{
		if (( tfp = fopen ( tfn, "w" )) == NULL )
		{
			printf ( "Cannot create temp file %s\n", tfn );
			exit ( 0 );
		}

		if (( rv = fseek ( ifp, Location, SEEK_SET )) == -1 )
		{
			printf ( "fseek %d %s\n", errno, strerror(errno) );
		}
			
		while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
		{
			tokcnt = GetTokens ( xbuffer );
			if ( tokcnt <= Index2 )
			{
				continue;
			}

			len = strlen(tokens[Index2]);
			if ( len >= MAXLABLEN )
			{
				printf ( "%s exceeds MAXLABLEN of %d\n", tokens[Index2], MAXLABLEN );
				exit ( 1 );
			}
			if ( Width2 < len )
			{
				Width2 = len;
			}
			fprintf ( tfp, "%s\n", tokens[Index2] );
		}

		fclose ( tfp );

		sprintf ( cmdline, "sort -u -o %s %s", tfn, tfn );
		system ( cmdline );
		tfp = fopen ( tfn, "r" );
		Dimension2 = 0;
		while ( fgets ( xbuffer, sizeof(xbuffer), tfp ) != NULL )
		{
			Dimension2++;
		}
		Labels2 = calloc ( Dimension2, sizeof(LABEL_RECORD) );
		rewind ( tfp );
		ndx = 0;
		while ( fgets ( xbuffer, sizeof(xbuffer), tfp ) != NULL )
		{
			len = strlen(xbuffer) - 1;
			xbuffer[len] = '\0';
			sprintf ( Labels2[ndx++].Label, "%s", xbuffer );
		}
		fclose ( tfp );

		if ( Debug )
		{
			printf ( "Dimension2 %d, Width2 %d\n", Dimension2, Width2 );
		}
	}

	unlink ( tfn );

	if (( rv = fseek ( ifp, Location, SEEK_SET )) == -1 )
	{
		printf ( "fseek %d %s\n", errno, strerror(errno) );
	}
	
	if ( Dimensions == 1 )
	{
		Size = Dimension1 * sizeof(CELL_RECORD);
	}
	else
	{
		Size = Dimension1 * Dimension2 * sizeof(CELL_RECORD);
	}
	if (( CellArray = malloc ( Size )) == NULL )
	{
		printf ( "malloc %d %s\n", errno, strerror(errno) );
		exit ( 1 );
	}
	memset ( CellArray, '\0', Size );
}
