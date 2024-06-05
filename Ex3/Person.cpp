#include "Person.h"

Person::Person(CharacterType characterType)
{
    _characterType = characterType;
    generateStats();
}

Person::~Person()
{
    DisposeArmor();
}

void Person::DisposeArmor()
{
    if (_head != nullptr)
    {
        delete _head;
        _head = nullptr;
    }

    if (_chest != nullptr)
    {
        delete _chest;
        _chest = nullptr;
    }

    if (_legs != nullptr)
    {
        delete _legs;
        _legs = nullptr;
    }

    if (_hands != nullptr)
    {
        delete _hands;
        _hands = nullptr;
    }
}

Person::Person(CharacterType characterType, size_t characterType_mainParameter, size_t health, size_t armor, size_t accuracy, size_t luck, size_t skill)
{
    _characterType = characterType;
    _health = health>maxValue? maxValue:health;
    _armor = armor > maxValue ? maxValue : armor;
    _accuracy = accuracy > maxValue ? maxValue : accuracy;
    _luck = luck > maxValue ? maxValue : luck;
    _skill = skill > maxValue ? maxValue : skill;

    _strength = 0;
    _intelligence = 0;
    _strength = 0;
    switch (getMainPerk())
    {
        case Person::MainPerkType::agility:
            _agility = characterType_mainParameter > maxValue ? maxValue : characterType_mainParameter;
            break;

        case Person::MainPerkType::intelligence:
            _intelligence = characterType_mainParameter > maxValue ? maxValue : characterType_mainParameter;
            break;

        case Person::MainPerkType::strength:
            _strength = characterType_mainParameter > maxValue ? maxValue : characterType_mainParameter;
            break;
    }
}

size_t Person::getMainPerkValue()
{
    switch (getMainPerk())
    {
    case MainPerkType::strength:
        return getStrength();
        break;
    case MainPerkType::intelligence:
        return getIntelligence();
        break;
    case MainPerkType::agility:
        return getAgility();
        break;
    default:
        break;
    }
}

Person::MainPerkType Person::getMainPerk()
{
    switch (CharacterType::defender)
    {
    case Person::CharacterType::defender:
        return MainPerkType::strength;
        break;
    case Person::CharacterType::healer:
        return MainPerkType::intelligence;
        break;
    case Person::CharacterType::melee:
        return MainPerkType::agility;
        break;
    case Person::CharacterType::range:
        return MainPerkType::intelligence;
        break;
    default:
        break;
    }
}


