class PhysicsObject{
    protected:
        vector2D position;
        vector2D dimensions;
        vector2D velocity;
        vector2D force;
        float mass;
    public:
        void physics(){
            vector2D acceleration = force/mass;
            velocity = acceleration;
            position += velocity;
        }
};
