#include "elev.h"
#include <stdio.h>
#include "queue.h"
#include "timer.h"
#include "states.h"

//Initializes elevator. Goes up if it starts between floors.
void init_state(void){

	while(elev_get_floor_sensor_signal() == (-1)){
		elev_set_motor_direction(DIRN_UP);
		state_set_direction(1);
	}
	

	elev_set_motor_direction(DIRN_STOP);

	state_set_current_floor(elev_get_floor_sensor_signal());
	state_set_door_open(0);
	state_set_direction(1);

}

//Opens door and sets timestamp
void open_door(void){
	elev_set_door_open_lamp(1);
	state_set_door_open(1);	
	timer_set(3);
}

//Used if stop-button is pressed. Clears  queue. Initializes hardware. If in floor: open door. If between floors: sets stop-between-floor-variable == 1.
void handle_stop(void){
	while (elev_get_stop_signal()){
		elev_set_motor_direction(DIRN_STOP);
		
		elev_set_stop_lamp(1);
		if(elev_get_floor_sensor_signal() != -1){
			elev_set_door_open_lamp(1);
			state_set_door_open(1);
		}
	}
	elev_set_stop_lamp(0);
	queue_clear();
	elev_init();
	elev_set_floor_indicator(state_get_current_floor());
	if(elev_get_floor_sensor_signal() != -1){
		open_door();
	}
	else{
		state_set_stop_button_between_floors(1);
	}

}



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }


    init_state();

    
    while(1){

		while (elev_get_stop_signal()){
		 	handle_stop();
		}

		//Runs while stop-button is not pressed 


		//Sets variable current_floor (0-3)
		int temp = elev_get_floor_sensor_signal();
		if(temp != -1){
			state_set_current_floor(temp); 
			elev_set_floor_indicator(state_get_current_floor());
		}
		

		//Polling order-buttons. If button pressed: turn on light and update queue.
		for(int i = 0; i<4; i++){ //Iterating through floors
			if (i !=3 && elev_get_button_signal(BUTTON_CALL_UP,i)==1){ //Checks if button up is pressed in floors 0-2
			    elev_set_button_lamp(BUTTON_CALL_UP,i,1);
			    queue_update(0,i);
			}
			if (i !=0 && elev_get_button_signal(BUTTON_CALL_DOWN,i)==1){ //Checks if button down is pressed in floors 1-3
			    elev_set_button_lamp(BUTTON_CALL_DOWN,i,1);
			    queue_update(1,i);
			}

			if (elev_get_button_signal(BUTTON_COMMAND,i)==1){ //Checks if button command is pressed in floors 0-3
			    elev_set_button_lamp(BUTTON_COMMAND,i,1);
			    queue_update(2,i);
			}
		} 

		//Checks if door is open in floor. If 3 seconds has passed: close door.
		if(state_get_door_open() == 1 && (elev_get_stop_signal() == 0)){

			if (timer_check()){
				elev_set_door_open_lamp(0);
				state_set_door_open(0);

			}
	
		}
			
		//Fetches next floor from queue-matrix.
		int wanted_floor = queue_get_current_order(state_get_current_floor(), state_get_direction());

		//Runs if floor is ordered and door is closed.
		if((wanted_floor != -1) && (state_get_door_open() == 0)){
			
			//If wanted floor is above elevator: drive up.
			if((wanted_floor - state_get_current_floor()) > 0 ){
			    elev_set_motor_direction(DIRN_UP);
			    state_set_direction(1);
			    state_set_stop_button_between_floors(0); //Stop-between-floor-variable == 0 if stop-button has been pressed between floors and new order is received 
			}
			  
			//If wanted floor is beneath elevator: drive down.  
			else if((wanted_floor - state_get_current_floor()) < 0){
			    elev_set_motor_direction(DIRN_DOWN);
			    state_set_direction(-1);
			    state_set_stop_button_between_floors(0);
			}
			
			//If wanted floor is reached: stop elevator, open door, delete floor from queue and turn of order-light
			else if(wanted_floor == state_get_current_floor() ){

			    if(elev_get_floor_sensor_signal() != -1){
				    elev_set_motor_direction(DIRN_STOP);
					open_door();
					queue_delete(elev_get_floor_sensor_signal());
					elev_turn_off_button_order(elev_get_floor_sensor_signal());
					state_set_stop_button_between_floors(0);
				}

				//Only occurs if stop-button is pressed between floors. If elevator is in wanted floor: switch direction.
				else if ((elev_get_floor_sensor_signal() == -1)&& (state_get_stop_button_between_floors() == 1)){

					if(state_get_direction() == 1){
						elev_set_motor_direction(DIRN_DOWN);
							
					}
					else{
						elev_set_motor_direction(DIRN_UP);
							
					}

					state_set_stop_button_between_floors(0);
					

				}
			}	

		}
		
    }

    
    return 0;
}
