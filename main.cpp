#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include <memory>
//"" is used for reletive includess
#include "headers/Vector2D.h"
#include "headers/Terrain.h"
#include "headers/PhysicsObject.h"

using namespace std;

void physics(vector<unique_ptr<PhysicsObject>>& physObj, chrono::steady_clock::time_point& timer, chrono::duration<double, micro>& accumulator, chrono::duration<double, micro>& physicsTimeStep){
    chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();//the current time
    chrono::duration<double, micro> timePassed = timer - currentTime;//the time passed since the game last updated the physics
    timer = currentTime;//update the time the game last updated the physics to now
    accumulator += timePassed;// add all the time that has passed since the last physics update to the accumulator
    while(accumulator >= physicsTimeStep){//for every full timestep ( in otherwords for every full 1/120 of a second has passed, advance the physics )
        for( int iteratorPhysicsObjects = 0; iteratorPhysicsObjects < physObj.size(); iteratorPhysicsObjects++){//rather than advance each object numerous time steps at once, advance each object 1 timestep, and then repeat until there are no remaining timesteps
            physObj[iteratorPhysicsObjects]->physics();
        }
        accumulator -= physicsTimeStep;// subtract the time of each timestep from the accumulator
    }
}

int main(){//Solomon I know SDL requires a different kind of main, so I'll let you handle that
    int gameState = 0; // 0 = game
    chrono::steady_clock::time_point timer = chrono::steady_clock::now();// the game timer, keeps track of the last time the physics were advanced
    chrono::duration<double, micro> accumulator = {};//keeps track of any remaining time to a full timestep
    vector<unique_ptr<PhysicsObject>> physObj = vector<unique_ptr<PhysicsObject>>();// I use a pointer here as all the physics objects need to exist in the same container
    chrono::duration<double, micro> physicsTimeStep(double(1.0)/double(120.0));//the amount of time each physics step advances the game, in this case 1/120 of a second
    //FROM HERE
    switch(gameState){
        case 0:
            physics(physObj, timer, accumulator, physicsTimeStep);
        break;
    }
    //TO HERE should be included in the gameloop
    return 0;
}
