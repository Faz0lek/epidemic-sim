# FILE:		Makefile
# AUTHOR:	Martin Kostelník (xkoste21), Radek Švec (xsvecr01)
# BRIEF:	IMS 2020 Project Makefile
# DATE:		7.12.2020

CC = g++

EXEC = ims-proj

all: clean $(EXEC)

$(EXEC):
	$(CC) -o $(EXEC) src/main.cpp

.PHONY = run

run:
	./$(EXEC)

.PHONY = pack

pack:
	zip -r 02_xsvecr01_xkoste12.zip src/main.ccp doc/doc.pdf Makefile

.PHONY = clean

clean:
	rm -f $(EXEC)
