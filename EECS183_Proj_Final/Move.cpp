/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Yewon Seo, Lena Sytsma-Reed, Ella Nestingen, and Carter Wolter#>
 * <#yewonseo, sytlena, enesting, cdwolt#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {

    // for pass, save, quit
    if (commandString == "") {
        isPass = true;
        return;
    }
    if (commandString == "S" || commandString == "s") {
        isSave = true;
        return;
    }
    if (commandString == "Q" || commandString == "q") {
        isQuit = true;
        return;
    }

    // if commandString starts with 'e'\
    // must convert char to int
    elevatorId = commandString[1] - '0';

    char action = commandString[2];
    if (action == 'p' || action == 'P') {
        isPickup = true;
        return;
    }
    else if (action == 'f' || action == 'F') {
        targetFloor = commandString[3] - '0';
        return;
    }

    return;
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isQuit || isSave) {
        return true;
    }
    if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing()) {

        // for pickup move
        if (isPickup) {
            return true;
        }

        // for servicing move
        if (targetFloor >= 0 && targetFloor < NUM_FLOORS 
            && targetFloor != elevators[elevatorId].getCurrentFloor()) {
            return true;
        }
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, 
                             const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int distance = 0;
    int target = 0;

    for (int i = 0; i < pickupList.length(); ++i) {

        // pickupList is a string and peopleToPickup is an int arr
        int personIndex = pickupList[i] - '0';
        peopleToPickup[i] = personIndex;
        ++numPeopleToPickup;
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(personIndex).getAngerLevel();
        target = pickupFloor.getPersonByIndex(personIndex).getTargetFloor();
        
        // set targetFloor to the target floor of person who should travel furtherest
        if (distance < abs(target - currentFloor)) {
            distance = abs(target - currentFloor);
            targetFloor = target;
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
