#include <cmath>
#include <algorithm>
#include"Board.cpp"


class CollsionResolver{
    private:
        float e;

    public:
        CollsionResolver(float e);
        float velocityAfterCollisionForObject1(float, float, float, float);
        float velocityAfterCollisionForObject2(float, float, float, float);
        float getCollisionOverlapWithCoins(float, float, float);
        void resolveOverlapWithCoins(Coin*, Coin*);
        void resolveCollisionWithCoins(Coin*, Coin*);
        void resolveCollisionWithSide(Coin*, Vector, Vector);
        void resolveCollisionWithBoard(Board*, Coin*);
        void moveCoinToHole(Coin*, Board*);
        void checkIfCoinInNet(Coin*, Vector, Board*);
        void resolveParticleInHoles(Coin*, Board*);
    friend class Coin;
};
