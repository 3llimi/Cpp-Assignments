#include <bits/stdc++.h>
 
using namespace std;
 
// Forward declarations
class Character;
class PhysicalItem;
class Container;
class SpellSheet;
 
// Base class for all entities
class Entity {
public:
    virtual ~Entity() {}
};
 
 
// Class representing a character
class Character : public Entity {
public:
    Character(const string& name, int healthPoints) : name(name), healthPoints(healthPoints), alive(true), spellCast(false) {} // Initialize spellCast to false
 
    const string& getName() const {
        return name;
    }
 
    int getHealthPoints() const {
        return healthPoints;
    }
    bool hasCastSpell() const {
        return spellCast;
    }
    void setHealthPoints(int healthPoints) {
        this->healthPoints = healthPoints;
    }
    void setSpellCast(bool value) {
        spellCast = value;
    }
    virtual void attack(Character& target, const string& weaponName) = 0;
    virtual void castSpell(Character& target, const string& spellName) = 0;
    virtual void drinkPotion(Character& target, const string& potionName) = 0;
    virtual void receiveDamage(int damage) {
        healthPoints -= damage;
        if (healthPoints <= 0 && alive) {
            healthPoints = 0;
            alive = false;
        }
    }
    bool isAlive() const {
        return alive;
    }
 
protected:
    string name;
    int healthPoints;
    bool alive;
    bool spellCast; // Flag to track if the character has already cast a spell
};
 
// Class representing a physical item
class PhysicalItem : public Entity {
public:
    PhysicalItem(const string& name) : name(name) {}
 
    const string& getName() const {
        return name;
    }
 
protected:
    string name;
};
 
// Class representing a container
class Container : public Entity {
public:
    virtual ~Container() {}
 
    virtual void addItem(shared_ptr<PhysicalItem> item) = 0;
    virtual void removeItem(const string& itemName) = 0;
    virtual bool isFull() const = 0;
};
 
// Class representing a spell sheet
class SpellSheet : public PhysicalItem {
public:
    SpellSheet(const string& name, int numAllowedTargets, int damageValue, const vector<string>& characterNames) : PhysicalItem(name), numAllowedTargets(numAllowedTargets), damageValue(damageValue), characterNames(characterNames) {}
 
    int getNumAllowedTargets() const {
        return numAllowedTargets;
    }
 
    int getDamageValue() const {
        return damageValue;
    }
 
    const vector<string>& getCharacterNames() const {
        return characterNames;
    }
 
private:
    int numAllowedTargets;
    int damageValue;
    vector<string> characterNames;
};
 
 
// Class representing a weapon
class Weapon : public PhysicalItem {
public:
    Weapon(const string& name, int damageValue) : PhysicalItem(name), damageValue(damageValue) {}
 
    int getDamageValue() const {
        return damageValue;
    }
 
private:
    int damageValue;
};
 
// Class representing a potion
class Potion : public PhysicalItem {
public:
    Potion(const string& name, int healValue) : PhysicalItem(name), healValue(healValue) {}
 
    int getHealValue() const {
        return healValue;
    }
 
private:
    int healValue;
};
 
// Class representing an arsenal container
class Arsenal : public Container {
public:
    Arsenal(int maxWeapons) : maxWeapons(maxWeapons) {}
 
    void addItem(shared_ptr<PhysicalItem> item) override {
        if (isFull()) {
            throw runtime_error("Error caught\n");
        }
        weapons.push_back(item);
    }
 
    void removeItem(const string& itemName) override {
        weapons.erase(remove_if(weapons.begin(), weapons.end(), [&](const shared_ptr<PhysicalItem>& item) {
            return item->getName() == itemName;
        }), weapons.end());
    }
 
    bool isFull() const override {
        return weapons.size() >= maxWeapons;
    }
 
    vector<shared_ptr<PhysicalItem>> weapons;
private:
    int maxWeapons; // Maximum capacity for the Arsenal
};
 
// Class representing a medical bag container
class MedicalBag : public Container {
public:
    MedicalBag(int maxPotions) : maxPotions(maxPotions) {}
 
