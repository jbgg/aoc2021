
solve1_prog=solve1

solve1_obj=main.o solve1.o input.o input_parse.o

CC=gcc
CFLAGS=-I.

all : $(solve1_prog)

$(solve1_prog) : $(solve1_obj)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.S
	$(CC) $(CFLAGS) -c -o $@ $<

%.o : %.c
	$(CC) -c -o $@ $<

clean :
	rm -rf $(solve1_prog) $(solve1_obj)
