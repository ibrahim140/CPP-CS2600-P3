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
	if (str != NULL)
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
				add_contacts(address_book);
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
	int userInput;
	ContactInfo newContact;
	char contactName[32], phoneNumber[32], email[32];
	char newName[32], newPhone[32], newEmail[32];

	if (address_book == NULL)
	{
		printf("The address book has no entries.\n");
		return e_fail;
	}

	menu_header("Edit Contacts:\n");
	printf("0. Exit\n");
	printf("1. Edit by Name\n");
	printf("2. Edit by Phone Number\n");
	printf("3. Edit by Email Address\n");
	printf("\n");

	do
	{
		userInput = get_option(NUM, "Please select an option: ");
		while (userInput < 0 || userInput > 3)
		{
			printf("Input invalid. Please enter a number from the menu.\n");
			menu_header("Edit Contacts:\n");
			printf("0. Exit\n");
			printf("1. Edit by Name\n");
			printf("2. Edit by Phone Number\n");
			printf("3. Edit by Email Address\n");
			printf("\n");

			userInput = get_option(NUM, "Please select an option: ");
		}

		switch (userInput)
		{
			case 1:
				printf("Please enter contact name: ");
				scanf("%s", contactName);
				printf("Please enter a new name: ");
				scanf("%s", newName);
				break;
			case 2:
				printf("Please enter contact phone number: ");
				scanf("%s", phoneNumber);
				printf("Please enter a new phone number: ");
				scanf("%s", newPhone);
				break;
			case 3:
				printf("Please enter contact email address: ");
				scanf("%s", email);
				printf("Please enter a new email address: ");
				scanf("%s", newEmail);
				break;
		}

		for (int i = 0; i < address_book->count; i++)
		{
			if (strcmp(address_book->list[i].name, contactName) == 0)
			{
				strcpy(address_book->list[i].name, newName);
				printf("Contact name has been edited.\n");
				break;
			}
			else if (strcmp(address_book->list[i].phone_numbers, phoneNumber) == 0)
			{
				strcpy(address_book->list[i].phone_numbers, newPhone);
				printf("Phone number has been edited.\n");
				break;
			}
			else if (strcmp(address_book->list[i].email_addresses, email) == 0)
			{
				strcpy(address_book->list[i].email_addresses, newEmail);
				printf("Email address has been edited.\n");
				break;
			}
		}
	} while (userInput != 0);
	
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
