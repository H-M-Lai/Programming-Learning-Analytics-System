#include <iostream>
#include <fstream>
#include <limits>
#include "Task3.hpp"
#include "Task1.hpp"

using namespace std;

static ActivityLogRecord logs[MAX_LOGS];
static int logFront = 0;
static int logCount = 0;
static int nextLogID = 1;

static void addLog(const ActivityAttempt& attempt) {
    int writeIndex;

    if (logCount < MAX_LOGS) {
        writeIndex = (logFront + logCount) % MAX_LOGS;
        logCount++;
    } else {
        writeIndex = logFront;
        logFront = (logFront + 1) % MAX_LOGS;
    }

    logs[writeIndex].logID = nextLogID++;
    logs[writeIndex].learnerID = attempt.learnerID;
    logs[writeIndex].topic = attempt.topic;
    logs[writeIndex].difficulty = attempt.difficulty;
    logs[writeIndex].score = attempt.score;
    logs[writeIndex].passed = attempt.passed;
}

void logActivityAttempt(const ActivityAttempt& attempt) {
    if (!learnerExists(attempt.learnerID)) {
        cout << "Log skipped: learner is not registered.\n";
        return;
    }
    addLog(attempt);
    cout << "Activity attempt logged successfully.\n";
}

void displayAllActivityLogs() {
    if (logCount == 0) {
        cout << "No activity logs available.\n";
        return;
    }

    cout << "\n--- ACTIVITY LOGS ---\n";
    for (int i = 0; i < logCount; i++) {
        int idx = (logFront + i) % MAX_LOGS;
        cout << "Log# " << logs[idx].logID
             << " | Learner: " << logs[idx].learnerID
             << " | Topic: " << logs[idx].topic
             << " | Diff: " << logs[idx].difficulty
             << " | Score: " << logs[idx].score
             << " | Result: " << (logs[idx].passed ? "PASS" : "FAIL")
             << "\n";
    }
}

void displayLogsByLearner() {
    string learnerID;

    cout << "Enter Learner ID to filter: ";
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

    bool found = false;
    cout << "\n--- LOGS FOR " << learnerID << " ---\n";
    for (int i = 0; i < logCount; i++) {
        int idx = (logFront + i) % MAX_LOGS;
        if (logs[idx].learnerID == learnerID) {
            found = true;
            cout << "Log# " << logs[idx].logID
                 << " | Topic: " << logs[idx].topic
                 << " | Diff: " << logs[idx].difficulty
                 << " | Score: " << logs[idx].score
                 << " | Result: " << (logs[idx].passed ? "PASS" : "FAIL")
                 << "\n";
        }
    }

    if (!found) {
        cout << "No logs found for this learner.\n";
    }
}

void exportLogsToCSV() {
    string filename;

    cout << "Enter output CSV filename (e.g., logs.csv): ";
    cin >> filename;

    ofstream out(filename.c_str());
    if (!out.is_open()) {
        cout << "Failed to open file for writing.\n";
        return;
    }

    out << "LogID,LearnerID,Topic,Difficulty,Score,Result\n";
    for (int i = 0; i < logCount; i++) {
        int idx = (logFront + i) % MAX_LOGS;
        out << logs[idx].logID << ','
            << logs[idx].learnerID << ','
            << logs[idx].topic << ','
            << logs[idx].difficulty << ','
            << logs[idx].score << ','
            << (logs[idx].passed ? "PASS" : "FAIL")
            << '\n';
    }

    out.close();
    cout << "Logs exported to " << filename << "\n";
}

int getDistinctLearnersFromLogs(string outLearnerIDs[], int maxOut) {
    int count = 0;

    for (int i = 0; i < logCount; i++) {
        int idx = (logFront + i) % MAX_LOGS;
        const string& id = logs[idx].learnerID;

        bool exists = false;
        for (int j = 0; j < count; j++) {
            if (outLearnerIDs[j] == id) {
                exists = true;
                break;
            }
        }

        if (!exists && count < maxOut) {
            outLearnerIDs[count++] = id;
        }
    }

    return count;
}

int getRecentLogsForLearner(const string& learnerID, ActivityLogRecord outLogs[], int maxOut, int recentLimit) {
    if (maxOut <= 0 || recentLimit <= 0 || logCount == 0) {
        return 0;
    }

    int stored = 0;

    for (int i = logCount - 1; i >= 0; i--) {
        int idx = (logFront + i) % MAX_LOGS;
        if (logs[idx].learnerID == learnerID) {
            if (stored < maxOut && stored < recentLimit) {
                outLogs[stored++] = logs[idx];
            }
            if (stored >= recentLimit) {
                break;
            }
        }
    }

    for (int i = 0; i < stored / 2; i++) {
        ActivityLogRecord temp = outLogs[i];
        outLogs[i] = outLogs[stored - 1 - i];
        outLogs[stored - 1 - i] = temp;
    }

    return stored;
}