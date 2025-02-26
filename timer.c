#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>  
#include <limits.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]){
	//----Verifying Input----//
	if (strlen(argv[1]) == 0){
		printf ("ERROR: Must input time interval\n");
		return 1;
	}

	char* p;
	errno = 0;
	long arg = strtol(argv[1], &p, 10);

	if (*p != '\0' || errno != 0){
		printf("ERROR: Input must be an integer\n");
		return 1;
	}

	if (arg < INT_MIN || arg > INT_MAX){
		printf("ERROR: Input out of range\n");
		return 1;
	}
	int timer_minutes = arg;
	//--------//

	printf("Your timer will be %d minutes long\n", timer_minutes);

	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime( &rawtime );

	int start_hour = timeinfo->tm_hour;
	int start_minute = timeinfo->tm_min;
	int start_second = timeinfo->tm_sec;
	
	char start_time[20];
	sprintf(start_time, "%02d:%02d:%02d", start_hour, start_minute, start_second);
	
	printf("%s\n", start_time);
	
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
	sprintf(end_time, "%02d:%02d:%02d",target_hour, target_minute, target_second);
	printf("Timer will end at: %s\n", end_time);
	
	int terminate = 0;
	while(terminate == 0){
		time_t rawchecktime;
		struct tm * checktimeinfo;
		time( &rawchecktime );
		checktimeinfo = localtime( &rawchecktime );
		
		char check_time[20];
		sprintf(check_time, "%02d:%02d:%02d",checktimeinfo->tm_hour,checktimeinfo->tm_min,checktimeinfo->tm_sec);
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
