#include <iostream>
using namespace std;

class Table {
    private:
        int seats_num;
        int occupied_seats = 0;
        int free_seats; // seats_num - occupied seats;
        bool isClean = 1; // yes - 1, no - 0
    
    public:
        int getSeatsNum() {
            return this -> seats_num;
        }

        void setSeatsNum(int num) {
            if (num == 4 || num == 8) {
                this -> seats_num = num;
            }
            else {
                cout << "\nInvalid number of seats selected.";
            }
        }

        int getOccupiedSeats() {
            return this -> occupied_seats;
        }

        void setOccupiedSeats(int seats) {
            this -> occupied_seats = seats;
        }

        bool getisClean() {
            return this -> isClean;
        }

        void setisClean(int cleanliness) {
            if (cleanliness == 0 || cleanliness == 1) {
                this -> isClean = cleanliness;
            }
            else {
                cout << "\nInvalid cleanliness level selected.";
            }
        }

        int getFreeSeats() {
            return this -> free_seats;
        }
        void setFreeSeats(int free) {
            this -> free_seats = free;
        }

        // default constructor
        Table() {
            seats_num = 4;
            occupied_seats = 0;
            free_seats = seats_num;
            isClean = 1;
        }

        // parameterize constructor
        Table(int capacity) {
            if (capacity > 0 && capacity <= 4) {
                seats_num = 4;
            }
            else {
                seats_num = 8; // max. seats
            }
            isClean = 1;
        }

        void useTable(Table *array, int size, int table_num) {
            int tableUsed = 0;
            for (int i = 0; i < size ; i++) {
                if ((array[i].getOccupiedSeats() == 0) && (array[i].getisClean() == 1)) {
                    tableUsed = 1;
                    cout << "\n\nYou are using Table #" << i + 1 << ".";
                    break;
                }
            }
            if (tableUsed == 0) {
                cout << "\nNo tables available right now.";
            }
        }

        void haveLunch(Table *array, int size, int table_num) {
            for (int i = 0; i < size ; i++) {
                if (i == table_num - 1) {
                    cout << "\n\nEnjoy your meal(s)!";
                    array[i].setisClean(0);
                }
            }
        }

        void cleanTable(Table *array, int size, int table_num) {
            for (int i = 0; i < size ; i++) {
                if (i == table_num - 1) {
                    cout << "\n\nThank you for cleaning the table!";
                    array[i].setisClean(1);
                }
            }
        }
};

void OccupyTable(Table *array, int size, int group_size) {
    for (int i = 0; i < size ; i++) {
        if (array[i].getOccupiedSeats() == 0) {
            if (array[i].getisClean() == 1) {
                if (group_size > 0 && group_size <= 4) {
                    array[i].setSeatsNum(4);
                }
                else {
                    array[i].setSeatsNum(8);
                }
                array[i].setOccupiedSeats(group_size);
                array[i].setFreeSeats(array[i].getSeatsNum() - group_size);
                cout << "\nAssigned table: Table #" << i + 1 << ".";
                cout << "\nTable's seating capacity: " << array[i].getSeatsNum() << "\n";
                break;
            }
            else {
                cout << "\n\nSorry, table is unclean and cannot be used.";
            }
        }
    }
}

void EmptyTable(Table *array, int size, int table_num) {
    int tableFound = 0;
    for (int i = 0; i < size ; i++) {
        if (i == table_num - 1) {
            tableFound = 1;
            array[i].setOccupiedSeats(0);
            array[i].setFreeSeats(array[i].getSeatsNum());
            cout << "\n\nTable #" << i + 1 << " successfully emptied.";
            break;
        }
    }

    if (tableFound == 0) {
        cout << "\n\nNo such table exists.";
    }
}

int main () {
    cout << "23K-0672\t\tSyeda Batool Kazmi\n";
    
    Table myTables[5];
    myTables[0].setSeatsNum(8);
    myTables[1].setSeatsNum(8);
    myTables[2].setSeatsNum(4);
    myTables[3].setSeatsNum(4);
    myTables[4].setSeatsNum(4);

    OccupyTable(myTables, 5, 4);
    OccupyTable(myTables, 5, 6);

    myTables -> useTable(myTables, 5, 1);
    myTables -> haveLunch(myTables, 5, 1);
    EmptyTable(myTables, 5, 1);
    myTables -> cleanTable(myTables, 5, 1);

    EmptyTable(myTables, 5, 2);

    return 0;
}