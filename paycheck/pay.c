#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


enum Mode { RATE, HOURS, DT_HOURS, TAXES, NONE };
struct AppState {
    
    // Pay rates
    double rate;
    double otRate;
    double dtRate;

    // Hours
    double hours;
    double otHours;
    double dtHours;
    
    // Sums
    double regPay;
    double otPay;
    double dtPay;

    double taxRate;
    double net;
    double gross;
    
    // Operation modes
    enum Mode opMode;

    // Optional parameters 
    int json;
};


struct AppState default_state() {
    
    struct AppState state;
    
    state.opMode = NONE;
    state.taxRate = 0.20;
    state.rate = 0.0; 
    state.hours = 0.0;
    state.regPay = 0.0;
    state.otRate = 0.0;
    state.otHours = 0.0;
    state.otPay = 0.0; 
    state.dtRate = 0.0; 
    state.dtHours = 0.0;
    state.dtPay = 0.0; 
    state.net = 0.0;
    state.gross = 0.0;
    state.json = 0;

    return state;
}


int set_op(char* modeStr, struct AppState* payStruct) {
    
    int status = 0;

    if (modeStr == NULL) return status;

    if (strcmp(modeStr, "-r") == 0) {
        payStruct->opMode = RATE;
        status = 1;
    }
    
    else if (strcmp(modeStr, "-h") == 0) {
        payStruct->opMode = HOURS;
        status = 1;
    }

    else if (strcmp(modeStr, "-d") == 0) {
        payStruct->opMode = DT_HOURS;
        status = 1;
    }

    else if (strcmp(modeStr, "-t") == 0) {
        payStruct->opMode = TAXES;
        status = 1;
    }

    else if (strcmp(modeStr, "-j") == 0) {
        payStruct->json = 1;
        status = 1;
    }

    return status;
}


void set_val(double value, struct AppState* payCheck) {

    const double OT_CUTOFF = 40.0;

    if (payCheck->opMode == RATE) {
        payCheck->rate = value;
        payCheck->otRate = payCheck->rate * 1.5;
        payCheck->dtRate = payCheck->rate * 2.0;
    }

    else if (payCheck->opMode == HOURS) {
        if (value > OT_CUTOFF) {
            payCheck->hours = OT_CUTOFF;
            payCheck->otHours = value - OT_CUTOFF;
        }
        else {
            payCheck->hours = value; 
        }
    }

    else if (payCheck->opMode == DT_HOURS) {
        payCheck->dtHours = value;
    }

    else if (payCheck->opMode == TAXES) {
        payCheck->taxRate = value;
    }

}


void calculate_state(struct AppState* payCheck) {

    double r = payCheck->rate;
    double ot = payCheck->otHours * (r * 1.5);
    payCheck->otPay = ot;
    double dt = payCheck->dtHours * (r * 2.0);
    payCheck->dtPay = dt;
    double pay = payCheck->hours * r;
    payCheck->regPay = pay;

    double net = pay + dt + ot;
    double taxes = net * payCheck->taxRate;

    payCheck->gross = net;
    payCheck->net = net - taxes;

}


int valid_input_values(struct AppState* payCheck) {

    int status = 1;

    if (payCheck->rate <= 0.1) {
        printf("Invalid pay rate\n");
        status = 0;
    }

    else if (payCheck->hours <= 0.001) {
        printf("Invalid hours\n");
        status = 0;
    }

    return status;

}


int arg_to_double(const char* arg, double* out) {
    
    if (arg == NULL || *arg == '\0') {
        return 0;
    }

    char* endptr;
    errno = 0;
    double val = strtod(arg, &endptr);

    while (*endptr && isspace((unsigned char)*endptr))
    {
        endptr++;
    }

    if (errno == 0 && *endptr == '\0') {
        *out = val;
        return 1;
    } 

    return 0;
}


