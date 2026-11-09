#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Inputs {
    string rawReading;
    int maxSigFigs;
    bool hasDecimal;
};

void getInputs(Inputs &inputs) {
    cout << "Enter the raw reading: ";
    cin >> inputs.rawReading;
    cout << "Enter the maximum number of significant figures: ";
    cin >> inputs.maxSigFigs;
    inputs.hasDecimal = false;
}

void processReading(const Inputs &inputs) {
    if (inputs.maxSigFigs <= 0) {
        cout << "[ERROR] Max significant figures must be greater than 0." << endl;
        return;
    }

    string rawReading = inputs.rawReading;
    int sigFigs = 0;
    bool hasDecimal = inputs.hasDecimal;

    // 1. Check for decimal point and erase it from our working copy
    for (int i = 0; i < static_cast<int>(rawReading.length()); i++) {
        if (rawReading[i] == '.') {
            rawReading.erase(i, 1);
            hasDecimal = true;
            break;
        }
    }

    // 2. Strip leading zeros & signs so backward scan doesn't count them
    int start = 0;
    while (start < static_cast<int>(rawReading.length()) && 
          (rawReading[start] < '1' || rawReading[start] > '9')) {
        start++;
    }

    // Edge case: if input was all zeros (e.g., "0" or "0.00")
    if (start == static_cast<int>(rawReading.length())) {
        sigFigs = 1;
    } else {
        rawReading = rawReading.substr(start); // Keep only from first 1-9 onward

        if (!hasDecimal) {
            bool foundNonZero = false;
            for (int i = static_cast<int>(rawReading.length()) - 1; i >= 0; --i) {
                if (rawReading[i] < '0' || rawReading[i] > '9') continue;
                if (rawReading[i] != '0') foundNonZero = true;
                if (foundNonZero) ++sigFigs;
            }
        } else {
            for (char digit : rawReading) {
                if (digit >= '0' && digit <= '9') {
                    ++sigFigs;
                }
            }
        }
    }

    // 3. Final Audit & Output
    cout << "\nDetected Significant Figures: " << sigFigs << endl;
    if (sigFigs <= inputs.maxSigFigs) {
        cout << "[OK] Valid sensor precision." << endl;
    } else {
        double numericValue = stod(inputs.rawReading); // Use original string with decimal
        cout << "[WARNING] Over-precise reading! Sensor limit is " << inputs.maxSigFigs << "." << endl;
        cout << "Rounded Value: " << setprecision(inputs.maxSigFigs) << numericValue << endl;
    }
}

int main() {
    Inputs sensorData;
    getInputs(sensorData);
    processReading(sensorData);
    return 0;
}
