/*
    RMIT University Vietnam
    Course: EEET2482/COSC2082
    Semester: 2023-2
    Lab Assessment: 1
    Author: Nguyen Son Tung
    ID: s3979348
    Compiler used: g++ 13.1.0
    Created  date: 05/08/2023
    Acknowledgement: None
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using std::cout, std::cin;

// using static variable to store fileName
// static std::string fileName = "data2.dat";
std::string fileName = "data2.dat";

class Time {
    private:
        int hour;
        int minute;

    public:
        Time(){
            hour = 0;
            minute = 0;
        }

        Time(int hour, int minute) : hour(hour), minute(minute) {
            // Condition for the evaluation
            if( (hour < 0 || hour > 23) && (minute < 0 || minute > 59) ){
                hour = 0;
                minute = 0;
            }
        }

        // Overflow the time into right format
        void overFlow(){
            if(minute >= 60){
                minute %= 60;
                hour++;
            }
            if(hour > 23){
                hour %= 24;
            }
        }

        friend Time operator + (Time&, Time&);

        friend std::ostream& operator << (std::ostream&, Time&);

        // IMPLEMENT new method to find the lowest time
        friend bool operator < (Time&, Time&);

};

Time operator + (Time& time1, Time& time2){
    Time temp;
    // Addition of hour and minute
    temp.hour = time1.hour + time2.hour;
    temp.minute = time1.minute + time2.minute;

    // Overflow before printing out
    temp.overFlow();

    cout << time1 << " + " << time2 << " = " << temp << '\n';
    return temp;
}

std::ostream& operator << (std::ostream& output, Time& time){

    // Format the value to become 2 digits
    cout << std::setw(2) << std::setfill('0') << time.hour << ":" 
         << std::setw(2) << std::setfill('0') << time.minute;

    return output;
}

// Method to the comparision
bool operator < (Time& time1, Time& time2){
    // Overflow times value first
    time1.overFlow();
    time2.overFlow();

    if(time1.hour < time2.hour){
        return true;
    } else if (time1.hour == time2.hour){
        return time1.minute < time2.minute;
    }

    return false;
}

// Read and assign value from file
void readData(Time* times){
    std::fstream file;
    file.open(fileName);
    
    // Error warning!
    if(!file.is_open()){
        std::cerr << "Unable to open file data2.dat!" << '\n';
        return;
    }
    
    std::string line;
    std::stringstream ssTime;
    int hour;
    int minute;
    
    // How the whole process works?
    // (from string line, stringstream ssTime, clear(), str(line))
    for(int i = 0; i < 4; i++){ 
        getline(file, line);
        ssTime.clear(); //How this clear() works?
        ssTime.str(line); //Initialize
        cout << "ss: " << ssTime.str() << std::endl; //Extract

        ssTime >> hour >> minute;
        cout << "ex: " << hour << ":" << minute << std::endl;
        *(times + i) = Time (hour, minute);
    }
}

// Method finding lowest time
Time& findLowestTime(Time times[4]){
    Time& lowestTime = times[0];
    for (int i = 0; i < 4; i++) {
        if(times[i] < lowestTime){
            lowestTime = times[i];
        }
    }
    return lowestTime;
}


int main(){
    // Question a b c
    Time time1 {5, 23};
    Time time2 {23, 42};
    Time test = time1 + time2;
    cout << '\n';

    // Question d
    Time times[4];
    readData(times);

    for(int i = 0; i < 4; i++){
        cout << "Time " << i << " = " << times[i] << '\n';
    }
    cout << '\n';
    cout << "Lowest time = " << findLowestTime(times) << '\n';

    return 0;
}