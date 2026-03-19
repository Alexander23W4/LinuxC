# In Makefile, the KEYWORD should either be a "pure variable" or a "command", and also could be Both
# a command could be dynamically execute or statically execute
# for example : for command A
# dynamic: make A
# static: make all: A B C     **dependency A B C  must be file

# For the following example:
# MAN=key.c
# show: $(MAN)
#        echo "showtime"
# $(MAN): 
#        (commands for generate key.c)
# make show: if key.c exist, execute following commands, if not, find key.c generate principle aka $(MAN) command
#            we need $(MAN) to generate key.c 
# 

# KEYWORDS: file_variable  non_file_variable  file_dependent_command    pure_execution_command
#      notice: pure_execution_command also could be dependency, means execute this command before execute me
#      dependency natrually includes ->dependent files or dir  ->pre-execute required commands

# foo=bar make all     this type could diliver variable foo to the following "make all" process

# all of the pure-execution_command should be added to **->.PHONY
#------FLAGS------
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

#------FILES------
# SOURCE
SOURCES=$(wildcard src/**/*.c src/*.c)   # use wildcard grasp all the .c file under the dir, batch them as SOURCES
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))   # use patsubst convert all the files in SOURCES to .o and batch them as OBJECTS

# TEST
TEST_SRC=$(wildcard tests/*_tests.c)     # search for test files  (*wildcard)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# TARGET
TARGET=build/liblist.a      # .a   static lib     copy all when compiling (cumbersome)
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))    # .so   shared lib   citing when compiling

#------SUBCOMMANDS------
# The Target Build
all: $(TARGET) $(SO_TARGET) tests     # operate   construct lib files -> operate test files
                                      # execute "make all" -> execute dependent commands: [$(TARGET) $(SO_TARGET) tests] 

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)  # make dev:  use new CFLAGS and execute "make all"
dev: all

$(TARGET): CFLAGS += -fPIC    # variable condition change:   reset some condition in order to build $(TARGET)
$(TARGET): build $(OBJECTS)   # recipe:  for generate $(TARGET)   # *** important: if $(OBJECT) is none, automatically compile .c->.o
	ar rcs $@ $(OBJECTS)
	ranlib $@
# pack all the .o files -> .a (static lib)     &     generate index link for .a

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)   

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += -ldl $(TARGET)
tests: $(TESTS)
	bash ./tests/runtests.sh

valgrind:                 # deliver VALGRIND variable to following "make" process, the following make process could use this variable 
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)    

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

target: $(TARGET) $(SO_TARGET)
	rm -rf $(OBJECTS)

#static test:
DIR=tests
FILE=list_tests.c
OBJECT=$(basename $(FILE))

debug:
	gcc -Wall -g -O0 ./$(DIR)/$(FILE) -o $(OBJECT)

fast:
	gcc -Wall -g -O2 ./$(DIR)/$(FILE) -o $(OBJECT)

lint:
	clang -Wall -g ./$(DIR)/$(FILE) --analyze -Xanalyzer -analyzer-output=text

val: $(OBJECT)
	valgrind ./$(OBJECT)

$(OBJECT): CFLAGS=-Wall -g
$(OBJECT): $(DIR)/$(FILE)
	gcc $(CFLAGS) -O0 ./$(DIR)/$(FILE) -o $(OBJECT)

# MAN=key.c
# show: $(MAN)
#	echo "showtime"
# $(MAN): 
#	(commands for generate key.c)