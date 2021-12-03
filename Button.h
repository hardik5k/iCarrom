#pragma once
class Button
{
private:
	int x, y;
	int width, height; 
public :
	Button(int xc , int yc); 
	friend class EventHandler; 
};

