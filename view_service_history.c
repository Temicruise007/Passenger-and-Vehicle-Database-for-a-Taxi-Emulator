#include"Taxi.h"
/*
	- WE can either service a taxi or check the number of time a vehicle has been serviced

	update:
	-view service history for a vehicle with a valid vin
	-read the taxi binary file to know if the users vin provided to the console is valid.
	-if it is, 
*/

int view_service_history() {

	const char* taxi_binaryfile = "taxi_binary.bin";
	FILE* vfd = fopen(taxi_binaryfile, "r+");    // vehicle file descriptor

	const char* service_binaryfile = "service_binary.bin";
	FILE* sfd = fopen(service_binaryfile, "r+"); //service file descriptor 

	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;

	SERVICE serv_struct;
	SERVICE_HEADER header_serv_rec;
	long rec_num;


	 // get the last allowable/ first available taxi vin
	// used as a condition to know if a vin is valid
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);


	do {
	
		printf("\nEnter vin of the vehicle you want to view its service history (0 to go back)->");
		scanf_s("%d", &rec_num);
		getchar();
		serv_struct.vin = rec_num;

		/* Valid record? */
		if (rec_num >= header_tax_rec.first_vin) {
			printf("\nRecord %u not found!\n", rec_num);
		}

		else if (rec_num > 0 && rec_num < START) {
			printf("\n%u is an Invalid entry try again!!\n", rec_num);
		}
		else if (rec_num >= START) {

			/* position to the specified record number */
			fseek(vfd, ((rec_num - START) * sizeof(TAXI)) + sizeof(TAXI_HEADER), SEEK_SET);

			/* read record */
			fread(&taxi_struct, sizeof(TAXI), 1, vfd);

			/* is record active */
			switch (taxi_struct.status) {
			case ACTIVE:
				// will probably be best to use a while loop to scan through the record
				// and print out the services done to a vehicle whose vin matches the vin
				//provided by the user

				fread(&serv_struct, sizeof(SERVICE), 1, sfd);
				printf("\nService history for %u\n", serv_struct.vin);
				printf("DATE -> %u/%u/%u\n", serv_struct.day, serv_struct.month, serv_struct.year);
				printf("%s\n", serv_struct.comment);
				break;

			case DELETED:
				printf("\nunfortunately this vehicle has been deleted...\n");
				printf("\nservice history no longer accessible\n\n");
				break;
			}
		}
		else {
			break; //rec_num must've been 0
		}
	} while (rec_num != 0);

	return 0;
}