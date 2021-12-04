#include"Vector.cpp"

class Circle{
    protected:
        Vector pos;
        float radius;
    public:
        Circle(float x, float y, float r){
            pos.set(x, y);
            this->radius = r;
        }
};
