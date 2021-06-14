
#include	"PivotTable.h"

int GetTokens ( char xbuffer[] )
{
	int		ndx, len;

	tokcnt = 0;
	tokens[tokcnt++] = xbuffer;
	len = strlen(xbuffer);
	for ( ndx = 0; ndx < len; ndx++ )
	{
		if ( xbuffer[ndx] == Delimiter )
		{
			xbuffer[ndx] = '\0';
			ndx++;
			if ( xbuffer[ndx] != '\0' )
			{
				tokens[tokcnt++] = &xbuffer[ndx];
			}
		}
	}

	return ( tokcnt );
}
