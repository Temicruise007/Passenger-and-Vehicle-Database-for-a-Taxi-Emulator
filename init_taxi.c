#include"Taxi.h"

int init_taxi() {

	/* In this function we do the following operations:
	- Read the vehicle.txt that contains the records of all the taxis/vehicles.
	- Copy the records into the created binary file.
	*/
	_set_fmode(_O_BINARY);

	const char*  taxi_textfile = "taxi.txt";
	const char* taxi_binaryfile = "taxi_binary.bin";

	FILE* vfdi = fopen(taxi_textfile, "r"); // vehicle file descriptor for input (vfdi)
	FILE* vfdo = fopen(taxi_binaryfile, "wb"); // vehicle file descriptor for output (vfdo)

	/* Declaring variables to be used */
	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;

	char taxi_rec[LENGTH];
	char* taxi_tok; //return the address of the token


	//setting the first taxi VIN to 1000
	header_tax_rec.first_vin = 1000;

	//taxi_vin is temporary and will be used to increment the vin of the record in the while loop
	long taxi_vin = header_tax_rec.first_vin; 


	while (fgets(taxi_rec, LENGTH, (FILE*)vfdi) != NULL) {

		TRUNCATE(taxi_rec);
		taxi_struct.vin = taxi_vin;

		taxi_tok = strtok(taxi_rec, "\t");
		taxi_struct.battery_soc = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.battery_capacity = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.charge_rate = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.taxi_state = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.building_parked = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.corner_parked = str_2_num(taxi_tok);

		taxi_tok = strtok(NULL, "\t");
		taxi_struct.distance = str_2_num(taxi_tok);

		taxi_struct.status = ACTIVE;


		/* create each binary record : write out the record to the binary file */
		fseek(vfdo, ((taxi_struct.vin - START) * sizeof(TAXI)) + sizeof(TAXI_HEADER), SEEK_SET);
		fwrite(&taxi_struct, sizeof(TAXI), 1, vfdo);

		// increment the temporary taxi VIN
		taxi_vin++; 
	}


	//update taxi header file with the next available taxi vin
	header_tax_rec.first_vin = taxi_vin;

	/*	
		writing to the header file
		- set the file pointer back to the beginning of the header
		- write to the header
	*/
	fseek(vfdo, 0, SEEK_SET);
	fwrite(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfdo);

	fclose(vfdi);
	fclose(vfdo);

	return 0;

}