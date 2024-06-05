#pragma once
#include <cstdlib>
#include <iostream>
class Person
{

public:

    const double skillsFactor = 0.1;
    const double mainSkillFactor = 1.3;
    const size_t maxValue = 10000;
    const size_t maxSignificantValue = 500000;
    enum class CharacterType { defender, healer, melee, range };
    enum class MainPerkType { strength, intelligence, agility };
    enum class EquipmentType { head, chest, hands, legs };
    struct Equipment
    {
        EquipmentType type;
        size_t health=0;
        size_t armor=0;
        size_t strength=0;
        size_t intelligence=0;
        size_t agility=0;
        size_t accuracy=0;
        size_t luck=0;
        size_t skill=0;
    };


public:

    size_t  _health, _armor, _strength, _intelligence, _agility, _accuracy, _luck, _skill;
    CharacterType _characterType;
    Equipment* _head=nullptr;
    Equipment* _chest= nullptr;
    Equipment* _hands= nullptr;
    Equipment* _legs= nullptr;


public:

    Person(CharacterType characterType, size_t characterType_mainParameter, size_t health, size_t armor, size_t accuracy, size_t luck, size_t skill);
    Person(CharacterType characterType);
    ~Person();
    void DisposeArmor();

    size_t getHealth();
    size_t getArmor();
    size_t getStrength();
    size_t getIntelligence();
    size_t getAgility();
    size_t getAccuracy();
    size_t getLuck();
    size_t getSkill();

    Person::MainPerkType getMainPerk();
    size_t getMainPerkValue();

    void generateStats();
    Equipment* generateEquipment(EquipmentType type, MainPerkType perk);
    void generateEquipments();
    void generatePerson();

    void printEquipment(Person::Equipment* equip);
    void printEquipments();
    void printStats();

    size_t doHit();
};




