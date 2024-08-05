#include"Taxi.h"

int service_taxi() {

	const char* taxi_binaryfile = "taxi_binary.bin";
	FILE* vfd = fopen(taxi_binaryfile, "r+");

	const char* service_binaryfile = "service_binary.bin";
	FILE* sfd = fopen(service_binaryfile, "r+"); //service file descriptor 

	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;
	long rec_num;

	SERVICE new_serv_struct;
	SERVICE_HEADER header_serv_rec;
	long service_count;

	char discard;
	char temp_comment[LENGTH];

	// get the last allowable/ first available taxi vin
   // used as a condition to know if a vin is valid
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);


	do {

		printf("\nEnter vin of the vehicle you want to service (0 to go back)-> ");
		scanf_s("%d", &rec_num);
		getchar();

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

				// access the service header record to get the first available service record number
				fseek(sfd, 0, SEEK_SET);
				fread(&header_serv_rec, sizeof(SERVICE_HEADER), 1, sfd);

				//print out the first available service record number
				printf("\n availabe service nuber is: %u\n", header_serv_rec.first_avail_rec_count);
				service_count = header_serv_rec.first_avail_rec_count;

				new_serv_struct.vin = rec_num; //to identify the vehicle that was serviced

				// tells us its position on the service record
				new_serv_struct.record_count = service_count;


				printf("\nServicing vehicle %u\n", new_serv_struct.vin);
				printf("please enter today's date in this format (day-month-year)\n");
				scanf("%u %c %u %c %u\n", &new_serv_struct.day, &discard, &new_serv_struct.month, &discard, &new_serv_struct.year);
				printf("please comment(describe) the service been done to the vehicle\n");
				printf("-> \n");
				fgets(temp_comment, LENGTH, stdin);
				TRUNCATE(temp_comment);
				strcpy(new_serv_struct.comment, temp_comment);

				/* place the file pointer at the new record position that is to be written to */
				fseek(sfd, (header_serv_rec.first_avail_rec_count - service_file_start) * sizeof(SERVICE) + sizeof(SERVICE_HEADER), SEEK_SET);

				/* write the new service data to the service record */
				fwrite(&new_serv_struct, sizeof(SERVICE), 1, sfd);

				/* update the header file to contain or hold the next avialable service record number */
				header_serv_rec.first_avail_rec_count += 1;

				// write to header file
				//  -set the file pointer back to the beginning of the header
				//  -then write to it
				fseek(vfd, 0, SEEK_SET);
				fwrite(&header_serv_rec, sizeof(SERVICE_HEADER), 1, vfd);

				break;

			case DELETED:
				printf("\nunfortunately this vehicle has been deleted...\n");
				printf("service history no longer accessible\n\n");
				break;
			}
		}
		else {
			break; //rec_num must've been 0
		}
	} while (rec_num != 0);

	return 0;

}