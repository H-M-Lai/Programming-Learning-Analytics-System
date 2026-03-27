#include <iostream>
#include <limits>
#include "Task2.hpp"
#include "Task1.hpp"
#include "Task3.hpp"

using namespace std;

const int MAX_ACTIVITIES = 8;
const int MAX_RESULTS = 300;

struct ActivityDef {
    string topic;
    int difficulty;
};

struct ActivityResult {
    string learnerID;
    string topic;
    int difficulty;
    int score;
    bool passed;
};

// One learner activity session at a time.
struct ActivitySession {
    bool active;
    string learnerID;
    int currentIndex;
    int historyStack[MAX_ACTIVITIES];
    int top;
};

// Predefined activity flow for the learning session.
static ActivityDef activities[MAX_ACTIVITIES] = {
    {"Variables & Data Types", 1},
    {"Conditionals", 1},
    {"Loops", 2},
    {"Functions", 2},
    {"Arrays", 3},
    {"Pointers", 4},
    {"Structures", 3},
    {"Recursion", 4}
};

static ActivitySession currentSession = {false, "", 0, {0}, -1};
static ActivityResult results[MAX_RESULTS];
static int resultCount = 0;

static bool readScore(int& score) {
    if (!(cin >> score)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    if (score < 0 || score > 100) return false;
    return true;
}

// Check whether the learner is currently in the active session queue.
static bool isLearnerInActiveSession(const string& id) {
    for (int i = 0; i < session.activeCount; i++) {
        int idx = (session.activeFront + i) % MAX_LEARNERS;
        if (session.activeQueue[idx] == id) return true;
    }
    return false;
}

void endActivitySession() {
    if (!currentSession.active) {
        cout << "No active activity session to end.\n";
        return;
    }
    cout << "Activity session ended for " << currentSession.learnerID << ".\n";

    currentSession.active = false;
    currentSession.learnerID = "";
    currentSession.currentIndex = 0;
    currentSession.top = -1;
}

void startActivitySession() {
    if (currentSession.active) {
        cout << "Session already active for " << currentSession.learnerID << ". Please end it first.\n";
        return;
    }

    string learnerID;
    cout << "Enter Learner ID to start session: ";
    if (!(cin >> learnerID)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!learnerExists(learnerID)) {
        cout << "Learner not registered.\n";
        return;
    }

    if (!isLearnerInActiveSession(learnerID)) {
        cout << "Learner is not in the Active Session! Please join the session via Task 1 first.\n";
        return;
    }

    currentSession.active = true;
    currentSession.learnerID = learnerID;
    currentSession.currentIndex = 0;
    currentSession.top = -1;

    cout << "Activity session started for " << learnerID << ".\n";
    displayCurrentActivity();
}

void nextActivity() {
    if (!currentSession.active) { cout << "No active activity session.\n"; return; }
    if (currentSession.currentIndex >= MAX_ACTIVITIES - 1) { cout << "Already at the last activity.\n"; return; }

    currentSession.top++;
    currentSession.historyStack[currentSession.top] = currentSession.currentIndex;
    currentSession.currentIndex++;

    displayCurrentActivity();
}

void goBackActivity() {
    if (!currentSession.active) { cout << "No active activity session.\n"; return; }
    if (currentSession.top < 0) { cout << "No previous activity to go back to.\n"; return; }

    currentSession.currentIndex = currentSession.historyStack[currentSession.top];
    currentSession.top--;

    displayCurrentActivity();
}

void submitCurrentActivity() {
    if (!currentSession.active) { cout << "No active activity session.\n"; return; }
    if (resultCount >= MAX_RESULTS) { cout << "Result storage is full.\n"; return; }

    int score;
    cout << "Enter score (0-100) for current activity: ";
    if (!readScore(score)) { cout << "Invalid score input.\n"; return; }

    ActivityResult result;
    result.learnerID = currentSession.learnerID;
    result.topic = activities[currentSession.currentIndex].topic;
    result.difficulty = activities[currentSession.currentIndex].difficulty;
    result.score = score;
    result.passed = score >= 50;

    results[resultCount++] = result;

    ActivityAttempt attempt;
    attempt.learnerID = result.learnerID;
    attempt.topic = result.topic;
    attempt.difficulty = result.difficulty;
    attempt.score = result.score;
    attempt.passed = result.passed;
    logActivityAttempt(attempt);

    cout << "Activity submitted: " << result.topic
         << " | Score: " << result.score
         << " | Result: " << (result.passed ? "PASS" : "FAIL") << "\n";
}

void displayCurrentActivity() {
    if (!currentSession.active) { cout << "No active activity session.\n"; return; }
    cout << "\nCurrent Learner: " << currentSession.learnerID << "\n";
    cout << "Current Activity: " << (currentSession.currentIndex + 1) << "/" << MAX_ACTIVITIES << "\n";
    cout << "Topic: " << activities[currentSession.currentIndex].topic << "\n";
    cout << "Difficulty: " << activities[currentSession.currentIndex].difficulty << "\n";
}

void displayActivityResults() {
    if (resultCount == 0) { cout << "No activity results recorded yet.\n"; return; }
    cout << "\n--- ACTIVITY RESULTS ---\n";
    for (int i = 0; i < resultCount; i++) {
        cout << "Learner: " << results[i].learnerID
             << " | Topic: " << results[i].topic
             << " | Diff: " << results[i].difficulty
             << " | Score: " << results[i].score
             << " | Result: " << (results[i].passed ? "PASS" : "FAIL") << "\n";
    }
}
