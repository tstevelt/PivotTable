
CFLAGS = -Wall
PROG = PivotTable
LIB = PivotTable.a
DIR = /usr/local/bin
PRG = $(DIR)/$(PROG)

FILES = \
	$(LIB)(PivotTable.o)	\
	$(LIB)(GetDelimiter.o)	\
	$(LIB)(GetIndex.o)		\
	$(LIB)(GetDimensions.o)	\
	$(LIB)(GetTokens.o)	\
	$(LIB)(GetArgs.o)

.SILENT:

$(PRG): $(LIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB)
	strip $(PRG)
	ls -l $(PRG)

$(LIB): $(FILES)

$(FILES): PivotTable.h

clean:
	rm -f $(LIB) $(PRG)

all:
	make clean
	make

.PRECIOUS: $(LIB)

