#ifndef TASK1_HPP
#define TASK1_HPP

#include <string>

using namespace std;


// Structures
// =====================

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


// Global Variables (extern)
// =====================

extern Learner registeredLearners[MAX_LEARNERS];
extern int registeredCount;
extern Session session;


// Function Prototypes
// =====================

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
