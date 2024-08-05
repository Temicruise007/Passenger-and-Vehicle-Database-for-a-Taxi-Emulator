#include"Taxi.h"

int view_taxi_record() {

	const char* taxi_binaryfile = "taxi_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* vfd = fopen(taxi_binaryfile, "r+");

	/* read file sequentially */
	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;
	long rec_num;

	/*
		- position the file pointer to the start-of-file (header)
		- read the header record(aka zeroth record)
		  it indicates the first available passenger id */
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);

	while (1) {

		/* Ask user for the taxi VIN */
		printf("\n");
		printf("Which Vehicle record would you like to view?\n");
		printf("It should be noted that vehicle VINS start from (1000)\n");
		printf("Please type in the VIN of the vehicle record you would like to view(Enter 0 to go back): ");
		scanf_s("%d", &rec_num);

		if (rec_num >= START) {

			/* Move through the vehicle record to the position of the vehicle vin inputted by the user */
			// START = 1000, Because vehicle vin starts from 1000
			fseek(vfd, ((rec_num - START) * sizeof(TAXI)) + sizeof(TAXI_HEADER), SEEK_SET);



			/* Making sure input is valid */
			if ((fread(&taxi_struct, sizeof(TAXI), 1, vfd) == 0)) {
				printf("\nInvalid entry\n\n");
			}

			/* making sure taxi is not deleted */
			//go back to record position again and read agian because file pointer moved after the reading occured above
			fseek(vfd, ((rec_num - START) * sizeof(TAXI)) + sizeof(TAXI_HEADER), SEEK_SET);
			fread(&taxi_struct, sizeof(TAXI), 1, vfd);
			if (taxi_struct.status == DELETED) {
				printf("\nvehicle has been deleted or no longer exist\n\n");
			}
			else if (taxi_struct.status == ACTIVE) {

				/*input must have been valid and vehicle exists or is not deleted*/
				printf("\nTaxi VIN: %-8u Battery soc: %-11u Battery cap: %-10u Charge rate: %u\n",
					taxi_struct.vin, taxi_struct.battery_soc, taxi_struct.battery_capacity, taxi_struct.charge_rate);
				printf("Taxi VIN: %-8u Taxi state: %-12u Building parked: %-6u Corner parked: %u\n",
					taxi_struct.vin, taxi_struct.taxi_state, taxi_struct.building_parked, taxi_struct.corner_parked);
				printf("Taxi VIN: %-8u Distance travelled: %u\n\n\n",
					taxi_struct.vin, taxi_struct.distance);
			}


		}
		else if (rec_num == 0) {
			break;
		}
		else {
			printf("\n\nInvalid entry!!!\n\n");
		}
	}

	fclose(vfd); //close binary file
	return 0;
}