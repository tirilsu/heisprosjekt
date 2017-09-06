//
//  Queue.c
//  heis
//
//  Created by Lina Theimann on 21.02.17.
//  Copyright © 2017 Lina Theimann. All rights reserved.
//

#include "queue.h"


static int queue_matrix[N_BUTTON][N_FLOOR]= {
    
    {0,0,0,0},  //order up
    {0,0,0,0},  //order down
    {0,0,0,0},   //command
};

void queue_clear(){
    for (int i=0; i<N_BUTTON; i++){
        for(int j=0; j<N_FLOOR; j++){
            if (queue_matrix[i][j] != -1){
                queue_matrix[i][j] = 0;
            }
        } 
    }
}


void queue_delete(int current_floor){
    queue_matrix[0][current_floor] = 0;
    queue_matrix[1][current_floor] = 0;
    queue_matrix[2][current_floor] = 0;
    }


void queue_update(int button, int floor){
    queue_matrix[button][floor] = 1;
}



int queue_get_current_order(int current_floor, int direction){
    

    //if previous direction is up
    if (direction == 1){ 

        //checks if floors above has orders up or command
        for (int i = current_floor; i < N_FLOOR; i++){
            if( queue_matrix[0][i] == 1 || queue_matrix[2][i] == 1 ){

                return i;
            }
        }

        //checks if floors above has order down
        for (int j = (N_FLOOR-1); j>=current_floor; j--){ 
            if(queue_matrix[1][j] == 1 ){
                return j;
            }
        }

        //checks if floors beneath has order down or command
        for (int i = current_floor; i >= 0; i--){
            if(queue_matrix[1][i] == 1 || queue_matrix[2][i] == 1){
                return i;
            }
        }

        //checks if floors beneath has order up
        for (int j = 0; j <= current_floor; j++){
            if( queue_matrix[0][j] == 1 ){
                return j;
            }
        }

    }    
    

    //if previous directin is down
    else if (direction == -1 ){


        //checks if floors beneath has order down or command
        for (int i = current_floor; i >= 0; i--){
            if(queue_matrix[1][i] == 1 || queue_matrix[2][i] == 1){
                return i;
            }
        }

        
        //checks if floors beneath has order up
         for (int j = 0; j <= current_floor; j++){
            if( queue_matrix[0][j] == 1 ){
                return j;
            }
        }

        //checks if floors above has order up or command
         for (int i = current_floor; i < N_FLOOR; i++){
            if( queue_matrix[0][i] == 1 || queue_matrix[2][i] == 1 ){

                return i;
            }
        }

        //checks if floors above has order down
        for (int j = (N_FLOOR-1); j>=current_floor; j--){ 
            if(queue_matrix[1][j] == 1 ){
                return j;
            }
        }

    }
    
    //if no order
    return -1;    
}