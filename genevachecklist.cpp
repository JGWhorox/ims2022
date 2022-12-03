/**
 * authors Johann A. Gawron - xgawro00, Patrik Slovák - xslova21
 * project Military Simulator
 * file genevachecklist.cpp
 * brief implementation of Military simulator main file for the subject Modelling and simulations
 */


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "genevachecklist.h"
#include "mapgenerator.h"
#include "classes.h"

int main(int argc, char** argv){
    //std::cout << "Welcome to your week's purgatory" << std::endl;
    
    Arguments args;
    
    std::string input;
    for (int i = 1; i < argc; i++){
        input += argv[i];
        if(i+1 < argc){
            input += " ";
        }
    }
    std::cout << input << std::endl;
    if(!parseArgs(args, input)){
        //std::cerr << "could not parse arguments, see help for more info" << std::endl;
        return -1;
    }
    //setupScenario
    MyMap map(25,25);
    std::list<std::pair<int, int>> blue_line;
    for (size_t y = 0; y < 25; y++)
    {
        //change for different generation
        if (y < 15){
            blue_line.push_back(std::make_pair(3,y));
        } else {
            blue_line.push_back(std::make_pair(4,y));
        }
    }
    map.set_blue_line(blue_line);

    //parseConfigs

    //configure armies 
    Army blueArmy;
    Army redArmy;
    
    //scuffed way of identifying armies in simulation algorithm #temporary #make your life easier, not harder
    blueArmy.armyID = 1;
    redArmy.armyID = 2;

    //config of resources
    blueArmy.ammo_supplies = 5000;
    blueArmy.antitank_supplies = 500;
    blueArmy.combat_supplies = 5000;
    blueArmy.food_supplies = 10000;

    redArmy.ammo_supplies = 5000;
    redArmy.antitank_supplies = 500;
    redArmy.combat_supplies = 5000;
    redArmy.food_supplies = 10000;

    blueArmy.logistics_effectivity = 95;
    redArmy.logistics_effectivity = 80;

    //config of army sizes
    blueArmy.battalions.push_back(generate_batalion(4,150,1,50,1,10,blueArmy.armyID)); //600 Infantry + 50 Combat Support units + 10 Tanks with crew
    blueArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,blueArmy.armyID));
    blueArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,blueArmy.armyID));
    blueArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,blueArmy.armyID));
    
    redArmy.battalions.push_back(generate_batalion(4,150,1,50,1,10,redArmy.armyID));
    redArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,redArmy.armyID));
    redArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,redArmy.armyID));
    redArmy.battalions.push_back(generate_batalion(5,130,1,50,0,0,redArmy.armyID));

    
    //executeSim(blueArmy, redArmy, map, 720/*1 month in hours*/);



    
    return 0;
}