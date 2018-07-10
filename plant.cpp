#include "plant.h"

using namespace std;
mutex Plant::mtx;
int Plant::growLimit = 1000;
Plant::Plant(int id, double sun){
    Plant::sun = sun;
    Plant::id = id;
    Plant::growLevel = 0;
    Plant::grown = false;
    Plant::dead = false;
    Plant::irrigation = 50;
    Plant::dry = 0;
    Plant::isRunning = true;
}

void Plant::grow(double sun){
    mtx.lock();
    this->used = true;
    this->irrigation -= 3;
    this->growLevel += (double)((double)((sun * 50)+(double)(5-dry)));
    //cout<<this->growLevel<<"growLevel "<< this->id<<endl;
    this->used = false;
    mtx.unlock();
}

void Plant::wait(int counter){
    for(int i = 0; i<counter; i++){
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Plant::water(){
    mtx.lock();
    this->irrigation += 5;
    mtx.unlock();
}

bool Plant::checkIfDry(){
    if(this->irrigation <= 4){
        this->dry++;
        if(this->dry == 5){
            this->dead = true;
        }
        return true;
    }
    return false;
}

bool Plant::checkIfGrown(){
    if(growLevel >= Plant::growLimit){
        this->grown = true;
        return true;
    }
    return false;
}

void Plant::restart(){
    this->grown = false;
    this->growLevel = 0;
    this->irrigation = 50;
}

void Plant::live(){
    while(isRunning){
        while(!this->dead){
            if(!this->checkIfDry()){
                this->grow(this->sun);
                if(this->checkIfGrown())
                    break;
            }
            this->wait(5);
        }
        while(this->grown)
            wait(5);
    }
}

int Plant::getIrrigation(){
    return this->irrigation;
}

double Plant::getGrowLevel(){
    return this->growLevel;
}

bool Plant::isGrown(){
    return this->grown;
}

bool Plant::isDead(){
    return this->dead;
}

double Plant::getSun(){
    return this->sun;
}

void Plant::setSun(double sun){
    mtx.lock();
    this->used = true;
    this->sun = sun;
    this->used = false;
    mtx.unlock();
}