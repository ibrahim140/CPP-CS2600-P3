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
	// check if type is NUM
	if (type == NUM)
	{
		while (1)
		{
			int userNumInput;

			printf("%s", msg);			// prompt user for input
			scanf("%d", &userNumInput); // take input from user
			while (getchar() != '\n')
				;

			if ((userNumInput >= 0) && (userNumInput <= 4)) // limit submenu options from 0 to 4
			{
				// return user input
				return userNumInput;
			}
			else
			{
				// notice of invalid input
				printf("Please enter a valid option.\n");
			}
		}
	}
	// check if type is CHAR
	else if (type == CHAR)
	{
		while (1)
		{
			char userCharInput;

			printf("%s", msg);			 // prompt user for input
			scanf("%c", &userCharInput); // take input from user

			if (userCharInput == 'Y' || userCharInput == 'y')
			{
				// return y
				return 'Y';
			}
			else
			{
				// return e_fail for any input besides 'y'
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
	// check if type is CHAR
	if (type == CHAR)
	{
		while (1)
		{
			char userCharInput;

			printf("%s", msg);			 // prompt user for input
			scanf("%c", &userCharInput); // take input from user
			while (getchar() != '\n')
				;

			// validate user input to y or n
			if (userCharInput == 'Y' || userCharInput == 'y')
			{
				return 'Y';
			}
			else if (userCharInput == 'N' || userCharInput == 'n')
			{
				return 'N';
			}
			fflush(stdout);
		}
	}
	// check if type is NUM
	else if (type == NUM)
	{
		while (1)
		{
			int userNumInput;

			printf("%s", msg);			// prompt user for input
			scanf("%d", &userNumInput); // take input from user
			while (getchar() != '\n')
				;
			if ((userNumInput >= 0) && (userNumInput <= 6)) //for main menu, options limited from 0 to 6
			{
				// return users input
				return userNumInput;
			}
			else
			{
				// notice of invalid input
				printf("Please enter a valid option.\n");
			}
		}
	}

	return NONE;
}

//saves the information to the address book
Status save_prompt(AddressBook *address_book)
{
	/*
	 * Save prompt will allow for the user to save information to address book
	 * Uses a do while loop to ensure it is asked after main menu stops
	 * All file information goes to the address book files
	 */

	char option;//used as varaible to obtain option from user to refer to in while loop later

	do
	{
		main_menu();

		//Obtains the option from the user to take that character
		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y' || option == 'y')//Both uppercase and lowercase is used to confirm yes
		{
			//Saves information and confirms that where it is saved, then closes program
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N' || option == 'n');//Both uppercase and lowercase is used to confirm no

	return e_success;
}

Status list_contacts(AddressBook *address_book)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */
	int pageCount = 2, pageStart = 0;
	int buffer;
	int temp;

	while (1)
	{
		// format the output
		menu_header("Search Result: \n");
		printf("=====================================================================================================================\n");
		printf(": %-7s", "S.No");
		printf(": %-35s", "Name");
		printf(": %-35s", "Phone No");
		printf(": %-31s:\n", "Email ID");
		printf("=====================================================================================================================\n");

		// create a buffer to hold the contacts info
		ContactInfo *personBuffer;

		for (int i = pageStart; i < pageCount + pageStart; i++)
		{
			// break if there are no more contacts to be printed
			if (i == address_book->count)
				break;

			int row = 0;
			personBuffer = &address_book->list[i];
			//format to print out the information
			printf(": %-7d", personBuffer->si_no);//prints SI number
			printf(": %-35s", personBuffer->name[0]);//print name
			printf(": %-35s", personBuffer->phone_numbers[0]);//print phone number
			printf(": %-31s:\n", personBuffer->email_addresses[0]);//print email addresses
			row++;

			//determines which row the information will be printed in
			while (row < 5)
			{
				//adds extra spaces to format the spacing correctly
				//: is used for the sides to add a border
				printf(": %-7s", "");
				printf(": %-35s", "");
				if (personBuffer->numberCount > row)
					printf(": %-35s", personBuffer->phone_numbers[row]);
				else
					printf(": %-35s", "");
				if (personBuffer->emailCount > row)
					printf(": %-31s:\n", personBuffer->email_addresses[row]);
				else
					printf(": %-31s:\n", "");
				row++;
			}
			//closes off the block to distinguish from other contact information
			printf("=====================================================================================================================\n");
		}
		
		printf("0. Back\n");
		printf("1. Next\n");
		printf("2. Previous\n");
		printf("\nPlease enter an Option: ");

		scanf("%d", &buffer);
		printf("%d", buffer);

		switch (buffer)
		{
		case 0:
			return e_success;
		case 1:
			pageStart += pageCount;
			if (pageStart >= address_book->count)
				pageStart = 0;
			break;
		case 2:
			if (pageStart == 0)
			{
				if (address_book->count % 2 != 0)
					temp = address_book->count + 1;
				else
					temp = address_book->count;
				pageStart = temp;
			}
			pageStart -= pageCount;
			break;
		default:
			break;
		}
	}
}

void menu_header(const char *str)
{
	fflush(stdout);

#ifdef OS_Windows
	system("cls");
#else
	system("clear");
#endif

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

//used to have a function when menu needs to be called again
void add_menu(char *addName, char *addNumber, char *addEmail)
{
	menu_header("Add menu\n");

	printf("0. Back\n");
	printf("1. Name     : %s\n", addName);
	printf("2. Phone No : %s\n", addNumber);
	printf("3. Email ID : %s\n\n", addEmail);
}

// function to print search menu
void search_menu()
{
	menu_header("Search Contact by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
}

// function to print edit menu
void edit_menu()
{
	menu_header("Search Contact to Edit by: \n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
}

// function to print delete menu
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
		case e_save:
			save_file(address_book);
			printf("Done. Press enter key to continue:");
			while (getchar() != '\n')
				;
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
	ContactInfo person = {"", "", "", 0, 0, 0}; //takes contact information and adds to string
	_Bool addedName = 0;						// flag for if name has been added
	_Bool addedPhone = 0;						// flag for if phone number has been added
	_Bool addedEmail = 0;						// flag for if email has been added
	_Bool added = 0;							// checks to see if anything has been added

	do
	{
		//calls menu to be displayed with updated information of contact
		add_menu(*person.name, *person.phone_numbers, *person.email_addresses);

		//obtain user's option
		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
		case 1: //user adds contact name
			printf("Please enter the name: ");
			gets(*person.name);
			addedName = 1;
			added = 1;
			break;
		case 2: //user adds contact phone number
			printf("Please enter the phone number: ");
			scanf("%s", *person.phone_numbers);
			addedPhone = 1;
			added = 1;
			person.numberCount++;
			break;
		case 3: //user adds contact email
			printf("Please enter the email address: ");
			scanf("%s", *person.email_addresses);
			addedEmail = 1;
			added = 1;
			person.emailCount++;
			break;
		case 0: //goes back to main menu
			if (added)
			{
				person.si_no = address_book->count;
				if (!addedName)
					strcpy(person.name[0], " ");
				if (!addedPhone)
					strcpy(person.phone_numbers[0], " ");
				if (!addedEmail)
					strcpy(person.email_addresses[0], " ");
				address_book->list[address_book->count++] = person;
			}
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
	//switch based on the field you are looking for
	switch (field)
	{
	//Print out serial number
	case 0:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			int row = 0;
			ContactInfo *personBuffer = &address_book->list[i];

			for (int count = 0; count < 1; count++) //iterating throught the columns 
			{
				if (personBuffer->si_no == atoi(str)) //print return information when found
				{
					printf(": %-7d", personBuffer->si_no);
					printf(": %-35s", personBuffer->name[0]);
					printf(": %-35s", personBuffer->phone_numbers[0]);
					printf(": %-31s:\n", personBuffer->email_addresses[0]);
					row++; //Do this for the next row
					
					while (row < 5)
					{
						printf(": %-7s", "");
						printf(": %-35s", "");
						if (personBuffer->numberCount > row)
							printf(": %-35s", personBuffer->phone_numbers[row]);
						else
							printf(": %-35s", "");
						if (personBuffer->emailCount > row)
							printf(": %-31s:\n", personBuffer->email_addresses[row]);
						else
							printf(": %-31s:\n", "");
						row++;
					}
					printf("=====================================================================================================================\n");
				}
			}
		}
		break; //break once all rows and columns have been found
	//print out name search
	case 1:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			int row = 0;
			ContactInfo *personBuffer = &address_book->list[i];

			for (int count = 0; count < 1; count++)//iterating throught the columns 
			{
				if (strcasecmp(personBuffer->name[count], str) == 0) //print return information when found
				{
					printf(": %-7d", personBuffer->si_no);
					printf(": %-35s", personBuffer->name[0]);
					printf(": %-35s", personBuffer->phone_numbers[0]);
					printf(": %-31s:\n", personBuffer->email_addresses[0]);
					row++; //print everything for next row

					while (row < 5)
					{
						printf(": %-7s", "");
						printf(": %-35s", "");
						if (personBuffer->numberCount > row)
							printf(": %-35s", personBuffer->phone_numbers[row]);
						else
							printf(": %-35s", "");
						if (personBuffer->emailCount > row)
							printf(": %-31s:\n", personBuffer->email_addresses[row]);
						else
							printf(": %-31s:\n", "");
						row++; //print everything for next row
					}
					printf("=====================================================================================================================\n");
				}
			}
		}
		break; //break once searched and print is complete
	//Search through the phone numbers
	case 2:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			int row = 0;
			ContactInfo *personBuffer = &address_book->list[i];

			for (int count = 0; count < personBuffer->numberCount; count++)//iterating throught the columns
			{
				if (strcasecmp(personBuffer->phone_numbers[count], str) == 0)//print when number has been found
				{
					printf(": %-7d", personBuffer->si_no);
					printf(": %-35s", personBuffer->name[0]);
					printf(": %-35s", personBuffer->phone_numbers[0]);
					printf(": %-31s:\n", personBuffer->email_addresses[0]);
					row++; //print everything for next row

					while (row < 5)
					{
						printf(": %-7s", "");
						printf(": %-35s", "");
						if (personBuffer->numberCount > row)
							printf(": %-35s", personBuffer->phone_numbers[row]);
						else
							printf(": %-35s", "");
						if (personBuffer->emailCount > row)
							printf(": %-31s:\n", personBuffer->email_addresses[row]);
						else
							printf(": %-31s:\n", "");
						row++; //print everything for next row
					}
					printf("=====================================================================================================================\n");
				}
			}
		}
		break; //break once searched and print is complete
	//Search by email address
	case 3:
		for (int i = 0; i < address_book->count; i++) //iterating through the rows
		{
			int row = 0;
			ContactInfo *personBuffer = &address_book->list[i];

			for (int count = 0; count < personBuffer->emailCount; count++)//iterating throught the columns
			{
				if (strcasecmp(personBuffer->email_addresses[count], str) == 0)//print when email has been found
				{
					printf(": %-7d", personBuffer->si_no);
					printf(": %-35s", personBuffer->name[0]);
					printf(": %-35s", personBuffer->phone_numbers[0]);
					printf(": %-31s:\n", personBuffer->email_addresses[0]);
					row++; //break once searched and print is complete

					while (row < 5)
					{
						printf(": %-7s", "");
						printf(": %-35s", "");
						if (personBuffer->numberCount > row)
							printf(": %-35s", personBuffer->phone_numbers[row]);
						else
							printf(": %-35s", "");
						if (personBuffer->emailCount > row)
							printf(": %-31s:\n", personBuffer->email_addresses[row]);
						else
							printf(": %-31s:\n", "");
						row++; //break once searched and print is complete
					}
					printf("=====================================================================================================================\n");
				}
			}
		}
		break; //break once searched and print is complete
	//If no case is used, use default
	default:
		break;
	}
	return e_success; //return back to main menu
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
		//gets user input based on name, number, email, and serial
		switch (option)
		{
		case 1: //user can search for name
			field = name;
			printf("Enter the name: ");
			gets(buffer); //get name input
			break;
		case 2: //user can search for phone number
			field = number;
			printf("Enter the phone number: ");
			gets(buffer); //get number input
			break;
		case 3: //user can search for email
			field = email;
			printf("Enter the email address: ");
			gets(buffer); //get email input
			break;
		case 4: //user can search for Serial Id
			field = serial;
			printf("Enter the serial number: ");
			gets(buffer); //get serial input
			break;
		case 0: //exit
			return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);
		printf("Press: [q] = Cancel: ");
		scanf("%s", buffer);
		if (strcmp(buffer, "q") == 0) //if q break
			break;

	} while (option != 0); //continue to loop while the option is not 0
	
	return e_success; //return back to the main menu
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for editing contacts here */
	int option;
	char buffer[NAME_LEN];
	Field field;
	char userPress;

	do
	{
		// Display search menu and get option from user
		edit_menu();
		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
		case 1: //user edits contact name
			field = name;
			printf("Enter the name: ");
			gets(buffer);
			break;
		case 2: //user edits contact phone number
			field = number;
			printf("Enter the phone number: ");
			scanf("%s", buffer);
			break;
		case 3: //user edits contact email
			field = email;
			printf("Enter the email address: ");
			scanf("%s", buffer);
			break;
		case 4: //user edits contact email
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
						printf("1. Name       : %s\n", personBuffer->name[0]);
						printf("2. Phone No 1 : %s\n", personBuffer->phone_numbers[0]);
						for (int j = 1; j < personBuffer->numberCount; j++)
							printf("            %d : %s\n", j + 1, personBuffer->phone_numbers[j]);
						printf("3. Email ID 1 : %s\n", personBuffer->email_addresses[0]);
						for (int j = 1; j < personBuffer->emailCount; j++)
							printf("            %d : %s\n", j + 1, personBuffer->email_addresses[j]);

						userPress = get_submenu_option(NUM, "\nPlease select an option: ");

						switch (userPress)
						{
						case 1: //name
							printf("Enter the name: [Just enter removes the entry]: ");
							gets(buffer);
							if (buffer[0] == '\n') // did user enter only?
								strcpy(*personBuffer->name, " ");
							else
								strcpy(*personBuffer->name, buffer);
							break;
						case 2: //phone number
							do
							{
								printf("Enter the phone number index to be changed [Max %d]: ", personBuffer->numberCount + 1);
								scanf("%s", &userPress);
								while (getchar() != '\n')
									;
								if (atoi(&userPress) == personBuffer->numberCount + 1)
									personBuffer->numberCount++;
							} while (atoi(&userPress) > personBuffer->numberCount + 1 || atoi(&userPress) < 1);

							printf("Enter the phone number: [Just enter removes the entry]: ");
							gets(buffer);
							if (buffer[0] == '\n')
								strcpy(personBuffer->phone_numbers[atoi(&userPress) - 1], " ");
							else
								strcpy(personBuffer->phone_numbers[atoi(&userPress) - 1], buffer);
							break;
						case 3: //email
							do
							{
								printf("Enter the email ID index to be changed [Max %d]: ", personBuffer->emailCount + 1);
								scanf("%s", &userPress);
								while (getchar() != '\n')
									;
								if (atoi(&userPress) == personBuffer->emailCount + 1)
									personBuffer->emailCount++;
							} while (atoi(&userPress) > personBuffer->emailCount + 1 || atoi(&userPress) < 1);

							printf("Enter the email ID: [Just enter removes the entry]: ");
							gets(buffer);
							if (buffer[0] == '\n')
								strcpy(personBuffer->email_addresses[atoi(&userPress) - 1], " ");
							else
								strcpy(personBuffer->email_addresses[atoi(&userPress) - 1], buffer);
							break;
						case 0: //go back
							return e_success;
						}
					} while (userPress != 0);
				}
			}
		}

	} while (option != 0);

	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for deleting contacts here */
	if (address_book == NULL)
	{
		// notify user the address book is empty
		printf("The address book is empty. Use Add Contact to add contacts.\n");
		return e_fail;
	}

	// declare local variables
	int option; // get user input for menu options
	char buffer[NAME_LEN]; // buffer to hold user inputs
	Field field; // field for passing to search funciton 
	char userPress; // get user input for option after search is called

	do
	{
		// Display search menu and get option from user
		delete_menu();
		// get user option for delete menu
		option = get_submenu_option(NUM, "Please select an option: ");

		switch (option)
		{
			case 1: //name
				field = name; // set field to name
				printf("Enter the name: "); // prompt user
				gets(buffer); // get input
				break;
			case 2: //phone number
				field = number; // set field to number
				printf("Enter the phone number: "); // prompt user
				gets(buffer); // get input
				break;
			case 3: //email
				field = email; // set field to email
				printf("Enter the email address: "); // prompt user
				gets(buffer); // get input
				break;
			case 4: //email
				field = serial; // set field to serial number
				printf("Enter the serial number: "); // prompt user
				gets(buffer); // get input
				break;
			case 0: //exits
				return e_success;
		}

		// Search for element that the buffer contains
		search(buffer, address_book, field);
		printf("Press: [s] = Select, [q] = Cancel: "); // prompt user for an input
		scanf("%s", &userPress);					   // get user input
		while (getchar() != '\n'); // clear standard input (to no get the '\n' character)

		if (userPress == 's' || userPress == 'S')
		{
			printf("Select a Serial Number (S.No) to Delete: "); //prompt user for serial # input
			scanf("%s", &userPress);							 // get user input
			while (getchar() != '\n');// clear standard input

			int i; // Local variable for loop iteration
			for (i = 0; i < address_book->count; i++) //iterating through the rows
			{
				// get contact from list and store into personBuffer
				ContactInfo *personBuffer = &address_book->list[i];
				// check if the users input matches the contact in the list
				if (personBuffer->si_no == atoi(&userPress))
				{
					// print the info of the contact to be deleted
					menu_header("Delete Contact:\n");
					printf("0. Back\n");
					printf("1. Name       : %s\n", personBuffer->name[0]); // print contact name
					printf("2. Phone No 1 : %s\n", personBuffer->phone_numbers[0]); // print contacts 1st phone number
					for (int j = 1; j < personBuffer->numberCount; j++) // iterate through the other phone numbers
						printf("            %d : %s\n", j + 1, personBuffer->phone_numbers[j]); // print other phone #'s
					printf("3. Email ID 1 : %s\n", personBuffer->email_addresses[0]); // print contacts 1st email ID
					for (int j = 1; j < personBuffer->emailCount; j++) // iterate through the other email ID's
						printf("            %d : %s\n", j + 1, personBuffer->email_addresses[j]); // print other email ID's
					break;
				}
			}
			// get user input for deleting contact
			char userInput2 = get_submenu_option(CHAR, "\nEnter 'Y' to delete. [Press any key to ignore]: ");

			// confirm if user wants to delete contact
			if (userInput2 == 'y' || userInput2 == 'Y')
			{
				// declare local tepm contacts
				ContactInfo tempContact1, tempContact2;

				// assign the contact at index 'i' to tempContact1
				tempContact1 = address_book->list[i];
				// assign the contact at the end of the list to tempContact2
				tempContact2 = address_book->list[address_book->count - 1];

				// move contact at index 'i' to the end of the list
				address_book->list[address_book->count - 1] = tempContact1;
				// move contact previosly at the end of the list to index 'i'
				address_book->list[i] = tempContact2;
				// decrement the count of the address book
				address_book->count--;
				// inform user of contact deletion
				printf("Contact has been deleted.\n\n");
			}
		}
	} while (option != 0);

	// return e_success
	return e_success;
}
