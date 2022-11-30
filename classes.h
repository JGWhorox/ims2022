#include <list>

#ifndef CLASSES_H
#define CLASSES_H


// parent classes
class Unit {
  public:
    enum State {healthy, wounded, dead};
    State state; // state of the unit
    int time_of_last_injury = 0;
    int number_of_medical_procedures = 0;

    //bool operator==(const Unit& a);
    
};

class Brigade {
  public:
    std::list<Unit> units; // number of units
    int ammo; // the amount of ammo
    int food; // the amount of food
    int units_died = 0;
    int units_wounded = 0;
    int units_recovered = 0;

    void add_units(int amount);
    void remove_dead_units();
    int ret_current_wounded_size();
};

// child classes
class Infantry: public Brigade {
    public:
        int antitank; // amount of antitank resources

        Infantry(int u, int a, int f, int at);
        void attack();
        void reposition();
};

class Medic: public Brigade {
    public:
        int meds; // healing resources

        Medic(int u, int a, int f, int m);
        void heal_units(std::list<Unit>);
};

class Tank: public Brigade {
    public:
        Tank(int u, int a, int f);
        void attack();
        void reposition();
};

#endif
