
prog=day3 day4 day5

all : $(prog)

.PHONY : $(prog)

$(prog) : 
	make -C $@

clean :
	make -C day3 clean
	make -C day4 clean
	make -C day5 clean
