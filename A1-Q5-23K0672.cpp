#include <iostream>
#include <string>
using namespace std;

class Restaurant {
private:
    string restaurant_name;
    string location;
    string* menu_list;
    float* price_list;
    string* valid_coupon_codes_list;
    static int coupons_redeemed_count;
    const float discount;

public:
    string getName() const {
        return restaurant_name;
    }

    string getLoc() {
        return location;
    }

    const string* getMenu() {
        return this->menu_list;
    }

    const float* getPrices() {
        return this->price_list;
    }

    const string* getValidCoupons() {
        return this->valid_coupon_codes_list;
    }

    void incrementCount() {
        this->coupons_redeemed_count++;
    }

    // default constructor with array initialization
    Restaurant(string name = "", string loc = "") : discount(0.25) { // gives 25% off by default as discounts weren't specified for every coupon 
        restaurant_name = name;
        location = loc;
        menu_list = nullptr;
        price_list = nullptr;
        valid_coupon_codes_list = nullptr;
        coupons_redeemed_count = 0;
    }

    // destructor to release used memory
    ~Restaurant() {
        delete[] menu_list;
        delete[] price_list;
        delete[] valid_coupon_codes_list;
    }

    void setMenu(int items) {
        if (items > 0) {
            menu_list = new string[items];
            cout << "\nPlease start entering items available on your menu:\n";
            for (int i = 0; i < items; i++) {
                string itemName;
                cout << "\t" << i + 1 << ". ";
                getline(cin, itemName);
                menu_list[i] = itemName;
            }
            price_list = new float[items];
            cout << "\nPlease enter the prices for all corresponding menu items:\n";
            cout << "\nItem\t\t\tPrice\n\n";
            for (int i = 0; i < items; i++) {
                float cost;
                cout << menu_list[i] << "\t\t\t";
                cin >> cost;
                if (cost > 0.0) {
                    price_list[i] = cost;
                }
                cin.ignore(); // consumes new line char
            }
            cout << "\nYour restaurant menu has been updated.\n";
        }
        else {
            cout << "\nInvalid menu items chosen.";
        }
    }

    int setCouponList() {
        int count = 0;
        string couponCode;

        cout << "\nPlease enter valid coupon codes users can redeem (or type '-1' to stop): \n";

        while (1) {
            cout << "Code #" << count + 1 << ". ";
            getline(cin, couponCode);
            if (couponCode == "-1") {
                break;
            }

            string* updateValidCoupons = new string[count + 1];
            for (int i = 0; i < count; i++) { // copying existing coupons (if any)
                updateValidCoupons[i] = valid_coupon_codes_list[i];
            }

            updateValidCoupons[count] = couponCode;
            count++;

            delete[] valid_coupon_codes_list;
            valid_coupon_codes_list = updateValidCoupons;
        }
        cout << "\nValid restaurant coupons have been updated.\n";
        return count;
    }

    void display_menu(int items) {
        cout << "\nDisplaying Restaurant Menu:\n";
        cout << "\nItem\t\t\tPrice\n\n";
        for (int i = 0; i < items; i++) {
            cout << menu_list[i] << "\t\t\t" << price_list[i] << endl;
        }
    }

    void generate_bill(int items, string coupon_code) {
        float totalBill = 0.0;
        string item;

        cout << "\nWelcome! I will be taking your order for " << restaurant_name << " at " << location << ".\n"
            << "Press -1 to stop entering items.\n" << endl;

        bool itemFound = false;
        for (int i = 0; i < items; i++) {
            cout << "Item " << i + 1 << ". ";
            getline(cin, item);

            if (item == "-1") {
                break;
            }
            for (int j = 0; j < items; j++) {
                if (item == menu_list[j]) {
                    itemFound = true;
                    totalBill += price_list[j];
                    break;
                }
            }
        }

        if (!itemFound) {
            cout << "Invalid item entered: " << item << endl;
        }

        bool isDiscounted = false;
        for (int j = 0; j < items; j++) {
            if (coupon_code == valid_coupon_codes_list[j]) {
                cout << "\nTotal Bill Generated: " << apply_discount(totalBill);
                isDiscounted = true;
                break;
            }
        }
        if (!isDiscounted) {
            cout << "\nTotal Bill Generated: " << totalBill;
        }
    }

    float apply_discount(float bill) {
        return bill * (1.0 - discount);
    }
};

int Restaurant::coupons_redeemed_count = 0;
const int maxBOGOCoupons = 10;

class BOGOCoupon {
private:
    string coupon_code;
    string valid_from;
    string valid_until;
    string restaurant_code;

public:
    string getCouponCode() {
        return this->coupon_code;
    }

    string getRestaurantCode() {
        return this->restaurant_code;
    }

    BOGOCoupon(string code = "", string from_date = "dd-mm-yy", string until_date = "dd-mm-yy", string prefix = "XY") {
        // date format: dd-mm-yy
        coupon_code = code;
        valid_from = from_date;
        valid_until = until_date;
        restaurant_code = prefix;
    }

