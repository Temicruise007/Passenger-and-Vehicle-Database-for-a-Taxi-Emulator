#include"Passenger.h"

int init_passenger(void) {

	/* In this function we do the following operations:
	- Read the passengers.txt that contains the records of all the passengers.
	- Copy the records into the created binary file.
	*/
	_set_fmode(_O_BINARY);


	const char* passenger_textfile = "passenger.txt";
	const char* passenger_binaryfile = "passenger_binary.bin";

	FILE* pfdi = fopen(passenger_textfile, "r"); // passenger input file descriptor used(pfdi)
	FILE* pfdo = fopen(passenger_binaryfile, "wb"); // passenger output file descriptor used(pfdo)


	/* Declaring variables to be used */
	PASSENGER pass_struct;
	HEADER header_pass_rec;


	char passenger_rec[LENGTH];
	char* pass_tok;  // returns the address of the token


	//setting first passanger ID to 1000
	header_pass_rec.first_id = 1000;

	//passenger_id is temporary and will be used to increment the [passenger ID(pid)] of the record in the while loop
	long passenger_id = header_pass_rec.first_id;


	while (fgets(passenger_rec, LENGTH, (FILE*)pfdi) > 0) {

		TRUNCATE(passenger_rec);
		pass_struct.pid = passenger_id;

		pass_tok = strtok(passenger_rec, "\t");
		pass_struct.time_req = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.orig_street = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.orig_avenue = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.orig_puc = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.dest_street = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.dest_avenue = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.dropof_corner = str_2_num(pass_tok);

		pass_tok = strtok(NULL, "\t");
		pass_struct.pass_state = str_2_num(pass_tok);

		pass_struct.status = ACTIVE;  // Initialize the status to ACTIVE

		passenger_id++; //increment the passenger id


		/*Create each binary record : Write out the record to the binary file*/
		fseek(pfdo, ((pass_struct.pid - START) * sizeof(PASSENGER)) + sizeof(HEADER), SEEK_SET);
		fwrite(&pass_struct, sizeof(PASSENGER), 1, pfdo);
	}


	//update header file with the next passenger id
	header_pass_rec.first_id = passenger_id; //nxt available id


	/* 
		Writing to the header file 
		-set the file pointer back to the beginning of the header
		-write to header

	*/
	fseek(pfdo, 0, SEEK_SET);
	fwrite(&header_pass_rec, sizeof(HEADER), 1, pfdo);

	fclose(pfdi);
	fclose(pfdo);

	return 0;
}