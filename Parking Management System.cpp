#include <iostream>
#include <string>
#include <vector>
using namespace std;

	int id = 1;
			int total_earnings = 0;
const string admin_password = "admin123";

// Forward declaration of classes
class Floor;
class Building;
class Location;
class Vehicle;

// Global vector  store vehicle records   : ALTERNATE OF ARRAY
vector<Vehicle> vehicle_list;

class Floor {
public:
int visited[11][11];
int number_of_vehicles;
 int floor_number; 
    Floor(int floor_number) : floor_number(floor_number) 
	{ 
        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                visited[i][j] = 0;
            }
        }
        number_of_vehicles = 0;
    }

    void display() {
        cout << endl;
    for (int i = 1; i <= 10; i++) {
        cout << "\t\t\t\t";
 	for (int j = 1; j <= 10; j++) {
    	if (visited[i][j] != 0)
            cout << "||  "; // filled spot
         else
                    cout << "**  "; // available spot
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Building {
public:
    string bname;
    Floor f1, f2, f3;

    Building(string bname) : bname(bname), f1(1), f2(2), f3(3) {} 

    string getname() {
        return bname;
 }
};

class Location {
public:
    Floor* floor;
    int x;
    int y;
};

class Vehicle {
public:
    int type_of_vehicle;
    long long phone_no;
    string vehicle_no;
    bool is_self_drive;
    int duration;
    int charges;
    Location of_this_vehicle;
    int id_no;

    Vehicle(int type_of_vehicle, long long phone_no, string vehicle_no, bool is_self_drive, int duration) {
        this->type_of_vehicle = type_of_vehicle;
        this->phone_no = phone_no;
        this->vehicle_no = vehicle_no;
        this->is_self_drive = is_self_drive;
        this->duration = duration;

   if (type_of_vehicle == 2) {
       this->charges = duration * 15;
    } else {
       this->charges = duration * 30;
        }
        this->id_no = id;
total_earnings += this->charges;
        vehicle_list.push_back(*this);
    }

    void get_E_slip() {
        cout << endl << "\t\t\t\t\t\t\t\t**** E-Slip ****" << endl;
        cout << "\t\t\t======================================================================================" << endl;
        cout << "\t\t\t\t         Vehicle Number      : " << vehicle_no << endl;
        cout << "\t\t\t\t         Phone Number        : " << phone_no << endl;
        cout << "\t\t\t\t         Duration of Parking : " << duration << " Hours" << endl;
        cout << "\t\t\t\t         Charges             : " << charges << "$" << endl;
        cout << "\t\t\t\t         Id                  : " << id_no << endl;
        cout << "\t\t\t\t         Location of Vehicle : ";

        cout << "Floor " << of_this_vehicle.floor->floor_number << ", ";
        cout << "Coordinates are (" << of_this_vehicle.x << "," << of_this_vehicle.y << ")" << endl;
        cout << "\t\t\t======================================================================================" << endl << endl;
    }
};

Location getlocation(Floor& datum) {
    Location now;
    now.floor = &datum;
    int flag = 0;

    for (int i = 1; i <= 10 && flag == 0; i++) {
        for (int j = 1; j <= 10 && flag == 0; j++) {
        if (datum.visited[i][j] != 0) {
             continue;
            } else {
         datum.visited[i][j] = id;
      now.x = i;
        now.y = j;
                flag = 1;
            }
        }
    }
    return now;
}

class Administrator : public Vehicle {
private:
    string password;

public:
    Administrator(int type_of_vehicle, long long phone_no, string vehicle_no, bool is_self_drive, int duration) :
        Vehicle(type_of_vehicle, phone_no, vehicle_no, is_self_drive, duration) {
        set_password();
    }

    void set_password() {
    string s;
    for (int i = 0; i < vehicle_no.size(); i++) {
	s.push_back(vehicle_no[vehicle_no.size() - 1 - i]);
        }
        password = s;
    }

    void display_admin() {
        cout << "\t\t\tEnter Pass key of this Vehicle : ";
        string pass_key;
        cin >> pass_key;
        if (pass_key == password) {
            cout << endl << "\t\t\t\t     ** DETAILS OF THE VEHICLE **   " << endl;
            cout << "\t\t===========================================================================" << endl;
            cout << "\t\t\t    Vehicle No          : " << vehicle_no << endl;
            cout << "\t\t\t    Phone No            : " << phone_no << endl;
            cout << "\t\t\t    Duration of Parking : " << duration << " Hours" << endl;
            cout << "\t\t===========================================================================" << endl << endl;
        } else {
            cout << "\n\t\t\t\t*** INVALID PASS KEY ***" << endl;
        }
    }

    void book_slot(Building& park) {
        cout << "\t\t\tSelect Floor (1/2/3): ";
        int floor_choice;
        cin >> floor_choice;

        if (floor_choice < 1 || floor_choice > 3) {
            cout << "\t\t\tInvalid Floor Selection!" << endl;
            return;
        }

        Floor* selected_floor;
        if (floor_choice == 1) {
            selected_floor = &park.f1;
        } else if (floor_choice == 2) {
            selected_floor = &park.f2;
        } else { 
            selected_floor = &park.f3;
        }

        // Display  floor layout before booking
        selected_floor->display();

        Location location = getlocation(*selected_floor);
        of_this_vehicle = location;

        // Display the selected floor layout after booking
        selected_floor->display();

        cout << "\t\t\tSlot booked successfully!" << endl;
    }
};

bool admin_login() {
    cout << "\t\t\t\tEnter Admin Password: ";
    string input_password;
    cin >> input_password;
    if (input_password == admin_password) {
        return true;
    } else {
        cout << "\n\t\t\t\t*** INVALID ADMIN PASSWORD ***\n";
        return false;
    }
}

void update_vehicle() {
    cout << "\t\t\tEnter Vehicle ID to update: ";
    int update_id;
    cin >> update_id;
    bool found = false;
for (vector<Vehicle>::iterator it = vehicle_list.begin(); it != vehicle_list.end(); ++it) {
        Vehicle& v = *it;
        if (v.id_no == update_id) {
            found = true;
            cout << "\t\t\tEnter new Phone Number: ";
            cin >> v.phone_no;
            cout << "\t\t\tEnter new Duration of Parking (In Hours): ";
            cin >> v.duration;
            v.charges = (v.type_of_vehicle == 2 ? v.duration * 15 : v.duration * 30);
            cout << "\t\t\tVehicle data updated successfully!" << endl;
            break;
        }
    }
    if (!found) {
    cout << "\t\t\tVehicle ID not found!" << endl;
    }
}

void delete_vehicle() {
cout << "\t\t\tEnter Vehicle ID to delete: ";
    int delete_id;
    cin >> delete_id;

    bool found = false;
    for (int i = 0; i < vehicle_list.size(); ++i) {
        if (vehicle_list[i].id_no == delete_id) {
	vehicle_list.erase(vehicle_list.begin() + i);
	found = true;
            cout << "\t\t\tVehicle record deleted successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "\t\t\tVehicle ID not found!" << endl;
    }
}

void search_vehicle() {
    cout << "\t\t\tEnter Vehicle ID to search: ";
    int search_id;
    cin >> search_id;
    bool found = false;
    for (vector<Vehicle>::iterator it = vehicle_list.begin(); it != vehicle_list.end(); ++it) {
        Vehicle& v = *it;
        if (v.id_no == search_id) {
            found = true;
            cout << "\t\t\tVehicle No: " << v.vehicle_no << endl;
            cout << "\t\t\tPhone No: " << v.phone_no << endl;
            cout << "\t\t\tDuration: " << v.duration << " Hours" << endl;
            cout << "\t\t\tCharges: " << v.charges << endl;
            cout << "\t\t\tLocation: Floor " << v.of_this_vehicle.floor->floor_number << ", Coordinates: (" << v.of_this_vehicle.x << "," << v.of_this_vehicle.y << ")" << endl;
            break;
        }
    }
    if (!found) {
        cout << "\t\t\tVehicle ID not found!" << endl;
    }
}

void display_all_customers() {
    cout << "\t\t\t---------------------- All Customers ----------------------" << endl;
    for (vector<Vehicle>::iterator it = vehicle_list.begin(); it != vehicle_list.end(); ++it) {
        Vehicle& v = *it;
        cout << "\t\t\tVehicle ID: " << v.id_no << endl;
        cout << "\t\t\tVehicle No: " << v.vehicle_no << endl;
        cout << "\t\t\tPhone No: " << v.phone_no << endl;
        cout << "\t\t\tDuration: " << v.duration << " Hours" << endl;
        cout << "\t\t\tCharges: " << v.charges << endl;
        cout << "\t\t\tLocation: Floor " << v.of_this_vehicle.floor->floor_number << ", Coordinates: (" << v.of_this_vehicle.x << "," << v.of_this_vehicle.y << ")" << endl;
        cout << "\t\t\t--------------------------------------------------------------------------------------" << endl;
    }
}

int main() {
    system("Color 4F");
    cout << "\t\t\t==================================================================================\n";
    cout << "\t\t\t*                                                                                *\n";
    cout << "\t\t\t*                               PARKING MANAGEMENT SYSTEM                        *\n";
    cout << "\t\t\t*                                                                                *\n";
    cout << "\t\t\t==================================================================================\n";

    Building park("Parking House");

    while (1) {
        cout << "\t\t\t=====================================================================\n";
        cout << "\t\t\t*                    Welcome to Parking Management System           *\n";
        cout << "\t\t\t* 1. Park Vehicle                                                   *\n";
        cout << "\t\t\t* 2. View Parking Slot Status                                       *\n";
        cout << "\t\t\t* 3. Admin Login                                                    *\n";
        cout << "\t\t\t* 4. Display All Customers                                          *\n";
        cout << "\t\t\t* 5. Exit                                                           *\n";
        cout << "\t\t\t=====================================================================\n";
        cout << "\t\t\tSelect an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\t\t\tEnter Vehicle Number: ";
            string vehicle_no;
            cin >> vehicle_no;
            cout << "\t\t\tEnter Phone Number: ";
            long long phone_no;
            cin >> phone_no;
            cout << "\t\t\tType of Vehicle (2/4): ";
            int type_of_vehicle;
            cin >> type_of_vehicle;
            bool is_self_drive = false;
            if (type_of_vehicle == 4) {
                cout << "\t\t\tIs the vehicle self-driven? (1 for Yes / 0 for No): ";
                cin >> is_self_drive;
            }
            cout << "\t\t\tDuration of Parking (In Hours): ";
            int duration;
            cin >> duration;

            Vehicle new_vehicle(type_of_vehicle, phone_no, vehicle_no, is_self_drive, duration);

            cout << "\t\t\tSelect Floor (1/2/3): ";
            int floor_choice;
            cin >> floor_choice;
            if (floor_choice == 1) {
                park.f1.display(); // Display the floor layout before booking
                new_vehicle.of_this_vehicle = getlocation(park.f1);
                park.f1.display(); // Display the floor layout after booking
            } else if (floor_choice == 2) {
                park.f2.display(); 
                new_vehicle.of_this_vehicle = getlocation(park.f2);
                park.f2.display(); 
            } else if (floor_choice == 3) {
                park.f3.display(); 
                new_vehicle.of_this_vehicle = getlocation(park.f3);
                park.f3.display(); 
            } else {
                cout << "\t\t\tInvalid Floor Selection!" << endl;
                continue;
            }

            id++;
            new_vehicle.get_E_slip();
        } else if (choice == 2) {
            cout << "\t\t\tSelect Floor (1/2/3): ";
            int floor_choice;
            cin >> floor_choice;
            if (floor_choice == 1) {
                park.f1.display();
            } else if (floor_choice == 2) {
                park.f2.display();
            } else if (floor_choice == 3) {
                park.f3.display();
            } else {
                cout << "\t\t\tInvalid Floor Selection!" << endl;
            }
        } else if (choice == 3) {
            if (admin_login()) {
                int admin_choice;
                do {
                    cout << "\t\t\t=====================================================================\n";
                    cout << "\t\t\t*                    Welcome Admin                                  *\n";
                    cout << "\t\t\t* 1. Update Vehicle Record                                         *\n";
                    cout << "\t\t\t* 2. Delete Vehicle Record                                         *\n";
                    cout << "\t\t\t* 3. Search Vehicle                                                *\n";
                    cout << "\t\t\t* 4. Book Parking Slot                                             *\n"; 
                    cout << "\t\t\t* 5. Display All Customers                                         *\n";
                    cout << "\t\t\t* 6. Logout                                                        *\n";
                    cout << "\t\t\t=====================================================================\n";
                    cout << "\t\t\tSelect an option: ";
                    cin >> admin_choice;

                    switch (admin_choice) {
                        case 1:
                            update_vehicle();
                            break;
                        case 2:
                            delete_vehicle();
                            break;
                        case 3:
                            search_vehicle();
                            break;
                        case 4:
                            {
                                Administrator admin(0, 0, "", false, 0); // Temporary admin object to access book_slot method
                                admin.book_slot(park);
                            }
                            break;
                        case 5:
                            display_all_customers();
                            break;
                        case 6:
                            cout << "\t\t\tAdmin Logged out successfully!" << endl;
                            break;
                        default:
                            cout << "\t\t\tInvalid Option!" << endl;
                    }
                } while (admin_choice != 6);
            }
        } else if (choice == 4) {
            display_all_customers();
        } else if (choice == 5) {
            cout << "\t\t\tThank you for using Parking Management System. Goodbye!" << endl;
            break;
        } else {
            cout << "\t\t\tInvalid Choice! Please select again." << endl;
        }
    }
    return 0;
}

