#pragma once 
#include <cmath>
#include <algorithm>
#include"Board.hpp"


class CollisionResolver{
    private:
        float e;

    public:
        CollisionResolver(float e);
        float velocityAfterCollisionForObject1(float, float, float, float);
        float velocityAfterCollisionForObject2(float, float, float, float);
        float getCollisionOverlapWithCoins(float, float, float);
        void resolveOverlapWithCoins(Coin*, Coin*, float, Vector);
        void resolveCollisionWithCoins(Coin*, Coin*);
        void resolveCollisionWithSide(Coin*, Vector, Vector);
        void resolveCollisionWithBoard(Board*, Coin*);
        void moveCoinToHole(Coin*, Board*);
        void checkIfCoinInNet(Coin*, Vector, Board*);
        void resolveParticleInHoles(Coin*, Board*);
    friend class Coin;
};
