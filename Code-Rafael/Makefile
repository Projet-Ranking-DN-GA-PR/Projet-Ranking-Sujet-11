CC = gcc
CFLAGS = -c -Wall
OBJS = main.o lecture.o calcul.o

.PHONY: test
test: clean main
	./main wb-cs-stanford.txt
	
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
