#include <iostream>
#include <limits>
#include "Task1.hpp"

using namespace std;

// Shared Task 1 state.
Learner registeredLearners[MAX_LEARNERS];
int registeredCount = 0;
Session session = {0, {}, 0, 0, 0, {}, 0, 0, 0};

static bool enqueue(string queueArr[], int& rear, int& count, const string& id) {
    if (count >= MAX_LEARNERS) return false;
    queueArr[rear] = id;
    rear = (rear + 1) % MAX_LEARNERS;
    count++;
    return true;
}

static bool dequeue(string queueArr[], int& front, int& count, string& removedID) {
    if (count == 0) return false;
    removedID = queueArr[front];
    front = (front + 1) % MAX_LEARNERS;
    count--;
    return true;
}

int findLearnerIndexByID(const string& id) {
    for (int i = 0; i < registeredCount; i++) {
        if (registeredLearners[i].learnerID == id) return i;
    }
    return -1;
}

bool learnerExists(const string& id) {
    return findLearnerIndexByID(id) != -1;
}

static bool existsInQueue(const string queueArr[], int front, int count, const string& id) {
    for (int i = 0; i < count; i++) {
        int idx = (front + i) % MAX_LEARNERS;
        if (queueArr[idx] == id) return true;
    }
    return false;
}

static bool isBlank(const string& s) {
    for (char c : s) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') return false;
    }
    return true;
}


// Register a new learner.
void registerLearner() {
    string id, name;

    cout << "Enter Learner ID: ";
    if (!(cin >> id)) {
        cout << "Invalid learner ID input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (id.empty()) {
        cout << "Learner ID cannot be empty!\n";
        return;
    }

    if (learnerExists(id)) {
        cout << "Learner ID already exists!\n";
        return;
    }
    if (registeredCount >= MAX_LEARNERS) {
        cout << "Registration list is full!\n";
        return;
    }

    cout << "Enter Learner Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    if (name.empty() || isBlank(name)) {
        cout << "Learner name cannot be empty!\n";
        return;
    }

    registeredLearners[registeredCount] = {id, name};
    registeredCount++;
    cout << "Learner registered successfully!\n";
}


// Add learner into active queue or waiting queue.
void joinSession() {
    string id;
    cout << "Enter Learner ID: ";
    if (!(cin >> id)) {
        cout << "Invalid learner ID input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (id.empty()) {
        cout << "Learner ID cannot be empty!\n";
        return;
    }

    if (!learnerExists(id)) {
        cout << "Learner not registered!\n";
        return;
    }

    if (session.capacity <= 0 || session.capacity > MAX_LEARNERS) {
        cout << "Session capacity is not configured correctly.\n";
        return;
    }

    if (existsInQueue(session.activeQueue, session.activeFront, session.activeCount, id) ||
        existsInQueue(session.waitingQueue, session.waitingFront, session.waitingCount, id)) {
        cout << "Learner is already in session queue.\n";
        return;
    }

    if (session.activeCount < session.capacity) {
        if (enqueue(session.activeQueue, session.activeRear, session.activeCount, id)) {
            cout << "Learner added to ACTIVE session.\n";
        } else {
            cout << "Active queue is full.\n";
        }
    } else {
        if (enqueue(session.waitingQueue, session.waitingRear, session.waitingCount, id)) {
            cout << "Session full. Added to WAITING queue.\n";
        } else {
            cout << "Waiting queue is full.\n";
        }
    }
}


// Remove one learner from active queue and promote from waiting queue.
void exitSession() {
    if (session.activeCount == 0) {
        cout << "No learners in active session.\n";
        return;
    }

    string exited;
    dequeue(session.activeQueue, session.activeFront, session.activeCount, exited);

    cout << "Learner " << exited << " exited session.\n";

    if (session.waitingCount > 0) {
        string next;
        dequeue(session.waitingQueue, session.waitingFront, session.waitingCount, next);
        enqueue(session.activeQueue, session.activeRear, session.activeCount, next);

        cout << "Learner " << next << " moved to ACTIVE session.\n";
    }
}


// Show all registered learners.
void displayRegisteredLearners() {
    if (registeredCount == 0) {
        cout << "No registered learners.\n";
        return;
    }

    for (int i = 0; i < registeredCount; i++) {
        cout << "ID: " << registeredLearners[i].learnerID
             << " | Name: " << registeredLearners[i].name << endl;
    }
}


// Show session capacity, active queue, and waiting queue.
void displaySessionStatus() {
    // Show current capacity and queue counts.
    cout << "\n--- SESSION CONFIGURATION ---\n";
    cout << "Current Capacity Limit: " << session.capacity << endl;
    cout << "Active Count: " << session.activeCount << (session.activeCount > session.capacity ? " (OVER CAPACITY)" : "") << " / " << session.capacity << endl;
    cout << "Waiting Count: " << session.waitingCount << endl;

    cout << "\n--- ACTIVE SESSION ---\n";
    if (session.activeCount == 0) cout << "Empty\n";
    for (int i = 0; i < session.activeCount; i++) {
        int idx = (session.activeFront + i) % MAX_LEARNERS;
        cout << i + 1 << ". " << session.activeQueue[idx] << endl;
    }

    cout << "\n--- WAITING QUEUE ---\n";
    if (session.waitingCount == 0) cout << "Empty\n";
    for (int i = 0; i < session.waitingCount; i++) {
        int idx = (session.waitingFront + i) % MAX_LEARNERS;
        cout << i + 1 << ". " << session.waitingQueue[idx] << endl;
    }
}

// Remove a learner from registration list.
void unregisterLearner() {
    string id;
    cout << "Enter Learner ID to remove: ";
    cin >> id;

    int index = findLearnerIndexByID(id);
    if (index == -1) {
        cout << "Learner ID not found.\n";
        return;
    }

    // Shift remaining records left to fill the gap.
    for (int i = index; i < registeredCount - 1; i++) {
        registeredLearners[i] = registeredLearners[i + 1];
    }
    registeredCount--;
    cout << "Learner " << id << " removed from system successfully.\n";
}


// Update session capacity.
void configureSession() {
    int cap;
    cout << "Enter new session capacity (max " << MAX_LEARNERS << "): ";
    
    if (!(cin >> cap)) {
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (cap <= 0 || cap > MAX_LEARNERS) {
        cout << "Invalid capacity. Must be between 1 and " << MAX_LEARNERS << ".\n";
        return;
    }

    session.capacity = cap;
    cout << "Session capacity successfully updated to " << session.capacity << ".\n";
}
