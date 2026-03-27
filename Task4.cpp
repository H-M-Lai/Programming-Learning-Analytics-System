#include <iostream>
#include <fstream>
#include "Task4.hpp"
#include "Task1.hpp"
#include "Task3.hpp"

using namespace std;

const int MAX_RISK_ITEMS = MAX_LEARNERS;
const int RISK_RECENT_LIMIT = 10;

struct AtRiskItem {
    string learnerID;
    int riskScore;
    int attempts;
    int failedAttempts;
    int averageScore;
    string recommendation;
};

// Max-heap for ranking learners by risk score.
struct PriorityQueue {
    AtRiskItem items[MAX_RISK_ITEMS];
    int size;

    PriorityQueue() : size(0) {}

    void insert(const AtRiskItem& item) {
        if (size >= MAX_RISK_ITEMS) return;
        items[size] = item;
        int i = size++;

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (items[i].riskScore > items[parent].riskScore) {
                AtRiskItem temp = items[i];
                items[i] = items[parent];
                items[parent] = temp;
                i = parent;
            } else break;
        }
    }

    AtRiskItem extractMax() {
        AtRiskItem top = items[0];
        items[0] = items[--size];

        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < size && items[left].riskScore > items[largest].riskScore)
                largest = left;
            if (right < size && items[right].riskScore > items[largest].riskScore)
                largest = right;
            if (largest == i) break;

            AtRiskItem temp = items[i];
            items[i] = items[largest];
            items[largest] = temp;
            i = largest;
        }
        return top;
    }

    bool isEmpty() { return size == 0; }
};

static AtRiskItem riskItems[MAX_RISK_ITEMS];
static int riskCount = 0;

static int toPercent(int value, int total) {
    if (total <= 0) return 0;
    return (value * 100) / total;
}

static string buildRecommendation(int avgScore, int failRate, int attempts) {
    if (attempts < 3) {
        return "Do more activities to build a stable performance profile.";
    }
    if (failRate >= 60) {
        return "Repeat core topics and attempt easier activities first.";
    }
    if (avgScore < 50) {
        return "Review weak topics and practice with guided examples.";
    }
    if (avgScore < 70) {
        return "Continue practice on medium difficulty and revisit mistakes.";
    }
    return "Maintain progress with mixed-difficulty practice.";
}

// Weighted risk score based on recent performance.
static int computeRiskScore(int avgScore, int failRate, int attempts) {
    int scoreRisk = 100 - avgScore;
    if (scoreRisk < 0) scoreRisk = 0;

    int activityRisk = (attempts < 3) ? 20 : 0;

    int total = (failRate * 50 + scoreRisk * 40 + activityRisk * 10) / 100;
    if (total < 0) total = 0;
    if (total > 100) total = 100;
    return total;
}

void generateAtRiskList() {
    string learnerIDs[MAX_LEARNERS];
    int learnerCount = getDistinctLearnersFromLogs(learnerIDs, MAX_LEARNERS);

    riskCount = 0;

    if (learnerCount == 0) {
        cout << "No logs available to generate risk list.\n";
        return;
    }

    PriorityQueue pq;

    for (int i = 0; i < learnerCount; i++) {
        ActivityLogRecord recent[RISK_RECENT_LIMIT];
        int attempts = getRecentLogsForLearner(learnerIDs[i], recent, RISK_RECENT_LIMIT, RISK_RECENT_LIMIT);

        if (attempts <= 0) continue;

        int totalScore = 0;
        int failed = 0;

        for (int j = 0; j < attempts; j++) {
            totalScore += recent[j].score;
            if (!recent[j].passed) failed++;
        }

        int avgScore = totalScore / attempts;
        int failRate = toPercent(failed, attempts);
        int riskScore = computeRiskScore(avgScore, failRate, attempts);

        AtRiskItem item;
        item.learnerID = learnerIDs[i];
        item.riskScore = riskScore;
        item.attempts = attempts;
        item.failedAttempts = failed;
        item.averageScore = avgScore;
        item.recommendation = buildRecommendation(avgScore, failRate, attempts);

        pq.insert(item);
    }

    while (!pq.isEmpty() && riskCount < MAX_RISK_ITEMS) {
        riskItems[riskCount++] = pq.extractMax();
    }

    cout << "At-risk list generated using recent activity logs.\n";
}

void displayAtRiskLearners() {
    if (riskCount == 0) {
        cout << "No at-risk list available. Generate it first.\n";
        return;
    }

    cout << "\n--- AT-RISK LEARNER PRIORITY LIST ---\n";
    for (int i = 0; i < riskCount; i++) {
        cout << (i + 1) << ". Learner: " << riskItems[i].learnerID
             << " | Risk: " << riskItems[i].riskScore
             << " | Attempts: " << riskItems[i].attempts
             << " | Failed: " << riskItems[i].failedAttempts
             << " | Avg Score: " << riskItems[i].averageScore
             << "\n";
        cout << "   Recommendation: " << riskItems[i].recommendation << "\n";
    }
}

void exportAtRiskLearners() {
    if (riskCount == 0) {
        cout << "No at-risk list available. Generate it first.\n";
        return;
    }

    string filename;
    cout << "Enter output CSV filename (e.g., risk_report.csv): ";
    cin >> filename;

    ofstream out(filename.c_str());
    if (!out.is_open()) {
        cout << "Failed to open file for writing.\n";
        return;
    }

    out << "LearnerID,RiskScore,Attempts,FailedAttempts,AverageScore,Recommendation\n";
    for (int i = 0; i < riskCount; i++) {
        out << riskItems[i].learnerID << ','
            << riskItems[i].riskScore << ','
            << riskItems[i].attempts << ','
            << riskItems[i].failedAttempts << ','
            << riskItems[i].averageScore << ','
            << '"' << riskItems[i].recommendation << '"'
            << '\n';
    }

    out.close();
    cout << "At-risk learner list exported to " << filename << "\n";
}
