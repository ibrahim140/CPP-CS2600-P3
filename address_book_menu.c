#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //#include "abk_fileops.h"
//#include "abk_log.h"
#include "address_book_menu.h" //#include "abk_menus.h"
#include "address_book.h" //#include "abk.h"

void clearInputBuffer()
{
	while(getchar() != '\n');
}

int get_submenu_option(int type, const char *msg)
{
	if(type == NUM)
	{
		while(1)
		{
			int userNumInput;
			
			printf("%s", msg);
			scanf("%d", &userNumInput);

			if((userNumInput >= 0) && (userNumInput <= 3)) //for menu options/features
			{
				return userNumInput;
			}
			else
			{
				printf("Please enter a valid option.");
			}
		}
	}
}

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
			char* userCharInput;

			printf("%s", msg);
			scanf("%s", &userCharInput);
			clearInputBuffer(); //clear input buffer, to make sure we dont get '\n' characters

			if(strcasecmp(userCharInput, "Y") == 0) // compare without case sensitivity
			{
				return 'Y';
			}
			else if(strcasecmp(userCharInput, "N") == 0)
			{
				return 'N';
			}
			else
			{
				printf("Please enter 'Y' for yes or 'N' for no.\n%s", msg);
			}
			printf("Please enter 'Y' or 'N'\n");
			fflush(stdout);
		}

	}
	else if (type == NUM)
	{
		while(1)
		{
			int userNumInput;
//			clearInputBuffer(); //clear input buffer -- may not be necessary..

			printf("%s", msg);
			scanf("%d", &userNumInput);

			if((userNumInput >= 0) && (userNumInput <= 6)) //for menu options/features
			{
				return userNumInput;
			}
			else
			{
				printf("Please enter a valid option.");
			}
		}
	}

	return NONE;
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

	//system("clear");
	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
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
	
	
	char* tempContactInfo;
	char nullStr[10] = {"\0"};
	int userInput;
	do
	{
		menu_header("Delete Contacts:\n");
		printf("1. Delete Contact by Name\n");
		printf("2. Delete Contact by Phone\n");
		printf("3. Delete Contact by E-mail\n");
		//printf("4. Delete by Serial Number");
		printf("4. Press 0 for Main Menu\n");
		userInput = get_submenu_option(NUM, "\nPlease select an option: ");
	
		switch (userInput)
		{
		case 1:
			printf("Enter Contact Name: ");
			scanf("%s", &tempContactInfo /* tempContact.name[0] */);
			break;
		case 2:
			printf("Enter Contact Phone Number: ");
			scanf("%s", &tempContactInfo /* tempContact.phone_numbers[0] */);
			break;
		case 3:
			printf("Enter Contact Email Address: ");
			scanf("%s", &tempContactInfo /* tempContact.email_addresses[0] */);
			break;
		/* case 4:
			printf("Enter Contact Serial Number: ");
			scanf("%s", tempContact.si_no[0]);
			break; */
		case 0:
			return e_success;
		}
	}while (userInput != 0);

	for(int i = 0; i < address_book->count; i++)
	{
		if(strcasecmp(*address_book->list[i].name, tempContactInfo) == 0)
		{
			//free(address_book->list[i]);
			strcpy(*address_book->list[i].name, nullStr);
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if(strcasecmp(*address_book->list[i].phone_numbers, tempContactInfo) == 0)
		{
			strcpy(*address_book->list[i].name, nullStr);
			//free(address_book->list[i]);
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if(strcasecmp(*address_book->list[i].email_addresses, tempContactInfo) == 0)
		{
			strcpy(*address_book->list[i].name, nullStr);
			//free(address_book->list[i]);
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		/* else if (strcasecmp(*address_book->list[i].si_no, tempContact.si_no) == 0)
		{
			free(address_book->list[i]);
			address_book->count--;
			printf("Contact has been deleted.\n");
		} */
		else
		{
			return e_no_match;
		}
		
	}
	delete_contact(address_book);
}
