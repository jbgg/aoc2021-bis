prog=15b
obj=input.o main.o

CC=gcc

all:$(prog)

.SUFFIXES: .S .o .c

$(prog): $(obj)
	$(CC) -o $(prog) $(obj)

.S.o:
	$(CC) -c -o $@ $<

.c.o:
	$(CC) -c -o $@ $<

clean:
	rm -rf *.o
	rm -rf $(prog)
