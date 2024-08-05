#include "Taxi.h"

int init_service_file() {

	const char* service_textfile = "service.txt";
	const char* service_binaryfile = "taxi_binary.bin";

	FILE* sfdi = fopen(service_textfile, "r"); // service file descriptor for input
	FILE* sfdo = fopen(service_binaryfile, "wb"); //service file descriptor for output

	/* Declaring variables to be used */
	SERVICE serv_struct;
	SERVICE_HEADER header_serv_rec;

	char serv_rec[LENGTH];
	char* serv_tok;

	//setting the first available record count to 1
	header_serv_rec.first_avail_rec_count = 1;

	//serv_count is temporary and will be used to increment the count of the record in the while loop
	long serv_count = header_serv_rec.first_avail_rec_count;

	while (fgets(serv_rec, LENGTH, (FILE*)sfdi) != NULL) {

		TRUNCATE(serv_rec);
		serv_struct.record_count = serv_count;

		serv_tok = strtok(serv_rec, "\t");
		serv_struct.vin = str_2_num(serv_tok);

		serv_tok = strtok(NULL, "\t");
		serv_struct.day = str_2_num(serv_tok);

		serv_tok = strtok(NULL, "\t");
		serv_struct.month = str_2_num(serv_tok);

		serv_tok = strtok(NULL, "\t");
		serv_struct.year = str_2_num(serv_tok);

		serv_tok = strtok(NULL, "\t");
		strcpy(serv_struct.comment, serv_tok);

		/* create each binary record : write out the record to the binary file */
		fseek(sfdo, ((serv_struct.vin - service_file_start) * sizeof(SERVICE)) + sizeof(SERVICE_HEADER), SEEK_SET);
		fwrite(&serv_struct, sizeof(SERVICE), 1, sfdo);

		// increment the temporary service record count
		serv_count++;
	}

	//update service header file with the next available record count
	header_serv_rec.first_avail_rec_count = serv_count;


	/*
		writing to the header file
		- set the file pointer back to the beginning of the header
		- write to the header
	*/
	fseek(sfdo, 0, SEEK_SET);
	fwrite(&header_serv_rec, sizeof(SERVICE_HEADER), 1, sfdo);

	fclose(sfdi);
	fclose(sfdo);
}