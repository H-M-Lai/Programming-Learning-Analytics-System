# Programming Learning Analytics & Personalization System (C++)

A console-based C++ prototype developed for a Data Structures assignment.  
This system simulates learner registration, session management, activity navigation, recent activity logging, and at-risk learner prioritization.

## Features

- Learner registration and unregistration
- Session queue management with active and waiting queues
- Activity navigation with next and back tracking
- Recent activity logging using a fixed-size circular structure
- At-risk learner ranking with recommendations
- CSV export for logs and risk reports

## Data Structures Used

- Arrays
- Circular queues
- Stack-based backtracking
- Priority queue / max-heap

## Project Structure

- `main.cpp` - main menu and module navigation
- `Task1.cpp` / `Task1.hpp` - learner registration and session management
- `Task2.cpp` / `Task2.hpp` - activity navigation and session flow
- `Task3.cpp` / `Task3.hpp` - recent activity logging and CSV export
- `Task4.cpp` / `Task4.hpp` - at-risk learner ranking and recommendations

## How to Compile

```powershell
g++ -g main.cpp Task1.cpp Task2.cpp Task3.cpp Task4.cpp -o program.exe
