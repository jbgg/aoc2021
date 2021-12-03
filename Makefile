
prog=day3

all : $(prog)

.PHONY : $(prog)

$(prog) : 
	make -C $@

clean :
	make -C day3 clean
