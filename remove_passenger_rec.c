#include"Passenger.h"

int remove_passenger_rec(long pid) {

	const char* passenger_binaryfile = "passenger_binary.bin";
	FILE* pfd = fopen(passenger_binaryfile, "r+");

	if (pfd == NULL) {
		printf("Error: Could not open passenger file.\n");
		return -1;
	}

	PASSENGER temp_passenger;
	HEADER header_pass_rec;

	//Read header to get the first available passenger id
	fseek(pfd, 0, SEEK_SET);
	fread(&header_pass_rec, sizeof(HEADER), 1, pfd);

	// Calculate the position of the record to be deleted
	long position = (pid - START) * sizeof(PASSENGER) + sizeof(HEADER);

	// Go to the position of the record in the file
	fseek(pfd, position, SEEK_SET);

	// Read the existing record
	fread(&temp_passenger, sizeof(PASSENGER), 1, pfd);

	// Check if the record exists
	if (temp_passenger.pid != pid) {
		printf("\nError: Record with passenger ID %ld not found.\n", pid);
		fclose(pfd);
		return -1;
	}

	//check if the record is already deleted
	if (temp_passenger.status == DELETED) {
		printf("\nError: Record with passenger ID %ld has already been deleted.\n", pid);
		fclose(pfd);
		return -1;
	}

	// Update the status to DELETED
	temp_passenger.status = DELETED;

	// Write the updated record back to the file
	fseek(pfd, position, SEEK_SET);
	fwrite(&temp_passenger, sizeof(PASSENGER), 1, pfd);

	fclose(pfd);

	printf("\nSuccessfully deleted passenger with ID %ld.\n", pid);
	return 0;
}