    void addItem(shared_ptr<PhysicalItem> item) override {
        if (isFull()) {
            throw runtime_error("Error caught\n");
        }
        potions.push_back(item);
    }
 
    void removeItem(const string& itemName) override {
        potions.erase(remove_if(potions.begin(), potions.end(), [&](const shared_ptr<PhysicalItem>& item) {
            return item->getName() == itemName;
        }), potions.end());
    }
 
    bool isFull() const override {
        return potions.size() >= maxPotions;
    }
 
    vector<shared_ptr<PhysicalItem>> potions;
private:
    int maxPotions;
};
 
// Class representing a spell book container
class SpellBook : public Container {
public:
    SpellBook(int maxSpells) : maxSpells(maxSpells) {}
 
    void addItem(shared_ptr<PhysicalItem> item) override {
        if (isFull()) {
            throw runtime_error("Error caught\n");
        }
        spellSheets.push_back(item);
    }
 
    void removeItem(const string& itemName) override {
        spellSheets.erase(remove_if(spellSheets.begin(), spellSheets.end(), [&](const shared_ptr<PhysicalItem>& item) {
            return item->getName() == itemName;
        }), spellSheets.end());
    }
 
    bool isFull() const override {
        return spellSheets.size() >= maxSpells;
    }
 
    vector<shared_ptr<PhysicalItem>> spellSheets;
private:
    int maxSpells;
};
class Narrator : public Character {
public:
    Narrator(const string& name) : Character(name, 1000) {} // Set initial health points for the narrator
 
    void attack(Character& target, const string& weaponName) override {
        throw runtime_error("Error caught\n");
    }
 
    void castSpell(Character& target, const string& spellName) override {
        throw runtime_error("Error caught\n");
    }
 
    void drinkPotion(Character& target, const string& potionName) override {
        throw runtime_error("Error caught\n");
    }
};
// Class representing a fighter character
class Fighter : public Character {
public:
    Fighter(const string& name, int healthPoints) : Character(name, healthPoints) {
        arsenal = make_shared<Arsenal>(3);
        medicalBag = make_shared<MedicalBag>(5);
    }
 
    void attack(Character& target, const string& weaponName) override {
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        auto weaponIter = find_if(arsenal->weapons.begin(), arsenal->weapons.end(), [&](const shared_ptr<PhysicalItem>& item) {
            return item->getName() == weaponName;
        });
 
        if (weaponIter == arsenal->weapons.end()) {
            cout << "Error caught" << endl;
            return;
        }
 
 
        int damageValue = static_pointer_cast<Weapon>(arsenal->weapons.front())->getDamageValue();
        target.receiveDamage(damageValue);
 
        cout << getName() << " attacks " << target.getName() << " with their " << weaponName << "!" << endl;
 
        if (!target.isAlive()) {
            cout << target.getName() << " has died..." << endl;
        }
    }
 
    void castSpell(Character& target, const string& spellName) override {
        throw runtime_error("Error caught\n");
    }
 
    void drinkPotion(Character& supplier, const string& potionName) override {
        if (!supplier.isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (medicalBag->potions.empty()) {
            cout << "Error caught\n";
            return;
        }
 
        bool potionFound = false;
        for (const auto& potion : medicalBag->potions) {
            if (potion->getName() == potionName) {
                potionFound = true;
                int healValue = static_pointer_cast<Potion>(potion)->getHealValue();
                supplier.setHealthPoints(supplier.getHealthPoints() + healValue);
                cout << supplier.getName() << " drinks " << potionName << " from " << getName() << "." << endl;
 
                // Remove the consumed potion from the character's medical bag
                medicalBag->removeItem(potionName);
                break;
            }
        }
 
        if (!potionFound) {
            cout << "Error caught\n";
        }
    }
 
 
    shared_ptr<Arsenal> arsenal;
    shared_ptr<MedicalBag> medicalBag;
};
 
// Class representing a wizard character
class Wizard : public Character {
public:
    Wizard(const string& name, int healthPoints) : Character(name, healthPoints) {
        spellBook = make_shared<SpellBook>(10);
        medicalBag = make_shared<MedicalBag>(10);
    }
 
