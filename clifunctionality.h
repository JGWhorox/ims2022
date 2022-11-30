/**
 * author Johann A. Gawron - xgawro00
 * project Military simulator
 * file clifinctionality.h
 * brief implementation of header file various CLI functionalities needed for this project
 */

#ifndef CLIFUNCTIONALITY_H
#define CLIFUNCTIONALITY_H

#include <string>
#include <vector>

struct Arguments {
    std::string configRed = "";
    std::string configBlue = "";
    std::string configScenario = "";
};

std::vector<std::string> split(std::string input);

void printHelp();

void printDebug(const Arguments &args);

bool parseArgs(Arguments &args, std::string input);

#endif