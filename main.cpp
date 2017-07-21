#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include <memory>
#include <SDL.h>
#include <SDL_image.h> //Do not need right now, but will need for later when we actually load images.
//"" is used for reletive includess
#include "headers/Vector2D.h"
#include "headers/Terrain.h"
#include "headers/PhysicsObject.h"

using namespace std;

//Global window and screen surface variable for the game
SDL_Window* gameWindow = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Renderer* gameRenderer = nullptr; //the renderer for the window that allows shapes to be drawn

const int SCREEN_WIDTH = 640; //set a constant height and width for the game (for testing purposes)
const int SCREEN_HEIGHT = 480;

//global functions for SDL
bool init();
void close();

void physics(vector<unique_ptr<PhysicsObject>>& physObj, chrono::steady_clock::time_point& timer, chrono::duration<double, micro>& accumulator, chrono::duration<double, micro>& physicsTimeStep) {
	chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();//the current time
	chrono::duration<double, micro> timePassed = currentTime - timer;//the time passed since the game last updated the physics
	timer = currentTime;//update the time the game last updated the physics to now
	accumulator += timePassed;// add all the time that has passed since the last physics update to the accumulator
	while (accumulator >= physicsTimeStep) {//for every full timestep ( in otherwords for every full 1/120 of a second has passed, advance the physics )
		for (int iteratorPhysicsObjects = 0; iteratorPhysicsObjects < physObj.size(); iteratorPhysicsObjects++) {//rather than advance each object numerous time steps at once, advance each object 1 timestep, and then repeat until there are no remaining timesteps
			physObj[iteratorPhysicsObjects]->physics();
		}
		accumulator -= physicsTimeStep;// subtract the time of each timestep from the accumulator
	}
}

void displayPhysicsObjects(vector<unique_ptr<PhysicsObject>>& physObj) { 
	for (int iteratorPhysicsObjects = 0; iteratorPhysicsObjects < physObj.size(); iteratorPhysicsObjects++) {//loop through and display every physics object in the vector
		physObj[iteratorPhysicsObjects]->display(gameRenderer);
	}
}

int main(int argc, char* args[]) {
	if (!init()) {
		cout << "Could not initialize SDL";
	} else {
		int gameState = 0; // 0 = game
		chrono::steady_clock::time_point timer = chrono::steady_clock::now();// the game timer, keeps track of the last time the physics were advanced
		chrono::duration<double, micro> accumulator = {};//keeps track of any remaining time to a full timestep
		vector<unique_ptr<PhysicsObject>> physObj = vector<unique_ptr<PhysicsObject>>();// I use a pointer here as all the physics objects need to exist in the same container
		//adding objects to physObj  (just for testing for now. We load one physics object with position (0, 0))
		physObj.push_back(unique_ptr<PhysicsObject> (new PhysicsObject()));
		//end additions here
		chrono::duration<double, micro> physicsTimeStep(double(1.0) / double(120.0));//the amount of time each physics step advances the game, in this case 1/120 of a second
																					 //FROM HERE
		SDL_Event gameMainEvent; //and event handle;
		
		while (gameState == 0) {
			SDL_UpdateWindowSurface(gameWindow);

			while (SDL_PollEvent(&gameMainEvent) != 0) { //if there is an event happening
				if (gameMainEvent.type == SDL_QUIT) { //If the user quits, exit the game loop by changing the value of gameState
					gameState = -1;
				}
			}

			//Here is were we can draw stuff
			//Clear screen
			SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //reset the background to white
			SDL_RenderClear(gameRenderer);

			//draw all of the physics objects
			physics(physObj, chrono::steady_clock::now(), accumulator, physicsTimeStep);
			displayPhysicsObjects(physObj);

			//Update screen
			SDL_RenderPresent(gameRenderer);
		}
		//TO HERE should be included in the gameloop
	}
	close(); //exit SDL

	return 0;
}

bool init() { //This function will create the window aswell as the surface
	bool success = true; //used to check if a window is successfully created

	//initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { //if something could not be initialized
		success = false; //failed
		cout << "Could not initialize SDL";
	} else { //SDL could be initialized
		gameWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gameWindow == nullptr) { //no window was created
			success = false;
			cout << "A window could not be created";
		} else {
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED); //no vsync
			if (gameRenderer == nullptr) {
				cout << "Could not create a renderer for the window";
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gameWindow); //screenSurface is automatically freed when the window is destroyed
	gameWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}
