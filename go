

PivotTable sample.csv ID -count
echo "---"

PivotTable sample.csv STATUS -count
echo "---"

PivotTable sample.csv ID STATUS -count
echo "---"
PivotTable sample.csv ID STATUS -sum BYTES
echo "---"
PivotTable sample.csv ID STATUS -avg BYTES
echo "---"
PivotTable sample.csv ID STATUS -min BYTES
echo "---"
PivotTable sample.csv ID STATUS -max BYTES
echo "---"

echo "The following ADDR reports are truncated ..."
PivotTable sample.csv ADDR -count | head
echo "---"
PivotTable sample.csv ADDR -sum BYTES | head
echo "---"
PivotTable sample.csv ADDR -avg BYTES | head
echo "---"
PivotTable sample.csv ADDR -min BYTES | head
echo "---"
PivotTable sample.csv ADDR -max BYTES | head

