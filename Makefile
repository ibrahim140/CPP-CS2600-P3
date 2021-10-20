#make program - checks to see if all dependencies are in the same directory
#then it runs the command to compile an executable program

addBook: address_book_fops.c address_book_menu.c main.c
	gcc -o a.exe address_book_fops.c address_book_menu.c main.c