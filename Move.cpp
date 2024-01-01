/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

const int checkTargetorPickUp = 2;

Move::Move(string commandString) : Move() {
    string data = commandString;
        stringstream s(data);
        
        if (commandString == "") {
            isPass = true;
        }
        else if (commandString == "S") {
            isSave = true;
        }
        else if (commandString == "Q") {
            isQuit = true;
        }
        else {
            if (commandString.at(checkTargetorPickUp) == 'f') {
                //junk to read and discard the letters
                char junk;
                
                s >> junk >> elevatorId >> junk >> targetFloor;
            }
            else if (commandString.at(checkTargetorPickUp) == 'p') {
                //junk to read and discard the letters
                char junk;
                
                s >> junk >> elevatorId >> junk;
                isPickup = true;
            }
        }
    }

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    Elevator e;
        
        if (isPass == true || isQuit == true || isSave == true) {
            return true;
        }
        else if (isPickup == true) {
            if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS
                && !(elevators[elevatorId].isServicing())) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (isPass == false && isQuit == false && isSave == false && isPickup == false) {
            if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS
                && targetFloor >= 0 && targetFloor < NUM_FLOORS
                && targetFloor != elevators[elevatorId].getCurrentFloor()
                && !(elevators[elevatorId].isServicing())) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
        totalSatisfaction = 0;
        
        // Creating array to store target floors
        int allTargetFloors[pickupList.length()];

        for (int i = 0; i < pickupList.length(); i++) {
            // Converting indice to an int
            char indiceChar = pickupList.at(i);
            int indice = indiceChar - '0';
            
            peopleToPickup[i] = indice;
            
            numPeopleToPickup++;
            
            // Determining anger level and updating satisfaction
            totalSatisfaction += (MAX_ANGER - (pickupFloor.getPersonByIndex(indice)).getAngerLevel());
            
            // Adding target floor to array of all target floors
            allTargetFloors[i] = (pickupFloor.getPersonByIndex(indice)).getTargetFloor();
        }
        
        // Determining final target floor
        targetFloor = allTargetFloors[0];
        
        for (int i = 1; i < pickupList.length(); i++) {
            int newTargetFloor = allTargetFloors[i];
            
            // If newTargetFloor more distant than targetFloor, update
            if (abs((newTargetFloor - currentFloor)) > abs((targetFloor - currentFloor))) {
                targetFloor = newTargetFloor;
            }
        }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
