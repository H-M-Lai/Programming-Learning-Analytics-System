#include <iostream>
#include <limits>
#include "Task1.hpp"
#include "Task2.hpp"
#include "Task3.hpp"
#include "Task4.hpp"

using namespace std;

static int readChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return choice;
}

static void runTask1Menu() {
    int choice = -1;

    do {
        cout << "\n===== TASK 1 MENU =====";
        
        cout << "\n(System Configuration: Capacity = " << session.capacity << ")";
        cout << "\n1. Register Learner";
        cout << "\n2. Join Session";
        cout << "\n3. Exit Session";
        cout << "\n4. Display Registered Learners";
        cout << "\n5. Display Session Status";
        cout << "\n6. Configure Session Capacity";
        cout << "\n7. Remove/Unregister Learner"; 
        cout << "\n0. Back to Main Menu";
        cout << "\nEnter choice: ";

        choice = readChoice();
        if (choice == -1) {
            cout << "Invalid input. Please enter a number from 0 to 7.\n";
            continue;
        }

        switch (choice) {
            case 1: registerLearner(); break;
            case 2: joinSession(); break;
            case 3: exitSession(); break;
            case 4: displayRegisteredLearners(); break;
            case 5: displaySessionStatus(); break;
            case 6: configureSession(); break;
            case 7: unregisterLearner(); break;
            case 0: break;
            default: cout << "Invalid choice! Please enter 0 to 7.\n";
        }
        
    } while (choice != 0);
}

static void runTask2Menu() {
    int choice = -1;

    do {
        cout << "\n===== TASK 2 MENU =====\n";
        cout << "1. Start Activity Session\n";
        cout << "2. Show Current Activity\n";
        cout << "3. Next Activity\n";
        cout << "4. Go Back Activity\n";
        cout << "5. Submit Current Activity Result\n";
        cout << "6. Display Activity Results\n";
        cout << "7. End Activity Session\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";

        choice = readChoice();
        if (choice == -1) {
            cout << "Invalid input. Please enter a number from 0 to 7.\n";
            continue;
        }

        switch (choice) {
            case 1: startActivitySession(); break;
            case 2: displayCurrentActivity(); break;
            case 3: nextActivity(); break;
            case 4: goBackActivity(); break;
            case 5: submitCurrentActivity(); break;
            case 6: displayActivityResults(); break;
            case 7: endActivitySession(); break;
            case 0: break;
            default: cout << "Invalid choice! Please enter 0 to 7.\n";
        }
    } while (choice != 0);
}

static void runTask3Menu() {
    int choice = -1;

    do {
        cout << "\n===== TASK 3 MENU =====\n";
        cout << "1. Display All Activity Logs\n";
        cout << "2. Filter Logs by Learner ID\n";
        cout << "3. Export Logs to CSV\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";

        choice = readChoice();
        if (choice == -1) {
            cout << "Invalid input. Please enter a number from 0 to 3.\n";
            continue;
        }

        switch (choice) {
            case 1: displayAllActivityLogs(); break;
            case 2: displayLogsByLearner(); break;
            case 3: exportLogsToCSV(); break;
            case 0: break;
            default: cout << "Invalid choice! Please enter 0 to 3.\n";
        }
    } while (choice != 0);
}

static void runTask4Menu() {
    int choice = -1;

    do {
        cout << "\n===== TASK 4 MENU =====\n";
        cout << "1. Generate At-Risk Learner List\n";
        cout << "2. Display At-Risk Learner List\n";
        cout << "3. Export At-Risk Learner List to CSV\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";

        choice = readChoice();
        if (choice == -1) {
            cout << "Invalid input. Please enter a number from 0 to 3.\n";
            continue;
        }

        switch (choice) {
            case 1: generateAtRiskList(); break;
            case 2: displayAtRiskLearners(); break;
            case 3: exportAtRiskLearners(); break;
            case 0: break;
            default: cout << "Invalid choice! Please enter 0 to 3.\n";
        }
    } while (choice != 0);
}

int main() {
    session.capacity = 3;  

    int mainChoice = -1;

    do {
        cout << "\n===== PLAPS MAIN MENU =====\n";
        cout << "1. Task 1: Learner Registration & Session Management\n";
        cout << "2. Task 2: Activity Navigation & Session Flow\n";
        cout << "3. Task 3: Recent Activity Logging & Performance History\n";
        cout << "4. Task 4: At-Risk Learner Priority & Recommendation Engine\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        mainChoice = readChoice();
        if (mainChoice == -1) {
            cout << "Invalid input. Please enter a number from 0 to 4.\n";
            continue;
        }

        switch (mainChoice) {
            case 1: runTask1Menu(); break;
            case 2: runTask2Menu(); break;
            case 3: runTask3Menu(); break;
            case 4: runTask4Menu(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please enter 0 to 4.\n";
        }

    } while (mainChoice != 0);

    return 0;
}
