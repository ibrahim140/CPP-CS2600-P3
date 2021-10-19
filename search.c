// C program for the above approach
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Driver Code
int main()
{
	
	// Substitute the full file path
	// for the string file_path

	FILE* fp = fopen("Book.csv", "r");

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
		int i=1;
		char name[100];
		printf("Enter Name: ");
		scanf("%s", name);
		printf("%s", name);
		
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
    
    printf("\n###### Address Book ######\n");
    printf("###### Seach Contact by:\n\n");
    printf("==========================================================================\n");
    printf(":No. : Name\t\t : Phone No \t\t : Email ID \t\t :\n");
    printf("==========================================================================\n");
    printf(":1 : Joey Weeler\t : 626-232-3232 \t : jweel@gmail.com \t :\n");
    printf("==========================================================================\n");
    printf("Press: [q] | Cancel: \n");

	if (!fp)
		printf("Can't open file\n");

	else {
		// Here we have taken size of
		// array 1024 you can modify it
		char buffer[1024];

		int row = 0;
		int column = 0;

		while (fgets(buffer, 1024, fp)) {
			column = 0;
			row = 0;

			// To avoid printing of column
			// names in file can be changed
			// according to need
			if (row == 1)
				continue;

			// Splitting the data
			char* value = strtok(buffer, ",");

			while (value) {
				// Column 1
				if (column == 0) {
					printf("Number: ");
				}

				// Column 2
				if (column == 1) {
					printf("\tName: ");
				}

				// Column 3
				if (column == 2) {
					printf("\tEmail: ");
				}

				printf("%s", value);
				value = strtok(NULL, ",");
				column++;
				row++;
			}

			printf("\n");
		}

		// Close the file
		fclose(fp);
	}
	return 0;
}
