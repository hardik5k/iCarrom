#include <cmath>
#include <algorithm>
#include <iostream>
#include"Vector.cpp"
#include"Coin.hpp"
#include"Board.hpp"
#pragma once

using namespace std;

float e = 0.50;
float eBoard = 0.80;
// Basic Principle ---> Linear momentum is conserved during collisons

//Equations derived using ----> 1. Conservation of total linear momentum of system, 2. e = v2 - v2 / u1 - u2
float velocityAfterCollisionForObject1(float m1, float m2, float v1, float v2){
    return v1 * ((m1 - (e * m2))/(m1 + m2)) + v2 * (((1 + e) * m2)/(m1 + m2));
}
float velocityAfterCollisionForObject2(float m1, float m2, float v1, float v2){
    return v2 * ((m2 - (e * m1))/(m1 + m2)) + v1 * (((1 + e) * m1)/(m1 + m2));
}

// Calculate the overlap ---> distance between centre of two particles(l) - sum of their radii(r1 + r2)
float getCollisionOverlapWithCoins(float r1, float r2, float sqrdistance){
    if (sqrdistance <= pow((r1 + r2), 2)) 
        return (r1 + r2 - sqrt(sqrdistance));
    else return -1;
}
void resolveOverlapWithCoins(Coin* coin1, Coin* coin2, float overlap, Vector cn){ 
    // We should separate the objects by an amount proportional to their masses.
    // del_position1 = (m1/ m1 + m2) * overlap in direction of contact normal.
    // del_position2 = (m2/ m2 + m1) * overlap in direction opposite to contact normal.
    float m1 = coin1->mass, m2 = coin2->mass;
    float totalMass = m1 + m2;
    Vector delta1 = cn.multiply(((m1)/(m1 + m2)) * overlap);
    Vector delta2 = cn.multiply(((m2)/(m1 + m2)) * overlap * -1);


    //separate the objects. (Two physical objects can’t occupy the same point in space at the same time)
    coin1->pos = coin1->pos.add(delta1);  
    coin2->pos = coin2->pos.add(delta2);    
}

void resolveCollisionWithCoins(Coin* coin1, Coin* coin2){
    Vector contactNormal = coin1->pos.sub(coin2->pos);
    float overlap = getCollisionOverlapWithCoins(coin1->radius, coin2->radius, contactNormal.getMagnitute(1));
    
    if (overlap < 0) return;  // no collision


    //Play collison sound if Overlap is positive(colliding objects).



    //Resolve velocities along tangent and normal at the contact point.
    //Using COM, find new velocity along normal.
    contactNormal = contactNormal.normalize();  // a unit vector along normal.
    Vector contactTangent(contactNormal.getY() * -1, contactNormal.getX());

    resolveOverlapWithCoins(coin1, coin2, overlap, contactNormal);

    // Vector sv = coin1->vel.sub(coin2->vel);
    // float x = sv.dotProduct(contactNormal);

    // if (x >= 0) return;

    // float ns = -1 * x;
    // float deltaVel = ns - x;

    // float totalMass = coin1->mass + coin2->mass;
    // float impulse = deltaVel/totalMass;

    // Vector imp = contactNormal.multiply(impulse);
    // Vector v1 = imp.multiply(coin1->mass);
    // Vector v2 = imp.multiply(-1 * coin2->mass);

    // coin1->vel = coin1->vel.add(v1);
    // coin2->vel = coin1->vel.add(v2);

    

    // velocity component along normal
    float velNormal1 = coin1->vel.dotProduct(contactNormal);
    float velNormal2 = coin2->vel.dotProduct(contactNormal);

    // velocity component along common tangent
    float velTangent1 = coin1->vel.dotProduct(contactTangent);
    float velTangent2 = coin2->vel.dotProduct(contactTangent);

    //final velocitiies after collision along normal
    Vector finalVelNormal1 = contactNormal.multiply(velocityAfterCollisionForObject1(coin1->mass, coin2->mass, velNormal1, velNormal2));
    Vector finalVelNormal2 = contactNormal.multiply(velocityAfterCollisionForObject2(coin1->mass, coin2->mass, velNormal1, velNormal2));

    //final velocitiies after collision along tangent
    Vector finalVelTangent1 = contactTangent.multiply(velTangent1);
    Vector finalVelTangent2 = contactTangent.multiply(velTangent2);

    //Updating coin velocities 
    coin1->vel = finalVelTangent1.add(finalVelNormal1);
    coin2->vel = finalVelTangent2.add(finalVelNormal2);

}

void resolveCollisionWithSide(Coin* coin, Vector edgeStart, Vector edgeEnd){
    // Calculate the overlap ---> distance between centre of coin and the closest point on line segment - radius of coin
    Vector contactSide = edgeEnd.sub(edgeStart);
    Vector temp = coin->pos.sub(edgeStart); // vector from edge to the coin
    float sideLength = contactSide.getMagnitute();
    float x = fmax(0, min(sideLength, (contactSide.dotProduct(temp)/sideLength)));
    Vector closestPoint = edgeStart.add(contactSide.normalize().multiply(x));
    Vector overlapNormal = coin->pos.sub(closestPoint);
    float distance = overlapNormal.getMagnitute(1);
    

    if (distance > coin->radius * coin->radius) return;

    //play collision sound


    // push back coin to offset overlap.
    coin->pos = coin->pos.add(overlapNormal.normalize().multiply(coin->radius - sqrt(distance)));


    // find out the final velocity vector after reflection.
    contactSide = contactSide.normalize();
    Vector perpendicular(contactSide.getY(), -1 * contactSide.getX());

    Vector velAlongEdge = contactSide.multiply(coin->vel.dotProduct(contactSide));
    Vector velAlongPerpendicular = perpendicular.multiply(coin->vel.dotProduct(perpendicular)).multiply(-1 * eBoard);

    coin->vel = velAlongEdge.add(velAlongPerpendicular);

}
void resolveCollisionWithBoard(Board* board, Coin* coin){
        for (int i = 0; i < 4; i++){
            resolveCollisionWithSide(coin, board->sides[i], board->sides[(i+1)%4]);
        }
        
}
int moveCoinToHole(Coin* c, Board* board){
    c->vel.set(0, 0);
    if (c->coinID == 0) return c->coinScore;
    for (int i = 0; i < board->coinsOnBoard.size(); i++){
        if (c->coinID == board->coinsOnBoard[i]->coinID){
            board->coinsOnBoard.erase(board->coinsOnBoard.begin() + i);
            break;
        }
    }
    return c->coinScore;
}
int checkIfCoinInNet(Coin* c, Vector h, Board* board){
// if (distance between center of coin and net hole < hole radius) ---> move coin to hole()
    Vector v = h.sub(c->pos);
    if (v.getMagnitute(1) < c->radius * c->radius) return moveCoinToHole(c, board);
    return 0;

}

int resolveParticleInHoles(Coin* coin, Board* board){
    for (int i = 0; i < 4; i++){
        int x = checkIfCoinInNet(coin, board->holes[i], board);
            if ( x != 0) return x;
    }
    return 0;
}