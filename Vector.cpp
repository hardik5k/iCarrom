#pragma once 
#include <cmath>

class Vector{
    private:
        float x, y;

    public:
        Vector(){}

        Vector(float x, float y){
            set(x, y);
        }
        void set(float x, float y){
            this->x = x;
            this->y = y;
        }

        float getX(){
            return this->x;
        }
        float getY(){
            return this->y;
        }

        float getMagnitute(int square = 0){
            return square ? pow(x,2) + pow(y,2) : sqrt(pow(x,2) + pow(y,2));
        }
        float getArgument(){
            return atan(this->y/this->x); 
        }
        
        float distanceFrom(Vector v){
            return sqrt(pow((this->x - v.x), 2) + pow((this->y - v.y), 2));
        }

        float dotProduct(Vector v){
            return (this->x * v.x + this->y * v.y);
        }
        
        Vector multiply(float i){
            Vector u(this->x * i, this->y * i);
            return u;
        }

        Vector normalize(){
            return this->multiply(1/this->getMagnitute());
        }

        Vector sub(Vector v){
            Vector u(this->x - v.x, this->y - v.y);
            return u;
        }
        Vector add(Vector v){
            Vector u(this->x + v.x, this->y + v.y);
            return u;
        }
        friend class Game ; 

};