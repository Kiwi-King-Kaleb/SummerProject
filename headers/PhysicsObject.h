class PhysicsObject{
    protected:
		SDL_Rect body; //added this just so that we can actually see something (a rectangle) displayed on the screen when we test
        vector2D position;
        vector2D dimensions;
        vector2D velocity;
        vector2D force;
        float mass;
    public:
		PhysicsObject() {
			body = {100, 100, 50, 50};
			mass = 1000000; // this is just to test the force. I noticed this value has to be pretty high or else it will move too
			//fast so we will have to make some changes later. (so that we don't have to use enormous values)
			position = vector2D(); //set the vectors to a default value of 0, 0
			dimensions = vector2D();
			velocity = vector2D();
			force = vector2D();
			force.setVector2D(0.1, 0); // This is just for testing purposes. I set the force to a value just to see if it works.
		}

        void physics(){
            vector2D acceleration = force/mass;
            velocity += acceleration; //This was = before so I chenged it to +=. Probably just a typo.
            position += velocity;
        }

		void display(SDL_Renderer* renderer) {
			body.x = position.x; //update the position of the body (the rect)
			body.y = position.y;
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); //equivilent to fill(255, 0, 0, 255) in processing (testing purposes so that we can see a colour)
			SDL_RenderFillRect(renderer, &body);
		}
};
