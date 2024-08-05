#pragma

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<io.h>

#define LENGTH 256
#define START 1000
#define service_file_start 1

enum REC_STATUS { DELETED, ACTIVE };

typedef struct taxi{
	long battery_soc;
	long battery_capacity;
	long charge_rate;
	long taxi_state;
	long building_parked;
	long corner_parked;
	long distance;
	enum REC_STATUS status;

	/*vin = taxi id (similar to passenger id) */
	long vin;
}TAXI;


struct header {

	long first_vin;
};
typedef struct header TAXI_HEADER;


typedef struct service {

	long record_count; // used to keep track of number of record, starting from 1

	long vin;
	long day;
	long month;
	long year;
	char comment[LENGTH];

}SERVICE;

struct service_header {
	long first_avail_rec_count;
};
typedef struct service_header SERVICE_HEADER;

#define TRUNCATE(name)		name[strlen(name)-1] = '\0'

extern int init_taxi();
extern int str_2_num(char* string);
extern int view_taxi_record();
extern int delete_taxi();
extern int add_new_taxi();
extern int init_service_file();
extern int service_taxi();
//extern int view_service_history();

