#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //#include "abk_fileops.h"
//#include "abk_log.h"
#include "address_book_menu.h" //#include "abk_menus.h"
#include "address_book.h" //#include "abk.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
	if(type == CHAR)
	{
		while(1)
		{
			char userCharInput;
			clearInputBuffer(); //clear input buffer

			printf("%s", msg);
			scanf("%c", &userCharInput);
			if(strcasecmp(userCharInput, 'Y') == 0) // compare without case sensitivity
			{
				return 'Y';
			}
			else if(strcasecmp(userCharInput, 'N') == 0)
			{
				return 'N';
			}
			else
			{
				printf("Please enter 'Y' for yes or 'N' for no.\n%s", msg);
			}
			fflush(stdout);
		}

	}
	else if (type == NUM)
	{
		while(1)
		{
			int userNumInput;
			clearInputBuffer(); //clear input buffer

			printf("%s", msg);
			scanf("%c", &userNumInput);
			if((userNumInput >= 0) && (userNumInput <= 6)) //for menu options/features
			{
				return userNumInput;
			}
			else
			{
				printf("Please enter a valid option.\n%s", msg);
			}
		}
	}

	return NONE;
}

void clearInputBuffer()
{
	while(getchar() != "\n");
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	if(address_book == NULL)
	{
		printf("The address book is empty.\n");
	}
	
	menu_header("Delete Contacts:\n");
	printf("1. Delete by Contact Name\n");
	printf("2. Delete by Phone Number\n");
	printf("3. Delete by E-mail Address\n");
	printf("4. Delete by Serial Number");
	printf("5. Press 0 to exit.\n");
	//printf("\n");
	
	ContactInfo tempContact;

	do
	{
		int userInput = get_option(NUM, "Please select an option: ");
		while(userInput < 0 || userInput > 4)
		{
			printf("Please input a valid choice.");
			menu_header("Delete Contacts:\n");
			printf("1. Delete by Contact Name\n");
			printf("2. Delete by Phone Number\n");
			printf("3. Delete by E-mail Address\n");
			printf("4. Delete by Serial Number");
			printf("5. Press 0 to exit.\n");

			userInput = get_option(NUM, "Please select an option: ");
		}

		switch (userInput)
		{
		case 1:
			printf("Enter Contact Name: ");
			scanf("%s", tempContact.name[0]);
			break;
		case 2:
			printf("Enter Contact Phone Number: ");
			scanf("%s", tempContact.phone_numbers[0]);
			break;
		case 3:
			printf("Enter Contact Email Address: ");
			scanf("%s", tempContact.email_addresses[0]);
			break;
		case 4:
			printf("Enter Contact Serial Number: ");
			scanf("%s", tempContact.si_no[0]);
			break;
		case 0:
			return e_success;
		}
	}while (userInput != 0)

	for(int i = 0; i < address_book->count; i++)
	{
		if(strcasecmp(address_book->list[i].name, tempContact.name) == 0)
		{
			free(address_book->list[i]) 
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if(strcasecmp(address_book->list[i].phone_numbers, tempContact.phone_numbers) == 0)
		{
			free(address_book->list[i])
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if(strcasecmp(address_book->list[i].email_addresses, tempContact.email_addresses) == 0)
		{
			free(address_book->list[i])
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if (strcasecmp(address_book->list[i].si_no, tempContact.si_no) == 0)
		{
			free(address_book->list[i])
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else
		{
			return e_no_match;
		}
		
	}
	delete_contact(address_book);
}
