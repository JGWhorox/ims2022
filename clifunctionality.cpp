/**
 * author Johann A. Gawron - xgawro00
 * project Military simulator
 * file clifinctionality.cpp
 * brief implementation of various CLI functionalities needed for this project
 */


#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <bits/stdc++.h>
#include <arpa/inet.h>

#include "clifunctionality.h"

std::vector<std::string> split(std::string input){
    std::vector<std::string> retvals;
    std::istringstream strStream(input);
    for(std::string s; strStream>>s;){
        retvals.push_back(s);
    }
    return retvals;
}

void printDebug(const Arguments &args){
    std::cout << "############## DEBUG INFO ##############" << std::endl;
    std::cout << args.configBlue << std::endl;
    std::cout << args.configRed << std::endl;
    std::cout << args.configScenario << std::endl;
    std::cout << "############# END OF DEBUG #############" << std::endl;
}

void printHelp(){
    std::cout << "##################################### HELP #####################################" << std::endl;
    std::cout << "\t-h\n\t\t prints help" << std::endl;
    std::cout << "\t-b <filePath>\n\t\tconfig file of team blue - defenders\n\t\tDefault ''" << std::endl;
    std::cout << "\t-r <filePath>\n\t\tconfig file of team red - attackers\n\t\tDefault " << std::endl;
    std::cout << "\t-s <filePath>\n\t\tconfig of scenario map and data\n\t\tDefault " << std::endl;
    std::cout << "################################## END OF HELP #################################" << std::endl;
}

bool parseArgs(Arguments &args, std::string input){
    if(input.empty()){
        return false;
    }

    std::vector<std::string> splitInput = split(input);

    for(auto it = splitInput.begin(); it != splitInput.end(); ++it){
        //checking for the config files
        if(*it == "-b"){
            if(it+1 != splitInput.end()){
                args.configBlue = *(++it);
            }
        }
        else if(*it == "-r"){
            if(it+1 != splitInput.end()){
                args.configRed = *(++it);
            }
        }
        else if(*it == "-s"){
            if(it+1 != splitInput.end()){
                args.configScenario = *(++it);
            }
        }
        else{         
            std::cerr << "not a defined flag see help for more info:" << std::endl;
            printHelp();
            return false;
        }
    }
    printDebug(args);
    return true;
}
    