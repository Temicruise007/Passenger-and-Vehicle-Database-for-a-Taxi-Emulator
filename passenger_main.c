#include"passenger.h"

int main() {

	int choice;


	printf("To make use of this software do either of the following\n");

	do
	{
		/*
			when you chose the option to initialize record
			- you're creating a new binary file if it does not already exist
			- if file already exist, then you're just deleting it's content and overwriting it with a new entry
		*/
		printf("\n0: To quit\n");
		printf("1: Initialize record\n");
		printf("2: view a particular passenger record\n");
		printf("3: display all passenger record\n");
		printf("4: add new passenger\n");
		printf("5: update a particular passenger record\n");
		printf("6: Delete a particular passenger record\n");
		printf("7: Restore a Deleted record\n");
		printf("choice -> ");
		scanf_s("%d", &choice);

		switch (choice) 
		{
		case 0:
			break;

		case 1:
			init_passenger();
			printf("\n Initializing successful!!!\n\n");
			break;

		case 2:
			view_pass_record();
			break;

		case 3:
			disp_all_pass_record();
			break;

		case 4:
			add_new_passenger();
			break;

		case 5:
			update_pass_record();
			break;
		case 6:
			printf("Enter the Passenger ID to remove-> ");
			long pid_to_remove;
			scanf_s("%ld", &pid_to_remove);
			remove_passenger_rec(pid_to_remove);
			break;

		case 7: {
			long pid_to_restore;
			printf("Enter the Passenger ID to restore record-> ");
			scanf_s("%ld", &pid_to_restore);
			restore_deleted_passenger_rec(pid_to_restore);
			break;
		}
		default:
			printf("Entry is Invalid: Please TRY AGAIN! \n\n");
		}
		
	} while (choice != 0);

	return;
}