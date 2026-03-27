#ifndef TASK3_HPP
#define TASK3_HPP

#include <string>

using namespace std;

const int MAX_LOGS = 200;

struct ActivityAttempt {
    string learnerID;
    string topic;
    int difficulty;
    int score;
    bool passed;
};

struct ActivityLogRecord {
    int logID;
    string learnerID;
    string topic;
    int difficulty;
    int score;
    bool passed;
};

void logActivityAttempt(const ActivityAttempt& attempt);
void displayAllActivityLogs();
void displayLogsByLearner();
void exportLogsToCSV();

int getDistinctLearnersFromLogs(string outLearnerIDs[], int maxOut);
int getRecentLogsForLearner(const string& learnerID, ActivityLogRecord outLogs[], int maxOut, int recentLimit);

#endif