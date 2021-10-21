#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"
void printlist(AddressBook *address_book)
{
	printf("---PRINTING LIST---\n");
	for(int i = 0; i < address_book->count; i++)
	{
		printf("Name: %s, Number: %s, Email: %s\n", address_book->list[i].name[0], 
					address_book->list[i].phone_numbers[0],address_book->list[i].email_addresses[0]);
	}
	printf("\n---FINISHED PRINTING---");
}

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
			address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo)*100);
			//address_book->list = (ContactInfo*)calloc(address_book->count, sizeof(ContactInfo));
			char fileLine[1024];
			int indexRow = 0, indexColumn = 0;
			fseek(address_book->fp, 0, SEEK_SET);

			while (fgets(fileLine, sizeof(fileLine), address_book->fp))
			{
				indexColumn = 0;
				indexRow++;
				ContactInfo readNewContact;
				char* stringTokenValue = strtok(fileLine, ",");

				while (stringTokenValue)
				{
					if (indexColumn == 0)
					{
						strcpy(readNewContact.name[0], stringTokenValue);
					}
					else if (indexColumn == 1)
					{
						strcpy(readNewContact.phone_numbers[0], stringTokenValue);
					}
					else if (indexColumn == 2)
					{
						strcpy(readNewContact.email_addresses[0], stringTokenValue);
					}
					stringTokenValue = strtok(NULL, ",");
					indexColumn++;
				}
				address_book->list[address_book->count++] = readNewContact;
			}
			fclose(address_book->fp);
			//printlist(address_book->list);
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
