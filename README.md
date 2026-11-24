# University Registration & Attendance System (C++)

A console-based university course registration and attendance system written in modern C++ (C++17), built around object-oriented design. Students enrol in and drop courses, lecturers run attendance sessions (card reader, QR code, or file replay), and administrators manage users and courses. All data is saved to CSV files between runs.

> Group project for **CO2203 – Object Oriented Programming**, Department of Computer Engineering, Faculty of Engineering, University of Sri Jayewardenepura, 2026. Team name: **Decrypt**.

---

## Features

**Student**
- View enrolled courses and a personal timetable
- Enrol in courses, with checks for capacity, prerequisites and timetable clashes
- Drop courses

**Lecturer**
- View taught courses and enrolment lists
- Open and close attendance sessions
- Capture attendance three ways: QR code token, console card reader, or file replay
- View attendance percentages

**Administrator**
- Create, update and remove users and courses (including prerequisites)
- Generate a system report and view attendance percentages

**System**
- CSV-based persistence: users, courses, enrolments and attendance are loaded at start-up and saved on exit
- Clear error messages using a custom exception hierarchy

---

## OOP design

| Concept | Where it is used |
| :-- | :-- |
| **Abstraction** | `Person` and `Course` are abstract base classes with pure virtual functions (`getRole()`, `displayMenu()`, `checkEligibility()`, ...) |
| **Inheritance** | `Student`, `Lecturer`, `Administrator` → `Person`; `LectureCourse`, `LabCourse`, `ProjectCourse` → `Course` |
| **Polymorphism** | Each user type shows its own dashboard through `displayMenu()`; each course type applies its own eligibility and grading rules |
| **Strategy pattern** | `AttendanceCapture` interface with three interchangeable strategies: `ConsoleCardReader`, `QRCodeCapture`, `FileReplayCapture` |
| **Templates** | Generic `Repository<T>` with explicit specialisations for `Person` and `Course` handling file loading and saving |
| **Exception handling** | `CustomException` base with `CapacityException`, `ClashException`, `NotEnrolledException`, `DuplicateAttendanceException`, `SessionClosedException` |
| **Encapsulation** | Domain data is kept private and changed only through class methods |

---

## Project structure

```
CO2203_Decrypt/
├── include/     # Header files (.h) – class declarations
├── src/         # Source files (.cpp) – implementations and main.cpp
├── data/        # CSV "database" files and test input for file replay
├── Makefile
└── README.md
```

---

## Build and run

Requirements: `g++` with C++17 support and `make`.

```bash
git clone https://github.com/ThilanPramuditha/CO2203_Decrypt.git
cd CO2203_Decrypt
make
./main
```

To remove compiled files: `make clean`

---

## Try it out

Log in with one of these test IDs:

| Role | User ID |
| :-- | :-- |
| Administrator | `A001` |
| Lecturer | `L001` |
| Student | `S001` |

Type `exit` at the login prompt to shut down safely and save all data.

`data/test_attendance.txt` is used by the file replay capture to test attendance input automatically, including malformed lines, to show how the system handles bad data.

### Sample output

```
=========================================
  UNIVERSITY REGISTRATION SYSTEM LOGIN
=========================================
Enter User ID ('exit' to shutdown): S001
[System] Authentication successful.

--- Student Dashboard ---
1. View Enrolled Courses
2. Enrol in a Course
3. Drop a Course
4. View Personal Timetable
5. Logout
```

---

## Team & contributions

**Team Decrypt** – three members, each owning a part of the system and working together to integrate it into one application.

| Member | Focus area |
| :-- | :-- |
| **Thilan Pramuditha** ([@ThilanPramuditha](https://github.com/ThilanPramuditha)) | Project lead – system architecture, integration and data persistence |
| **Didula Dissanayake** ([@diddissavoid](https://github.com/diddissavoid)) | Domain models, business rules and user dashboards |
| **Kaveesha Herath** ([@kbkherathlknknb-cmyk](https://github.com/kbkherathlknknb-cmyk)) | Scheduling, timetabling and the attendance module |

### Thilan Pramuditha – Project lead, integration & persistence
- Set up the project structure and the C++17 build system
- Designed and built the core `RegistrationSystem` engine: login, main loop and polymorphic menu routing
- Built the generic `Repository<T>` template for saving and loading data to CSV files
- Implemented the `FileReplayCapture` and QR code token attendance methods and connected them to lecturer attendance sessions
- Completed the administrator features and led integration and testing of the full system

### Didula Dissanayake – Domain models & user dashboards
- Designed the `Person` hierarchy (`Student`, `Lecturer`, `Administrator`) and the `Course` hierarchy (`LectureCourse`, `LabCourse`, `ProjectCourse`)
- Implemented enrolment and course eligibility rules, along with the custom exception classes
- Built the interactive student, lecturer and administrator dashboards with input validation and clear error handling

### Kaveesha Herath – Scheduling & attendance
- Implemented timetable scheduling with clash detection (`Timetable`, `TimetableSlot`)
- Built the attendance model: sessions, records, the attendance register and correction records
- Designed the `AttendanceCapture` interface and the card reader, QR code and file replay capture classes

### How we worked
- Modules were developed on separate feature branches and merged into `main` through reviewed pull requests
- Regular integration and testing kept the modules working together as one system

---

## Acknowledgements

QR code generation uses the [QR Code generator library](https://www.nayuki.io/page/qr-code-generator-library) by Project Nayuki (MIT License).