    void attack(Character& target, const string& weaponName) override {
        throw runtime_error("Error caught\n");
    }
 
    void castSpell(Character& target, const string& spellName) override {
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (hasCastSpell()) { // Check if the character has already cast a spell
            cout << "Error caught" << endl;
            return;
        }
 
 
        bool spellFound = false;
        for (const auto& spell : spellBook->spellSheets) {
            if (spell->getName() == spellName) {
                spellFound = true;
                int damage = static_pointer_cast<SpellSheet>(spell)->getDamageValue();
 
                // Check if the target is within the allowed targets of the spell
                const vector<string>& allowedTargets = static_pointer_cast<SpellSheet>(spell)->getCharacterNames();
                if (find(allowedTargets.begin(), allowedTargets.end(), target.getName()) == allowedTargets.end()) {
                    cout << "Error caught" << endl;
                    return;
                }
 
                target.receiveDamage(damage);
                cout << getName() << " casts " << spellName << " on " << target.getName() << "!" << endl;
                target.receiveDamage(target.getHealthPoints());
                cout << target.getName() << " has died..." << endl;
                setSpellCast(true);
                spellBook->removeItem(spellName);
                break;
            }
        }
 
        if (!spellFound) {
            throw runtime_error("Error caught\n");
        }
    }
 
    void drinkPotion(Character& supplier, const string& potionName) override {
        if (!supplier.isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (medicalBag->potions.empty()) {
            cout << "Error caught\n";
            return;
        }
 
        bool potionFound = false;
        for (const auto& potion : medicalBag->potions) {
            if (potion->getName() == potionName) {
                potionFound = true;
                int healValue = static_pointer_cast<Potion>(potion)->getHealValue();
                supplier.setHealthPoints(supplier.getHealthPoints() + healValue);
                cout << supplier.getName() << " drinks " << potionName << " from " << getName() << "." << endl;
 
                // Remove the consumed potion from the character's medical bag
                medicalBag->removeItem(potionName);
                break;
            }
        }
 
        if (!potionFound) {
            cout << "Error caught\n";
        }
    }
 
    shared_ptr<SpellBook> spellBook;
    shared_ptr<MedicalBag> medicalBag;
};
 
// Class representing an archer character
class Archer : public Character {
public:
    Archer(const string& name, int healthPoints) : Character(name, healthPoints) {
        arsenal = make_shared<Arsenal>(2);
        medicalBag = make_shared<MedicalBag>(3);
        spellBook = make_shared<SpellBook>(2);
    }
 
    void attack(Character& target, const string& weaponName) override {
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        auto weaponIter = find_if(arsenal->weapons.begin(), arsenal->weapons.end(), [&](const shared_ptr<PhysicalItem>& item) {
            return item->getName() == weaponName;
        });
 
        if (weaponIter == arsenal->weapons.end()) {
            cout << "Error caught" << endl;
            return;
        }
 
        int damageValue = static_pointer_cast<Weapon>(arsenal->weapons.front())->getDamageValue();
        target.receiveDamage(damageValue);
        cout << getName() << " attacks " << target.getName() << " with their " << weaponName << "!" << endl;
 
        if (!target.isAlive()) {
            cout << target.getName() << " has died..." << endl;
        }
    }
 
    void castSpell(Character& target, const string& spellName) override {
 
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
 
        if (hasCastSpell()) { // Check if the character has already cast a spell
            cout << "Error caught" << endl;
            return;
        }
        bool spellFound = false;
        for (const auto& spell : spellBook->spellSheets) {
            if (spell->getName() == spellName) {
                spellFound = true;
                int damage = static_pointer_cast<SpellSheet>(spell)->getDamageValue();
 
                // Check if the target is within the allowed targets of the spell
                const vector<string>& allowedTargets = static_pointer_cast<SpellSheet>(spell)->getCharacterNames();
                if (find(allowedTargets.begin(), allowedTargets.end(), target.getName()) == allowedTargets.end()) {
                    cout << "Error caught" << endl;
                    return;
                }
 
                target.receiveDamage(damage);
                cout << getName() << " casts " << spellName << " on " << target.getName() << "!" << endl;
                target.receiveDamage(target.getHealthPoints());
                cout << target.getName() << " has died..." << endl;
                setSpellCast(true);
                spellBook->removeItem(spellName);
                break;
            }
        }
 
        if (!spellFound) {
            throw runtime_error("Error caught\n");
        }
    }
 
