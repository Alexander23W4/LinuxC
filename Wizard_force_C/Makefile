CFLAGS=-Wall -g
DIR=C6
FILE=c6.c
OBJECT=$(basename $(FILE))


debug: 
	gcc $(CFLAGS) -o0 ./$(DIR)/$(FILE) -o $(OBJECT)

fast: 
	gcc $(CFLAGS) -o2 ./$(DIR)/$(FILE) -o $(OBJECT)

lint:
	clang ./$(DIR)/$(FILE) --analyze -Xanalyzer -analyzer-output=text

valgrind:
	valgrind ./$(OBJECT)

run:
	./$(OBJECT)

clean:
	rm -rf $(OBJECT)

print:

.PHONY: debug fast lint valgrind run clean
