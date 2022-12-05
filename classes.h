#include <list>

#ifndef CLASSES_H
#define CLASSES_H

class Army;

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
    
    double DMG_taken = 0.0;

    double ammo; // the amount of ammo
    double food; // the amount of food
    double supplies;

    int units_died = 0;
    int units_wounded = 0;
    int units_recovered = 0;
    int units_reinforced_other_battalion = 0;
    bool airdrop = false;

    Company(int units, int ammo, int food, int supplies);
    
    void add_units(int amount);
    void remove_dead_units();
    int ret_current_wounded_size();
    int ret_current_healthy_size();
    Unit* ret_healthy_unit();
    
    void heal_units(int time);
};

class Battalion {
  public:
  std::list<Company*> companies; 
  std::pair<int, int> position;
  bool in_fight = false;
  double moving = 0.0;
  bool fortifying_or_recon = false; //possible delete
  int action_cooldown_counter = 0; 
  int armyID;
  bool is_backup = false;
  int backup_timeout = 0;
  Battalion* enemy_Battalion;
  int attack_power;
  bool attacking_logistics = false;
  int airdrop_timeout = 0;
  
  
  bool addCompany(Company &com);
  bool removeCompany(Company &com);
  
  void call_backup(Army &army);
  bool update_battalion(double casualties, int munition_lost, int supplies_lost, double modifier, int hour);
  void assign_backup(Battalion backup_bat);
  void check_supplies();
  void call_airdrop(Army army, int time, int distance);
  void assign_airdrop(Army army);
  int get_all_ammo();
  double get_ammo_saturation();
  
  int countHistoricalDead();
  int get_number_of_companies();
  int get_base_attack_power();
  int get_number_of_healthy_units();

};

class Army {
  public:
    std::list<Battalion> battalions;

    double logistics_effectivity = 1; //0 - 1 
    double professionalism; // 0 - 1
    double technology_level; // 1 - 4.99 - 1 = first muskets, 2 = napoleonic wars, 3 = WW2, 4 = around 90's - 00's

    double ammo_supplies;
    double food_supplies;
    double combat_supplies;
    //int antitank_supplies;
    int armyID;

    void report_stats(int hour, bool debug, bool show_army_stats, bool show_battalion_stats, bool show_units);
    Battalion* ret_battalion_on_position(std::pair<int,int> position);

};


Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy);

#endif
