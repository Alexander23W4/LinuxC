O_FILE=num_vari.o
FILE_NAME=$(basename $(O_FILE))


all: $(O_FILE) 
	touch $(FILE_NAME)
	rv32obj $(O_FILE) >> $(FILE_NAME)

$(O_FILE):
	rv32gcc -O1 -c $(FILE_NAME).c

	

clean:
	rm -rf ./*.o ./*.s