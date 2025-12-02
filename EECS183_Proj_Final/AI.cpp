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

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {

    // first round
    //if (buildingState.turn == 0) {
    //    return "e0f1";
   // }

    // Winning Stategy 1: go to the floor that has people with highest anger levels.
    int sumAnger;
    double avgAnger = 0;
    int greatestAvgAnger = 0;
    int targetFloor = 0;
    string move = "e";
    int elevId = 0;
    int elevIdFinal = 0;
    int distance = 0;
    int shortestD = NUM_FLOORS;

    // if all elevators are servicing, we should pass the round
    if (buildingState.elevators[0].isServicing 
        && buildingState.elevators[1].isServicing && buildingState.elevators[2].isServicing) {
        return "";
    }

    // if at least one elevator is not servicing
    for (int j = 0; j < NUM_FLOORS; ++j) {

        // initialize sum everytime the loop iterates
        sumAnger = 0;
        for (int i = 0; i < buildingState.floors[j].numPeople; ++i) {
            sumAnger += buildingState.floors[j].people[i].angerLevel;
        }

        // get average anger level of each floor
        avgAnger = sumAnger / (buildingState.floors[j].numPeople * 1.0);

        cout << "Sum: " << sumAnger << endl
            << "Avg: " << avgAnger << endl;

        if (avgAnger > greatestAvgAnger/* && (MAX_ANGER - avgAnger) > shortestD*/) {
            greatestAvgAnger = avgAnger;
            targetFloor = buildingState.floors[j].floorNum;
        }
    }

    // get the closest elevator
    for (int k = 0; k < NUM_ELEVATORS; ++k) {

        // only if the elevator is available
        if (!buildingState.elevators[k].isServicing) {

            elevId = buildingState.elevators[k].elevatorId;
            distance = abs(buildingState.floors[targetFloor].floorNum
                - buildingState.elevators[k].currentFloor);

            if (shortestD > distance) {
                shortestD = distance;
                elevIdFinal = elevId;
            }
        }
    }

    // append the elevator ID
    move.append(to_string(elevIdFinal));

    // pick up when targetFloor == currentFloor of the elevator
    if (targetFloor == buildingState.elevators[elevIdFinal].currentFloor) {
        if (buildingState.floors[targetFloor].numPeople == 0) {
            return "";
        }
        move.append("p");
        return move;
    }

    // if not picking up, perform service move
    move.append("f");
    move.append(to_string(targetFloor));
    return move;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {

    bool hasUpRequest = floorToPickup.getHasUpRequest();
    bool hasDownRequest = floorToPickup.getHasDownRequest();
    string pickupList = "";
    int elevatorID = move.getElevatorId();
    int currentFloor = buildingState.elevators[elevatorID].currentFloor;
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

    // if a floor has people with highest anger level up/down
    for (int j = 0; j < floorToPickup.getNumPeople(); ++j) {

        // if a person wants to go up or down
        if (currentFloor < floorToPickup.getPersonByIndex(j).getTargetFloor()) {
            upAnger += floorToPickup.getPersonByIndex(j).getAngerLevel();
            up.append(to_string(j));
        }
        else {
            downAnger += floorToPickup.getPersonByIndex(j).getAngerLevel();
            down.append(to_string(j));
        }
    }

    // compute the average
    upAvgAnger = upAnger * 1.0 / up.length();
    downAvgAnger = downAnger * 1.0 / down.length();

    // pick up whoever with larger average anger level
    if (upAvgAnger > downAvgAnger) {
        return up;
    }
    else if (upAvgAnger < downAvgAnger) {
        return down;
    }
    else if (up.length() >= down.length()) {

        // if the average is the same, compare the number of people 
        return up;
    }
    return down;
}
