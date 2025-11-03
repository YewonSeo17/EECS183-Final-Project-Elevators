/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
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

void test_Person();

void start_tests() {
    test_Person();
    
    return;
}

void test_Person() {
    Person p1("0f1t9a1");
    cout << p1.getTurn() << " " << p1.getCurrentFloor() << " " << p1.getTargetFloor() << " " << p1.getAngerLevel() << endl;
    Person p2("77f1t9a1");
    cout << p2.getTurn() << " " << p2.getCurrentFloor() << " " << p2.getTargetFloor() << " " << p2.getAngerLevel() << endl;

}
