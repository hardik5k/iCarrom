#include"Object.h"
#include "Coin.hpp"

Coin::Coin(const char* texturename, SDL_Renderer* ren, int x, int y, int r, float mass,int coinscore) : Object( texturename, ren,  x,  y){
            this->radius = r;
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
            this->coinID = id++;
            this->coinScore = coinscore; 
            

}
 void Coin:: move(){
            /*if ((this->vel.getX() > 0.0000002) && (this->vel.getY() > 0.0000002))
            {
                this->vel.set(this->vel.getX() - 0.0000002, this->vel.getY() - 0.0000002);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
            }
            else if(this->vel.getX() < -0.0000002 && this->vel.getY() < -0.0000002)
            {
                this->vel.set(this->vel.getX() + 0.0000002, this->vel.getY() + 0.0000002);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
            }
            else if(this->vel.getX() < -0.0000002 && this->vel.getY() > 0.0000002)
            {
                this->vel.set(this->vel.getX() + 0.0000002, this->vel.getY() - 0.0000002);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
            }
            else if(this->vel.getX() > 0.0000002 && this->vel.getY() < -0.0000002)
            {
                this->vel.set(this->vel.getX() - 0.0000002, this->vel.getY() + 0.0000002);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
            }
            else
            {
                this->vel.set(0, 0);
            }*/
                if (this->vel.getMagnitute() < 0.005) this->vel.set(0,0);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
                //this->vel.set(this->vel.getX() - 0.1, this->vel.getY() - 0.1);
                if(this->vel.getMagnitute() > 0.01)
                    this->vel = this->vel.multiply(0.9998);
                else
                    this->vel = this->vel.multiply(0.998);
}
int Coin:: Coin:: id = 0;
