#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdbool.h>

#define MAX_SESSION_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 50
#define MAXX_USERNAME_LENGTH 50
#define MAX_TUTOR_CODE_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_TP_NUMBER_LENGTH 50

#define MAX_SESSION_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 50
#define MAXX_TUTOR_CODE_LENGTH 10

#define MAX_ID_LENGTH 20
#define MAX_LINE_LENGTH 100

void saveUsersToFile();
void loadUsersFromFile();
void registerUser(const char* username, const char* password);
int loginUser(const char* username, const char* password);

int tutorExists(const char* username); // Declare tutorExists function here
void registerTutor();
int loginTutor(const char* username, const char* password);
int tutorLogin();

int studentExists(const char* username);
void registerStudent();
int loginStudent(const char* username, const char* password);
int studentLogin();

void newSession();
void viewSessions();
void enrollStudent();

void tutorViewSessions();

void studentEnroll();

#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define FILENAME "register&password.txt"


char loggedInTutorId[MAX_ID_LENGTH];

char loggedInStudentId[MAX_ID_LENGTH];




//Admin Register and Login Functions




typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int numUsers = 0;


void saveUsersToFile() {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error opening file for writing.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

void loadUsersFromFile() {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No registered users found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
    }

    fclose(file);
}

void registerUser(const char* username, const char* password) {
    if (numUsers >= MAX_USERS) {
        printf("Cannot register new user. Maximum user limit reached.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("\033[1;31m"); // Set text color to red
            printf("Username already exists. Please choose a different username." "\xF0\x9F\x98\x85 " "\n"); // Unicode representation of the "grinning face with sweat" emoji
            printf("\033[0m"); // Reset text color to default
            return;
        }
    }

    User newUser;
    strncpy(newUser.username, username, MAX_USERNAME_LENGTH);
    strncpy(newUser.password, password, MAX_PASSWORD_LENGTH);

    users[numUsers++] = newUser;

    printf("\033[1;32m"); // Set text color to green
    printf("Registration successful!" "\xF0\x9F\x91\x8D " "\n"); // Unicode representation of the "thumbs up" emoji
    printf("\033[0m"); // Reset text color to default

    saveUsersToFile();
}


int loginUser(const char* username, const char* password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("\033[1;32m"); // Set text color to green
            printf("Login successful!" "\xF0\x9F\x91\x8D " "\n"); // Unicode representation of the "thumbs up" emoji
            printf("\033[0m"); // Reset text color to default
            return 1;
        }
    }

    return 0;  // indicate login failure
}




//Admin Functions


void registerTutor() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];
    char session[MAX_SESSION_LENGTH];

    printf("Enter Tutor ID: ");
    scanf("%s", username);

    if (tutorExists(username)) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Tutor ID already exists. Please choose a different ID." "\xF0\x9F\x98\x85 " "\n"); // Unicode representation of the "grinning face with sweat" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter session: ");
    getchar(); // Clear the newline character left by previous scanf
    fgets(session, sizeof(session), stdin);
    session[strcspn(session, "\n")] = '\0'; // Remove newline character

    FILE* file = fopen("tutors.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s %s\n", username, password, name, session);
        fclose(file);
        printf("\033[1;32m"); // Set text color to green
        printf("Tutor registered successfully." "\xF0\x9F\x91\x8C " "\n"); // Unicode representation of the "OK hand gesture" emoji
        printf("\033[0m"); // Reset text color to default
    } else {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for writing.\n");
        printf("\033[0m"); // Reset text color to default
    }
}




int loginTutor(const char* username, const char* password) {
    FILE* file = fopen("tutors.txt", "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No registered tutors found.\n");
        printf("\033[0m"); // Reset text color to default
        return 0;  // indicate login failure
    }

    char tutorUsername[MAX_USERNAME_LENGTH];
    char tutorPassword[MAX_PASSWORD_LENGTH];
    char tutorName[MAX_NAME_LENGTH];

    while (fscanf(file, "%s %s %[^\n]", tutorUsername, tutorPassword, tutorName) == 3) {
        if (strcmp(tutorUsername, username) == 0 && strcmp(tutorPassword, password) == 0) {
            fclose(file);
            return 1;  // indicate login success
        }
    }

    fclose(file);
    return 0;  // indicate login failure
    
    
    if (strcmp(username, password) == 0) {
        return 1;
    } else {
        return 0;
    }
}



