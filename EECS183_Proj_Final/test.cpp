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
void test_Floor();
void test_Elevator();

void start_tests() {
    test_Person();
    test_Elevator();
    test_Floor();
    
    return;
}

void test_Person() {
    cout << "Testing Person" << endl;
   
    Person p1("0f1t9a1");
    cout << p1.getTurn() << " " << p1.getCurrentFloor() << " " << p1.getTargetFloor() << " " << p1.getAngerLevel() << endl;
    Person p2("77f1t9a1");
    cout << p2.getTurn() << " " << p2.getCurrentFloor() << " " << p2.getTargetFloor() << " " << p2.getAngerLevel() << endl;

}
void test_Elevator() {
    cout << "Now Testing Elevator" << endl;
    cout << "Testing serviceRequest()" << endl;
    Elevator M1;
    M1.serviceRequest(5);
    
    cout << "M1.serviceRequest() " << "Expected 5; Actual: " << M1.getTargetFloor() << endl;
    cout << "M1.serviceRequest() " << "Expected 1; Actual: " << M1.isServicing() << endl;

    cout << "Testing tick()" << endl;

    M1.tick(3);

    cout << "M1.tick(3) " << "Expected 1; Actual: " << M1.getCurrentFloor() << endl;
    cout << "M1.tick(3) " << "Expected 1; Actual: " << M1.isServicing() << endl;

    M1.tick(3);
    M1.tick(3);
    M1.tick(3);
    M1.tick(3);

    cout << "M1.tick(3) " << "Expected 5; Actual: " << M1.getCurrentFloor() << endl;
    cout << "M1.tick(3) " << "Expected 0; Actual: " << M1.isServicing() << endl;
   


    return;
}
void test_Floor() {
    cout << "Testing Floor" << endl;
    Person p1("0f1t9a1");
    Floor f1;
    f1.addPerson(p1, 3);
    cout << f1.getHasUpRequest() << " " << f1.getHasDownRequest() << endl;
}