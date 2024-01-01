/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    
    int totalNumPeople = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        totalNumPeople += buildingState.floors[i].numPeople;
    }
        
    if (totalNumPeople == 0) {
        return "";
    }
    //AI pass ("" is returned at bottom of function)
    int count = 0;
    for (int i = 0; i < NUM_ELEVATORS; i++){
        //use ! becasue isServicing is set to false
        if (buildingState.elevators[i].isServicing){
            count++;
        }
    }
    //AI pickup or go to floor
    if (count != 3){
        for (int i = 0; i < NUM_ELEVATORS; i++){
            //When an elevator is not servicing...
            if (!buildingState.elevators[i].isServicing){
                //finds current floor of elevator
                int elevatorCurrentFloor = buildingState.elevators[i].currentFloor;
                //finds if there are people on the same floor as the elevator
                int peopleCurrentFloor = buildingState.floors[elevatorCurrentFloor].numPeople;
                //if there are people on the same floor...
                if (peopleCurrentFloor > 0){
                    string pickupMove = "e" + to_string(i) + "p";
                    return pickupMove;
                }
                //if there are not people on the same floor...
                else if (peopleCurrentFloor == 0){
                    int highestPeopleCount = 0;
                    int floorMostPeople = 0;
                    for (int j = 0; j < NUM_FLOORS; j++){
                        if (buildingState.floors[j].numPeople > highestPeopleCount){
                            highestPeopleCount = buildingState.floors[j].numPeople;
                            floorMostPeople = j;
                        }
                    }
                    string jToStr = to_string(floorMostPeople);
                    string toFloorMove = "e" + to_string(i) + "f" + jToStr;
                    return toFloorMove;
                }
            }
        }

    }
    return "";
}
string getAIPickupList(const Move& move, const BuildingState& buildingState,
                           const Floor& floorToPickup)
    {
    int countUpRequest = 0;
        int countDownRequest = 0;
        string pickupListDown = "";
        string pickupListUp;
        
        for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
            int upOrDownRequest = floorToPickup.getPersonByIndex(i).getTargetFloor() -
            floorToPickup.getPersonByIndex(i).getCurrentFloor();
            
            bool upRequest = false;
            bool downRequest = false;
            
            if (upOrDownRequest > 0) {
                upRequest = true;
                downRequest = false;
            }
            else if (upOrDownRequest < 0) {
                downRequest = true;
                upRequest = false;
                
            }
            
            if (downRequest) {
                countDownRequest++;
                pickupListDown += to_string(i);
            }
            else if (upRequest) {
                countUpRequest++;
                pickupListUp += to_string(i);
            }
        }
        
        if (countUpRequest > countDownRequest) {
            return pickupListUp;
        }
        else if (countDownRequest > countUpRequest) {
            return pickupListDown;
        }
        else {
            return pickupListUp;
        }
}

