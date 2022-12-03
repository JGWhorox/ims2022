#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <map>
#include <list>
#include <string>


class Cell{
    public:
        int posx;
        int posy;
        bool is_fortified;
        double cover;
        enum Occupations {neutral, blue, red};
        Occupations occupation;

        Cell();
        Cell(int x, int y);
};

class MyMap{
    public:
        std::map<std::pair<int, int>, Cell> cells;

        MyMap();
        MyMap(int x, int y);
        void GenerateMyMap(int x_size, int y_size);
        Cell get_cell(std::pair<int, int> coords);
        void set_occupation(std::pair<int, int> coords, Cell::Occupations occup);
        void set_fortification(std::pair<int, int> coords);
        void set_blue_line(std::list<std::pair<int, int>> blue_line);
        
};

#endif