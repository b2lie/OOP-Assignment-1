#include <iostream>
using namespace std;

class RollerCoaster {
    private:
        string name;
        float height, length;
        int capacity, speed;
        int currentNumRiders = 0;
        bool rideInProgress;

    public:
        RollerCoaster() {
            name = "roller coaster";
            height = 500.0;
            length = 2000.0;
            capacity = 20;
            rideInProgress = false;
        }

        RollerCoaster(string rcName, float rcHeight, float rcLength, int rcCapacity) {
            name = rcName;
            height = rcHeight;
            length = rcLength;
            if (rcCapacity > 3) {
                if ((rcCapacity % 2 != 0) || (rcCapacity % 3 != 0)) {
                    rcCapacity = (rcCapacity / 2);
                    rcCapacity *= 2;
                }
                capacity = rcCapacity;
            }
            else {
                cout << "\nSeat capacity has to be greater than 3.";
            }
            
        }

        string getName() {
            return this -> name;
        }

        void setName(string rcName) {
            this -> name = rcName;
        }

        float getHeight() {
            return this -> height;
        }

        void setHeight(float rcHeight) {
            this -> height = rcHeight;
        }

        float getLength() {
            return this -> length;
        }

        void setLength(float rcLength) {
            this -> length = rcLength;
        }

        int getSpeed() {
            return this -> speed;
        }

        void setSpeed(int rcSpeed) {
            this -> speed = rcSpeed;
        }

        void increaseSpeed(int inc) {
            this -> speed += inc;
        }

        void decreaseSpeed(int dec) {
            this -> speed -= dec;
        }

        int getCapacity() {
            return this -> capacity;
        }

        void setCapacity(int rcCapacity) {
            if ((rcCapacity > 3) && ((rcCapacity % 2 != 0) || (rcCapacity % 3 != 0))) {
                rcCapacity = (rcCapacity / 2);
                this -> capacity = rcCapacity *= 2;
            }
            else {
                cout << "Invalid capacity entered.";
            }
        }

        int getcurrentNumRiders() {
            return this -> currentNumRiders;
        }

        void setcurrentNumRiders(int rcRiders) {
            this -> currentNumRiders = rcRiders;
        }

        bool getrideInProgress() {
            return this -> rideInProgress;
        }

        bool setrideInProgress(bool choice) {
            this -> rideInProgress = choice;
        }

        int seatRiders(int rcRiders) {
            if (!rideInProgress) {
                if (rcRiders <= capacity) {
                    setcurrentNumRiders(rcRiders);
                    cout << "\n\nAll riders are seated in "<< capacity << " no. of seats.";
                    return 0;
                }
                else {
                    int notSeated = rcRiders - capacity;
                    setcurrentNumRiders(capacity);
                    cout << "\n\nNo. of riders that couldn't be seated: " << notSeated;
                    return notSeated;
                }
            }
            else {
                cout << "\n\nRide is currently in progress. Please wait for your turn.";
            }
        }

        int startRide() {
            if (!rideInProgress) {
                if (currentNumRiders == capacity) {
                    setrideInProgress(true);
                    cout << "\n\nAll seats have been occupied by the riders.\n";
                }
                else {
                    int emptySeats = capacity - currentNumRiders;
                    cout << "\n\nNo. of empty seats: " << emptySeats << "\n";
                    return emptySeats;
                }
            }
            else {
                setrideInProgress(true);
                cout << "\n\nRide is currently in progress.";
                return -1;
            }
        }

        void stopRide() {
            if (rideInProgress) {
                rideInProgress = !rideInProgress;
                cout << "\n\nRide has stopped.";
            }
        }

        void unloadRide() {
            if (!rideInProgress) {
                setcurrentNumRiders(0);
                cout << "\n\nRiders have unboarded successfully.";
            }
            else {
                cout << "\n\nCannot unboard yet. Ride is still in progress.";
            }
        }

        void accelerateCoaster(string rollNum) {
            for (int i = rollNum.length() - 1; i >= 0; i--) {
                int digit = rollNum[i] - '0';
                if (digit == 0) {
                    continue;
                }
                else {
                    increaseSpeed(digit);
                    cout << "\nSpeed increased by: " << digit;
                    cout << "\nCurrent speed: " << getSpeed();
                    break;
                }
            }
        }

        void decelerateCoaster(string rollNum) {
            for (int i = 0; i < rollNum.length(); i++) {
                int digit = rollNum[i] - '0';
                if (digit == 0) {
                    continue;
                }
                else {
                    decreaseSpeed(digit);
                    cout << "\n\nSpeed decreased by: " << digit;
                    cout << "\nCurrent speed: " << getSpeed();
                    break;
                }
            }
        }
};

int main () {
    cout << "23K-0672\t\tSyeda Batool Kazmi\n";

    RollerCoaster coaster1;
    RollerCoaster coaster2("My Roller Coaster", 80.5, 70.25, 6);

    coaster2.setSpeed(2000);
    coaster2.seatRiders(9);

    coaster2.startRide();
    coaster2.accelerateCoaster("0672");

    coaster2.startRide(); // shows that ride that's still in progress can't be "started"
    coaster2.unloadRide(); // shows that a moving ride cannot be unloaded

    coaster2.decelerateCoaster("0672");
    coaster2.stopRide();
    
    coaster2.unloadRide();

    return 0;
}