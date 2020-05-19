// Alex Santiago
//NID: al625608
//COP 3502, Summer 2018

#include <stdio.h>
#include "Elevate.h"

double AverageWaitTime(int num_floors, int left, int right);
int SmallestDelta(int pickup_floor, int left, int right);
int Delta(int PickupFloor, int ElevatorFloor);

int main(int argc, char **argv){

	int i, j;
	int x, y, LEFT, RIGHT;
	int DistOfLeft, DistOfRight;
	double LeftEl, RightEl;

	LEFT = 1;
	RIGHT = 1;

	printf("%d  %d\n", LEFT, RIGHT);


	//This "for loop" loops through the command line arguments passing them to the functions, comparing them and printing the results as it loops
	for(i = 1; i < argc; i++){
		j = 0;
		x = argv[i][j] - '0';
		y = argv[i][j+2] - '0';

		//Here I call the Delta function and store the values in my variables
		DistOfLeft = Delta(x,LEFT);
		DistOfRight = Delta(x, RIGHT);

		if(DistOfLeft < DistOfRight){
					LEFT = y;
				}else if(DistOfLeft > DistOfRight){
					RIGHT = y;
				}else if(DistOfLeft == DistOfRight){
		//Here I call the AverageWaitTime function and store the values in my variables
					RightEl = AverageWaitTime(9, y, RIGHT);
					LeftEl = AverageWaitTime(9, LEFT, y);
		//This nested if statement compares the values returned from the AverageWaitTime function
					if(LeftEl > RightEl){
						LEFT = y;
					}else{
						RIGHT = y;
					}
				}else if((DistOfLeft == DistOfRight) && (LeftEl == RightEl)){
					RIGHT = y;
				}
			printf("%d  %d\n", LEFT, RIGHT);
	}

	return 0;
}

//This Function calculates the average wait time using data returned from the Smallest Delta function and returns a double to main
double AverageWaitTime(int num_floors, int left, int right){

	int i;
	double sum;
	sum = 0.00;

	for(i = 1; i <= num_floors; i++){
		sum += SmallestDelta(i, left, right);
	}

	return (sum/num_floors);
}

//This function calculates the smallest distance between the two elevators, and the pickup floor and returns it as an integer to the AverageWaitTime function
int SmallestDelta(int pickup_floor, int left, int right){

	int sum;

	if(left == pickup_floor){
		sum = 0;
	}else if(right == pickup_floor){
		sum = 0;
	}else if((left == pickup_floor) && (right == pickup_floor)){
		sum = 0;
	}else if(left < pickup_floor && right > pickup_floor && right > left && (pickup_floor - left) < (right - pickup_floor)){
		sum = (left - pickup_floor);
	}else if(left > pickup_floor && left < right && (left - pickup_floor) < (right - pickup_floor)){
		sum = (left - pickup_floor);
	}else if(left < pickup_floor && left < right && right < pickup_floor && (pickup_floor - left) < (pickup_floor - right)){
		sum = (left - pickup_floor);
	}else if(left > pickup_floor && left > right &&  right < pickup_floor && (left - pickup_floor) < (pickup_floor - right)){
		sum = (left - pickup_floor);
	}else if(left > pickup_floor && left > right && right > pickup_floor && (left - pickup_floor) < (right - pickup_floor)){
		sum = (left - pickup_floor);
	}else if(left < pickup_floor && left > right && (pickup_floor - left) < (pickup_floor - right)){
		sum = (left - pickup_floor);
	}else{
		sum = (right - pickup_floor);
	}


	if(sum < 0){
		return -sum;
	}else{
		return sum;
	}
}

//This function calculates the distance between the elevator floor passed to it and the pickup floor
int Delta(int PickupFloor, int ElevatorFloor){

	int dist;
	dist = ElevatorFloor - PickupFloor;
	if(dist < 0)
		return -dist;
	else
		return dist;
}

double difficultyRating(void){
	return 4.00;
}

double hoursSpent(void){
	return 13.00;
}
