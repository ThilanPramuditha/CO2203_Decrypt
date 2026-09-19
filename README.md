# CO2203 Group Project: University Registration System
**Group Name:** Decrypt

## Build & Run Instructions
To compile the system, open your terminal in the root directory and run:
`make`

To start the application, run:
`./main`

## Test Login Credentials
Here are some test accounts you can use to log into the system and test the different menus:
* **Administrator:** A001 
* **Lecturer:** L001 
* **Student:** S001 

*(Note: You can type 'exit' at the login prompt at any time to safely shut down the system and save all data).*

## Data Files
All the system data is saved in the `data/` directory. 
* The `.csv` files act as our database to persist users, courses, and attendance records between program runs.
* The `test_attendance.txt` file is used specifically to test the FileReplayCapture attendance mechanism and check how the system handles malformed data.