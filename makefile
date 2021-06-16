
CFLAGS = -Wall
PROG = PivotTable
LIB = PivotTable.a
DIR = /usr/local/bin

FILES = \
	$(LIB)(PivotTable.o)	\
	$(LIB)(GetDelimiter.o)	\
	$(LIB)(GetIndex.o)		\
	$(LIB)(GetDimensions.o)	\
	$(LIB)(GetTokens.o)	\
	$(LIB)(GetArgs.o)

.SILENT:

$(PROG): $(LIB)
	echo "using gcc to load $(PROG)"
	gcc -o $(PROG) $(LIB)
	strip $(PROG)
	ls -l $(PROG)

$(LIB): $(FILES)

$(FILES): PivotTable.h

install:
	cp -pv $(PROG) $(DIR)/$(PROG)

clean:
	rm -f $(LIB) $(PROG)

all:
	make clean
	make

.PRECIOUS: $(LIB)

