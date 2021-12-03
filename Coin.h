#pragma once
#include "Circle.cpp"
class Coin :
    public Circle
{
    Coin(int x, int y, int r) :Circle(x, y, r){}
    friend class EventHandler; 

};

