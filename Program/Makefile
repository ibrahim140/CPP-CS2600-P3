#make program - checks to see if all dependencies are in the same directory
#then it runs the command to compile an executable program

CC = gcc

all: addBook

addBook: src\\address_book_fops.c src\\address_book_menu.c src\\main.c
	$(CC) -o bin\\main src\\address_book_fops.c src\\address_book_menu.c src\\main.c