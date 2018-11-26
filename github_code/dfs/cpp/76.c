//
//  DepthFirstSearch.cpp
//  CircleMandala
//
//  Created by Gonzalez, Mario on 9/21/14.
//
//

#include "DepthFirstSearch.h"
#include "../Action.h"
#include "../../GridDirections.h"
#include <array>
#include <iterator>
#include <chrono>       // std::chrono::system_clock
#include <random>       // std::default_random_engine

namespace search {
    DepthFirstSearch::DepthFirstSearch(){
        frontier = new Sequence();
    }
    
    void DepthFirstSearch::advance( State* currentNode, Grid* gridModel, Sequence* sequence ) {
        std::array<Action, 6> frontier = {
            Action(currentNode->gridPoint, GRID_DIRECTION::NORTH_WEST),
            Action(currentNode->gridPoint, GRID_DIRECTION::NORTH),
            Action(currentNode->gridPoint, GRID_DIRECTION::NORTH_EAST),
            Action(currentNode->gridPoint, GRID_DIRECTION::SOUTH_EAST),
            Action(currentNode->gridPoint, GRID_DIRECTION::SOUTH),
            Action(currentNode->gridPoint, GRID_DIRECTION::SOUTH_WEST)
        };
//        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//        shuffle(frontier.begin(), frontier.end(), std::default_random_engine(seed));

        bool hasValidState = false;
        // Pick the first action from above that is valid
        for(auto& anAction : frontier) {
            
            State* aState = anAction.execute(currentNode, gridModel);
            
            if( aState->gridPoint == NULL ) continue;
            if( sequence->containsState( aState ) ) continue;
            if( aState->gridPoint->hasStartPetalFacingDirection( anAction.direction ) ) {
                continue;
            }
            
            hasValidState = true;
            sequence->pushState( aState );
            
            break;
        }
        
        std::cout << "DepthFirstSearch::advance hasValidState:" << hasValidState << std::endl;
        
        if( !hasValidState ) {
            currentNode = sequence->popState();
            sequence->insertAtHead( currentNode );
        }
    }
}