size_t Person::getHealth()
{
    size_t sum = _health;
    if (_head != nullptr) sum += _head->health;
    if (_chest != nullptr) sum += _chest->health;
    if (_hands != nullptr) sum += _hands->health;
    if (_legs != nullptr) sum += _legs->health;
    sum += getMainPerkValue() * skillsFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getArmor()
{
    size_t sum = _armor;
    if (_head != nullptr) sum += _head->armor;
    if (_chest != nullptr) sum += _chest->armor;
    if (_hands != nullptr) sum += _hands->armor;
    if (_legs != nullptr) sum += _legs->armor;
    sum += getMainPerkValue() * skillsFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getStrength()
{
    size_t sum = _strength;
    if (_head != nullptr) sum += _head->strength;
    if (_chest != nullptr) sum += _chest->strength;
    if (_hands != nullptr) sum += _hands->strength;
    if (_legs != nullptr) sum += _legs->strength;
    if (getMainPerk() == Person::MainPerkType::strength)
        sum *= mainSkillFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getIntelligence()
{
    size_t sum = _intelligence;
    if (_head != nullptr) sum += _head->intelligence;
    if (_chest != nullptr) sum += _chest->intelligence;
    if (_hands != nullptr) sum += _hands->intelligence;
    if (_legs != nullptr) sum += _legs->intelligence;
    if (getMainPerk()==Person::MainPerkType::intelligence)
        sum *= mainSkillFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getAgility()
{
    size_t sum = _agility;
    if (_head != nullptr) sum += _head->agility;
    if (_chest != nullptr) sum += _chest->agility;
    if (_hands != nullptr) sum += _hands->agility;
    if (_legs != nullptr) sum += _legs->agility;
    if (getMainPerk() == Person::MainPerkType::agility)
        sum *= mainSkillFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getAccuracy()
{
    size_t sum = _accuracy;
    if (_head != nullptr) sum += _head->accuracy;
    if (_chest != nullptr) sum += _chest->accuracy;
    if (_hands != nullptr) sum += _hands->accuracy;
    if (_legs != nullptr) sum += _legs->accuracy;
    sum += getMainPerkValue() * skillsFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getLuck()
{
    size_t sum = _luck;
    if (_head != nullptr) sum += _head->luck;
    if (_chest != nullptr) sum += _chest->luck;
    if (_hands != nullptr) sum += _hands->luck;
    if (_legs != nullptr) sum += _legs->luck;
    sum += getMainPerkValue() * skillsFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::getSkill()
{
    size_t sum = _skill;
    if (_head != nullptr) sum += _head->skill;
    if (_chest != nullptr) sum += _chest->skill;
    if (_hands != nullptr) sum += _hands->skill;
    if (_legs != nullptr) sum += _legs->skill;
    sum += getMainPerkValue() * skillsFactor;

    if (sum > maxSignificantValue) sum = maxSignificantValue;
    return sum;
}

size_t Person::doHit()
{
    size_t significantAccuracy = 1+ 1.5 * getAccuracy() / maxSignificantValue;
    size_t significantLuck = 1+ 1.5 * getLuck() / maxSignificantValue;
    size_t significantSkill = 1 + 1.5 * getSkill() / maxSignificantValue;
    size_t damage = getMainPerkValue() * significantSkill;
    

    const size_t randMax = 100;

    size_t rnd = rand()%randMax;
    size_t compare = 15 * significantLuck; //чем больше прокачиваемся тем больше шанс x2
    if (rnd <= compare) damage *= 2;

    rnd = rand() % randMax; 
    compare = 65 * significantAccuracy; //чем больше прокачиваемся тем меньше промахов
    if (rnd > compare) damage = 1;

    return damage;
}


void Person::generateStats()
{
    size_t maxrand = maxValue / 1.5;
    size_t rnd = rand() % maxrand;
    size_t multiple = maxrand * 0.2;
    size_t min = maxrand - multiple;
    size_t dec = 2* multiple;

    _health = min+rand() % dec;
    _armor = min + rand() % dec;
    _accuracy = min + rand() % dec;
    _luck = min + rand() % dec;
    _skill = min + rand() % dec;

    _strength = 0;
    _intelligence = 0;
    _strength = 0;
    switch (getMainPerk())
    {
    case Person::MainPerkType::agility:
        _agility = min + rand() % dec;
        break;

    case Person::MainPerkType::intelligence:
        _intelligence = min + rand() % dec;
        break;

    case Person::MainPerkType::strength:
        _strength = min + rand() % dec;
        break;
    }
}

Person::Equipment* Person::generateEquipment(EquipmentType type, MainPerkType perk)
{
    size_t maxrand = maxValue / 1.5;
    size_t rnd = rand() % maxrand;
    size_t multiple = maxrand * 0.2;
    size_t min = maxrand - multiple;
    size_t dec = 2 * multiple;

    Person::Equipment* equip;
    try 
    {
        equip = new Person::Equipment();
    }
    catch (const char* error_message)
    {
        throw;
    }


    equip->health= min + rand() % dec;
    equip->armor= min + rand() % dec;

    switch (perk)
    {
    case Person::MainPerkType::agility:
        equip->agility = min + rand() % dec;
        break;

    case Person::MainPerkType::intelligence:
        equip->intelligence = min + rand() % dec;
        break;

    case Person::MainPerkType::strength:
        equip->strength = min + rand() % dec;
        break;
    }

    size_t val1 = rand() % 3;
    size_t val2= rand() % 3;
    switch (val1)
    {
    case 0:
        equip->accuracy = min + rand() % dec;
        break;
    case 1:
        equip->luck = min + rand() % dec;
        break;
    case 2:
        equip->skill = min + rand() % dec;
        break;
    }

    if (val1 != val2)
    {
        switch (val2)
        {
        case 0:
            equip->accuracy = min + rand() % dec;
            break;
        case 1:
            equip->luck = min + rand() % dec;
            break;
        case 2:
            equip->skill = min + rand() % dec;
            break;
        }
    }

    return equip;
}

void Person::generateEquipments()
{
    _head = generateEquipment(Person::EquipmentType::head, getMainPerk());
    _chest = generateEquipment(Person::EquipmentType::chest, getMainPerk());
    _hands = generateEquipment(Person::EquipmentType::hands, getMainPerk());
    _legs = generateEquipment(Person::EquipmentType::legs, getMainPerk());
}

void Person::generatePerson()
{
    generateStats();
    generateEquipments();
}

void Person::printEquipment(Person::Equipment *equip)
{
    if (equip != nullptr)
    {
        std::cout << "Equip:"
            << " health=" << equip->health
            << " armor=" << equip->armor
            << " strength=" << equip->strength
            << " intelligence=" << equip->intelligence
            << " agility=" << equip->agility
            << " accuracy=" << equip->accuracy
            << " luck=" << equip->luck
            << " skill=" << equip->skill
            << "\n";
    }
}

void Person::printEquipments()
{
    printEquipment(_head);
    printEquipment(_chest);
    printEquipment(_hands);
    printEquipment(_legs);

}

void Person::printStats()
{
    std::cout << "Stats:"
        << " health=" << _health
        << " armor=" << _armor
        << " strength=" << _strength
        << " intelligence=" << _intelligence
        << " agility=" << _agility
        << " accuracy="<<_accuracy
        << " luck=" << _luck
        << " skill=" << _skill
        << "\n";
    
}
