#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

// void printlist(AddressBook *address_book)
// {
// 	printf("---PRINTING LIST---\n");
// 	for (int i = 0; i < address_book->count; i++)
// 	{
// 		printf("%s,%s,%s\n", address_book->list[i].name[0], address_book->list[i].phone_numbers[0], address_book->list[i].email_addresses[0]);
// 	}
// 	printf("---FINISHED PRINTING---\n\n");
// }

Status load_file(AddressBook *address_book)
{
	char line[200]; // buffer for line from file

	// Open default file
	// If doesnt exist it will be created
	address_book->fp = fopen(DEFAULT_FILE, "a+");

	// Initialize address book attributes
	address_book->list = (ContactInfo *)malloc(sizeof(ContactInfo) * 100);
	address_book->count = 0;

	// create local variable to iterate through each item in each line of the csv file
	int indexColumn = 0;
	// set the seek to the start of the file
	fseek(address_book->fp, 0, SEEK_SET);

	// get a line from the file
	while(fgets(line, sizeof(line), address_book->fp))
	{
		// create a local variable to hold the contact info
		ContactInfo personBuffer;
		// set the index of the columns 0 
		indexColumn = 0;
		// seperate the line at the delimiter ","
		char *stringTokenValue = strtok(line, ",");

		// check if stringTokenValue has something in it
		while (stringTokenValue)
		{
			// first column is amount of phone #'s that contact has
			if(indexColumn == 0)
			{
				// set contacts numberCount from the stringTokenValue
				personBuffer.numberCount = atoi(stringTokenValue);
			}
			// second column is amount of email ID's that contact has
			else if(indexColumn == 1)
			{
				// set contacts emailCount from the stringTokenValue		
				personBuffer.emailCount = atoi(stringTokenValue);
			}
			// third column is the contacts serial number
			else if(indexColumn == 2)
			{
				// set contacts serial number from the stringTokenValue
				personBuffer.si_no = atoi(stringTokenValue);
			}
			// fourth column is contacts name
			else if(indexColumn == 3)
			{
				// set contacts name from the stringTokenValue
				strcpy(personBuffer.name[0], stringTokenValue);
			}
			// fifth column is where the phone #'s start (allowed 5)
			else if(indexColumn == 4)
			{
				// iterate through all phone numbers for the specific contact
				for(int i = 0; i < personBuffer.numberCount; i++)
				{
					// if the contact has a phone #, enter if block
					if(stringTokenValue)
					{
						// copy stringTokenValue into contacts phone numbers at index 'i' 
						strcpy(personBuffer.phone_numbers[i], stringTokenValue);
						// reset stringTokenValue for every phone number except the last
						if(i != personBuffer.numberCount - 1)
							stringTokenValue = strtok(NULL, ",");
					}
				}
			}
			// fifth column is where the email ID's start (allowed 5)
			else if(indexColumn == 5)
			{
				// iterate through all email ID's for the specific contact
				for(int i = 0; i < personBuffer.emailCount; i++)
				{
					// if the contact has an email ID, enter if block
					if(stringTokenValue)
					{
						// copy stringTokenValue into contacts email ID's at index 'i' 
						strcpy(personBuffer.email_addresses[i], stringTokenValue);
						// reset stringTokenValue for every email ID except the last
						if(i != personBuffer.emailCount - 1)
							stringTokenValue = strtok(NULL, ",");
					}
				}
			}
			// reset stringTokenValue
			stringTokenValue = strtok(NULL, ",");
			// increment the column for the next item in the line
			indexColumn++;
		}
		// store contact into list and increment count
		address_book->list[address_book->count++] = personBuffer;
	}

	// close the file
	fclose(address_book->fp);
	// return e_success
	return e_success;
}

//Function opens up the address book file and saves all the contact information changes to it
Status save_file(AddressBook *address_book)
{
	address_book->fp = fopen(DEFAULT_FILE, "w");//opens up file

	if (address_book->fp == NULL)//checks if the file is there
	{
		printf("Unable to open file.");
		return e_fail;
	}

	//loops through to save information
	for (int i = 0; i < address_book->count; i++)
	{
		//adds list of count for the phone numbers, emails, identification number, and names
		fprintf(address_book->fp, "%d,%d,%d,%s,", address_book->list[i].numberCount, address_book->list[i].emailCount, address_book->list[i].si_no, address_book->list[i].name[0]);
		for (int j = 0; j < address_book->list[i].numberCount; j++)
		{
			fprintf(address_book->fp, "%s,", address_book->list[i].phone_numbers[j]);//adds each phone number under that contact
		}
		for (int j = 0; j < address_book->list[i].emailCount; j++)
		{
			fprintf(address_book->fp, "%s,", address_book->list[i].email_addresses[j]);//added each contact under that phone number
		}
		fprintf(address_book->fp, "\n");//enters into new line
	}

	fclose(address_book->fp);//closes the file
	return e_success;
}
