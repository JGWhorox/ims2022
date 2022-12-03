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

class Company {
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

class Battalion {
  public:
  std::list<Company*> companies; 
  std::pair<int, int> position;
  bool in_fight = false;
  bool preparing_for_attack = false;
  bool moving = false;
  bool fortifying_or_recon = false;
  int armyID;
  
  int countHistoricalDead();
  bool addCompany(Company com);
  bool removeCompany(Company com);

};

class Army {
  public:
  std::list<Battalion> battalions;
  double logistics_effectivity = 1;
  int ammo_supplies;
  int food_supplies;
  int combat_supplies;
  int antitank_supplies;
  int armyID;

};

// child classes
class Infantry: public Company {
    public:
        int antitank; // amount of antitank resources

        Infantry(int units, int ammo, int food, int at);
        void attack();
        void reposition();
};

class CombatSupport: public Company {
    public:
        int supplies; // healing resources

        CombatSupport(int units, int ammo, int food, int supplies);
        void heal_units(std::list<Unit>);
};

class Tank: public Company {
    public:
        Tank(int u, int a, int f);
        void attack();
        void reposition();
};

Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy);

#endif
