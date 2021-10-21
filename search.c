#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE* fp = fopen("address_book.csv", "r");
	char answer[100];
	do{
	

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
	printf("Press: [q] to cancel: \n");
	scanf("%s", answer);
	}while (strcmp(answer, "q") != 0);

	fclose(fp);
	return 0;
}