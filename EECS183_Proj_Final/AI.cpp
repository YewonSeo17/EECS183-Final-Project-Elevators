/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Yewon Seo, Lena Sytsma-Reed, Ella Nestingen, and Carter Wolter#>
 * <#yewonseo, sytlena, enesting, cdwolt#>
 *
 * Final Project - Elevators
 */
#include "AI.h"
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

// this checks if the first parameter is in the given array
bool isInArray(int value, int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

// this gets the summation of anger levels of all individuals on the given floor
int newSumAnger(const BuildingState& buildingState, int floorNum, int elevId) {
    int sumAnger = 0;
    int explodeDist = abs(buildingState.elevators[elevId].currentFloor - floorNum);
    int trialExplode = 0;

    for (int i = 0; i < buildingState.floors[floorNum].numPeople; ++i) {
        trialExplode = buildingState.floors[floorNum].people[i].angerLevel + explodeDist;

        // do not consider individuals who will explode no matter what we do
        if (trialExplode < 10) {
            sumAnger += buildingState.floors[floorNum].people[i].angerLevel;
        }
    }

    return sumAnger;
}

// this gets the closest elevator to the target floor
int getClosestElevator(const BuildingState& buildingState, int target) {
    int elevId = -1;
    int distance = -1;
    int elevIdFinal = -1;
    int shortestD = NUM_FLOORS;

    for (int k = 0; k < NUM_ELEVATORS; ++k) {

        // only if the elevator is available
        if (!buildingState.elevators[k].isServicing) {
            elevId = buildingState.elevators[k].elevatorId;
            distance = abs(target - buildingState.elevators[k].currentFloor);

            if (shortestD > distance) {
                shortestD = distance;
                elevIdFinal = elevId;
            }
        }
    }

    return elevIdFinal;
}

// loops through floors and determines floor with highest anger level that is not already being serviced
int getNextBestFloor(const BuildingState& buildingState, int targetFloors[]) {
    int sumAnger = 0;
    int greatestSumAnger = 0;
    int moveTargetFloor = 0;
    int closestElevator = 0;

    for (int j = 0; j < NUM_FLOORS; ++j) {
        sumAnger = 0;

        if (!isInArray(buildingState.floors[j].floorNum, targetFloors, NUM_ELEVATORS)) {
            closestElevator = getClosestElevator(buildingState, j);
            sumAnger = newSumAnger(buildingState, j, closestElevator);

            // use the sum of anger levels instead of average
            if (sumAnger > greatestSumAnger) {
                greatestSumAnger = sumAnger;
                moveTargetFloor = buildingState.floors[j].floorNum;
            }
        }
    }

    return moveTargetFloor;
}

string getAIMoveString(const BuildingState& buildingState) {

    // Winning Stategy: go to the floor that has people with highest anger levels
    int sumAnger;
    double avgAnger = 0;
    int greatestAvgAnger = 0;
    string move = "e";
    int elevIdFinal = 0;
    int bestTargetFloor = -1;

    // if all elevators are servicing, we should pass the round
    if (buildingState.elevators[0].isServicing
        && buildingState.elevators[1].isServicing && buildingState.elevators[2].isServicing) {
        return "";
    }

    // create array of current target floors and use that array to find next best floor
    int currentTargets[NUM_ELEVATORS] = { -1, -1, -1 };

    for (int k = 0; k < NUM_ELEVATORS; ++k) {
        if (buildingState.elevators[k].isServicing) {
            currentTargets[k] = buildingState.elevators[k].targetFloor;
        }
    }

    cout << "{ " << currentTargets[0] << ", " << currentTargets[1] << ", "
        << currentTargets[2] << " }" << endl;

    bestTargetFloor = getNextBestFloor(buildingState, currentTargets);
    elevIdFinal = getClosestElevator(buildingState, bestTargetFloor);

    // append the elevator ID
    move.append(to_string(elevIdFinal));

    // pick up when targetFloor == currentFloor of the elevator
    if (bestTargetFloor == buildingState.elevators[elevIdFinal].currentFloor) {
        if (buildingState.floors[bestTargetFloor].numPeople == 0) {
            return "";
        }
        move.append("p");
        return move;
    }

    // if not picking up, perform service move
    move.append("f");
    move.append(to_string(bestTargetFloor));
    return move;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
    const Floor& floorToPickup) {
    bool hasUpRequest = floorToPickup.getHasUpRequest();
    bool hasDownRequest = floorToPickup.getHasDownRequest();
    string pickupList = "";
    int elevatorID = move.getElevatorId();
    int currentFloor = buildingState.elevators[elevatorID].currentFloor;
    int upRequests = 0;
    int downRequests = 0;
    int upAnger = 0;
    int downAnger = 0;
    double upAvgAnger = 0;
    double downAvgAnger = 0;
    string up = "";
    string down = "";

    // if a floor only has people with up requests or down requests
    if ((hasUpRequest && !hasDownRequest) || (!hasUpRequest && hasDownRequest)) {
        for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
            pickupList.append(to_string(i));
        }
        return pickupList;
    }

    // if a floor has more people going up or down
    for (int j = 0; j < floorToPickup.getNumPeople(); ++j) {
        // if a person wants to go up or down
        if (currentFloor < floorToPickup.getPersonByIndex(j).getTargetFloor()) {
            upAnger += floorToPickup.getPersonByIndex(j).getAngerLevel();
            up.append(to_string(j));
            upRequests++;
        }
        else {
            downAnger += floorToPickup.getPersonByIndex(j).getAngerLevel();
            down.append(to_string(j));
            downRequests++;
        }
    }

    // compute the average
    upAvgAnger = upAnger * 1.0 / up.length();
    downAvgAnger = downAnger * 1.0 / down.length();

    // pick up all people in the greater requested direction
    if (upRequests > downRequests) {
        return up;
    }
    else if (upRequests < downRequests) {
        return down;
    }
    else if (upRequests == downRequests) {

        // if there are equal number of people on both sides,
        // compare the average anger level
        if (upAvgAnger > downAvgAnger) {
            return up;
        }
        else {
            return down;
        }
    }
    return down;
}