void format_json(struct AppState* appState) {

    // state.opMode = NONE;
    // state.taxRate = 0.20;
    // state.rate = 0.0; 
    // state.hours = 0.0;
    // state.regPay = 0.0;
    // state.otRate = 0.0;
    // state.otHours = 0.0;
    // state.otPay = 0.0; 
    // state.dtRate = 0.0; 
    // state.dtHours = 0.0;
    // state.dtPay = 0.0; 
    // state.net = 0.0;
    // state.gross = 0.0;
    // state.json = 0;

    printf("{"
        "\"rate\": %.2f,"
        "\"regHours\": %.2f,"
        "\"regPay\": %.2f,"
        "\"otRate\": %.2f,"
        "\"otHours\": %.2f,"
        "\"otPay\": %.2f,"
        "\"dtRate\": %.2f,"
        "\"dtHours\": %.2f,"
        "\"dtPay\": %.2f,"
        "\"gross\": %.2f,"
        "\"net\": %.2f,"
        "\"taxPercent\": %.2f}",
        appState->rate,
        appState->hours,
        appState->regPay,
        appState->otRate,
        appState->otHours,
        appState->otPay,
        appState->dtRate,
        appState->dtHours,
        appState->dtPay,
        appState->gross,
        appState->net,
        appState->taxRate * 100.0

    ); 

}


void show_state(struct AppState* appState) {

    if (appState->json) {
        format_json(appState);
        return;
    }

    printf("\n");

    if (appState->regPay >= 1.0) { 
        printf("Regular: %.2f hours @ $%.2f = %.2f\n", 
                appState->hours, 
                appState->rate, 
                appState->regPay);
    }
    
    if (appState->otPay >= 1.0) { 
        printf("Over time: %.2f hours @ $%.2f = %.2f\n", 
                appState->otHours, 
                appState->otRate, 
                appState->otPay);
    }


    if (appState->dtPay >= 1.0) { 
        printf("Double time: %.2f hours @ $%.2f = %.2f\n", 
                appState->dtHours, 
                appState->dtRate, 
                appState->dtPay);
    }

    if (appState->net >= 0.1) {
        printf("\nGross: %.2f\n", appState->gross);
        printf("Net: %.2f\n", appState->net);
    }
}


const char* HELP_STR = "paycheck - Simple paycheck calculator\n"
"\n"
"DESCRIPTION\n"
"    Calculates gross and net pay with support for regular hours,\n"
"    overtime, double time, and taxes.\n"
"\n"
"SYNOPSIS\n"
"    paycheck [OPTIONS] [VALUE]\n"
"\n"
"OPTIONS\n"
"    -r RATE        Set hourly pay rate (required)\n"
"    -h HOURS       Set regular hours worked (max 40 before OT)\n"
"    -d HOURS       Set double time hours (paid at 2x rate)\n"
"    -t RATE        Set tax rate as decimal (e.g. 0.22 for 22%%)\n"
"    -j             Data is output in json format\n"
"\n"
"EXAMPLES\n"
"    paycheck -r 25.50 -h 45 -t 0.18\n"
"    paycheck -r 30 -h 38 -d 3 -t 0.25\n"
"    paycheck -r 15 -h 60 -t 0.12 -j\n"
"\n"
"NOTES\n"
"    * Hours above 40 are automatically treated as overtime (1.5x)\n"
"    * Use -d for double time hours\n"
"    * All values are passed by value to the internal functions\n"
"    * Run with no arguments to see this help\n";


int main(int argc, char *argv[])
{

    struct AppState state = default_state();
    double val = 0.0;

    // Show help menu if no args are passed
    if (argc == 1) {
        printf("%s", HELP_STR);
        return 0;
    }

    // Parse arguments
    for (int i = 1; i < argc; i++) {
    
        char* arg = argv[i];

        // If a help string is detected then print the menu and exit
        if (strcmp(arg, "--help") == 0) {
            printf("%s", HELP_STR);
            return 0;
        }

        // Set for flags to set the correct options
        else if (!set_op(arg, &state)) {
            if (arg_to_double(arg, &val)) {
                set_val(val, &state);
            }
        };

    }

    // Confirm that enough input values were provided to calculate a pay check
    if (!valid_input_values(&state)) {
        printf("Use --help for options\n");
        return 1;
    }

    // Run the calculations and show the data
    calculate_state(&state);
    show_state(&state);

    return 0;

}

