#include "states.h"
#include "elev.h"

static int door_open;
static int current_floor;
static int direction;
static int stop_between_floors;


void state_set_current_floor(int floor){
    current_floor = floor;
}

int state_get_current_floor(){
    return current_floor;
}

void state_set_direction(int dir){
	if(elev_get_floor_sensor_signal() != -1){
    	direction = dir;
    }
  
}

int state_get_direction(){
    return direction;
}


void state_set_door_open(int door){
    door_open = door;
}
int state_get_door_open(){
    return door_open;
}

void state_set_stop_button_between_floors(int stop){
	stop_between_floors = stop;
}

int state_get_stop_button_between_floors(){
	return stop_between_floors;
}
