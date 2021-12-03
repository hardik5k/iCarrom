#pragma once
class Sides
{
private:
	float x, y;
	int limit_range; 

public:
	Sides(float x, float y);
	friend class EventHandler; 
};

