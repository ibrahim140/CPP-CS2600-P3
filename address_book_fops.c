#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;
	struct stat buffer; //memory allocation for the buffer on stack
	/* 
	 * Check for file existance
	 */
	ret = stat(DEFAULT_FILE, &buffer);

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "r");
		if (address_book->fp == NULL)
		{
			printf("File could not be opened.");
			return e_fail;
		}
		else
		{
			char name[32], phone[32], email[32];
			int row = 0, column = 0;;
			enum {MAXC = 512};
			char buf[MAXC] = "";
			
			while (fgets(buf, MAXC, address_book->fp) != NULL)
			{
				column = 0;
				char *value = strtok(buf, ", ");
				while (value)
				{
					if (column == 0)
						strcpy(*address_book->list[row].name, value);
					else if (column == 1)
						strcpy(*address_book->list[row].phone_numbers, value);
					else if (column == 2)
						strcpy(*address_book->list[row].email_addresses, value);
				}
				value = strtok(NULL, ", ");
				row++;
			}

			fclose(address_book->fp);
		}
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
