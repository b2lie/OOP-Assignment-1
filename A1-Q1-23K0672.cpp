#include <iostream>
using namespace std;

class Pet {
    private:
        string species = " ";
        string healthStatus = "Healthy"; // default status
        int hungerLevel = 5; // default hunger & happiness
        int happinessLevel = 5;
        string *specialSkills = new string[5]; // max. possible skills = 5

    public:
        string getSpecies() {
            return this -> species;
        }
            
        void setSpecies(string animal) {
            this -> species = animal;
        }
            
        string gethealthStatus() {
            return this -> healthStatus;
        }

        void sethealthStatus(string status) {
            this -> healthStatus = status;
        }

        int gethappinessLevel() {
            return this -> happinessLevel; 
        }

        void sethappinessLevel(int lvl) {
            this -> happinessLevel = lvl;
        }

        void incHappinessLevel(int inc) {
            this -> happinessLevel += inc;
        }

        int gethungerLevel() {
            return this -> hungerLevel; 
        }

        void sethungerLevel(int inc) {
            this -> hungerLevel += inc;
        }

        void setspecialSkills(int i, string skillname) {
            if (i >= 0 && i < 5) {
                this -> specialSkills[i] = skillname;
            }
        }

        string * getspecialSkills(int j) {
            return &(this -> specialSkills[j]);
        }

        void displayPetDetails() {
            cout << "\n\nDisplaying your Pet's Details:\n";
            cout << "\n\tHealth Status: " << healthStatus;
            cout << "\n\tHunger Level: " << hungerLevel;
            cout << "\n\tHappiness Level: " << happinessLevel;
            cout << "\n\tSpecial Skills: \n";
            for (int i = 0; i < 5; i++) {
                if (!specialSkills[i].empty()) {
                    cout << "\t" << i + 1 << ". "  << specialSkills[i];
                }
            }
        }

        void updateHappiness(char interaction) { // pass Y to feed, N to ignore request
            if ((happinessLevel < 10 && happinessLevel >= 0) && (hungerLevel < 10 && hungerLevel >= 0)) {
                if (interaction == 'Y') {
                    incHappinessLevel(1);
                }
                else if (interaction == 'N') {
                    incHappinessLevel(-1);
                }
                else {
                    cout << "Invalid request. Pet was not interactd with.\n";
                }
            }

            cout << "\nCurrent Happiness Level: " << happinessLevel << endl;

            if (happinessLevel > 5 && happinessLevel <= 10) {
                cout << "Your pet is feeling fuller now and is super happy ^-^!!";
            }

            if (happinessLevel >= 0 && happinessLevel <= 5 ) {
                cout << "Your pet is upset :( You should feed it to make it happy.";
                updateHunger();
            }
        }

        void updateHealth() {
            if (happinessLevel < 5 || happinessLevel < 5) { 
            // checking unhappiness too b/c it can be a common sign for sickness in pets
                sethealthStatus("Sick");
            }
            else {
                sethealthStatus("Healthy");
            }
        }
        
        void updateHunger() {
            char choice;
            cout << "\n\nWould you like to feed your pet? (Y - yes / N - no)\n";
            cin >> choice;
            getchar();
            updateHappiness(choice);
        }
};

const int max_pets = 4;

class Adopter {
        private:
            string adopterName;
            string adopterMobileNum; // keeping it a string for functionality
            int curr_pets = 0;
            int x = 0;
            Pet *adoptedPetRecords[max_pets];

        public:
            Adopter (string name, string num) { // paramterized constructor
                adopterName = name;
                adopterMobileNum = num;
                for (int i = 0; i < max_pets; ++i) {
                    adoptedPetRecords[i] = new Pet;
                }
            }

            ~Adopter() { // destructor to remove pet records via dma
                for (int i = 0; i < max_pets; ++i) {
                    delete adoptedPetRecords[i];
                }
            }

            string getadopterName() {
                return this -> adopterName;
            }
            
            void adoptPet() {
                cout << "\nThanks for adopting a pet! Please enter it's details here: " << endl;
                string species, skill;
                cout << "Species (a.k.a. animal type): ";
                getline(cin, species);

                adoptedPetRecords[x] -> updateHealth();
                adoptedPetRecords[x] -> setSpecies(species);

                cout << "Enter skills here (or type ' ' to stop): \n";
                int skills_num = 0;
                while (skills_num < 5 && x < max_pets) {
                    cout << "\tSkill #" << skills_num + 1 << ": ";
                    getline(cin, skill);
                    if (skill == " ") {
                        break;
                    }
                    adoptedPetRecords[x] -> setspecialSkills(skills_num, skill);
                    skills_num++;
                }
                x++;
            }

            void returnPet() {
                string name;
                cout << "\n\nProcessing 'return pet' request . . .";
                cout << "\nEnter pet name to return it: ";
                getline(cin, name);

                int flag = 0;
                for (int i = 0; i < max_pets; i++) {
                    if (adoptedPetRecords[i] -> getSpecies() == name) {
                        adoptedPetRecords[i] -> setSpecies(" ");
                        adoptedPetRecords[i] -> sethappinessLevel(0);
                        adoptedPetRecords[i] -> sethealthStatus("Healthy");
                        adoptedPetRecords[i] -> sethungerLevel(5);
                        for (int j = 0; j < 5; j++) {
                            adoptedPetRecords[i] -> setspecialSkills(j, "");
                        }
                        cout << "\nPet successfully returned.";
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    cout << "\nInvalid pet name. Pet could not be returned.";
                }
            }

            void displayAdoptedPets() {
                cout << "\n\nPets adopted by: " << adopterName << endl;
                for (int i = 0; i < max_pets; i++) {
                    if (adoptedPetRecords[i] -> getSpecies() != " ") {
                        cout << "\nPet #" << i + 1 << ":\nName: " << adoptedPetRecords[i] -> getSpecies();
                        cout << "\n\tHappiness: " << adoptedPetRecords[i] -> gethappinessLevel();
                        cout << "\n\tHealth: " << adoptedPetRecords[i] -> gethealthStatus();
                        cout << "\n\tHunger: " << adoptedPetRecords[i] -> gethungerLevel();
                        cout << "\n\tSkills:";
                        for (int j = 0; j < 5; j++) {
                            string skill = *(adoptedPetRecords[i] -> getspecialSkills(j));
                            if (!skill.empty()) { 
                                // checks whether innput is blank, else it'd keep printing till skill #5 unnecessarily
                                cout << "\n\t\t#" << j + 1 << ": " << skill;
                            }
                        }
                    }
                }
            }
};

int main () {
    Pet p1, p2;
    Adopter a1("Batool", "123"), a2("Zainab", "234");

    cout << "Please remember: you can only assign 5 Special Skills (maximum) to your pets." << endl;
    
    a1.adoptPet(); // pets adopted by batool
    a1.adoptPet();
    a2.adoptPet();

    a1.returnPet(); // pet returned by batool
    a1.displayAdoptedPets();
    p1.updateHunger();

    a2.displayAdoptedPets();
    p2.updateHunger();

    p1.displayPetDetails(); // batool's pets displayed
    p2.displayPetDetails();

    return 0;
}
