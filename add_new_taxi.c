#include"Taxi.h"

int add_new_taxi() {

	const char* taxi_binaryfile = "taxi_binary.bin";

	FILE* vfd = fopen(taxi_binaryfile, "r+"); // vehicle file descriptor for output (vfdo)

	/* Declaring variables to be used */
	TAXI new_taxi;
	TAXI_HEADER header_tax_rec;
	long vin;

	/* Access header record to get first vehicle vin */
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);

	/* print out the first avialable vehicle vin*/
	printf("\navailable vehicle vin is: %u\n", header_tax_rec.first_vin);
	vin = header_tax_rec.first_vin;


	/* prompt user for the data */
	printf("Enter the Battery soc: -> ");
	scanf_s("%u", &new_taxi.battery_soc);

	printf("Enter the  Battery capacity: -> ");
	scanf_s("%u", &new_taxi.battery_capacity);

	printf("Enter the  Charge rate: -> ");
	scanf_s("%u", &new_taxi.charge_rate);

	printf("Enter the  Taxi state: -> ");
	scanf_s("%u", &new_taxi.taxi_state);

	printf("Enter the  Building parked: -> ");
	scanf_s("%u", &new_taxi.building_parked);

	printf("Enter the  Corner parked: -> ");
	scanf_s("%u", &new_taxi.corner_parked);

	new_taxi.distance = 0;
	
	//automatically set the status to active
	new_taxi.status = ACTIVE;

	//update the new vehicle vin with the first availabe vehicle vin
	new_taxi.vin = vin;

	/* display the newly added vehicle record */
	printf("\nTaxi VIN: %-8u Battery soc: %-11u Battery cap: %-10u Charge rate: %u\n",
		new_taxi.vin, new_taxi.battery_soc, new_taxi.battery_capacity, new_taxi.charge_rate);
	printf("Taxi VIN: %-8u Taxi state: %-12u Building parked: %-6u Corner parked: %u\n",
		new_taxi.vin, new_taxi.taxi_state, new_taxi.building_parked, new_taxi.corner_parked);
	printf("Taxi VIN: %-8u Distance travelled: %u\n\n\n",
		new_taxi.vin, new_taxi.distance);

	/* place the file pointer at the new record position that is to be written to */
	fseek(vfd, (header_tax_rec.first_vin - START) * sizeof(TAXI) + sizeof(TAXI_HEADER), SEEK_SET);

	/* write the vehicle data to the record */
	fwrite(&new_taxi, sizeof(TAXI), 1, vfd);


	/* update the header file to contain or hold the next avialable vehicle vin */
	header_tax_rec.first_vin += 1;

	// write to header file
	//  -set the file pointer back to the beginning of the header
	//  -then write to it
	fseek(vfd, 0, SEEK_SET);
	fwrite(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);

	fclose(vfd);
	return 0;
}	