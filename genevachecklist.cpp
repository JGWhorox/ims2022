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

    //parseConfigs

    //loadArmies
    
    //setupScenario

    
    //executeSim
    


    
    return 0;
}