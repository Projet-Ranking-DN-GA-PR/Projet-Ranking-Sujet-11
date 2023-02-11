CC = gcc
CFLAGS = -c -Wall -g
OBJS = main.o lire_stocker.o

.PHONY: run
run: main
	./main graphe8sommets.txt
	
main: $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c *.h
	$(CC) $(CFLAGS) $<

%.o: %.c %.h
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean: 
	rm -f $(OBJS)
	rm -f main
	ls -l
