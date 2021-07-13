CC = gcc
CPLUS = g++
.PHONY: gen_random clean all timer


all: gen_random timer

gen_random:
	$(CPLUS) $@.cc -o bin/$@

timer:
	$(CPLUS) $@.cc -o bin/$@
clean:
	rm -rf bin/*


