# FILE:		Makefile
# AUTHOR:	Martin Kostelník (xkoste21), Radek Švec (xsvecr01)
# BRIEF:	IMS 2020 Project Makefile
# DATE:		7.12.2020

CC = g++

EXEC = ims-proj

.PHONY = all

all: clean $(EXEC)

$(EXEC):
	$(CC) -o $(EXEC) src/main.cpp

.PHONY = run1

run1: all
	./$(EXEC) italy1

.PHONY = run2

run2: all
	./$(EXEC) italy2

.PHONY = run

run: all
	./$(EXEC) czech1

.PHONY = run3

run3: all
	./$(EXEC) czech2

.PHONY = run4

run4: all
	./$(EXEC) czech3

.PHONY = run5

run5: all
	./$(EXEC) czech4


.PHONY = pack

pack:
	rm -f 02_xsvecr01_xkoste12.zip
	cp doc/doc.pdf .
	zip -r 02_xsvecr01_xkoste12.zip src/main.cpp doc.pdf Makefile
	rm -f doc.pdf

.PHONY = clean

clean:
	rm -f $(EXEC) 02_xsvecr01_xkoste12.zip