    void drinkPotion(Character& supplier, const string& potionName) override {
        if (!supplier.isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (!isAlive()) {
            cout <<"Error caught" << endl;
            return;
        }
        if (medicalBag->potions.empty()) {
            cout << "Error caught\n";
            return;
        }
 
        bool potionFound = false;
        for (const auto& potion : medicalBag->potions) {
            if (potion->getName() == potionName) {
                potionFound = true;
                int healValue = static_pointer_cast<Potion>(potion)->getHealValue();
                supplier.setHealthPoints(supplier.getHealthPoints() + healValue);
                cout << supplier.getName() << " drinks " << potionName << " from " << getName() << "." << endl;
 
                // Remove the consumed potion from the character's medical bag
                medicalBag->removeItem(potionName);
                break;
            }
        }
 
        if (!potionFound) {
            cout << "Error caught\n";
        }
    }
 
    shared_ptr<Arsenal> arsenal;
    shared_ptr<MedicalBag> medicalBag;
    shared_ptr<SpellBook> spellBook;
};
 
// Define classes and containers here
 
string formatCharacterOutput(const string& name, const string& type, int healthPoints) {
    return name + ":" + type + ":" + to_string(healthPoints);
}
 
string formatWeaponOutput(const string& name, int damageValue) {
    return name + ":" + to_string(damageValue);
}
 
string formatPotionOutput(const string& name, int healValue) {
    return name + ":" + to_string(healValue);
}
 
string formatSpellOutput(const string& name, int numAllowedTargets) {
    return name + ":" + to_string(numAllowedTargets);
}
vector<string> characterCreationOrder; // Define a vector to store the order of character creation
 
void createCharacter(unordered_map<string, shared_ptr<Character>>& characters, const string& type, const string& name, int initHP) {
    if (characters.find(name) == characters.end()) {
        if (type == "fighter") {
            characters[name] = make_shared<Fighter>(name, initHP);
        } else if (type == "wizard") {
            characters[name] = make_shared<Wizard>(name, initHP);
        } else if (type == "archer") {
            characters[name] = make_shared<Archer>(name, initHP);
        }
        characterCreationOrder.push_back(name); // Store the name in the order it was created
        cout << "A new " << type << " came to town, " << name << "." << endl;
    } else {
        throw runtime_error("Error caught\n");
    }
}
 
void createItem(unordered_map<string, shared_ptr<Character>>& characters, unordered_map<string, shared_ptr<PhysicalItem>>& items, const string& itemType, const string& ownerName, const string& itemName, int value, const vector<string>& characterNames) {
    if (characters.find(ownerName) == characters.end()) {
        cout << "Error caught" << endl;
        return;
    }
 
    if (items.find(itemName) != items.end()) {
        cout << "Error caught"<< endl;
        return;
    }
 
 
    shared_ptr<Character> ownerCharacter = characters[ownerName];
    if (!(ownerCharacter->isAlive())) {
        cout <<"Error caught" << endl;
        return;
    }
    if (itemType == "weapon") {
        if (value < 1) {
            cout << "Error caught" << endl;
            return;
        }
        items[itemName] = make_shared<Weapon>(itemName, value);
        auto fighterOwner = dynamic_pointer_cast<Fighter>(ownerCharacter);
        auto archerOwner = dynamic_pointer_cast<Archer>(ownerCharacter);
 
        if (fighterOwner) {
            fighterOwner->arsenal->addItem(items[itemName]);
            cout << ownerName << " just obtained a new weapon called " << itemName << "." << endl;
        }else if(archerOwner){
            archerOwner->arsenal->addItem(items[itemName]);
            cout << ownerName << " just obtained a new weapon called " << itemName << "." << endl;
        } else {
            cout << "Error caught" << endl;
        }
    } else if (itemType == "potion") {
        if (value < 1) {
            cout << "Error caught" << endl;
            return;
        }
        items[itemName] = make_shared<Potion>(itemName, value);
        auto fighterOwner = dynamic_pointer_cast<Fighter>(ownerCharacter);
        auto archerOwner = dynamic_pointer_cast<Archer>(ownerCharacter);
        auto wizardOwner = dynamic_pointer_cast<Wizard>(ownerCharacter);
 
        if (fighterOwner) {
            fighterOwner->medicalBag->addItem(items[itemName]);
            cout << ownerName << " just obtained a new potion called " << itemName << "." << endl;
        } else if (archerOwner){
            archerOwner->medicalBag->addItem(items[itemName]);
            cout << ownerName << " just obtained a new potion called " << itemName << "." << endl;
        } else if (wizardOwner){
            wizardOwner->medicalBag->addItem(items[itemName]);
            cout << ownerName << " just obtained a new potion called " << itemName << "." << endl;
        } else {
            cout << "Error caught" << endl;
        }
    }else if (itemType == "spell") {
        bool allCharactersExist = true;
        for (const auto& characterName : characterNames) {
            if (characters.find(characterName) == characters.end() || !characters[characterName]->isAlive()) {
                cout << "Error caught" << endl;
                return;
            }
        }
 
        // Check if the owner character is a Wizard or Archer
        auto ownerCharacter = characters[ownerName];
        auto wizardOwner = dynamic_pointer_cast<Wizard>(ownerCharacter);
        auto archerOwner = dynamic_pointer_cast<Archer>(ownerCharacter);
 
        if (wizardOwner || archerOwner) {
            auto spellBook = wizardOwner ? wizardOwner->spellBook : archerOwner->spellBook;
            // Check if the spell book is full
            if (!spellBook->isFull() && allCharactersExist) {
                // Create and add the spell item to the spell book
                items[itemName] = make_shared<SpellSheet>(itemName, value, value, characterNames);
                spellBook->addItem(items[itemName]);
                cout << ownerName << " just obtained a new spell called " << itemName << "." << endl;
            } else {
                cout << "Error caught" << endl;
            }
        } else {
            cout << "Error caught" << endl;
        }
    } else {
        cout << "Error caught" << endl;
    }
}
 
string formatDialogue(const string& dialogue, unordered_map<string, shared_ptr<Character>>& characters) {
    stringstream ss(dialogue);
    string speaker, speech;
    int sp_len;
    vector<string> speechParts;
 
    // Parse the dialogue string
    ss.ignore(9); // ignore "Dialogue "
    getline(ss, speaker, ' ');
    ss >> sp_len;
    for (int i = 0; i < sp_len; ++i) {
        string part;
        getline(ss, part, ',');
        speechParts.push_back(part);
    }
 
    // Check if the speaker exists
    if (characters.find(speaker) == characters.end() || !characters[speaker]->isAlive()) {
        return "Error caught";
    }
 
    // Concatenate speech parts
    for (size_t i = 0; i < speechParts.size(); ++i) {
        speech += speechParts[i];
        if (i != speechParts.size() - 1)
            speech += " ";
    }
 
    // Format and return the dialogue
    return speaker + ":" + speech;
}
 
int main() {
 
    // Redirect input and output to files
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    streambuf *cinbuf = std::cin.rdbuf();
    streambuf *coutbuf = std::cout.rdbuf();
    cin.rdbuf(inputFile.rdbuf());
    cout.rdbuf(outputFile.rdbuf());
 
    // Declare containers for characters and items
    unordered_map<string, shared_ptr<Character>> characters;
    unordered_map<string, shared_ptr<PhysicalItem>> items;
    // Create a narrator character and add it to the characters container
    shared_ptr<Narrator> narrator = make_shared<Narrator>("Narrator");
    characters["Narrator"] = narrator;
 
    // Read the number of events from input
    int n;
    cin >> n;
    cin.ignore(); // Add this line to consume the newline character
 
    // Loop through each event
    for (int i = 0; i < n; ++i) {
        string event;
        getline(cin, event);
 
        // Parse the event using stringstream
        stringstream ss(event);
        string eventType;
        ss >> eventType; // Extract the event type
 
        try {
            // Handle different event types
            if (eventType == "Dialogue") {
                // Handle Dialogue event
                cout << formatDialogue(event, characters) << endl;
            }
            else if (eventType == "Create") {
                // Handle Create event
                string objectType;
                ss >> objectType;
                if (objectType == "character") {
                    // Handle character creation
                    string charType, name;
                    int initHP;
                    ss >> charType >> name >> initHP;
                    createCharacter(characters, charType, name, initHP);
                } else if (objectType == "item") {
                    // Handle item creation
                    string itemType, ownerName, itemName;
                    int value;
                    ss >> itemType >> ownerName >> itemName >> value;
                    if (itemType == "spell") {
                        // Handle spell item creation
                        int m = value;
                        vector<string> characterNames;
                        // Parse character names
                        for (int j = 0; j < m; ++j) {
                            string characterName;
                            ss >> characterName;
                            characterNames.push_back(characterName);
                        }
                        // Call createItem function with the parsed data
                        createItem(characters, items, itemType, ownerName, itemName, value, characterNames);
                    } else {
                        // For other item types, call createItem with an empty characterNames vector
                        createItem(characters, items, itemType, ownerName, itemName, value, {});
                    }
                }
            } else if (eventType == "Attack") {
                // Handle Attack event
                string attackerName, targetName, weaponName;
                ss >> attackerName >> targetName >> weaponName;
                if (characters.find(attackerName) != characters.end() && characters.find(targetName) != characters.end()) {
                    auto attackerFighter = dynamic_pointer_cast<Fighter>(characters.at(attackerName));
                    auto attackerArcher = dynamic_pointer_cast<Archer>(characters.at(attackerName));
                    if (attackerFighter) {
                        attackerFighter->attack(*characters.at(targetName), weaponName);
                    } else if (attackerArcher){
                        attackerArcher->attack(*characters.at(targetName), weaponName);
                    }
                    else {
                        cout << "Error caught" << endl;
                    }
                } else {
                    cout << "Error caught" << endl;
                }
            } else if (eventType == "Cast") {
                // Handle Cast event
                string casterName, targetName, spellName;
                ss >> casterName >> targetName >> spellName;
                if (characters.find(casterName) != characters.end() && characters.find(targetName) != characters.end()) {
                    characters.at(casterName)->castSpell(*characters.at(targetName), spellName);
                } else {
                    throw runtime_error("Error caught\n");
                }
            }else if (eventType == "Drink") {
                // Handle Drink event
                string supplierName, drinkerName, potionName;
                ss >> drinkerName >> supplierName >> potionName;
                if (characters.find(drinkerName) != characters.end()) {
                    if (characters.find(supplierName) != characters.end()) {
                        characters.at(drinkerName)->drinkPotion(*characters.at(supplierName), potionName);
                    } else if (supplierName == drinkerName) {
                        characters.at(drinkerName)->drinkPotion(*characters.at(drinkerName), potionName);
                    } else {
                        throw runtime_error("Error caught\n");
                    }
                } else {
                    throw runtime_error("Error caught\n");
                }
            } else if (eventType == "Death") {
                string charName;
                ss >> charName;
                cout << charName << " has died..." << endl;
            } else if (eventType == "Show") {
                string showType;
                ss >> showType;
                if (showType == "characters") {
                    vector<string> aliveCharacters;
                    for (const auto& charName : characterCreationOrder) { // Iterate over the vector of character names
                        auto characterPtr = characters[charName];
                        if (characterPtr->isAlive()) {
                            aliveCharacters.push_back(characterPtr->getName());
                        }
                    }
                    sort(aliveCharacters.begin(), aliveCharacters.end()); // Sort alive characters alphabetically
 
                    // Display sorted alive characters
                    for (const string& characterName : aliveCharacters) {
                        auto characterPtr = characters[characterName];
                        string characterType;
                        if (dynamic_pointer_cast<Fighter>(characterPtr)) {
                            characterType = "fighter";
                        } else if (dynamic_pointer_cast<Wizard>(characterPtr)) {
                            characterType = "wizard";
                        } else if (dynamic_pointer_cast<Archer>(characterPtr)) {
                            characterType = "archer";
                        }
                        cout << formatCharacterOutput(characterPtr->getName(), characterType, characterPtr->getHealthPoints()) << " ";
                    }
                    cout << endl;
                } else if (showType == "weapons") {
                    string characterName;
                    ss >> characterName;
                    if (characters.find(characterName) != characters.end() ) {
                        auto fighter = dynamic_pointer_cast<Fighter>(characters.at(characterName));
                        auto archer = dynamic_pointer_cast<Archer>(characters.at(characterName));
                        if ((fighter && fighter->isAlive()) || (archer && archer->isAlive())) {
                            auto arsenal = fighter ? fighter->arsenal : archer->arsenal;
                            vector<string> weaponNames;
                            for (const auto& weapon : arsenal->weapons) {
                                weaponNames.push_back(weapon->getName());
                            }
                            sort(weaponNames.begin(), weaponNames.end()); // Sort weapon names alphabetically
 
                            // Display sorted weapon names
                            for (const string& weaponName : weaponNames) {
                                auto weapon = items[weaponName];
                                cout << formatWeaponOutput(weapon->getName(), dynamic_pointer_cast<Weapon>(weapon)->getDamageValue()) << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "Error caught" << endl;
                        }
                    } else {
                        cout << "Error caught" << endl;
                    }
                } else if (showType == "potions") {
                    // Show potions of a character
                    string characterName;
                    ss >> characterName;
                    if (characters.find(characterName) != characters.end()) {
                        auto fighter = dynamic_pointer_cast<Fighter>(characters.at(characterName));
                        auto wizard = dynamic_pointer_cast<Wizard>(characters.at(characterName));
                        auto archer = dynamic_pointer_cast<Archer>(characters.at(characterName));
                        if ((fighter && fighter->isAlive()) || (archer && archer->isAlive()) ||(wizard && wizard->isAlive())) {
                            auto medicalBag = fighter ? fighter->medicalBag : (wizard ? wizard->medicalBag : archer->medicalBag);
                            vector<string> potionNames;
                            for (const auto& potion : medicalBag->potions) {
                                potionNames.push_back(potion->getName());
                            }
                            sort(potionNames.begin(), potionNames.end()); // Sort potion names alphabetically
 
                            // Display sorted potion names
                            for (const string& potionName : potionNames) {
                                auto potion = items[potionName];
                                cout << formatPotionOutput(potion->getName(), dynamic_pointer_cast<Potion>(potion)->getHealValue()) << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "Error caught" << endl;
                        }
                    } else {
                        cout << "Error caught" << endl;
                    }
                } else if (showType == "spells") {
                    // Show spells of a character
                    string characterName;
                    ss >> characterName;
                    if (characters.find(characterName) != characters.end()) {
                        auto wizard = dynamic_pointer_cast<Wizard>(characters.at(characterName));
                        auto archer = dynamic_pointer_cast<Archer>(characters.at(characterName));
                        if ((archer && archer->isAlive()) ||(wizard && wizard->isAlive())) {
                            auto spellBook = wizard ? wizard->spellBook : archer->spellBook;
                            vector<string> spellNames;
                            for (const auto& spell : spellBook->spellSheets) {
                                spellNames.push_back(spell->getName());
                            }
                            sort(spellNames.begin(), spellNames.end()); // Sort spell names alphabetically
 
                            // Display sorted spell names
                            for (const string& spellName : spellNames) {
                                auto spell = items[spellName];
                                cout << formatSpellOutput(spell->getName(), dynamic_pointer_cast<SpellSheet>(spell)->getNumAllowedTargets()) << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "Error caught" << endl;
                        }
                    } else {
                        cout << "Error caught" << endl;
                    }
                }
                else {
                    throw runtime_error("Error caught\n");
                }
            } else {
                throw runtime_error("Error caught\n");
            }
        } catch (const exception& e) {
            // Handle exceptions
            cout << "Error caught"<<endl;
        }
    }
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    return 0;
}