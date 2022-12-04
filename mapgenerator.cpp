#include <fstream>
#include <string>

#include <simlib.h>

#include "mapgenerator.h"

MyMap::MyMap(){}

MyMap::MyMap(int x, int y){
    GenerateMyMap(x,y);
};

void MyMap::GenerateMyMap(int x_size, int y_size){
    
    max_x = x_size-1;
    max_y = y_size-1;

    for (size_t i = 0; i < x_size; i++)
    {
        for (size_t j = 0; j < y_size; j++)
        {
            Cell new_cell(i,j);
            std::pair<int, int> coords(i,j);
            cells.insert({coords, new_cell});
        }
    }
}

Cell& MyMap::get_cell(std::pair<int, int> coords){
    return cells.find(coords)->second;
}

void MyMap::set_occupation(std::pair<int, int> coords, Cell::Occupations occup){
    std::map<std::pair<int, int>, Cell>::iterator it = cells.find(coords);
    it->second.occupation = occup;
}

void MyMap::set_fortification(std::pair<int, int> coords){
    std::map<std::pair<int, int>, Cell>::iterator it = cells.find(coords);
    it->second.is_fortified = true;
    it->second.cover = 1; // max cover value
}

void MyMap::set_blue_line(std::list<std::pair<int, int>> blue_line){
    for (auto coords: blue_line){
        Cell cell = get_cell(coords);
        set_fortification(coords);
    }
}

Cell::Cell(){}

Cell::Cell(int x, int y){
    posx = x;
    posy = y;
    cover = Random() / 2; // Random() == 0-0.99
    occupation = Cell::neutral;
    is_fortified = false;
}