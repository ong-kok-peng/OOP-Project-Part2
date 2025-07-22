/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleStrategies.h"

string ScheduleStrategies::compareTimeFromRecords(string freightTime, string cargoTime) {
    try {
        //convert string timestamp to integer
        int freightTime_int = stoi(freightTime); int cargoTime_int = stoi(cargoTime);
        int cargoTime_intCutoff = 0;

        //calculate cut off cargo time from freight time
        if (freightTime_int % 100 >= 0 && freightTime_int % 100 < 44) {
            cargoTime_intCutoff = freightTime_int + 15; //still can add 15 because time dosen't overflow
        }
        else if (freightTime_int % 100 >= 45 && freightTime_int % 100 <= 59) {
            cargoTime_intCutoff = freightTime_int + 55; //15+40 (to skip 60 to 99)
        }

        //check if cargo time is within 15 mins after freight time
        if (cargoTime_int >= freightTime_int && cargoTime_int <= cargoTime_intCutoff) {
            return "MATCHED";
        }
        else if (cargoTime_int < freightTime_int) {
            return "LATE_CARGO";
        }
        else if (cargoTime_int > cargoTime_intCutoff) {
            return "EARLY_CARGO";
        }
    }
    catch (const invalid_argument& e) {
        return "STOI_ERROR";
    }
}