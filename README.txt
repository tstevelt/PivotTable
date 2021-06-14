

USAGE: PivotTable file col1      <function [arg]>
USAGE: PivotTable file col1 col2 <function [arg]>
Functions:
  -count
  -sum column
  -avg column
  -min column
  -max column

Background:
I got tired of pulling CSV files from my AWS Linux server back to my iMac to create Pivot Tables in Open Office.

The sample.csv file is from an Apache Server access_log file.  The access_log file was processed with ApacheLogToCSV program.
* Uses pipe delimiters.
* Breaks up date and time and formats date as mm/dd/yy
* The second field in the log file contains the Country Code (courtesy of MaxMind GeoIP).

See https://github.com/tstevelt/ApacheLogToCSV

Please contact me if there are other pivot table functions you like to use.

