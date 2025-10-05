#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

/**
 * @brief Converts an uppercase English alphabet character to lowercase.
 *
 * @param ch A single character to be converted.
 * @return The lowercase equivalent of the input character if it's uppercase;
 *         otherwise returns the same character unchanged.
 */
char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch + ('a' - 'A');  // convert manually
    return ch; // unchanged if already lowercase or non-alphabetic
}

/**
 * @brief Checks whether a given string contains any digits (0–9).
 *
 * @param str The input string to be validated.
 * @return true if the string contains digits, false otherwise.
 */
bool containsDigit(const string& str) {
    for (char c : str) {
        if (c >= '0' && c <= '9')
            return true;
    }
    return false;
}

/**
 * @brief Determines whether a given string is a palindrome.
 *
 * A palindrome reads the same forward and backward,
 * considering only alphabetic strings (no digits, spaces, or symbols).
 *
 * @param str The input string to be checked.
 * @return true if the string is a palindrome, false otherwise.
 */
bool isPalindrome(const string& str) {
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        if (toLower(str[left]) != toLower(str[right]))
            return false;

        left++;
        right--;
    }

    return true;
}

/**
 * @brief Entry point of the program.
 *
 * Continuously asks the user to enter strings and determines
 * whether each is a palindrome or not. Throws an exception if
 * the input contains any digits. The user can press Esc to quit.
 *
 * @return int Exit status (0 for normal termination).
 */
int main() {
    cout << "        PALINDROME CHECKER        \n";


    while (true) {
        cout << "Enter a string to check (or press Esc to quit): ";

        char ch = _getch();
        if (ch == 27) {  // ASCII for Esc
            cout << "\nProgram exited.\n";
            break;
        }

        string input;
        cout << ch;
        getline(cin, input);
        input = ch + input;

        try {
            if (containsDigit(input))
                throw invalid_argument("Input contains digits. Please enter letters only.");

            if (isPalindrome(input))
                cout << "Result: Palindrome\n\n";
            else
                cout << "Result: Not Palindrome\n\n";
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << "\n\n";
        }
    }

    return 0;
}
