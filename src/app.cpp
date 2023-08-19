#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

string units[3] = {" deg. C", " deg. F", " K"};
bool isPrecise = false;
int unit = 0;
int option;
string unitText = units[unit];

double roundUp(double num, bool precise) {
    if (precise) return num;
    return ceil(num);
}

void loop() {
    system("cls"); // Not safe!!!

    cout << "--------- Temperature Converter ---------" << endl;
    //cout << "0: Celsius (deg. C)" << endl << "1: Fahrenheit (deg. F)" << endl << "2: Kelvin (K)" << endl;
    //cout << endl << "Other settings" << endl;
    cout << "0: Begin converting" << endl;
    cout << "1: Select unit of conversion" << endl;
    cout << "2: Precision of conversions" << endl;
    cout << endl << "Selected unit: " << units[unit] << endl;
    cout << "Are conversions precise? (0: False; 1: True): " << isPrecise << endl;
    cout << "Choose option by entering their corresponding number: ";
    
    cin >> option;
    cout << "-----------------------------------------" << endl;

    switch (option) {
        case 1:
            cout << "0: Celsius (deg. C)" << endl << "1: Fahrenheit (deg. F)" << endl << "2: Kelvin (K)" << endl;
            cout << "Choose unit by entering their corresponding number: ";
            cin >> unit;
            unitText = units[unit];
            break;
        case 2:
            cout << "Change this setting to '" << !isPrecise << "'? (y/n): ";
            char inp;
            cin >> inp;
            if (inp == 'y') isPrecise = !isPrecise;
            break;
        
        default:
            break;
    }
    if (option != 0) loop();
    
    while (true) {
        string tempOption;
        cout << "Enter temperature (or option \"quit\" to return to menu): ";
        cin >> tempOption;
        if (tempOption == "quit") loop();

        double temperature = stod(tempOption);

        // Mathematical expressions for every temperature conversion
        const double c_to_f = roundUp((temperature * 1.8) + 32, isPrecise);
        const double c_to_k = roundUp(temperature + 273.15, isPrecise);
        const double k_to_c = roundUp(temperature - 273.15, isPrecise);
        const double f_to_c = roundUp((temperature - 32) * 5/9, isPrecise);
        const double f_to_k = roundUp((temperature - 32) * 5/9 + 273.15, isPrecise);
        const double k_to_f = roundUp((temperature - 273.15) * 1.8 + 32, isPrecise);

        // Conversion ranges/indexes:
        //  Celsius: (0-1)
        //  Fahrenheit: (2-3)
        //  Kelvin: (4-5)
        const double degs[6] = {c_to_f, c_to_k, f_to_c, f_to_k, k_to_c, k_to_f};

        cout << temperature << unitText << " is equivalent to: " << endl;

        // Selects the correct starting index for the selected unit (refer to degs[] array above).
        int selectorBegin = unit * 2; // 0*2=0; 1*2=2; 2*2=4; ...

        // Outputs answers in a way that every OTHER unit is shown (aka filtering out the selected unit).
        for (int i = 0; i < sizeof(units)/sizeof(units[0]); i++) {
            try {
                if (units[i] != unitText) {
                    cout << "(+) " << degs[selectorBegin] << units[i] << endl;
                    selectorBegin++;
                }
            }
            catch (...) { // Catches any exception. In this case, an index-out-of-range exception is expected.
                break;
            }
        }
    }
}

int main() {
    loop();
    return 0;
}



