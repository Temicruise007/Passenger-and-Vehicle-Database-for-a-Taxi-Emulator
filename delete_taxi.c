#include "Taxi.h"

int delete_taxi() {

	const char* taxi_binaryfile = "taxi_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* vfd = fopen(taxi_binaryfile, "r+");

	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;
	long rec_num;

	/* Read header, indicates first available/ last allowable record */
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);

	do 
	{
		printf("\nEnter vehicle record number to delete (0 to go back)->");
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
			switch (taxi_struct.status)
			{
			case ACTIVE:
				taxi_struct.status = DELETED;

				/* Reposition file position back to rec_no */
				fseek(vfd, ((rec_num - START) * sizeof(TAXI)) + sizeof(TAXI_HEADER), SEEK_SET);
				/* Now write */
				fwrite(&taxi_struct, sizeof(TAXI), 1, vfd);
				printf("\nRecord %u now deleted\n", rec_num);
				break;

			case DELETED:
				printf("\nRecord %u was already deleted\n", rec_num);
				break;
			default:
				printf("Record %u - Invalid status %d\n", rec_num, taxi_struct.status);
				break;
			}// end of switch case
		}
		else {
			break;
		}// end of error handling
	} while (rec_num != 0);

	return 0;
}