    bool is_valid(string current_date, string code) {
        // date format: dd-mm-yy
        int from_day = (valid_from[0] - '0') * 10 + (valid_from[1] - '0');
        int from_month = (valid_from[3] - '0') * 10 + (valid_from[4] - '0');
        int from_year = (valid_from[6] - '0') * 10 + (valid_from[7] - '0');

        int to_day = (valid_until[0] - '0') * 10 + (valid_until[1] - '0');
        int to_month = (valid_until[3] - '0') * 10 + (valid_until[4] - '0');
        int to_year = (valid_until[6] - '0') * 10 + (valid_until[7] - '0');

        int curr_day = (current_date[0] - '0') * 10 + (current_date[1] - '0');
        int curr_month = (current_date[3] - '0') * 10 + (current_date[4] - '0');
        int curr_year = (current_date[6] - '0') * 10 + (current_date[7] - '0');

        for (int i = 0; i < maxBOGOCoupons; i++) {
            if (code == coupon_code) {
                // if ((curr_day >= from_day && curr_day <= to_day) && (curr_month >= from_month && curr_month <= to_month)
                //     && (curr_year >= from_year && curr_year <= to_year)) {
                if ((curr_year > from_year || (curr_year == from_year && curr_month > from_month) || (curr_year == from_year && curr_month == from_month && curr_day >= from_day))
        && (curr_year < to_year || (curr_year == to_year && curr_month < to_month) || (curr_year == to_year && curr_month == to_month && curr_day <= to_day))) {

                    string check_code = "";
                    for (int i = 0; i < 2 && i < coupon_code.length(); i++) {
                        if (coupon_code[i] >= 'A' && coupon_code[i] <= 'Z') {
                            check_code += coupon_code[i];
                        }
                    }
                    return (check_code == restaurant_code); // will return true if correct
                }
                return false;
            }
        }
    }
};

class User {
private:
    string name;
    int age;
    string mobile_number;
    BOGOCoupon* coupons_list; // coupons the user already has
    string* redeemed_coupons_list; // coupons redeemed by the user
    int coupon_count;
    Restaurant thisRestaurant;

public:
    const Restaurant& getThisRestaurant() const {
        return thisRestaurant;
    }

    User(string userName = "", int userAge = 20, string mobnum = "+92 xxx xxxxxxx") {
        name = userName;
        age = userAge;
        mobile_number = mobnum;
        coupons_list = nullptr;
        redeemed_coupons_list = new string[maxBOGOCoupons];
        for (int i = 0; i < maxBOGOCoupons; ++i) {
            redeemed_coupons_list[i] = "";
        }
        coupon_count = 0;
    }

    ~User() {
        delete[] coupons_list;
        delete[] redeemed_coupons_list;
    }

    void accumulate_coupon(BOGOCoupon userCoupon) {
        BOGOCoupon* updateCouponsList = new BOGOCoupon[coupon_count + 1];
        for (int i = 0; i < coupon_count; i++) {
            updateCouponsList[i] = coupons_list[i]; // copying existing coupons (if any)
        }
        updateCouponsList[coupon_count] = userCoupon;
        coupon_count++;
        delete[] coupons_list;
        coupons_list = updateCouponsList;
    }

    bool has_valid_coupon(string currDate, string code, string item, int menuSize, Restaurant restaurant) {
        // validates and checks if coupon hasn't been redeemed already for a specific restaurant's item
        for (int i = 0; i < coupon_count; i++) {
            BOGOCoupon coupon = coupons_list[i];
            const string* menu_list = restaurant.getMenu();
            bool itemAvailable = false;
            for (int j = 0; j < menuSize; ++j) {
                if (menu_list[j] == item) {
                    itemAvailable = true;
                    break;
                }
            }
            if ((itemAvailable) && (coupon.is_valid(currDate, code)) && (coupon.getCouponCode() == code)) {
                return true;
            }
        }
        return false;
    }

    bool redeem_coupon(string currDate, string code, int menuSize, Restaurant &restaurant) {
    for (int i = 0; i < coupon_count; i++) {
        BOGOCoupon coupon = coupons_list[i];
        if (coupon.is_valid(currDate, code)) {
            if (redeemed_coupons_list[i] != coupon.getCouponCode()) {
                redeemed_coupons_list[i] = coupon.getCouponCode();
                restaurant.incrementCount();
                return true; 
            } else {
                cout << "\nCoupon has already been redeemed.\n";
                return false; 
            }
        }
    }
        cout << "\n\nInvalid or expired coupon.\n";
        return false; 
    }
};

int main() {
    Restaurant r1("Food Haven", "City Center");
    r1.setMenu(3);
    r1.setCouponList();
    r1.display_menu(3);
    r1.generate_bill(3, "FH-BOGO-12345");

    BOGOCoupon b1("FH-BOGO-12345", "20-01-22", "30-03-25", "FH");
    User u1("Batool", 18, "+54 333 2228589");
    bool couponRedeemedu1 = u1.redeem_coupon("26-02-24", "FH-BOGO-12345", 3, r1);
    if (!couponRedeemedu1) {
        cout << "Coupon could not be redeemed.\n";
    }
    else {
        cout << "Coupon successfully redeemed.\n";
    }

    Restaurant r2("Pixel Bites", "Cyber Street");
    r2.setMenu(3);
    r2.setCouponList();
    r2.display_menu(3);
    r2.generate_bill(3, "PB-BOGO-67890");

    BOGOCoupon b2("PB-BOGO-67890", "20-01-22", "30-03-25", "PB");
    User u2("Rida", 17, "+54 321 2013050");
    bool couponRedeemedu2 = u2.redeem_coupon("26-02-24", "PB-BOGO-67890", 3, r2);
    if (!couponRedeemedu2) {
        cout << "Coupon could not be redeemed.\n";
    }
    else {
        cout << "Coupon successfully redeemed.\n";
    }

    return 0;
}