int tutorLogin() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loginSuccess = 0;

    while (!loginSuccess) {
        printf("Enter Tutor ID: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        loginSuccess = loginTutor(username, password);

        if (!loginSuccess) {
            printf("\033[1;31m"); // Set text color to red
            printf("Invalid Tutor ID or password. Please try again." "\xF0\x9F\x99\x83 " "\n"); // Unicode representation of the "upside-down face" emoji
            printf("\033[0m"); // Reset text color to default
        }
    }
    
    strncpy(loggedInTutorId, username, MAX_ID_LENGTH - 1);  // Store the logged-in tutor ID
    
    
    printf("\033[1;32m"); // Set text color to green
    printf("Tutor login successful!" "\xF0\x9F\x91\x8D " "\n");// Unicode representation of the "OK hand gesture" emoji
    printf("\033[0m"); // Reset text color to default
    return 1;  // Return 1 for successful login
}



int tutorExists(const char* username) {
    FILE* file = fopen("tutors.txt", "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No registered tutors found.\n");
        printf("\033[0m"); // Reset text color to default
        return 0;  // Tutor doesn't exist
    }

    char tutorUsername[MAX_USERNAME_LENGTH];

    while (fscanf(file, "%s", tutorUsername) == 1) {
        if (strcmp(tutorUsername, username) == 0) {
            fclose(file);
            return 1;  // Tutor exists
        }
    }

    fclose(file);
    return 0;  // Tutor doesn't exist
}




void registerStudent() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];

    printf("Enter Student ID: ");
    scanf("%s", username);

    if (studentExists(username)) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Student ID already exists. Please choose a different ID." "\xF0\x9F\x98\x85" "\n"); // Unicode representation of the "grinning face with sweat" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter name: ");
    getchar(); // Clear the newline character left by previous scanf
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    FILE* file = fopen("students.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", username, password, name);
        fclose(file);
        printf("\033[1;32m"); // Set text color to green
        printf("Student registered successfully." "\xE2\x9C\x85" "\n"); // Unicode representation of "✅" emoji
        printf("\033[0m"); // Reset text color to default
    } else {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for writing.\n");
        printf("\033[0m"); // Reset text color to default
    }
}


int loginStudent(const char* username, const char* password) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No registered students found.\n");
        printf("\033[0m"); // Reset text color to default
        return 0;  // indicate login failure
    }

    char studentUsername[MAX_USERNAME_LENGTH];
    char studentPassword[MAX_PASSWORD_LENGTH];
    char studentName[MAX_NAME_LENGTH];

    while (fscanf(file, "%s %s %[^\n]", studentUsername, studentPassword, studentName) == 3) {
        if (strcmp(studentUsername, username) == 0 && strcmp(studentPassword, password) == 0) {
            fclose(file);
            return 1;  // indicate login success
        }
    }

    fclose(file);
    return 0;  // indicate login failure
}


int studentLogin() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int loginSuccess = 0;

    while (!loginSuccess) {
        printf("Enter Student ID: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        loginSuccess = loginStudent(username, password);

        if (!loginSuccess) {
            printf("\033[1;31m"); // Set text color to red
            printf("Invalid Student ID or password. Please try again." "\xE2\x9D\x8C" "\n"); // Unicode representation of "❌" emoji
            printf("\033[0m"); // Reset text color to default
        }
    }
    
    strncpy(loggedInStudentId, username, MAX_ID_LENGTH - 1);  // Store the logged-in student TP number

    printf("\033[1;32m"); // Set text color to green
    printf("Student login successful!" "\xE2\x9C\x85" "\n"); // Unicode representation of "✅" emoji
    printf("\033[0m"); // Reset text color to default
    return 1;  // Return 1 for successful login
}


