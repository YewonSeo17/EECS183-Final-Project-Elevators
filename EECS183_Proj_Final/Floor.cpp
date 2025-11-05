/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Yewon Seo, Lena Sytsma-Reed, Ella Nestingen, and Carter Wolter#>
 * <#yewonseo, sytlena, enesting, cdwolt#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
	// Initializing variable and array
	int countExploded = 0;
	int arrayRemove[MAX_PEOPLE_PER_FLOOR];

	// Goes through all people on the floor
	for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; ++i) {
		// Checks if they have exploded and adds them to the array
		// of exploded people if they have
		if (people[i].tick(currentTime)) {
			arrayRemove[countExploded] = i;
			countExploded++;
		}
		// Calling the remove function with out indeces of removed people
		removePeople(arrayRemove, countExploded);
		
		
	}
    return 0;
}

void Floor::addPerson(Person newPerson, int request) {
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		++numPeople;
		if (request > 0) {
			hasUpRequest = true;
			return;
		}
		hasDownRequest = true;
	}
	return;
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
	
	// create a temporary array to store remaining elements
	Person newArr[MAX_PEOPLE_PER_FLOOR];

	// arrPos tracks index of newArr
	int arrPos = 0;
	int i;

	// i goes through from first to the last index
	for (i = 0; i < MAX_PEOPLE_PER_FLOOR; ++i) {

		// if statement executes when i is not the index to remove
		if (i != indicesToRemove[numPeopleToRemove]) {

			// for indices to not remove, they are stored into newArr 
			// in a squished form
			newArr[arrPos] = people[i];
		}
	}

	// after removing, replace people with newArr
	// for loop is separated from the one above to avoid possible bugs
	for (i = 0; i < MAX_PEOPLE_PER_FLOOR; ++i) {
		people[i] = newArr[i];
	}
	resetRequests();
}

void Floor::resetRequests() {
	for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; ++i) {
		if (people[i].getTargetFloor() == people[i].getCurrentFloor()) {
			return;
		}
		else if (people[i].getTargetFloor() > people[i].getCurrentFloor()) {
			hasUpRequest = true;
		}
		else {
			hasDownRequest = true;
		}
	}
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
