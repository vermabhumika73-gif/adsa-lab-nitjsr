#include <iostream>
using namespace std;

int main() {
    const int ROWS = 5;  // You can change the size as needed
    const int COLS = 5;

    int arr[ROWS][COLS] = {0}; // Initialize all elements to 0

    cout << "Initial 2D array (" << ROWS << "x" << COLS << "):\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    char choice;
    do {
        int row, col, value;

        cout << "\nEnter row (0-" << ROWS - 1 << "): ";
        cin >> row;
        cout << "Enter column (0-" << COLS - 1 << "): ";
        cin >> col;
        cout << "Enter value: ";
        cin >> value;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            arr[row][col] = value;
        } else {
            cout << "Invalid row or column!\n";
        }

        cout << "\nUpdated 2D array:\n";
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nDo you want to insert another value? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Program finished.\n";
    return 0;
}

