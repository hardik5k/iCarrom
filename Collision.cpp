#include <cmath>
#include "vector.h"
// Basic Principle ---> Linear momentum is conserved during collisons

//Equations derived using ----> 1. Conservation of total linear momentum of system, 2. e = v2 - v2 / u1 - u2
float velocityAfterCollisionForObject1(float m1, float m2, float v1, float v2){
    return v1 * ((m1 - e * m2)/(m1 + m2)) + v2 * (((1 + e) * m2)/(m1 + m2));
}
float velocityAfterCollisionForObject2(float m1, float m2, float v1, float v2){
    return v2 * ((m2 - e * m1)/(m1 + m2)) + v1 * (((1 + e) * m1)/(m1 + m2));
}

// Calculate the overlap ---> distance between centre of two particles(l) - sum of their radii(r1 + r2)
float getCollisionOverlapWithCoins(float r1, float r2, float sqrdistance){
    if (sqrdistance <= pow((r1 + r2), 2)) 
        return (r1 + r2 - sqrt(sqrdistance));
    else return -1;
}
void resolveOverlapWithCoins(float overlap, Vector cn){ 
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

void resolveCollisionWithCoins(){
    Vector contactNormal = coin1->pos.sub(coin2->pos);

    float overlap = getCollisionOverlapWithCoins(coin1->radius, coin2->radius, contactNormal.getMagnitute(1));
    
    if (overlap < 0) return;  // no collision


    //Play collison sound if Overlap is positive(colliding objects).



    //Resolve velocities along tangent and normal at the contact point.
    //Using COM, find new velocity along normal.
    contactNormal = contactNormal.normalize();  // a unit vector along normal.
    Vector contactTangent(-1 * contactNormal.getY(), contactNormal.getX());

    resolveOverlapWithCoins(coin1, coin2, overlap, contactNormal);


    // velocity component along normal
    float velNormal1 = coin1->vel.dotProduct(contactNormal);
    float velNormal2 = coin2->vel.dotProduct(contactNormal);

    // velocity component along common tangent
    float velTangent1 = coin1->vel.dotProduct(contactTangent);
    float velTangent2 = coin2->vel.dotProduct(contactTangent);

    //final velocitiies after collision along normal
    Vector finalVelNormal1 = contactNormal.multiply(velocityAfterCollisionForObject1());
    Vector finalVelNormal2 = contactNormal.multiply(velocityAfterCollisionForObject2());

    //final velocitiies after collision along tangent
    Vector finalVelTangent1 = contactTangent.multiply(velTangent1);
    Vector finalVelTangent2 = contactTangent.multiply(velTangent2);

    //Updating coin velocities 
    coin1->vel = finalVelTangent1.add(finalVelNormal1);
    coin2->vel = finalVelTangent2.add(finalVelNormal2);

}

void resolveCollisionWithSide(){
    // Calculate the overlap ---> distance between centre of coin and the closest point on line segment - radius of coin
    Vector contactSide = edge->getEnd().sub(edge->getStart());
    Vector temp = coin->pos.sub(edge->getStart()); // vector from edge to the coin
    float sideLength = contactSide.getMagnitute();
    float x = max(0, min(sideLength, (contactSide.dotProduct(temp))));
    Vector closestPoint = edge->getStart() + contactSide.normalize().multiply(x);

    Vector overlapNormal = coin->pos.sub(closestPoint);
    float distance = overlapNormal.getMagnitute(1);

    if (distance > coin->radius * coin->radius) return;

    // push back coin to offset overlap.
    coin->pos = coin->pos.add(overlapNormal.normalize().multiply(distance));


    // find out the final velocity vector after reflection.
    contactSide = contactSide.normalize();
    Vector perpendicular(contactSide.getY(), -1 * contactSide.getX());

    Vector velAlongEdge = contactSide.multiply(coin->vel.dotProduct(contactSide));
    Vector velAlongPerpendicular = -e * perpendicular.multiply(coin->vel.dotProduct(perpendicular));

    coin->vel = velAlongEdge.add(velAlongPerpendicular);

}
void checkIfCoinInNet(){
// if (distance between center of coin and net hole < hole radius) ---> move coin to hole()
}
void moveCoinToHole(){
// if coin is not a striker ---> increase score, 
}
void resolveParticleInHole(){
    Vector v = board->holes[i].pos.sub(coin->pos);

    if (v.getMagnitute(1))
}