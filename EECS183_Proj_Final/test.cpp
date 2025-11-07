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
void test_Move();

void start_tests() {
    cout << "\nTesting Start!\n";
    test_Person();
    test_Elevator();
    test_Floor();
    test_Move();
    
    return;
}

void test_Person() {
    cout << "\nTesting Person" << endl;
   
    Person p1("0f1t9a1");
    cout << p1.getTurn() << " " << p1.getCurrentFloor() << " " << p1.getTargetFloor() << " " << p1.getAngerLevel() << endl;
    Person p2("77f1t9a1");
    cout << p2.getTurn() << " " << p2.getCurrentFloor() << " " << p2.getTargetFloor() << " " << p2.getAngerLevel() << endl;

}
void test_Elevator() {
    cout << "\nNow Testing Elevator" << endl;
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
    cout << "\nTesting Floor\n";
    cout << "Testing addPerson()\n";
    Person p1("0f1t9a1");
    Floor f1;
    f1.addPerson(p1, 3);
    cout << f1.getHasUpRequest() << " " << f1.getHasDownRequest() << endl;

    cout << "Testing removePeople() and resetRequest()" << endl;
    
    f1.addPerson(Person("2f3t5a2"), 2);
    f1.addPerson(Person("5f3t2a4"), -1);
    f1.addPerson(Person("8f8t4a3"), -4);
    
    cout << "Expected f1t9a1; Actual: ";
    f1.getPersonByIndex(0).print(cout);
    
    cout << "\nExpected f3t5a2; Actual: ";
    f1.getPersonByIndex(1).print(cout);
    
    int indice_to_remove1[1] = { 0 };
    f1.removePeople(indice_to_remove1, 1);
    
    cout << "\nExpected f3t5a2; Actual: ";
    f1.getPersonByIndex(0).print(cout);

    cout << "\nExpected f3t2a4; Actual: ";
    f1.getPersonByIndex(1).print(cout);

    cout << "\nExpected 3; Actual: " << f1.getNumPeople() << endl;

    int indice_to_remove2[2] = { 0, 2 };
    f1.removePeople(indice_to_remove2, 2);

    cout << "\nExpected f8t4a3; Actual: ";
    f1.getPersonByIndex(0).print(cout);

    cout << "\n\nExpected 1; Actual: " << f1.getNumPeople() << endl;

    cout << "Testing tick()\n";

    f1.tick(3);
    f1.tick(5);
    int i = 0;
    cout << "\nExpected 1; Actual: " << f1.getNumPeople() << endl;
    f1.tick(10);
    cout << "\nExpected 1; Actual: " << f1.getNumPeople() << endl;
    while (i < 5) {
        f1.tick(15);
        i++;
    }

    cout << "\nExpected 0; Actual: " << f1.getNumPeople() << endl;

    f1.addPerson(Person("2f3t5a2"), 2);
    f1.addPerson(Person("2f3t5a2"), 2);
    f1.addPerson(Person("2f3t5a2"), 2);

    return;
}

void test_Move() {
    cout << "\nTesting Move\n";
    cout << "Testing non default constructor\n";

    Move m0("e1f4");
    Move m1("e1p");
    Move m2("e5f0");
    Move m3("");
    Move m4("S");
    Move m5("Q");
    Move m6("e9f9");

    Elevator elevs[NUM_ELEVATORS];
    elevs[0].setCurrentFloor(1);
    elevs[0].serviceRequest(4);
    elevs[1].setCurrentFloor(6);
    elevs[1].serviceRequest(3);
    elevs[2].setCurrentFloor(8);
    elevs[2].serviceRequest(2);

    cout << "Expected: 1, Actual: " << m0.isValidMove(elevs);
    cout << "\nExpected: 1, Actual: " << m1.isValidMove(elevs);
    cout << "\nExpected: 0, Actual: " << m2.isValidMove(elevs);
    cout << "\nExpected: 1, Actual: " << m3.isValidMove(elevs);
    cout << "\nExpected: 1, Actual: " << m4.isValidMove(elevs);
    cout << "\nExpected: 1, Actual: " << m5.isValidMove(elevs);
    cout << "\nExpected: 0, Actual: " << m6.isValidMove(elevs);

    cout << "\nExpected: 1, Actual: " << m0.getElevatorId();
    cout << "\nExpected: -1, Actual: " << m3.getElevatorId();
    cout << "\nExpected: 9, Actual: " << m6.getElevatorId();
    return;
}