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

using namespace std;

std::vector<string> split(string input){
    vector<string> retvals;
    istringstream strStream(input);
    for(string s; strStream>>s;){
        retvals.push_back(s);
    }
    return retvals;
}

void printDebug(const Arguments &args){
    cout << "############## DEBUG INFO ##############" << endl;
    cout << args.configBlue << endl;
    cout << args.configRed << endl;
    cout << args.configScenario << endl;
    cout << "############# END OF DEBUG #############" << endl;
}

void printHelp(){
    cout << "##################################### HELP #####################################" << endl;
    cout << "\t-h\n\t\t prints help" << endl;
    cout << "\t-b <filePath>\n\t\tconfig file of team blue - defenders\n\t\tDefault ''" << endl;
    cout << "\t-r <filePath>\n\t\tconfig file of team red - attackers\n\t\tDefault " << endl;
    cout << "\t-s <filePath>\n\t\tconfig of scenario map and data\n\t\tDefault " << endl;
    cout << "################################## END OF HELP #################################" << endl;
}

bool parseArgs(Arguments &args, string input){
    if(input.empty()){
        return false;
    }

    vector<string> splitInput = split(input);

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
            cerr << "not a defined flag see help for more info:" << endl;
            printHelp();
            return false;
        }
    }
    printDebug(args);
    return true;
}
    