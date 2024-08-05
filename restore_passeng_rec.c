#include"Passenger.h"

int restore_deleted_passenger_rec(long pid) {
    const char* passenger_binaryfile = "passenger_binary.bin";
    FILE* pfd = fopen(passenger_binaryfile, "r+b"); // read and write in binary mode

    if (pfd == NULL) {
        printf("Failed to open the file.\n");
        return -1;
    }

    // Position to the record to restore
    fseek(pfd, ((pid - START) * sizeof(PASSENGER)) + sizeof(HEADER), SEEK_SET);

    PASSENGER temp;

    // Check if the record exists
    if (fread(&temp, sizeof(PASSENGER), 1, pfd) != 1) {
        printf("\nRecord not found.\n");
        fclose(pfd);
        return -1;
    }

    // Check if the record is already ACTIVE
    if (temp.status == ACTIVE) {
        printf("\nThe record is already ACTIVE and cannot be restored.\n");
        fclose(pfd);
        return -1;
    }

    // Restore the record
    temp.status = ACTIVE;

    // Move the file pointer back to the start of this specified record
    //fseek(pfd, -sizeof(PASSENGER), SEEK_CUR); gives error
    fseek(pfd, -(long)sizeof(PASSENGER), SEEK_CUR); //might fix the error, not tried yet
    //fseek(pfd, ((pid_to_restore - START) * sizeof(PASSENGER)) + sizeof(HEADER), SEEK_SET);


    // Write the updated record back to the file
    fwrite(&temp, sizeof(PASSENGER), 1, pfd);

    fclose(pfd);
    printf("\nSuccessfully restored the passenger record with ID -> %ld .\n", pid);
    return 0;
}