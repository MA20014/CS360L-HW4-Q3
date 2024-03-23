#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HugeInteger {
private:
    vector<int> digits; // Vector to store digits of the number

public:
    // Constructor to initialize digits vector with 40 elements, all set to 0
    HugeInteger() : digits(40, 0) {}

    // Method to input a number
    void input() {
        string number;
        cout << "Enter a number (up to 40 digits): ";
        cin >> number;

        // Remove leading zeros
        number.erase(0, min(number.find_first_not_of('0'), number.size() - 1));

        int length = number.length();

        if (length > 40) {
            cout << "Number exceeds 40 digits. Only first 40 digits will be considered." << endl;
            length = 40;
        }

        int start = 40 - length;
        for (int i = 0; i < length; ++i) {
            digits[start + i] = number[i] - '0'; // Convert character to integer and store in digits vector
        }
    }

    // Method to output the number
    void output() {
        string number_str;
        for (int digit : digits) {
            number_str += to_string(digit); // Convert each digit to string and concatenate
        }
        number_str.erase(0, min(number_str.find_first_not_of('0'), number_str.size() - 1));

        if (number_str.empty()) {
            number_str = "0";
        }
        cout << "HugeInteger: " << number_str << endl;
    }

    // Method to add two HugeInteger objects
    HugeInteger add(const HugeInteger& other) {
        HugeInteger result;
        int carry = 0;

        for (int i = 39; i >= 0; --i) {
            int total = digits[i] + other.digits[i] + carry;
            result.digits[i] = total % 10; // Store the last digit of the sum
            carry = total / 10; // Calculate the carry for the next iteration
        }

        return result;
    }

    // Method to subtract two HugeInteger objects
    HugeInteger subtract(const HugeInteger& other) {
        HugeInteger result;
        int borrow = 0;

        for (int i = 39; i >= 0; --i) {
            int diff = digits[i] - other.digits[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = diff;
        }

        return result;
    }

    // Method to check if two HugeInteger objects are equal
    bool isEqualTo(const HugeInteger& other) {
        return digits == other.digits;
    }

    // Method to check if two HugeInteger objects are not equal
    bool isNotEqualTo(const HugeInteger& other) {
        return !isEqualTo(other);
    }

    // Method to check if one HugeInteger object is greater than the other
    bool isGreaterThan(const HugeInteger& other) {
        for (int i = 0; i < 40; ++i) {
            if (digits[i] > other.digits[i]) {
                return true;
            } else if (digits[i] < other.digits[i]) {
                return false;
            }
        }
        return false;
    }

    // Method to check if one HugeInteger object is less than the other
    bool isLessThan(const HugeInteger& other) {
        return !(isGreaterThan(other) || isEqualTo(other));
    }

    // Method to check if one HugeInteger object is greater than or equal to the other
    bool isGreaterThanOrEqualTo(const HugeInteger& other) {
        return isEqualTo(other) || isGreaterThan(other);
    }

    // Method to check if one HugeInteger object is less than or equal to the other
    bool isLessThanOrEqualTo(const HugeInteger& other) {
        return isEqualTo(other) || isLessThan(other);
    }

    // Method to check if the HugeInteger object is zero
    bool isZero() {
        return all_of(digits.begin(), digits.end(), [](int digit) { return digit == 0; });
    }
};

int main() {
    HugeInteger num1, num2;
    num1.input();
    num2.input();

    num1.output();
    num2.output();

    cout << "Addition of this is :";
    HugeInteger result_add = num1.add(num2);
    result_add.output();

    cout << "Subtraction of this is :";
    HugeInteger result_subtract = num1.subtract(num2);
    result_subtract.output();

    cout << "Comparison:" << endl;
    cout << "Is Equal: " << (num1.isEqualTo(num2) ? "true" : "false") << endl;
    cout << "Is Not Equal: " << (num1.isNotEqualTo(num2) ? "true" : "false") << endl;
    cout << "Is Greater Than: " << (num1.isGreaterThan(num2) ? "true" : "false") << endl;
    cout << "Is Less Than: " << (num1.isLessThan(num2) ? "true" : "false") << endl;
    cout << "Is Greater Than or Equal To: " << (num1.isGreaterThanOrEqualTo(num2) ? "true" : "false") << endl;
    cout << "Is Less Than or Equal To: " << (num1.isLessThanOrEqualTo(num2) ? "true" : "false") << endl;

    cout << "Is num1 zero? " << (num1.isZero() ? "true" : "false") << endl;

    return 0;
}
