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

//custom includes
#include "genevachecklist.h"
#include "mapgenerator.h"
#include "classes.h"
#include "scenario_config.h"

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
    
    Army blueArmy;
    Army redArmy;
    MyMap map;

    configureScenario(blueArmy,redArmy,map);


    

    
    //executeSim(blueArmy, redArmy, map, 720/*1 month in hours*/);



    
    return 0;
}