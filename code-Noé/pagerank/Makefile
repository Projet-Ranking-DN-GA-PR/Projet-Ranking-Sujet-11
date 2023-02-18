CC = gcc
CFLAGS = -c -Wall -g
OBJS = main.o lire_stocker.o

.PHONY: run
run: main
<<<<<<< HEAD
	./main graphe_a_8_sommet 
=======
	./main ../wb-cs-stanford.txt
>>>>>>> d6a04c629a0ad3073d3778a5f9172ad97e6aa8a0
	
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
