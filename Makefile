
dirs=$(shell for i in `seq 3 11`; do echo day$$i; done)

all :
	@for d in $(dirs); do \
		make -C $$d; \
	done

clean :
	@for d in $(dirs); do \
		make -C $$d clean; \
	done
