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
			char fileLine[1000]
			int index = 0;
			char* stringTokenValue;

			fseek(fp, 0, SEEK_SET);

			do
			{	
				ContactInfo readNewContact;
				stringTokenValue = strtok(fileLine, ", ");

				while(stringTokenValue)
				{
					//copy string to contactslist, stringTokenValue is the value to be copied
					strcpy(readNewContact.name[0], stringTokenValue);
					stringTokenValue = strtok(NULL, ", ");
					strcpy(readNewContact.phone_numbers[0], stringTokenValue);
					stringTokenValue = strtok(NULL, ", ");
					strcpy(readNewContact.email_addresses[0], stringTokenValue);
					stringTokenValue = strtok(NULL, ", ");
				}
				//test if the file is parsed correctly
				// printf("Contact Name: %s, ", readNewContact.name[0]); //print name
				// printf("Phone Number: %s, ", readNewContact.phone_numbers[0]); //print phone #
				// printf("Email Address: %s\n", readNewContact.email_addresses[0]); // print email
				index++;
			} while (fgets(fileLine, sizeof(fileLine), address_book->fp);
			
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
