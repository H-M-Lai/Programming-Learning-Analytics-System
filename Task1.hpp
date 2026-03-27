#ifndef TASK1_HPP
#define TASK1_HPP

#include <string>

using namespace std;


// Basic data structures for Task 1.

struct Learner {
    string learnerID;
    string name;
};

const int MAX_LEARNERS = 100;

struct Session {
    int capacity;
    string activeQueue[MAX_LEARNERS];
    int activeFront;
    int activeRear;
    int activeCount;

    string waitingQueue[MAX_LEARNERS];
    int waitingFront;
    int waitingRear;
    int waitingCount;
};


// Shared Task 1 state.

extern Learner registeredLearners[MAX_LEARNERS];
extern int registeredCount;
extern Session session;


// Task 1 function declarations.

void registerLearner();
void joinSession();
void exitSession();
void displayRegisteredLearners();
void displaySessionStatus();
void configureSession(); 
void unregisterLearner();
bool learnerExists(const string& id);
int findLearnerIndexByID(const string& id);

#endif
