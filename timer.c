#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>  
#include <limits.h> 
#include <stdlib.h> 
#include <unistd.h>

//----Function verifies whether input set in CLI is valid for processing----//
int verify_input(char* argument){
	char* p;
	errno = 0;
	long arg = strtol(argument, &p, 10);

	if(*p != '\0' || errno != 0){
		printf("ERROR: Input must be an integer\n");
		return 1;
	}

	else if(arg < 0 || arg > INT_MAX){
		printf("ERROR: Input is out of range. Please input an acceptable number (1-2147483647)\n");
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char* argv[]){
	if(strlen(argv[1]) == 0){
		printf ("ERROR: Must input argument\n");
		return 1;
	}
	/* for (i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			switch (argv[i][1]){
				case 'w':
					printf("Work interval was specified\n");
					if(strlen(argv[i++]) != 0){
						if(verify_input(argv[i++]) == 0){
							char* p;
							long arg = strtol(argv[i++], &p, 10);
							int work_interval = arg;
						}
						else{
							break;
						}
					}
					else{
						break;
					}
			}
		}
	}*/
//FUCKED
//
//

	if(verify_input(argv[1]) == 1){
		return 1;
	}	

	char* p;
	errno = 0;
	long arg = strtol(argv[1], &p, 10);
	int timer_minutes = arg;

	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime( &rawtime );

	int start_hour = timeinfo->tm_hour;
	int start_minute = timeinfo->tm_min;
	int start_second = timeinfo->tm_sec;

	char start_time[20];
	sprintf(start_time, "%02d:%02d:%02d", start_hour, start_minute, start_second);

	int target_minute = start_minute + timer_minutes;
	int target_hour = start_hour + (target_minute/60);
	if(target_minute >= 60){
		target_minute = target_minute % 60;
	}
	if(target_hour >= 24){
		target_hour = target_hour % 24;
	}

	int target_second = start_second;
	char end_time[20];
	sprintf(end_time, "%02d:%02d:%02d", target_hour, target_minute, target_second);
	printf("Timer will end @ %s\n", end_time);

	int terminate = 0;
	while(terminate == 0){
		time_t rawchecktime;
		struct tm * checktimeinfo;
		time( &rawchecktime );
		checktimeinfo = localtime( &rawchecktime );
		
		char check_time[20];
		sprintf(check_time, "%02d:%02d:%02d",checktimeinfo->tm_hour,checktimeinfo->tm_min,checktimeinfo->tm_sec);
		sleep(1);
		//printf("%s\n",check_time);
		int result = strcmp(check_time, end_time);
		if(result==0){
			printf("Time is up!\n");
			terminate = 1;
		}
		else{
			terminate = 0;
		}
	}
	return 0;
}
