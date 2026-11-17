#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

const double G = 9.81;
const double PI = 3.14159265358979323846;

// --- 
void calculate_multimeter() {
    double nominal_ohms, tolerance_pct, measured_ohms, battery_voltage;

    cout << "\nEnter nominal resistance (ohms): ";
    cin >> nominal_ohms;
    cout << "Enter tolerance (%): ";
    cin >> tolerance_pct;
    cout << "Enter measured resistance (ohms): ";
    cin >> measured_ohms;
    cout << "Enter battery voltage (V): ";
    cin >> battery_voltage;

    if (nominal_ohms <= 0 || tolerance_pct < 0 || measured_ohms <= 0 || battery_voltage <= 0) {
        cout << "Error: Resistance and voltage must be > 0." << endl;
        return; 
    }

    double error_pct = ((measured_ohms - nominal_ohms) / nominal_ohms) * 100.0;
    bool is_in_spec = (abs(error_pct) <= tolerance_pct);
    double current_amps = battery_voltage / measured_ohms;
    double current_mA = current_amps * 1000.0;
    double power_mW = battery_voltage * current_mA;

    cout << "\n--- Multimeter Report ---" << endl;
    cout << "Error percentage: " << error_pct << "%" << endl;
    cout << "Is in specification: " << (is_in_spec ? "Yes (IN-SPEC)" : "No (OUT-OF-SPEC)") << endl;
    cout << "Current: " << current_mA << " mA (" << current_amps << " A)" << endl;
    cout << "Power: " << power_mW << " mW" << endl;
}

// --- MODULE 2: 
void calculate_speed_normalizer() {
    double raw_speed;
    string type_of_speed;

    cout << "\nEnter raw speed: ";
    cin >> raw_speed;
    cout << "Enter type of speed (m/s, km/h, mph, rpm): ";
    cin >> type_of_speed;

    cout << "\n--- Speed Conversion ---" << endl;
    if (type_of_speed == "m/s") {
        cout << "SI Speed: " << raw_speed << " m/s" << endl;
    } else if (type_of_speed == "km/h") {
        cout << "SI Speed: " << raw_speed / 3.6 << " m/s" << endl;
    } else if (type_of_speed == "mph") {
        cout << "SI Speed: " << raw_speed / 2.237 << " m/s" << endl;
    } else if (type_of_speed == "rpm") {
        cout << "Angular Velocity: " << (2.0 * PI * raw_speed) / 60.0 << " rad/s" << endl;
    } else {
        cout << "Unknown speed type." << endl;
    }
}

// --- MODULE 3: 
void calculate_free_fall_circular_motion() {
    double height, mass_kg, velocity_ms, radius;

    cout << "\nEnter drop height (m): ";
    cin >> height;
    cout << "Enter object mass (kg): ";
    cin >> mass_kg;
    cout << "Enter tangential speed (m/s): ";
    cin >> velocity_ms;
    cout << "Enter circle radius (m): ";
    cin >> radius;

    if (height < 0 || mass_kg <= 0 || radius <= 0) {
        cout << "Error: Height must be >= 0, and mass/radius must be > 0." << endl;
        return;
    }

    double fall_time = sqrt((2.0 * height) / G);
    double impact_vel_ms = sqrt(2.0 * G * height);
    double angular_vel_rads = velocity_ms / radius;
    double centripetal_accel = angular_vel_rads * angular_vel_rads * radius;
    double centripetal_force = mass_kg * centripetal_accel;

    cout << "\n--- Physics Solver Report ---" << endl;
    cout << "Fall time: " << fall_time << " s" << endl;
    cout << "Impact velocity: " << impact_vel_ms << " m/s" << endl;
    cout << "Angular velocity: " << angular_vel_rads << " rad/s" << endl;
    cout << "Centripetal acceleration: " << centripetal_accel << " m/s^2" << endl;
    cout << "Centripetal force: " << centripetal_force << " N" << endl;
}

int main() {
    int choice; 
    cout << fixed << setprecision(2);

    while (true) {
        cout << "\nSelect module (1: Multimeter, 2: Speed Normalizer, 3: Free Fall & Circular Motion, 0: Exit): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number (0-3)." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                calculate_multimeter();
                break;
            case 2:
                calculate_speed_normalizer();
                break;
            case 3:
                calculate_free_fall_circular_motion();
                break;
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid module selection." << endl;
                break;
        }
    }
}