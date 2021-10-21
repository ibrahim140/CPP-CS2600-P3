#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //#include "abk_fileops.h"
//#include "abk_log.h"
#include "address_book_menu.h" //#include "abk_menus.h"
#include "address_book.h" //#include "abk.h"

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
	if(type == CHAR)
	{
		while(1)
		{
			char userCharInput;

			printf("%s", msg);
			scanf("%c", &userCharInput);

			if(userCharInput == 'Y') // compare without case sensitivity
			{
				return 'Y';
			}
			else if(userCharInput == 'N')
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
		while(1)
		{
			int userNumInput;

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
	printf("2. Phone Number: %s\n", addNumber);
	printf("3. Email Address: %s\n", addEmail);
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
	int option;
	ContactInfo person;
	int numberCount = 0;
	int emailCount = 0;

	do
	{
		add_menu(*person.name, *person.phone_numbers, *person.email_addresses);

		option = get_option(NUM, "");

		switch(option)
		{
			case 1://name
				printf("Please enter the name: ");
				scanf("%s", *person.name);
				break;
			case 2://phone number
				printf("Please enter the phone number: ");
				scanf("%s", *person.phone_numbers);
				person.numberCount++;
				break;
			case 3://email
				printf("Please enter the email address: ");
				scanf("%s", *person.email_addresses);
				person.emailCount++;
				break;
			case 0://exit
				address_book->list[address_book->count] = person;
				break;
		}
	} while (option != 0);
	
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	return e_success;
}

Status search_contact(AddressBook *address_book)
{
    int choice;
    printf("###### Address Book ######\n");
    printf("###### Seach Contact by:\n\n");
    printf("0:Back\n");
    printf("1:Name\n");
    printf("2:Phone No\n");
    printf("3:Email ID\n");
    printf("\nPlease select an option:");
	scanf("%d", &choice);
	if(choice == 1){
		char name[1024];
		printf("Enter Name: ");
		scanf("%s", name);
		enum { MAXC = 512 };
		int found = 0, line = 0;
    	char buf[MAXC] = "";
    	
    	while (fgets (buf, MAXC, fp)) {     
        	if (strstr (buf, name)) {
        	   	found = 1;	
				break;
			} 							
        	if (strchr (buf, '\n')){
				line++;
			} 
    	}
		if (found){
			printf("\n###### Address Book ######\n");
    		printf("###### Seach results by:\n\n");
    		printf("========================================================================\n");
    		printf(": Name\t\t\t : Phone No      \t\t : Email ID \n");
    		printf("========================================================================\n");
			int column = 0;
			char* value = strtok(buf, ",");
			while (value) {
				if (column == 0){
					printf("Name: ");
				}
				if (column == 1){
					printf("\tPhone No:");
				}
				if (column == 2){
					printf("\tEmail:");
				}
					printf("%s", value);
					value = strtok(NULL, ",");
					column++;
				};
			printf("========================================================================\n");
		}
	}
	if(choice == 2){
		char number[100];
		printf("Enter Number: ");
		scanf("%s", number);
		enum { MAXC = 512 };
		int found = 0, line = 0;
    	char buf[MAXC] = "";
    	
    	while (fgets (buf, MAXC, fp)) {     
        	if (strstr (buf, number)) {      
        	   	found = 1; 					
				break;           
        	}
        	if (strchr (buf, '\n')) line++; 
    	}
		if (found){
			printf("\n###### Address Book ######\n");
    		printf("###### Seach results by:\n\n");
    		printf("========================================================================\n");
    		printf(": Name\t\t\t : Phone No      \t\t : Email ID \n");
    		printf("========================================================================\n");
			int column = 0;
			char* value = strtok(buf, ",");
			while (value) {
				if (column == 0){
					printf("Name: ");
				}
				if (column == 1){
					printf("\tPhone No:");
				}
				if (column == 2){
					printf("\tEmail:");
				}
					printf("%s", value);
					value = strtok(NULL, ",");
					column++;
				};
			printf("========================================================================\n");
		}
	}
	if(choice == 3){
		char email[100];
		printf("Enter Email ID: ");
		scanf("%s", email);
		enum { MAXC = 512 };
		int found = 0, line = 0;
    	char buf[MAXC] = "";
    	
    	while (fgets (buf, MAXC, fp)) {     
        	if (strstr (buf, email)) {      
        	   	found = 1; 					
				break;           
        	}
        	if (strchr (buf, '\n')) line++; 
    	}
		if (found){
			printf("\n###### Address Book ######\n");
    		printf("###### Seach results by:\n\n");
    		printf("========================================================================\n");
    		printf(": Name\t\t\t : Phone No      \t\t : Email ID \n");
    		printf("========================================================================\n");
			int column = 0;
			char* value = strtok(buf, ",");
			while (value) {
				if (column == 0){
					printf("Name: ");
				}
				if (column == 1){
					printf("\tPhone No:");
				}
				if (column == 2){
					printf("\tEmail:");
				}
					printf("%s", value);
					value = strtok(NULL, ",");
					column++;
				};
			printf("========================================================================\n");
		}
	} 
	printf("Press: [q] | Cancel: \n");

	fclose(fp);
	return 0;
}	
	/* Add the functionality for search contacts here */
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
	return e_success;
}
