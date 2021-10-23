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
				personBuffer.si_no = atoi(stringTokenValue);
			}
			else if (indexColumn == 1)
			{
				strcpy(personBuffer.name[0], stringTokenValue);
			}
			else if (indexColumn == 2)
			{
				strcpy(personBuffer.phone_numbers[0], stringTokenValue);
			}
			else if (indexColumn == 3)
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
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if(address_book->fp == NULL)
	{
		printf("Unable to open file.");
		return e_fail;
	}

	for (int i = 0; i < address_book->count; i++)
	{
		fprintf(address_book->fp, "%d,%s,%s,%s,\n",  address_book->list[i].si_no, address_book->list[i].name[0],
				 &address_book->list[i].phone_numbers[i][0], &address_book->list[i].email_addresses[i][0]); 		// for phone and email, used 2D array.. 

		//address_book->list[i].si_no + "," + address_book->list[i].name + "," + address_book->list[i].phone_numbers + "," + address_book->list[i].email_addresses + ",";
	}

	fclose(address_book->fp);

	return e_success;
}
