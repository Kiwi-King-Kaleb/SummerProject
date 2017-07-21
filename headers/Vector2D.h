struct vector2D{
    float x;
    float y;

	vector2D::vector2D() { //added this as a default constructo)
		x = 0.0;
		y = 0.0;
	}

	void setVector2D(float newXValue, float newYValue) { //added this because it is handy and we will probably need it.
		x = newXValue;
		y = newYValue;
	}

    vector2D operator+(vector2D& vector2){
        vector2D result;
        result.x = x + vector2.x;
        result.y = y + vector2.y;
        return result;
    }

    void operator+=(vector2D& vector2){
        x += vector2.x;
        y += vector2.y;
    }

    vector2D operator-(vector2D& vector2){
        vector2D result;
        result.x = x - vector2.x;
        result.y = y - vector2.y;
        return result;
    }

    void operator-=(vector2D& vector2){
        x -= vector2.x;
        y -= vector2.y;
    }

    vector2D operator*(float multiplier){
        vector2D result;
        result.x = x * multiplier;
        result.y = y * multiplier;
        return result;
    }

    vector2D operator*(int multiplier){
        vector2D result;
        result.x = x * multiplier;
        result.y = y * multiplier;
        return result;
    }

    vector2D operator/(float divisor){
        vector2D result;
        result.x = x/divisor;
        result.y = y/divisor;
        return result;
    }

    vector2D operator/(int divisor){
        vector2D result;
        result.x = x/divisor;
        result.y = y/divisor;
        return result;
    }

    float mag(){
        return sqrt(pow(x,2)+pow(y,2));
    }

    void normalize(){
        int t_x = x/mag();
        int t_y = y/mag();
        x = t_x;
        y = t_y;
    }
};
