CFLAGS=-Wall -g
PATH=C5
FILE=./$(PATH)/c5.c
OBJECT=$(basename $(FILE))


debug: 
	gcc $(CFLAGS) -o0 $(FILE) -o $(OBJECT)

fast: 
	gcc $(CFLAGS) -o2 $(FILE) -o $(OBJECT)

lint:
	clang $(FILE) --analyze -Xanalyzer -analyzer-output=text

valgrind:
	valgrind ./$(OBJECT)

run:
	./$(OBJECT)

clean:
	rm -rf $(OBJECT)

.PHONY: debug fast lint valgrind run clean