int studentExists(const char* username) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("\033[0m"); // Reset text color to default
        printf("No registered students found.\n");
        printf("\033[0m"); // Reset text color to default
        return 0;  // Student doesn't exist
    }

    char studentUsername[MAX_USERNAME_LENGTH];

    while (fscanf(file, "%s", studentUsername) == 1) {
        if (strcmp(studentUsername, username) == 0) {
            fclose(file);
            return 1;  // Student exists
        }
    }

    fclose(file);
    return 0;  // Student doesn't exist
}





void newSession() {
    char sessionCode[MAX_SESSION_LENGTH];
    char title[MAX_NAME_LENGTH];
    char day[MAX_NAME_LENGTH];
    char startTime[MAX_NAME_LENGTH];
    char location[MAX_NAME_LENGTH];
    char tutorCode[MAX_USERNAME_LENGTH];

    printf("Enter Session Code: ");
    scanf("%s", sessionCode);

    // Check if the session code already exists
    FILE* sessionFile = fopen("sessions.txt", "r");
    if (sessionFile != NULL) {
        char existingSessionCode[MAX_SESSION_LENGTH];
        while (fscanf(sessionFile, "%s", existingSessionCode) == 1) {
            if (strcmp(existingSessionCode, sessionCode) == 0) {
                fclose(sessionFile);
                printf("\033[1;31m"); // Set text color to red
                printf("Session with the same code already exists." "\xF0\x9F\x98\x85 " "\n"); // Unicode representation of the "grinning face with sweat" emoji
                printf("\033[0m"); // Reset text color to default
                return;
            }
        }
        fclose(sessionFile);
    }

    printf("Enter Title: ");
    getchar(); // Clear the newline character left by previous scanf
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove newline character

    printf("Enter Day: ");
    scanf("%s", day);

    printf("Enter Start Time: ");
    scanf("%s", startTime);

    printf("Enter Location: ");
    scanf("%s", location);

    printf("Enter Tutor Code: ");
    scanf("%s", tutorCode);

    // Check if the Tutor code already exists
    FILE* tutorFile = fopen("sessions.txt", "r");
    if (tutorFile != NULL) {
        char existingTutorCode[MAX_USERNAME_LENGTH];
        while (fscanf(tutorFile, "%s", existingTutorCode) == 1) {
            if (strcmp(existingTutorCode, tutorCode) == 0) {
                fclose(tutorFile);
                printf("\033[1;31m"); // Set text color to red
                printf("Tutor Code with the same code already exists." "\xF0\x9F\x98\x85" "\n"); // Unicode representation of the "grinning face with sweat" emoji
                printf("\033[0m"); // Reset text color to default
                return;
            }
        }
        fclose(tutorFile);
    }

    FILE* file = fopen("sessions.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s %s %s %s\n", sessionCode, title, day, startTime, location, tutorCode);
        fclose(file);
        printf("\033[1;32m"); // Set text color to green
        printf("Session created successfully." "\xE2\x9C\x85 " "\n"); // Unicode representation of "✅" emoji
        printf("\033[0m"); // Reset text color to default
    } else {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for writing.\n");
        printf("\033[0m"); // Reset text color to default
    }
}






