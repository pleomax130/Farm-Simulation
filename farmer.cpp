#include "farmer.h"

using namespace std;

Farmer::Farmer(Plant ** field1, Plant ** field2, Plant ** field3, int size){
    Farmer::isRunning = true;
    Farmer::field1 = field1;
    Farmer::field2 = field2;
    Farmer::field3 = field3;
    Farmer::size = size;
    Farmer::progress = 0;
    Farmer::warehouse = 0;
    Farmer::crops = 0;
}
void Farmer::wait(int counter){
    this->progress = 0;
    for(int i = 0; i<counter; i++){
        this_thread::sleep_for(chrono::milliseconds(100));
        this->progress++;
    }
}

void Farmer::water(int number){
    this->state = "watering";
    if(number==1){
        for(int i=0; i<size; i++){
            while(true){
                if(!field1[i]->used){
                    field1[i]->water();
                    break;
                }
            }
        }
    }
    else if(number==2){
        for(int i=0; i<size; i++){
            while(true){
                if(!field2[i]->used){
                    field2[i]->water();
                    break;
                }
            }
        }
    }
    else if(number==3){
        for(int i=0; i<size; i++){
            while(true){
                if(!field3[i]->used){
                    field3[i]->water();
                    break;
                }
            }
        }
    }
}

void Farmer::collect(int number){
    this->state = "collecting";
    if(number==1){
        for(int i=0; i<size; i++){
            if(field1[i]->isGrown()){
                int x = (std::rand()%10)+5;
                this->crops += x;
                field1[i]->restart();
            }
        }
    }
    else if(number==2){
        for(int i=0; i<size; i++){
            if(field2[i]->isGrown()){
                int x = (std::rand()%10)+5;
                this->crops += x;
                field2[i]->restart();
            }
        }
    }
    else if(number==3){
        for(int i=0; i<size; i++){
            if(field3[i]->isGrown()){
                int x = (std::rand()%10)+5;
                this->crops += x;
                field3[i]->restart();
            }
        }
    }
}

void Farmer::takeToWarehouse(){
    int half = this->crops/2;
    this->crops =0;
    int diff = 400 - this->warehouse + half;
    if(diff < 0){
        this->warehouse += half - diff;
        this->crops -= diff;
        while(!Animal::used){
            Animal::used = true;
            Animal::food += crops+half;
        }
        Animal::used = false;
    }
    else{
        this->warehouse += half;
        while(!Animal::used){
            Animal::used = true;
            Animal::food += half;
        }
        Animal::used = false;
    }
    if(this->warehouse >300)
        warehouse = 0;
}
void Farmer::manage(){
    while(this->isRunning){
        this->state = "moving";
        this->wait(20);
        for(int j = 1; j<4; j++){
            this->fieldNumber = j;
            for(int i = 0; i<size; i++){
                this->collect(j);
                this->wait(1);
            }
            for(int i = 0; i<size; i++){
                this->water(j);
                this->wait(1);
            }
        }
        this->state = "movingBack";
        this->wait(20);
        this->takeToWarehouse();
    }
}

int Farmer::getWarehouse(){
    return this->warehouse;
}
