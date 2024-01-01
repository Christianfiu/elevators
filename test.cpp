/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

// declare your test functions here
void test_person();
void test_elevator();
void file_check();
void test_floor();

void start_tests() {
    
    file_check();
    test_person();
    test_elevator();
    test_floor();
    
}

// write test functions here
void file_check() {

    // open one of the text files that are part of the starter code
    ifstream ins;
    ins.open("new.in");

    // if the file was not in the correct directory, the stream state is fail
    if (ins.fail()) {
        cout << "Could not open new.in" << endl;
    }
    else {
        cout << "Success! Text files are in the right directory." << endl;
    }

    return;
}


void test_person() {
    cout << endl;
    cout << "Testing person class" << endl;
    
    string input = "10f0t5a5";
    Person p(input);
    
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    
    cout << "Expected 10 0 5 5, actual: " << p.getTurn() << " " << p.getCurrentFloor()
    << " " << p.getTargetFloor() << " " << p.getAngerLevel() << endl;

    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE); //parameter = 5

    cout << exploded << " Expected 0" << endl;

    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;

    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1); //parameter = 4

    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;

    p.tick(TICKS_PER_ANGER_INCREASE); //7 after

    p.tick(TICKS_PER_ANGER_INCREASE); //8 after

    p.tick(TICKS_PER_ANGER_INCREASE); //9 after

    exploded = p.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded << " Expected 1" << endl;
}

void test_elevator() {
    
    cout << endl;
    cout << "testing elevator class" << endl;
    
    Elevator e;
    e.setCurrentFloor(3);
    //testing serviceRequest
    e.serviceRequest(6);
    cout << "Expected 6 1, actual: " << e.getTargetFloor() << " " << e.isServicing() << endl;
    
    //testing tick
    e.tick(TICKS_PER_ELEVATOR_MOVE);
    
}

void test_floor(){
    
    cout << endl;
    cout << "testing floor class" << endl;
    
    Person p[MAX_PEOPLE_PER_FLOOR];
    cout << p[8].getCurrentFloor() << " " << p[8].getTargetFloor() << endl;
    
    //testing removePeople
    
    

}
