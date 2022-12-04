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
    int units_reinforced_other_battalion = 0;

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
  bool is_backup;
  int backup_timeout;
  Battalion* enemy_Battalion;
  int attack_power;
  
  int countHistoricalDead();
  bool addCompany(Company com);
  bool removeCompany(Company com);
  void call_backup(Army army);
  int get_base_attack_power();
  int get_number_of_healthy_units();

};

class Army {
  public:
  std::list<Battalion> battalions;
  
  double logistics_effectivity = 1; //0 - 1 
  double professionalism; // 0 - 1
  double technology_level; // 1 - 4.99 - 1 = first muskets, 2 = napoleonic wars, 3 = WW2, 4 = around 90's - 00's

  int ammo_supplies;
  int food_supplies;
  int combat_supplies;
  int antitank_supplies;
  int armyID;

};


Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy);

#endif