void viewSessions(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("Unable to open the file.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("\033[1;32m"); // Set text color to green
    printf(" ---------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default

    char sessionCode[MAX_LINE_LENGTH];
    char tpNumber[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    char location[MAX_LINE_LENGTH];
    char tutorCode[MAX_LINE_LENGTH];

    // Read and display the header line
    fgets(sessionCode, sizeof(sessionCode), file);
    printf("\033[1;36m"); // Set text color to cyan
    printf("%13s  | %11s | %8s | %10s | %10s |\n", "Session Code", "TP Number", "Name", "Location", "Tutor Code");
    printf("\033[0m"); // Reset text color to default
    printf("\033[1;32m"); // Set text color to green
    printf(" ---------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default

    // Read and display each session
    while (fscanf(file, "%s %s %s %s %s", sessionCode, tpNumber, name, location, tutorCode) == 5) {
        printf("\033[1;36m"); // Set text color to green
        printf("%13s  | %11s | %8s | %10s | %10s |\n", sessionCode, tpNumber, name, location, tutorCode);
        printf("\033[0m"); // Reset text color to default
    }

    fclose(file);
}





void enrollStudent() {
    char sessionCode[MAX_SESSION_LENGTH];
    char tpNumber[MAX_TP_NUMBER_LENGTH];
    char studentName[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    char tutorCode[MAX_TUTOR_CODE_LENGTH];

    printf("Enter the session code: ");
    scanf("%s", sessionCode);

    // Check if the session code exists in sessions.txt
    FILE* sessionFile = fopen("sessions.txt", "r");
    if (sessionFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No sessions found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int sessionExists = 0;
    char savedSessionCode[MAX_SESSION_LENGTH];
    while (fscanf(sessionFile, "%s", savedSessionCode) != EOF) {
        if (strcmp(sessionCode, savedSessionCode) == 0) {
            sessionExists = 1;
            break;
        }
    }
    fclose(sessionFile);

    if (!sessionExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("Session with the provided code does not exist." "\xE2\x9D\x8C " "\n");// Unicode representation of "❌" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter the TP number: ");
    scanf("%s", tpNumber);

    // Check if the TP number exists in students.txt
    FILE* studentFile = fopen("students.txt", "r");
    if (studentFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No student records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int tpNumberExists = 0;
    char savedTPNumber[MAX_TP_NUMBER_LENGTH];
    while (fscanf(studentFile, "%s", savedTPNumber) != EOF) {
        if (strcmp(tpNumber, savedTPNumber) == 0) {
            tpNumberExists = 1;
            break;
        }
    }
    fclose(studentFile);

    if (!tpNumberExists) {
        printf("No TP number found.\n");
        return;
    }

    printf("Enter the student's name: ");
    getchar();  // Clear the newline character from the previous input
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = '\0';  // Remove the trailing newline

    // Check if the student name exists in students.txt
    FILE* studentFileCheck = fopen("students.txt", "r");
    if (studentFileCheck == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No student records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int studentNameExists = 0;
    char savedStudentName[MAX_NAME_LENGTH];
    while (fscanf(studentFileCheck, "%s", savedStudentName) != EOF) {
        if (strcmp(studentName, savedStudentName) == 0) {
            studentNameExists = 1;
            break;
        }
    }
    fclose(studentFileCheck);

    if (!studentNameExists) {
        printf("No student name found.\n");
        return;
    }

    printf("Enter the location: ");
    scanf("%s", location);

    printf("Enter the tutor code: ");
    scanf("%s", tutorCode);

    // Check if the tutor code exists in tutors.txt
    FILE* tutorFile = fopen("tutors.txt", "r");
    if (tutorFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No tutor records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int tutorExists = 0;
    char savedTutorCode[MAX_TUTOR_CODE_LENGTH];
    while (fscanf(tutorFile, "%s", savedTutorCode) != EOF) {
        if (strcmp(tutorCode, savedTutorCode) == 0) {
            tutorExists = 1;
            break;
        }
    }
    fclose(tutorFile);

    if (!tutorExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("Tutor with the provided code does not exist." "\xE2\x9D\x8C " "\n"); // Unicode representation of "❌" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    // Add the enrollment to the enrollments file
    FILE* enrollmentFile = fopen("enrollments.txt", "a");
    if (enrollmentFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for writing.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    fprintf(enrollmentFile, "%s %s %s %s %s\n", sessionCode, tpNumber, studentName, location, tutorCode);
    fclose(enrollmentFile);

    printf("\033[1;32m"); // Set text color to green
    printf("Enrollment successful!" "\xE2\x9C\x85 " "\n"); // Unicode representation of "✅" emoji
    printf("\033[0m"); // Reset text color to default
}








//Tutor Function

void tutorViewSessions() {
    char tutorId[MAX_ID_LENGTH];

    printf("Enter tutor ID: ");
    scanf("%s", tutorId);
    printf("\n");

    if (strcmp(tutorId, loggedInTutorId) != 0) {
        printf("\033[1;31m"); // Set text color to red
        printf("Please enter the same tutor ID that you logged in with." "\xF0\x9F\x98\x91" "\n"); // Unicode representation of the "expressionless face" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }
 
    FILE* file = fopen("sessions.txt", "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No session file found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    char line[MAX_LINE_LENGTH];
    bool foundSessions = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, tutorId) != NULL) {
            printf("\033[1;36m"); // Set text color to cyan
            printf("%s", line);
            printf("\033[0m"); // Reset text color to default
            foundSessions = true;
        }
    }

    fclose(file);

    if (!foundSessions) {
        printf("\033[1;31m"); // Set text color to red
        printf("No sessions assigned to this tutor ID.\n");
        printf("\033[0m"); // Reset text color to default
    }
}




//Student function

void studentEnroll() {



    
#define MAX_LINE_LENGTH 100
#define MAX_LOCATION_LENGTH 50
#define MAX_TUTOR_CODE_LENGTH 50
#define MAX_SESSION_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_TP_NUMBER_LENGTH 50

void sessionsView() {
    FILE* sessionFile = fopen("sessions.txt", "r");
    if (sessionFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No sessions found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("\033[1;32m"); // Set text color to green
    printf("------------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default
    
    printf("\033[1;36m"); // Set text color to cyan
    printf("%-6s %-20s %-15s %-8s %-4s\n", "| Code |", "| Session| ", "| Day&Time |", "| Location |", "| Tutor |");
    printf("\033[0m"); // Reset text color to default
    
    printf("\033[1;32m"); // Set text color to green
    printf("------------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default

    char sessionCode[MAX_LINE_LENGTH];
    char sessionName[MAX_LINE_LENGTH];
    char dayTime[MAX_LINE_LENGTH];
    char Location[MAX_LOCATION_LENGTH];
    char TutorCode[MAX_TUTOR_CODE_LENGTH];

    while (fscanf(sessionFile, "%s %[^\n] %[^\n] %s %[^\n]", sessionCode, sessionName, dayTime, Location, TutorCode) != EOF) {
        printf("\033[1;36m"); // Set text color to green
        printf("%-6s %-20s\n%-15s\n%-8s %-4s\n\n", sessionCode, sessionName, dayTime, Location, TutorCode);
        printf("\033[0m"); // Reset text color to default
    }

    fclose(sessionFile);
}




    char sessionCode[MAX_SESSION_LENGTH];
    char tpNumber[MAX_TP_NUMBER_LENGTH];
    char studentName[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    char tutorCode[MAX_TUTOR_CODE_LENGTH];

   FILE* sessionFile; // Declare sessionFile variable

    sessionsView(); // Call the sessionsView function to display sessions

    printf("Enter the session code: ");
    scanf("%s", sessionCode);

    // Check if the session code exists in sessions.txt
    sessionFile = fopen("sessions.txt", "r");
    if (sessionFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No sessions found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }
    int sessionExists = 0;
    char savedSessionCode[MAX_SESSION_LENGTH];
    while (fscanf(sessionFile, "%s", savedSessionCode) != EOF) {
        if (strcmp(sessionCode, savedSessionCode) == 0) {
            sessionExists = 1;
            break;
        }
    }
    fclose(sessionFile);

    if (!sessionExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("Session with the provided code does not exist." "\xF0\x9F\x98\x85 " "\n"); // Unicode representation of the "grinning face with sweat" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter the TP number: ");
    scanf("%s", tpNumber);

    // Check if the TP number exists in students.txt
    FILE* studentFile = fopen("students.txt", "r");
    if (studentFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No student records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int tpNumberExists = 0;
    char savedTPNumber[MAX_TP_NUMBER_LENGTH];
    while (fscanf(studentFile, "%s", savedTPNumber) != EOF) {
        if (strcmp(tpNumber, savedTPNumber) == 0) {
            tpNumberExists = 1;
            break;
        }
    }
    fclose(studentFile);

    if (!tpNumberExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("No TP number found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter the student's name: ");
    getchar();  // Clear the newline character from the previous input
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = '\0';  // Remove the trailing newline

    // Check if the student name exists in students.txt
    FILE* studentFileCheck = fopen("students.txt", "r");
    if (studentFileCheck == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No student records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int studentNameExists = 0;
    char savedStudentName[MAX_NAME_LENGTH];
    while (fscanf(studentFileCheck, "%s", savedStudentName) != EOF) {
        if (strcmp(studentName, savedStudentName) == 0) {
            studentNameExists = 1;
            break;
        }
    }
    fclose(studentFileCheck);

    if (!studentNameExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("No student name found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    // Check if the student is already enrolled in the session
    FILE* enrollmentFile = fopen("enrollments.txt", "r");
    if (enrollmentFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No enrollment records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    bool isEnrolled = false;
    char enrollmentSessionCode[MAX_SESSION_LENGTH];
    char enrollmentTPNumber[MAX_TP_NUMBER_LENGTH];
    while (fscanf(enrollmentFile, "%s %s", enrollmentSessionCode, enrollmentTPNumber) != EOF) {
        if (strcmp(sessionCode, enrollmentSessionCode) == 0 && strcmp(tpNumber, enrollmentTPNumber) == 0) {
            isEnrolled = true;
            break;
        }
    }
    fclose(enrollmentFile);

    if (isEnrolled) {
        printf("\033[1;31m"); // Set text color to red
        printf("The student is already enrolled in the session." "\xF0\x9F\x98\x85 " "\n"); // Unicode representation of the "grinning face with sweat" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    printf("Enter the location: ");
    scanf("%s", location);

    printf("Enter the tutor code: ");
    scanf("%s", tutorCode);

    // Check if the tutor code exists in tutors.txt
    FILE* tutorFile = fopen("tutors.txt", "r");
    if (tutorFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No tutor records found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    int tutorExists = 0;
    char savedTutorCode[MAX_TUTOR_CODE_LENGTH];
    while (fscanf(tutorFile, "%s", savedTutorCode) != EOF) {
        if (strcmp(tutorCode, savedTutorCode) == 0) {
            tutorExists = 1;
            break;
        }
    }
    fclose(tutorFile);

    if (!tutorExists) {
        printf("\033[1;31m"); // Set text color to red
        printf("Tutor with the provided code does not exist." "\xE2\x9D\x8C " "\n"); // Unicode representation of "❌" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    // Add the enrollment to the enrollments file
    enrollmentFile = fopen("enrollments.txt", "a");
    if (enrollmentFile == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for writing.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    fprintf(enrollmentFile, "%s %s %s %s %s\n", sessionCode, tpNumber, studentName, location, tutorCode);
    fclose(enrollmentFile);

    printf("\033[1;32m"); // Set text color to green
    printf("Enrollment successful!" "\xE2\x9C\x85 " "\n"); // Unicode representation of "✅" emoji
    printf("\033[0m"); // Reset text color to default
    

}






void studentViewSessions() {
    char studentId[MAX_ID_LENGTH];

    printf("Enter student TP number: ");
    scanf("%s", studentId);
    printf("\n");

    if (strcmp(studentId, loggedInStudentId) != 0) {
        printf("\033[1;31m"); // Set text color to red
        printf("Please enter the same TP number that you logged in with." "\xF0\x9F\x98\x91" "\n"); // Unicode representation of the "expressionless face" emoji
        printf("\033[0m"); // Reset text color to default
        return;
    }

    FILE* file = fopen("enrollments.txt", "r");
    if (file == NULL) {
        printf("\033[1;31m"); // Set text color to red
        printf("No enrollment file found.\n");
        printf("\033[0m"); // Reset text color to default
        return;
    }

    char line[MAX_LINE_LENGTH];
    bool foundSessions = false;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, studentId) != NULL) {
            printf("\033[1;36m"); // Set text color to cyan
            printf("%s", line);
            printf("\033[0m"); // Reset text color to default
            foundSessions = true;
        }
    }

    fclose(file);

    if (!foundSessions) {
        printf("\033[1;31m"); // Set text color to red
        printf("No sessions enrolled for this student TP number." "\xE2\x9D\x8C " "\n"); // Unicode representation of "❌" emoji
        printf("\033[0m"); // Reset text color to default
    }
}





