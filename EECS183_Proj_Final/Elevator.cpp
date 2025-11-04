/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Yewon Seo, Lena Sytsma-Reed, Ella Nestingen, and Carter Wolter#>
 * <#yewonseo, sytlena, enesting, cdwolt#>
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;

void Elevator::tick(int currentTime) {
    // Checking if currentTime is divisible by TICKS_PER_ELEVATOR_MOVE
    // and that the elevator is servicing
    if (currentTime % TICKS_PER_ELEVATOR_MOVE == 0 && servicing) {
        // If the elevator is higher than its target floor,
        // it will move down a floor
        if (currentFloor > targetFloor) {
            currentFloor--;
            return;
        }
        // If it's below the target floor, than it will move up a floor
        else currentFloor++;
    }
    // If the elevator is already at its target floor, it will stop servicing 
    if (currentFloor == targetFloor) {
        servicing = false;
    }
    return;
}

void Elevator::serviceRequest(int floorNum) {
    // Set target floor of the elevator to the service request inputed
    targetFloor = floorNum;
    // Elevator will now be in service
    servicing = true;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
