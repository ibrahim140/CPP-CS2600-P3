#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //#include "abk_fileops.h"
//#include "abk_log.h"
#include "address_book_menu.h" //#include "abk_menus.h"
#include "address_book.h"	   //#include "abk.h"

int get_submenu_option(int type, const char *msg)
{
	if (type == NUM)
	{
		while (1)
		{
			int userNumInput;

			printf("%s", msg);
			scanf("%d", &userNumInput);
			while (getchar() != '\n');

			if ((userNumInput >= 0) && (userNumInput <= 4)) //for menu options/features
			{
				return userNumInput;
			}
			else
			{
				printf("Please enter a valid option.\n");
			}
		}
	}
	else if(type == CHAR)
	{
		while(1)
		{
			char userCharInput;

			printf("%s", msg);
			scanf("%c", &userCharInput);

			if (userCharInput == 'Y' || userCharInput == 'y')
			{
				return 'Y';
			}
			else
			{
				return e_fail;
			}
		}
		
	}
	

	return NONE;
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
	if (type == CHAR)
	{
		while (1)
		{
			char userCharInput;

			printf("%s", msg);
			scanf("%c", &userCharInput);
			while(getchar() != '\n');
			//fflush(stdout);

			if (userCharInput == 'Y' || userCharInput == 'y')
			{
				return 'Y';
			}
			else if (userCharInput == 'N' || userCharInput == 'n')
			{
				return 'N';
			}
			// else
			// {
			// 	printf("Please enter 'Y' for yes or 'N' for no.\n%s", msg);
			// }
			fflush(stdout);
		}
	}
	else if (type == NUM)
	{
		while (1)
		{
			int userNumInput;

			printf("%s", msg);
			scanf("%d", &userNumInput);
while(getchar() != '\n');
			//fflush(stdout);
			if ((userNumInput >= 0) && (userNumInput <= 6)) //for menu options/features
			{
				return userNumInput;
			}
			else
			{
				printf("Please enter a valid option.\n");
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

		if (option == 'Y' || option == 'y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N' || option == 'n');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book /* const char *title, int *index, const char *msg, Modes mode */)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */
	int pageCount = 2, pageStart = 0;
	int buffer;
	while (1)
	{
		menu_header("Search Result: \n");
		printf("=====================================================================================================================\n");
		printf(": %-7s", "S.No");
		printf(": %-35s", "Name");
		printf(": %-35s", "Phone No");
		printf(": %-31s:\n", "Email ID");
		printf("=====================================================================================================================\n");

		/* Add the functionality for adding contacts here */
		ContactInfo *personBuffer;

		for (int i = pageStart; i < pageCount + pageStart; i++) //iterating through the rows
		{
			int row = 0;
			ContactInfo *personBuffer = &address_book->list[i];

			for (int count = 0; count < 1; count++)
			{
				printf(": %-7d", personBuffer->si_no);
				printf(": %-35s", personBuffer->name[0]);
				printf(": %-35s", personBuffer->phone_numbers[count]);
				printf(": %-31s:\n", personBuffer->email_addresses[count]);
				row++;
				while (row < 5)
				{
					printf(": %-7s", "");
					printf(": %-35s", "");
					printf(": %-35s", "");
					printf(": %-31s:\n", "");
					row++;
				}
				printf("=====================================================================================================================\n");
			}
		}
		printf("0. Back\n");
		printf("1. Next\n");
		printf("2. Previous\n" );
		printf("\nPlease enter an Option: ");
		//while(getchar() != '\n'); 
		scanf("%d", &buffer);
		printf("%d", buffer);
		switch(buffer)
		{
			case 0:
				return e_success;
			case 1:
				pageStart += pageCount;
				//return e_success;
				break;
			case 2:
				pageStart -= pageCount;
				//return e_success;
				break;
			default:
				break;
		}
		/* if(strcmp(buffer, "0"))
		{
			//return e_success;
			break;
		}
		else if (strcmp(buffer, "1"))
		{
			pageStart += pageCount;
			//return e_success;
		}
		else
		{
			pageStart -= pageCount;
		} */
	}
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

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

void add_menu(char *addName, char *addNumber, char *addEmail)
{
	menu_header("Add menu\n");

	printf("0. Back\n");
	printf("1. Name: %s\n", addName);
	printf("2. Phone No: %s\n", addNumber);
	printf("3. Email ID: %s\n\n", addEmail);
}

void search_menu()
{
	menu_header("Search Contact by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
}

void edit_menu()
{
	menu_header("Search Contact to Edit by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
}

void delete_menu()
{
	menu_header("Search Contact to Delete by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
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

		if ((address_book->count == 0) && (option != e_add_contact))
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
			list_contacts(address_book);
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
	int option;
	ContactInfo person = {"", "", "", 0};
	_Bool added = 0;

	do
	{
		add_menu(*person.name, *person.phone_numbers, *person.email_addresses);

		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
		case 1: //name
			printf("Please enter the name: ");
			gets(*person.name);
			added = 1;
			break;
		case 2: //phone number
			printf("Please enter the phone number: ");
			scanf("%s", *person.phone_numbers);
			added = 1;
			// person.numberCount++;
			break;
		case 3: //email
			printf("Please enter the email address: ");
			scanf("%s", *person.email_addresses);
			added = 1;
			// person.emailCount++;
			break;
		case 0: //exit
			if (added)
				address_book->list[address_book->count++] = person;
			break;
		}
	} while (option != 0);

	return e_success;
}

Status search(const char *str, AddressBook *address_book, Field field)
{
	/* Add the functionality for searching contacts here */
	// Print the title
	menu_header("Search Result: \n");
	printf("=====================================================================================================================\n");
	printf(": %-7s", "S.No");
	printf(": %-35s", "Name");
	printf(": %-35s", "Phone No");
	printf(": %-31s:\n", "Email ID");
	printf("=====================================================================================================================\n");

	/* Add the functionality for adding contacts here */
	ContactInfo *personBuffer;

	switch (field)
	{
		case 0:
			for (int i = 0; i < address_book->count; i++) //iterating through the rows
			{
				int row = 0;
				ContactInfo *personBuffer = &address_book->list[i];

				for (int count = 0; count < 1; count++)
				{
					if (personBuffer->si_no == atoi(str))
					{
						printf(": %-7d", personBuffer->si_no);
						printf(": %-35s", personBuffer->name[0]);
						printf(": %-35s", personBuffer->phone_numbers[count]);
						printf(": %-31s:\n", personBuffer->email_addresses[count]);
						row++;
						while (row < 5)
						{
							printf(": %-7s", "");
							printf(": %-35s", "");
							printf(": %-35s", "");
							printf(": %-31s:\n", "");
							row++;
						}
						printf("=====================================================================================================================\n");
					}
				}
			}
			break;
		case 1:
			for (int i = 0; i < address_book->count; i++) //iterating through the rows
			{
				int row = 0;
				ContactInfo *personBuffer = &address_book->list[i];

				for (int count = 0; count < 1; count++)
				{
					if (strcasecmp(personBuffer->name[count], str) == 0) //if(strcasecmp(userCharInput, "Y") == 0)
					{
						printf(": %-7d", personBuffer->si_no);
						printf(": %-35s", personBuffer->name[0]);
						printf(": %-35s", personBuffer->phone_numbers[count]);
						printf(": %-31s:\n", personBuffer->email_addresses[count]);
						row++;
						while (row < 5)
						{
							printf(": %-7s", "");
							printf(": %-35s", "");
							printf(": %-35s", "");
							printf(": %-31s:\n", "");
							row++;
						}
						printf("=====================================================================================================================\n");
					}
				}
			}
			break;

		case 2:
			for (int i = 0; i < address_book->count; i++) //iterating through the rows
			{
				int row = 0;
				ContactInfo *personBuffer = &address_book->list[i];

				for (int count = 0; count < 1; count++)
				{
					if (strcasecmp(personBuffer->phone_numbers[count], str) == 0)
					{
						printf(": %-7d", personBuffer->si_no);
						printf(": %-35s", personBuffer->name[0]);
						printf(": %-35s", personBuffer->phone_numbers[count]);
						printf(": %-31s:\n", personBuffer->email_addresses[count]);
						row++;
						while (row < 5)
						{
							printf(": %-7s", "");
							printf(": %-35s", "");
							printf(": %-35s", "");
							printf(": %-31s:\n", "");
							row++;
						}
						printf("=====================================================================================================================\n");
					}
				}
			}
			break;

		case 3:
			for (int i = 0; i < address_book->count; i++) //iterating through the rows
			{
				int row = 0;
				ContactInfo *personBuffer = &address_book->list[i];

				for (int count = 0; count < 1; count++)
				{
					if (strcasecmp(personBuffer->email_addresses[count], str) == 0)
					{
						printf(": %-7d", personBuffer->si_no);
						printf(": %-35s", personBuffer->name[0]);
						printf(": %-35s", personBuffer->phone_numbers[count]);
						printf(": %-31s:\n", personBuffer->email_addresses[count]);
						row++;
						while (row < 5)
						{
							printf(": %-7s", "");
							printf(": %-35s", "");
							printf(": %-35s", "");
							printf(": %-31s:\n", "");
							row++;
						}
						printf("=====================================================================================================================\n");
					}
				}
			}
			break;
		default:
			break;
	}

	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for searching contacts here */
	int option;
	char buffer[NAME_LEN];
	Field field;

	do
	{
		// Display search menu and get option from user
		search_menu();
		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
		case 1: //name
			field = name;
			printf("Enter the name: ");
			gets(buffer);
			break;
		case 2: //phone number
			field = number;
			printf("Enter the phone number: ");
			gets(buffer);
			break;
		case 3: //email
			field = email;
			printf("Enter the email address: ");
			gets(buffer);
			break;
		case 4: //email
			field = serial;
			printf("Enter the serial number: ");
			gets(buffer);
			break;
		case 0: //exit
			return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);
		printf("Press: [q] = Cancel: ");
		scanf("%s", buffer);
		if (strcmp(buffer, "q") == 0)
			break;

	} while (option != 0);

	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for editing contacts here */
	int option1, option2;
	char buffer[NAME_LEN];
	Field field;
	char userPress;

	do
	{
		// Display search menu and get option from user
		edit_menu();
		option1 = get_submenu_option(NUM, "Please select an option: ");

		switch (option1)
		{
		case 1: //name
			field = name;
			printf("Enter the name: ");
			gets(buffer);
			break;
		case 2: //phone number
			field = number;
			printf("Enter the phone number: ");
			scanf("%s", buffer);
			break;
		case 3: //email
			field = email;
			printf("Enter the email address: ");
			scanf("%s", buffer);
			break;
		case 4: //email
			field = serial;
			printf("Enter the serial number: ");
			scanf("%s", buffer);
			break;
		case 0: //exit
			return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);
		printf("Press: [s] = Select, [q] = Cancel: ");
		scanf("%s", &userPress);

		if (userPress == 's' || userPress == 'S')
		{
			printf("Select a Serial Number (S.No) to Edit: ");
			scanf("%s", &userPress);

			for (int i = 0; i < address_book->count; i++) //iterating through the rows
			{
				ContactInfo *personBuffer = &address_book->list[i];
				if (personBuffer->si_no == atoi(&userPress))
				{
					do
					{
						menu_header("Edit Contact:\n");
						printf("0. Back\n");
						printf("1. Name	      : %s\n", personBuffer->name[0]);
						printf("2. Phone No 1 : %s\n", personBuffer->phone_numbers[0]);
						printf("3. Email ID 1 : %s\n\n", personBuffer->email_addresses[0]);
						option2 = get_submenu_option(NUM, "Please select an option: ");
						switch (option2)
						{
						case 1: //name
							printf("Enter the name: [Just enter removes the entry]: ");
							//fgets(buffer, sizeof(buffer), stdin);
							gets(buffer);
							if (buffer[0] == '\n') // did user enter only?
								strcpy(*personBuffer->name, "");
							else
								strcpy(*personBuffer->name, buffer);
							break;
						case 2: //phone number
							printf("Enter the phone number: [Just enter removes the entry]: ");
							//fgets(buffer, sizeof(buffer), stdin);
							gets(buffer);
							if (buffer[0] == '\n')
								strcpy(*personBuffer->phone_numbers, "");
							else
								strcpy(*personBuffer->phone_numbers, buffer);
							break;
						case 3: //email
							printf("Enter the email address: [Just enter removes the entry]: ");
							//fgets(buffer, sizeof(buffer), stdin);
							gets(buffer);
							if (buffer[0] == '\n')
								strcpy(*personBuffer->email_addresses, "");
							else
								strcpy(*personBuffer->email_addresses, buffer);
							break;
						case 0: //go back
							break;
						}
					} while (option2 != 0);
				}
			}
		}

	} while (option1 != 0);

	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for deleting contacts here */
	if (address_book == NULL)
	{
		printf("The address book is empty. Use Add Contact to add contacts.\n");
		return e_fail;
	}

	int option;
	char buffer[NAME_LEN];
	Field field;
	char userPress;

	do
	{
		// Display search menu and get option from user
		delete_menu();
		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
			case 1: //name
				field = name;
				printf("Enter the name: ");
				gets(buffer);
				break;
			case 2: //phone number
				field = number;
				printf("Enter the phone number: ");
				gets(buffer);
				break;
			case 3: //email
				field = email;
				printf("Enter the email address: ");
				gets(buffer);
				break;
			case 4: //email
				field = serial;
				printf("Enter the serial number: ");
				gets(buffer);
				break;
			case 0: //exits
				return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);
		printf("Press: [s] = Select, [q] = Cancel: ");
		scanf("%s", &userPress);
		while (getchar() != '\n');

		if (userPress == 's' || userPress == 'S')
		{
			printf("Select a Serial Number (S.No) to Delete: ");
			scanf("%s", &userPress);
			while (getchar() != '\n');

			int i;
			for (i = 0; i < address_book->count; i++) //iterating through the rows
			{
				ContactInfo *personBuffer = &address_book->list[i];
				if (personBuffer->si_no == atoi(&userPress))
				{	
					// for(int j = 0; j < 5; j++)
					// {
						menu_header("Delete Contact:\n");
						printf("0. Back\n");
						printf("1. Name     : %s\n", personBuffer->name[0]);
						printf("2. Phone No : %s\n", personBuffer->phone_numbers[0]/* [j] */); 
						printf("3. Email ID : %s\n", personBuffer->email_addresses[0]/* [j] */);
						break;
					// }
				}
			}
			char userInput2 = get_submenu_option(CHAR, "\nEnter 'Y' to delete. [Press any key to ignore]: ");
			
			if (userInput2 == 'y' || userInput2 == 'Y')
			{
				// // move the contact at index i to the end of the list and decrement 
				// // the address book counter to remove access to that contact from the list
				ContactInfo tempContact1, tempContact2;

				tempContact1 = address_book->list[i];
				tempContact2 = address_book->list[address_book->count - 1];

				address_book->list[address_book->count - 1] = tempContact1;
				address_book->list[i] = tempContact2;
				address_book->count--;
				printf("Contact has been deleted.\n\n");
			}
		}
	}while (option != 0);

	//save_prompt(address_book);

	return e_success;
}