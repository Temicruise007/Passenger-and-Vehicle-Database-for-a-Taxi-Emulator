#include"Taxi.h"

int main() {

	int choice;


	printf("To make use of this software, choose an option from the menu below\n");

	while (1)
	{
		/*
			when you chose the option to initialize record
			- you're creating a new binary file if it does not already exist
			- if file already exist, then you're just deleting it's content and overwriting it with
			  a new entry
		*/
		printf("\n0: To quit");
		printf("\n1: Initialize record\n");
		printf("2: view a particular taxi record\n");
		printf("3: To deleted a taxi record\n");
		printf("4: add new taxi to the record\n");
		printf("choice -> ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0:
			break;

		case 1:
			init_taxi();
			printf("\n Initializing successful!!!\n\n");
			break;

		case 2:
			view_taxi_record();
			break;

		case 3:
			delete_taxi();
			break;

		case 4:
			add_new_taxi();
			break;

		default:
			printf("Entry is Invalid: Please TRY AGAIN! \n\n");

		}

		if (choice == 0) {
			break;
		}
	}
}