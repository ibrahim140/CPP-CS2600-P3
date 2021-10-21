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
			while(getchar() != '\n');

			if ((userNumInput >= 0) && (userNumInput <= 3)) //for menu options/features
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

			if ((userNumInput >= 0) && (userNumInput <= 6)) //for menu options/features
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
	menu_header("Search Result:");

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

void add_menu(char *addName, char *addNumber, char *addEmail)
{
	menu_header("Add menu\n");

	printf("0. Back\n");
	printf("1. Name: %s\n", addName);
	printf("2. Phone No: %s\n", addNumber);
	printf("3. Email ID: %s\n", addEmail);
	printf("\n");
}

void search_menu()
{
	menu_header("Search Contact by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("\n");
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
			//list_contacts(address_book) break;
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
				scanf("%s", *person.name);
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
	// Print the title
	menu_header("Search Result: \n");
	printf("=====================================================================================================================\n");
	printf(":%7s", "S.No");
	printf(":%35s", "Name");
	printf(":%35s", "Phone No");
	printf(":%35s:\n", "Email ID");
	printf("=====================================================================================================================\n");

	/* Add the functionality for adding contacts here */
	ContactInfo *personBuffer;

	switch (field)
	{
	case 0:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			ContactInfo *personBuffer = &address_book->list[i];

			for (int contactName = 0; contactName < 1; contactName++) //iterate through names, but only 1 name so only 1 column
			{
				if (strcasecmp(personBuffer->name[contactName], str) == 0) //if(strcasecmp(userCharInput, "Y") == 0)
				{
					printf("%s", personBuffer->name[contactName]); // not sure if this is necessary
																   // return e_success;
				}
			}
		}
		break;

	case 1:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			ContactInfo *personBuffer = &address_book->list[i];
			printf("%s\n%s\n\n", personBuffer->phone_numbers[0], str);
			for (int contactPhone = 0; contactPhone < 1; contactPhone++) //iterate through phone #'s
			{
				if (strcasecmp(personBuffer->phone_numbers[contactPhone], str) == 0)
				{
					printf("%s", personBuffer->phone_numbers[contactPhone]); // not sure if this is necessary
																			 // return e_success;
				}
			}
		}
		break;

	case 2:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			ContactInfo *personBuffer = &address_book->list[i];
			for (int contactEmail = 0; contactEmail < 1; contactEmail++) //iterate through names, but only 1 name so only 1 column
			{
				if (strcasecmp(personBuffer->email_addresses[contactEmail], str) == 0)
				{
					printf("%s", personBuffer->email_addresses[contactEmail]); // not sure if this is necessary
																			   // return e_success;
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
		case 0: //exit
			return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);

	} while (option != 0);

	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	int userInput1, userInput2;
	char userPress;
	char contactName[32], phoneNumber[32], email[32];
	char newName[32], newPhone[32], newEmail[32];

	if (address_book == NULL)
	{
		printf("The address book has no entries.\n");
		return e_fail;
	}

	do
	{
		menu_header("Search Contact to Edit by:\n");
		printf("0. Exit\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n");
		userInput1 = get_submenu_option(NUM, "\nPlease select an option: ");

		switch (userInput1)
		{
		case 1:
			printf("Enter the name: ");
			scanf("%s", contactName);
			printf("==========================================================================\n");
			printf(": Name\t\t : Phone No \t\t : Email ID \t\t :\n");
			printf("==========================================================================\n");
			for (int i = 0; i < address_book->count; i++)
			{
				if (strcmp(*address_book->list[i].name, contactName) == 0)
				{
					strcpy(contactName, *address_book->list[i].name);
					strcpy(phoneNumber, *address_book->list[i].phone_numbers);
					strcpy(email, *address_book->list[i].email_addresses);
				}
			}
			printf(": %s \t\t : %s \t\t : %s \t\t :\n", contactName, phoneNumber, email);
			printf("==========================================================================\n");
			printf("Press: [s] = Select, [q] = Cancel: ");
			scanf("%s", &userPress);

			if (userPress == 's')
			{
				do
				{
					menu_header("Edit Contact:\n");
					printf("0. Back\n");
					printf("1. Name     : %s\n", contactName);
					printf("2. Phone No : %s\n", phoneNumber);
					printf("3. Email ID : %s\n", email);
					userInput2 = get_option(NUM, "\nPlease select an option: ");
					switch (userInput2)
					{
					case 1:
						printf("Enter Name: [Just enter removes the entry]: ");
						scanf("%s", newName);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].name, contactName) == 0)
							{
								strcpy(*address_book->list[i].name, newName);
								strcpy(contactName, newName);
								break;
							}
						}
						break;
					case 2:
						printf("Enter Phone Number: [Just enter removes the entry]: ");
						scanf("%s", newPhone);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].phone_numbers, phoneNumber) == 0)
							{
								strcpy(*address_book->list[i].phone_numbers, newPhone);
								strcpy(phoneNumber, newPhone);
								break;
							}
						}
						break;
					case 3:
						printf("Enter Email ID: [Just enter removes the entry]: ");
						scanf("%s", newEmail);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].email_addresses, email) == 0)
							{
								strcpy(*address_book->list[i].email_addresses, newEmail);
								strcpy(email, newEmail);
								break;
							}
						}
						break;
					default:
						break;
					}
				} while (userInput2 != 0);
			}
			else if (userPress == 'q')
				break;
			break;
		case 2:
			printf("Enter the phone number: ");
			scanf("%s", phoneNumber);
			printf("==========================================================================\n");
			printf(": Name\t\t : Phone No \t\t : Email ID \t\t :\n");
			printf("==========================================================================\n");
			for (int i = 0; i < address_book->count; i++)
			{
				if (strcmp(*address_book->list[i].phone_numbers, phoneNumber) == 0)
				{
					strcpy(contactName, *address_book->list[i].name);
					strcpy(phoneNumber, *address_book->list[i].phone_numbers);
					strcpy(email, *address_book->list[i].email_addresses);
				}
			}
			printf(": %s \t\t : %s \t\t : %s \t\t :\n", contactName, phoneNumber, email);
			printf("==========================================================================\n");
			printf("Press: [s] = Select, [q] = Cancel: ");
			scanf("%s", &userPress);

			if (userPress == 's')
			{
				do
				{
					menu_header("Edit Contact:\n");
					printf("0. Back\n");
					printf("1. Name     : %s\n", contactName);
					printf("2. Phone No : %s\n", phoneNumber);
					printf("3. Email ID : %s\n", email);
					userInput2 = get_option(NUM, "\nPlease select an option: ");
					switch (userInput2)
					{
					case 1:
						printf("Enter Name: [Just enter removes the entry]: ");
						scanf("%s", newName);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].name, contactName) == 0)
							{
								strcpy(*address_book->list[i].name, newName);
								strcpy(contactName, newName);
								break;
							}
						}
						break;
					case 2:
						printf("Enter Phone Number: [Just enter removes the entry]: ");
						scanf("%s", newPhone);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].phone_numbers, phoneNumber) == 0)
							{
								strcpy(*address_book->list[i].phone_numbers, newPhone);
								strcpy(phoneNumber, newPhone);
								break;
							}
						}
						break;
					case 3:
						printf("Enter Email ID: [Just enter removes the entry]: ");
						scanf("%s", newEmail);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].email_addresses, email) == 0)
							{
								strcpy(*address_book->list[i].email_addresses, newEmail);
								strcpy(email, newEmail);
								break;
							}
						}
						break;
					default:
						break;
					}
				} while (userInput2 != 0);
			}
			else if (userPress == 'q')
				break;
			break;
		case 3:
			printf("Enter the email ID: ");
			scanf("%s", email);
			printf("==========================================================================\n");
			printf(": Name\t\t : Phone No \t\t : Email ID \t\t :\n");
			printf("==========================================================================\n");
			for (int i = 0; i < address_book->count; i++)
			{
				if (strcmp(*address_book->list[i].email_addresses, email) == 0)
				{
					strcpy(contactName, *address_book->list[i].name);
					strcpy(phoneNumber, *address_book->list[i].phone_numbers);
					strcpy(email, *address_book->list[i].email_addresses);
				}
			}
			printf(": %s \t\t : %s \t\t : %s \t\t :\n", contactName, phoneNumber, email);
			printf("==========================================================================\n");
			printf("Press: [s] = Select, [q] = Cancel: ");
			scanf("%s", &userPress);

			if (userPress == 's')
			{
				do
				{
					menu_header("Edit Contact:\n");
					printf("0. Back\n");
					printf("1. Name     : %s\n", contactName);
					printf("2. Phone No : %s\n", phoneNumber);
					printf("3. Email ID : %s\n", email);
					userInput2 = get_option(NUM, "\nPlease select an option: ");
					switch (userInput2)
					{
					case 1:
						printf("Enter Name: [Just enter removes the entry]: ");
						scanf("%s", newName);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].name, contactName) == 0)
							{
								strcpy(*address_book->list[i].name, newName);
								strcpy(contactName, newName);
								break;
							}
						}
						break;
					case 2:
						printf("Enter Phone Number: [Just enter removes the entry]: ");
						scanf("%s", newPhone);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].phone_numbers, phoneNumber) == 0)
							{
								strcpy(*address_book->list[i].phone_numbers, newPhone);
								strcpy(phoneNumber, newPhone);
								break;
							}
						}
						break;
					case 3:
						printf("Enter Email ID: [Just enter removes the entry]: ");
						scanf("%s", newEmail);
						for (int i = 0; i < address_book->count; i++)
						{
							if (strcmp(*address_book->list[i].email_addresses, email) == 0)
							{
								strcpy(*address_book->list[i].email_addresses, newEmail);
								strcpy(email, newEmail);
								break;
							}
						}
						break;
					default:
						break;
					}
				} while (userInput2 != 0);
			}
			else if (userPress == 'q')
				break;
			break;
		}

	} while (userInput1 != 0);

	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	if (address_book == NULL)
	{
		printf("The address book is empty. Use Add Contact to add contacts.\n");
		return e_fail;
	}

	char *tempContactInfo;
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
			scanf("%s", tempContactInfo /* tempContact.name[0] */);
			break;
		case 2:
			printf("Enter Contact Phone Number: ");
			scanf("%s", tempContactInfo /* tempContact.phone_numbers[0] */);
			break;
		case 3:
			printf("Enter Contact Email Address: ");
			scanf("%s", tempContactInfo /* tempContact.email_addresses[0] */);
			break;
		/* case 4:
			printf("Enter Contact Serial Number: ");
			scanf("%s", tempContact.si_no[0]);
			break; */
		case 0:
			return e_success;
		}
	} while (userInput != 0);

	for (int i = 0; i < address_book->count; i++)
	{
		if (strcasecmp(*address_book->list[i].name, tempContactInfo) == 0)
		{
			//free(address_book->list[i]);
			strcpy(*address_book->list[i].name, nullStr);
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if (strcasecmp(*address_book->list[i].phone_numbers, tempContactInfo) == 0)
		{
			strcpy(*address_book->list[i].name, nullStr);
			//free(address_book->list[i]);
			address_book->count--;
			printf("Contact has been deleted.\n");
		}
		else if (strcasecmp(*address_book->list[i].email_addresses, tempContactInfo) == 0)
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
	return e_success;
}
