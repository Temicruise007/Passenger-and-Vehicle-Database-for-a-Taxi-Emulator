/* Update any student record regardless of its location in the
   file (direct access).
 * This is *not* accessing records using the passenger number, instead
   it is using the record number.  How to access using a key other
   than the record number will be discussed in class by larry hughes later.
*/

#include"Passenger.h"

int update_pass_record() {

	const char* passenger_binaryfile = "passenger_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* pfd = fopen(passenger_binaryfile, "r+");

	/* read the file sequentially*/
	PASSENGER passeng_rec;
	HEADER header_pass_rec;
	long rec_num;
	int choice;

	/*
		- position the file pointer to the start-of-file (header)
		- read the header record(aka zeroth record)
		  it indicates the first available/ last allowable passenger id */
	fseek(pfd, 0, SEEK_SET);
	fread(&header_pass_rec, sizeof(HEADER), 1, pfd);

	do{

		printf("\nEnter the passenger record number you want to change (0 to go back) ->");
		scanf_s("%u", &rec_num);
		getchar();

		if (rec_num >= header_pass_rec.first_id) {
			printf("\n%u is an Invalid record\n\n", rec_num);
		}
		else if (rec_num > 0 && rec_num < START) {
			printf("\n%u is an Invalid entry try again!!\n", rec_num);
		}
		else if (rec_num >= START) {

			/* Position to specified record number */
			fseek(pfd, ((rec_num - START) * sizeof(PASSENGER)) + sizeof(HEADER), SEEK_SET);
			//fseek(pfd, rec_num * sizeof(PASSENGER), SEEK_SET);

			// once the file position is moved, the record is read
			// the user can change the contents of the record
			// once changed, the record is written back to the file
			fread(&passeng_rec, sizeof(PASSENGER), 1, pfd);

			// Check if the record has been deleted first.
			if (passeng_rec.status == DELETED) {
				printf("\nThe record for passenger ID %ld has been deleted.\n\n", rec_num);
				continue; // Skip the rest of this loop iteration
			}

			printf("\nRecord %u found\n", rec_num);
			printf("passenger ID: %-6u Request time: %-8u Orig street: %-8u Orig avenue: %u\n",
				passeng_rec.pid, passeng_rec.time_req, passeng_rec.orig_street, passeng_rec.orig_avenue);
			printf("passenger ID: %-6u orig puc: %-12u dest street: %-8u dest avenue: %u\n",
				passeng_rec.pid, passeng_rec.orig_puc, passeng_rec.dest_street, passeng_rec.dest_avenue);
			printf("passenger ID: %-6u drop-of-corner: %-6u passenger state: %u\n\n\n",
				passeng_rec.pid, passeng_rec.dropof_corner, passeng_rec.pass_state);

			printf("\nWhich field is to be changed?\n");
			printf("0: to go back\n");
			printf("1: Request time\n");
			printf("2: Orig street\n");
			printf("3: Orig avenue\n");
			printf("4: Orig puc\n");
			printf("5: dest street\n");
			printf("6: Orig avenue\n");
			printf("7: drop-of-corner\n");
			printf("8: passenger state\n");
			printf("choice -> ");
			scanf_s("%d", &choice);

			while (choice != 0) {
				getc(stdin); //clear NL from input buffer
				switch (choice) {
				case 1:
					printf("\nEnter the new Request time -> ");
					scanf_s("%u", &passeng_rec.time_req);
					break;

				case 2:
					printf("Enter the new Orig street -> ");
					scanf_s("%u", &passeng_rec.orig_street);
					break;

				case 3:
					printf("Enter the new Orig avenue -> ");
					scanf_s("%u", &passeng_rec.orig_avenue);
					break;

				case 4:
					printf("Enter the new Orig puc -> ");
					scanf_s("%u", &passeng_rec.orig_puc);
					break;

				case 5:
					printf("Enter the new dest street -> ");
					scanf_s("%u", &passeng_rec.dest_street);
					break;

				case 6:
					printf("Enter the new dest avenue -> ");
					scanf_s("%u", &passeng_rec.dest_avenue);
					break;

				case 7:
					printf("Enter the new drop-of-corner -> ");
					scanf_s("%u", &passeng_rec.dropof_corner);
					break;

				case 8:
					printf("Enter the new passenger state (0 or 1) -> ");
					scanf_s("%u", &passeng_rec.pass_state);
					break;

				default:
					printf("\n%d is an Invalid entry try again!!\n", choice);
				}
				// ask user for choice - great technique for repeating until 0
				printf("\nWhich field is to be changed?\n");
				printf("0: to back\n");
				printf("1: Request time\n");
				printf("2: Orig street\n");
				printf("3: Orig avenue\n");
				printf("4: Orig puc\n");
				printf("5: dest street\n");
				printf("6: Orig avenue\n");
				printf("7: drop-of-corner\n");
				printf("8: passenger state\n");
				printf("choice -> ");
				scanf_s("%d", &choice);
				
			}
			/*
			 * Modified record must be written back to the file;
			   however, the last read moved the file pointer to
			   the start of the next record, therefore, it is
			   necessary to lseek() "back" to the record ??? larry hughes might have meant fseek() back to record
			 */
			fseek(pfd, (rec_num - START) * sizeof(PASSENGER) + sizeof(HEADER), SEEK_SET);
			/* Now the record can be written to the file */
			fwrite(&passeng_rec, sizeof(PASSENGER), 1, pfd);
		}
		else {
			break;
		}
	
	} while (rec_num != 0);

	fclose(pfd);
	return 0;
}