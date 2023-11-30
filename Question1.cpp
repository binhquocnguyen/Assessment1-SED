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
#include <fstream>
#include <sstream>
using std::cout, std::cin;

// Calculate the sumDigit
int sumDigit(int num){
    int sum = 0;
    while(num != 0){
        sum += (num % 10);
        num /= 10;
    }
    return sum;
}

// Check if the sumDigit of the number if the palindrome
bool checkPal(int num){
    std::string sumString = std::to_string( sumDigit(num) );
    int length = sumString.length();

    for(int i = 0; i < length / 2; i++){
        if(sumString[i] != sumString[length - i - 1]){
            return false;
        }
    }
    return true;
}

// Check if the single number if palindrome
// Why having 2 checkPal()? In which cases we use each of them? 
bool checkPalFromSingleNumber(int num){
    std::string numString = std::to_string(num);
    int length = numString.length();

    for(int i = 0; i < length / 2; i++){
        if(numString[i] != numString[length - i - 1]){
            return false;
        }
    }
    return true;
}

/**
 * METHOD of accepting NUMBER instead of SUMDIGIT(num)
*/
#if 0
void recPal(int num){
    std::string sumString = std::to_string(sumDigit(num));

    if(checkPal(num)){
        cout << num << ": " << "Result " << sumString << " is a palindrome" << '\n';
        return;
    }
    cout << num << ": " << "Result " << sumString << " is not a palindrome" << '\n';

    bool isPlus {};
    int amount = 0;
    while(true){
        if(checkPal(num + amount)){
            isPlus = true;
            break;
        }

        if(checkPal(num - amount)){
            isPlus = false;
            break;
        }
        amount++;
    }

    if(isPlus){
        cout << "Add " << amount << " to make it a palindrome" << '\n';
    } else {
        cout << "Minus " << amount << " to make it a palindrome" << '\n';
    }
}
#endif

/**
 * METHOD of accepting SUMDIGIT(num) instead of NUMBER
*/
#if 1
void recPal(int sum){
    std::string sumString = std::to_string(sum);

    if(checkPalFromSingleNumber(sum)){
        cout << "Result " << sumString << " is a palindrome" << '\n';
        return;
    }
    cout << "Result " << sumString << " is not a palindrome" << '\n';

    bool isPlus {};
    int amount = 0;
    while(true){
        if(checkPalFromSingleNumber(sum + amount)){
            isPlus = true;
            break;
        }

        if(checkPalFromSingleNumber(sum - amount)){
            isPlus = false;
            break;
        }
        amount++;
    }

    if(isPlus){
        cout << "Add " << amount << " to make it a palindrome" << '\n';
    } else {
        cout << "Minus " << amount << " to make it a palindrome" << '\n';
    }
}
#endif

// Read number from file and print the SampleRun
void readFile(std::string fileName){
    // How this function works with the file? 
    std::ifstream file;
    file.open(fileName);

    if(!file.is_open()){
        std::cerr << "Unable to open file!" << '\n';
        return;
    }

    std::string line;
    while(getline(file, line)){ //So getline returns true when it finds line?
        int num = std::stoi(line); // Is the file string by default, so we use stoi() here?
        // recPal(num);

        cout << num << ": ";
        recPal( sumDigit(num) );
        cout << '\n';
    }
}

int main(int argc, char** argv){
    // Error message and helping command
    if(argc != 2){
        std::cerr << "Available for 1 input only!" << '\n';
        std::cerr << "Command: g++ Question1.cpp -o a.exe" << '\n';
        std::cerr << "Run by: ./a.exe <file_name>" << '\n';
        return -1;
    }

    std::string fileName { argv[1]};
    readFile(fileName);

    return -1; //??
    return 0;
}