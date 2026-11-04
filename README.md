
# LostLink – Smart Campusmart Campus Lost & Found Management System 

*Lost something? Let LostLink connect you to it!*

## 📌 Project Overview

LostLink is a C language-based Smart Campus Lost & Found Management System designed to help students report lost and found belongings within their college campus.

The system allows users to register lost and found items, identify possible matches through a rule-based matching system, verify ownership using private clues, and track the recovery status of items.

It also uses file handling in C to save and load item records.

## 🎯 Objectives

- To provide an organised system for reporting lost and found items.
- To reduce the difficulty of finding lost belongings on campus.
- To identify possible matches between lost and found items.
- To improve ownership verification through private clues.
- To maintain item recovery records using file handling.

## ✨ Features

### 1. Report Lost Item
Students can register lost items by entering:
- Item name
- Category
- Colour
- Brand
- Location
- Date
- Private ownership clue

### 2. Report Found Item
Users can register items they have found on campus by entering their details.

### 3. View All Items
Displays all registered lost and found item reports.

### 4. Intelligent Item Matching
The system calculates a matching score out of 100 based on:

| Matching Criteria | Points |
|---|---:|
| Same category | 20 |
| Same item name | 15 |
| Same colour | 20 |
| Same brand | 20 |
| Same location | 15 |
| Same date | 10 |
| **Total** | **100** |

Match priority:
- 80–100: High
- 60–79: Moderate
- 40–59: Low

### 5. Private Ownership Verification
The owner can enter the private clue provided during lost-item registration. The system checks whether the clue matches.

### 6. Recovery Status Tracking
Items can have the following statuses:
- Reported
- Pending Staff Approval
- Recovered

### 7. Staff Approval
The staff approval option allows a pending recovery to be marked as recovered.

### 8. File Handling
The system uses C file handling functions to save and load records through a binary file named `campus_data.dat`.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Compiler:** GCC / ByteXL C Compiler
- **Version Control:** Git
- **Repository Hosting:** GitHub

## 📚 C Concepts Used

- Structures (`struct`)
- Arrays
- Strings and string functions
- User-defined functions
- Loops
- Conditional statements
- Pointers and file pointers
- File handling (`fopen`, `fwrite`, `fread`, `fclose`)
- Switch-case statements

## ▶️ How to Run the Project

### Step 1: Clone the repository

```bash
git clone YOUR_GITHUB_REPOSITORY_LINK
```

Replace the placeholder with your actual GitHub repository link.

### Step 2: Open the project folder

```bash
cd LostLink
```

### Step 3: Compile the C program

If GCC is installed, run:

```bash
gcc main.c -o LostLink
```

### Step 4: Run the program

On Windows:

```bash
LostLink.exe
```

On Linux or macOS:

```bash
./LostLink
```

You can also run the program using the ByteXL online C compiler.

## 📋 Main Menu

```text
====================================
             LOSTLINK
====================================

1. Report Lost Item
2. Report Found Item
3. View All Items
4. Find Possible Matches
5. Verify Item Ownership
6. Staff: Approve Recovery
7. Exit
```

## 💡 Project Advantages

- Simple and user-friendly menu-based interface.
- Helps organise campus lost and found reports.
- Provides rule-based matching to identify possible items.
- Uses private clues for an additional ownership check.
- Maintains recovery status.
- Demonstrates practical applications of C programming concepts.

## ⚠️ Limitations

- The current version uses exact text matching.
- The program supports a maximum of 100 item records.
- Data persistence depends on whether the compiler environment preserves the binary data file.
- Staff approval is simulated and does not include a real login system.
- Private clues are not encrypted in the data file.

## 🏁 Conclusion

LostLink provides a simple and organised solution for managing lost and found items within a college campus. By combining item registration, rule-based matching, ownership verification, recovery tracking, and file handling, the project demonstrates how C programming concepts can be applied to solve a real-world campus problem.

---

**Project Name:** LostLink  
**Project type:** college project
**Programming Language:** C  
**Domain:** Campus Management / Lost and Found System
