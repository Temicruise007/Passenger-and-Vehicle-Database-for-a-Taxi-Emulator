#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<io.h>

#define LENGTH 256
#define START 1000

enum REC_STATUS{DELETED, ACTIVE};

/* Declaring the passenger structure */
struct passenger {

	long time_req;
	long orig_street;
	long orig_avenue;
	long orig_puc; // (puc) stands for pick up corner
	long dest_street;
	long dest_avenue;
	long dropof_corner;
	long pass_state;
	enum REC_STATUS status;
	/*pid = passenger id */
	long pid;   

};
typedef struct passenger PASSENGER;


struct header {

	long first_id;
};
typedef struct header HEADER;


#define TRUNCATE(name)		name[strlen(name)-1] = '\0'

//extern FILE* pfd;

extern int init_passenger();
extern int view_pass_record();
extern int disp_all_pass_record();
extern int add_new_passenger();
extern int str_2_num(char* string);
extern int update_pass_record();
extern int remove_passenger_rec(long);
extern int restore_deleted_passenger_rec(long);