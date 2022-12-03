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

#include <vector>

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

    int map_size_x = 10;
    int map_size_y = 10;
    MyMap map(map_size_x,map_size_y);
    std::list<std::pair<int, int>> blue_line;
    for (size_t y = 0; y < map_size_y; y++)
    {
        //change for different generation 
        //default moves line one cell to the right after middle point
        if (y < map_size_y/2){
            blue_line.push_back(std::make_pair(map_size_x/3,y));
        } else {
            blue_line.push_back(std::make_pair(map_size_x/3+1,y));
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

    //config of national resources
    blueArmy.ammo_supplies = 5000;
    blueArmy.antitank_supplies = 500;
    blueArmy.combat_supplies = 5000;
    blueArmy.food_supplies = 10000;

    redArmy.ammo_supplies = 5000;
    redArmy.antitank_supplies = 500;
    redArmy.combat_supplies = 5000;
    redArmy.food_supplies = 10000;

    blueArmy.logistics_effectivity = 0.95;
    redArmy.logistics_effectivity = 0.80;

    //config of army sizes and
    //config initial position armies on the mapmake_pair(1,1)
    blueArmy.battalions.push_back(generate_battalion(4,150,1,50,1,10,blueArmy.armyID,map_size_x/3,2)); //600 Infantry + 50 Combat Support units + 10 Tanks with crew
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3,4));
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3+1,6));
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3+1,8));
    
    redArmy.battalions.push_back(generate_battalion(4,150,1,50,1,10,redArmy.armyID,map_size_x,2));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,4));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,6));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,8));


    

    
    //executeSim(blueArmy, redArmy, map, 720/*1 month in hours*/);



    
    return 0;
}