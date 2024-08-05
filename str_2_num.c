#include"Passenger.h"

int str_2_num(char* string) {
	
	long num = 0;

	for (int i = 0; string[i] != '\0'; ++i) {

		if (string[i] >= '0' && string[i] <= '9') {
			num = num * 10 + string[i] - '0';
		}
		
	}

	return num;
}