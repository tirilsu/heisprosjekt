void state_set_current_floor(int floor);

//Returns which floor the elevator is in (0-3)
int state_get_current_floor();

void state_set_direction(int dir);

//returns 1 if direction up and -1 if direction down
int state_get_direction();


void state_set_door_open(int door);

// returns 1 if door is open and 0 if closed
int state_get_door_open();

void state_set_stop_button_between_floors(int stop);

//returns 1 if stop button is pressed between two floors
int state_get_stop_button_between_floors();