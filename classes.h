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
    enum Type {infantry, combat_support, tank};
    Type type;
    
    int ammo; // the amount of ammo
    int food; // the amount of food
    int supplies;
    int units_died = 0;
    int units_wounded = 0;
    int units_recovered = 0;

    Company(int units, int ammo, int food, int supplies);
    
    void add_units(int amount);
    void remove_dead_units();
    int ret_current_wounded_size();
    
    void heal_units(std::list<Unit>);
};

class Battalion {
  public:
  std::list<Company*> companies; 
  std::pair<int, int> position;
  bool in_fight = false;
  bool preparing_for_attack = false;
  bool moving = false;
  bool fortifying_or_recon = false; //possible delete
  int action_cooldown_counter = 0; 
  int armyID;
  Battalion* enemy_Battalion;
  int attack_power;
  
  int countHistoricalDead();
  bool addCompany(Company com);
  bool removeCompany(Company com);
  int get_base_attack_power();

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


Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy);

#endif
