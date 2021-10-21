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
	for (int i = 0; i < address_book->count; i++)
	{
		printf("Name: %s, Number: %s, Email: %s\n", address_book->list[i].name[0], address_book->list[i].phone_numbers[0], address_book->list[i].email_addresses[0]);
	}
	printf("\n---FINISHED PRINTING---\n");
}

Status load_file(AddressBook *address_book)
{
	char line[200]; // buffer for line from file

	// Open default file
	// If doesnt exist it will be created
	address_book->fp = fopen(DEFAULT_FILE, "a+");

	// Initialize address book attributes
	address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo) * 100);
	address_book->count = 0;

	int indexColumn = 0;
	fseek(address_book->fp, 0, SEEK_SET);

	while (fgets(line, sizeof(line), address_book->fp))
	{
		ContactInfo personBuffer;
		indexColumn = 0;
		char *stringTokenValue = strtok(line, ",");

		while (stringTokenValue)
		{
			if (indexColumn == 0)
			{
				strcpy(personBuffer.name[0], stringTokenValue);
			}
			else if (indexColumn == 1)
			{
				strcpy(personBuffer.phone_numbers[0], stringTokenValue);
			}
			else if (indexColumn == 2)
			{
				strcpy(personBuffer.email_addresses[0], stringTokenValue);
			}
			stringTokenValue = strtok(NULL, ",");
			indexColumn++;
		}
		address_book->list[address_book->count++] = personBuffer;
	}
	//printlist(address_book);

	fclose(address_book->fp);
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	// /*
	//  * Write contacts back to file.
	//  * Re write the complete file currently
	//  */
	// address_book->fp = fopen(DEFAULT_FILE, "wb");

	// if (address_book->fp == NULL)
	// {
	// 	return e_fail;
	// }

	// /*
	//  * Add the logic to save the file
	//  * Make sure to do error handling
	//  */
	// for (int i = 0; i < address_book->count; i++)
	// {
	// 	fwrite(address_book->list[i], sizeof(struct ContactInfo), 1, address_book->fp);
	// }

	// fclose(address_book->fp);

	return e_success;
}
