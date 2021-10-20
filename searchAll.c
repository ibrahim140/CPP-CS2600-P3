#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Driver Code
int main()
{
	// Substitute the full file path
	// for the string file_path

	FILE* fp = fopen("address_book.csv", "r");

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
		char name[100];
		printf("Enter Name: ");
		scanf("%s", name);
		//printf("%s", name);
		enum { MAXC = 512 };
		int found = 0, line = 0;
    	char buf[MAXC] = "";
    	

    	while (fgets (buf, MAXC, fp)) {     /* read each line */
        	if (strstr (buf, name)) {       /* test for term  */
        	    found = 1; 					/* set found flag */
				break;           
        	}
        	if (strchr (buf, '\n')) line++; /* increment line */
    	}
		if (found){
		printf("\n###### Address Book ######\n");
    	printf("###### Seach Contact by:\n\n");
    	printf("========================================================================\n");
    	printf(": Name\t\t\t : Phone No      \t\t : Email ID \n");
    	printf("========================================================================\n");
		char buffer[1024];
		int row = line;
		int column = 0;
		while (fgets(buffer, 1024, fp)){
		column = 0;
		char* value = strtok(buffer, ",");

			while (value) {
				// Column 1
				if (column == 0) {
					printf("Name: ");
				}

				// Column 2
				if (column == 1) {
					printf("\tNumber: ");
				}

				// Column 3
				if (column == 2) {
					printf("\tEmail: ");
				}

				printf("%s", value);
				value = strtok(NULL, ",");
				column++;
			}
		}
		printf ("'%s' found on line %zu.\n", name, line + 1);
		printf("========================================================================\n");
		}
	}
	if(choice == 2){
		char number[100];
		printf("Enter Number: ");
		scanf("%s", number);
	}
	if(choice == 3){
		char email[100];
		printf("Enter Email ID: ");
		scanf("%s", email);
	}
    
	printf("Press: [q] | Cancel: \n");

	//fclose(fp);
	return 0;
}
