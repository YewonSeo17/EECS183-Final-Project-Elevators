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
    elevatorId = commandString[1];

    if (commandString[2] == 'f') {
        targetFloor = commandString[3];
    }
    else if (commandString[2] == 'p') {
        isPickup = true;
    }
    else if (commandString == "") {
        isPass = true;
    }
    else if (commandString == "S") {
        isSave = true;
    }
    else if (commandString == "Q") {
        isQuit = true;
    }
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
        peopleToPickup[i] = pickupList[i];
        ++numPeopleToPickup;
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(i).getAngerLevel();
        target = pickupFloor.getPersonByIndex(i).getTargetFloor();
        
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
