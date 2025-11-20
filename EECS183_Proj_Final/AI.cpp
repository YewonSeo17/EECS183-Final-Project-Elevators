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
using namespace std;

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    // Winning Stategy 1: go to the floor that has people with highest anger levels.
    int sumAnger;
    double avgAnger = 0;
    int greatestAvgAnger = 0;
    int targetFloor = 0;
    string move = "e";
    int elevId;
    int distance = 0;
    int shortestD = NUM_FLOORS;

    // if all elevators are servicing, we should pass the round
    if (buildingState.elevators[0].isServicing && buildingState.elevators[1].isServicing && buildingState.elevators[2].isServicing) {
        return "";
    }

    // if at least one elevator is not servicing
    for (int j = 0; j < NUM_FLOORS; ++j) {

        // initialize sum everytime the loop iterates
        sumAnger = 0;
        for (int i = 0; i < buildingState.floors->numPeople; ++i) {
            sumAnger += buildingState.floors->people[i].angerLevel;
        }

        // get average anger level of each floor
        avgAnger = sumAnger / (buildingState.floors->numPeople * 1.0);

        // get the closest elevator
        for (int k = 0; k < NUM_ELEVATORS; ++k) {

            // only if the elevator is available
            if (!buildingState.elevators[k].isServicing) {

                elevId = buildingState.elevators[k].elevatorId;
                distance = abs(buildingState.floors[j].floorNum
                    - buildingState.elevators[k].currentFloor);

                if (shortestD < distance) {
                    shortestD = distance;
                    move.append(to_string(elevId));
                }
            }
        }

        if (avgAnger > greatestAvgAnger && (MAX_ANGER - avgAnger) > shortestD) {
            greatestAvgAnger = avgAnger;
            targetFloor = buildingState.floors->floorNum;
        }

        // we should: differentiate sumAnger based on up/down requests -> impossible
        // we should: ignore ppl that will explode no matter what AI does based
        //            on the distance between the target floor & the elevator -> resolved
    }

    move.append("f");
    move.append(to_string(targetFloor));

    // we should: pickup move

    return move;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    return "";
}
