ifeq ($(strip $($t)),)
	t := a
endif

.PHONY: all
all: $(t).out

.PHONY: clean
clean:
	rm -rf *.out sol

.PHONY: veryclean
veryclean:
	rm -rf *.cc *.out sol

$(t).out: ./sol/$(t).cc
	g++ -O2 -std=c++20 $< -o $@

./sol/$(t).cc: $(t).cc ./lib/*.h
	./expand.sh $< $@

%:
	@echo "error: set the target with the variable t"
	@echo "-> did you mean \"make t=$@\"?"
