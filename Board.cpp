#include <vector> 
#include "Vector.cpp"
#include "Coin.cpp"

class Board{
    private:
        vector<Vector> sides;
        vector<Coin*> coins; 
        int center_x, center_y;
        int width = 600, height = 600;  
    public:
    Board(){
        Vector v1(20, 545);
        Vector v2(20, 20);
        Vector v3(545, 20);
        Vector v4(545, 545);
        sides.push_back(v1);
        sides.push_back(v2);
        sides.push_back(v3);
        sides.push_back(v4);
    }
    friend class Game;

};