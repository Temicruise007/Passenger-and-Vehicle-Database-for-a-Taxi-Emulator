#include"Passenger.h"

int add_new_passenger() {

	const char* passenger_binaryfile = "passenger_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* pfd = fopen(passenger_binaryfile, "r+");

	/* read the file sequentially*/
	PASSENGER new_passenger;
	HEADER header_pass_rec;
	long pid;


	/* Access header record to get first available passenger id */
	fseek(pfd, 0, SEEK_SET);
	fread(&header_pass_rec, sizeof(HEADER), 1, pfd);

	/* print out the first available passenger id*/
	printf("\navailable passenger id is: %u \n", header_pass_rec.first_id);
	pid = header_pass_rec.first_id;

	

	/*prompt user for the data of the new passenger record*/
	printf("Enter the Request time -> ");
	scanf_s("%u", &new_passenger.time_req);

	printf("Enter the Orig street -> ");
	scanf_s("%u", &new_passenger.orig_street);

	printf("Enter the Orig avenue -> ");
	scanf_s("%u", &new_passenger.orig_avenue);

	printf("Enter the Orig puc -> ");
	scanf_s("%u", &new_passenger.orig_puc);

	printf("Enter the dest street -> ");
	scanf_s("%u", &new_passenger.dest_street);

	printf("Enter the dest avenue -> ");
	scanf_s("%u", &new_passenger.dest_avenue);

	printf("Enter the drop-of-corner -> ");
	scanf_s("%u", &new_passenger.dropof_corner);

	printf("Enter the passenger state (0 or 1) -> ");
	scanf_s("%u", &new_passenger.pass_state);

	//update new passenger id with the  first available passenger id
	new_passenger.pid = pid;

	/* display the newly added passenger record */
	printf("\npassenger ID: %-6u Request time: %-8u Orig street: %-8u Orig avenue: %u\n",
		new_passenger.pid, new_passenger.time_req, new_passenger.orig_street, new_passenger.orig_avenue);
	printf("passenger ID: %-6u orig puc: %-12u dest street: %-8u dest avenue: %u\n",
		new_passenger.pid, new_passenger.orig_puc, new_passenger.dest_street, new_passenger.dest_avenue);
	printf("passenger ID: %-6u drop-of-corner: %-6u passenger state: %u\n\n\n",
		new_passenger.pid, new_passenger.dropof_corner, new_passenger.pass_state);

	/* place the file pointer at the new record position that is to be written to */
	fseek(pfd, (header_pass_rec.first_id - START) * sizeof(PASSENGER) + sizeof(HEADER), SEEK_SET);

	/* Write the passenger data to the passenger file */
	fwrite(&new_passenger, sizeof(PASSENGER), 1, pfd);


	/* update the header file to contain or to hold the next available passenger id*/
	header_pass_rec.first_id += 1;



	/*
		Writing to the header file
		-set the file pointer back to the beginning of the header
		-write to header

	*/
	fseek(pfd, 0, SEEK_SET);
	fwrite(&header_pass_rec, sizeof(HEADER), 1, pfd);// write to header

	fclose(pfd);
	return 0;
}