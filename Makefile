
prog=day3 day4

all : $(prog)

.PHONY : $(prog)

$(prog) : 
	make -C $@

clean :
	make -C day3 clean
	make -C day4 clean
