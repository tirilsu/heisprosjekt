//
//  Queue.h
//  heis
//
//  Created by Lina Theimann on 21.02.17.
//  Copyright © 2017 Lina Theimann. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>


#define N_BUTTON 3
#define N_FLOOR 4

//used if stop-button is pressed. All entries in queue-matrix == 0
void queue_clear();

//deletes orders in current floor (up/down/command)
void queue_delete(int current_floor);

//new order added to queue-matrix
void queue_update(int button, int floor);

//returns the next floor to go to. Returns -1 if no order.
int queue_get_current_order(int current_floor, int direction);



#endif /* queue_h */
