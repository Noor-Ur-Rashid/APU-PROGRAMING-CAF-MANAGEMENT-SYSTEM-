#include <stdio.h>
#include "function.h"

int main() {
    loadUsersFromFile();

    int choice;
    int mainExit = 0;

    while (!mainExit) {
        printf("\033[1;36m"); // Set text color to cyan
        printf("\n\n" "\xE2\x9C\xA8 \xF0\x9F\x8C\x9F " " Welcome to APU Programing Café Management System " "\xE2\x9C\xA8 \xF0\x9F\x8C\x9F " "\n"); //Unicode representation of the "sparkles" emoji AND Unicode representation of the "star" emoji
        printf("\033[0m"); // Reset text color to default
        
        printf("Please select role:\n");
        printf("1. Admin\n");
        printf("2. Tutor\n");
        printf("3. Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int ad_choice;
                int adminExit = 0;

                int ad_choice1;
                int registerExit = 0;

                while (!registerExit) {
                    printf("\n\n1. Register\n");
                    printf("2. Login\n");
                    printf("3. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ad_choice1);

                    switch (ad_choice1) {
                        case 1: {
                            char username[MAX_USERNAME_LENGTH];
                            char password[MAX_PASSWORD_LENGTH];
                            printf("Enter username: ");
                            scanf("%s", username);
                            printf("Enter password: ");
                            scanf("%s", password);
                            registerUser(username, password);
                            break;
                        }

                        case 2: {
                            char username[MAX_USERNAME_LENGTH];
                            char password[MAX_PASSWORD_LENGTH];
                            printf("Enter username: ");
                            scanf("%s", username);
                            printf("Enter password: ");
                            scanf("%s", password);
                            int loginSuccess = loginUser(username, password);
                            adminExit = 0;

                            if (loginSuccess) {
                                while (!adminExit) {
                                    printf("\033[1;31m"); // Set text color to red
                                    printf("\n\nWelcome to admin page..." "\xF0\x9F\x98\x88 " "\n"); // Unicode representation of the "smiling face with horns" emoji
                                    printf("\033[0m"); // Reset text color to default
                                    
                                    printf("Select function:\n");
                                    printf("1. Register new tutor\n");
                                    printf("2. Register new student\n");
                                    printf("3. Make new session\n");
                                    printf("4. View sessions\n");
                                    printf("5. Enroll student\n");
                                    printf("6. Exit\n");
                                    printf("Enter your choice: ");
                                    scanf("%d", &ad_choice);

                                    switch (ad_choice) {
                                        case 1:
                                            printf("Registering a new tutor...\n\n");
                                            registerTutor();
                                            break;
                                        case 2:
                                            printf("Registering a new student...\n\n");
                                            registerStudent();
                                            break;
                                        case 3:
                                            printf("Creating new sessions...\n\n");
                                            newSession();
                                            break;
                                        case 4:
                                            printf("Viewing sessions...\n\n");
                                            viewSessions("enrollments.txt");
                                            break;
                                        case 5:
                                            printf("Enrolling a student...\n\n");
                                            enrollStudent();
                                            break;
                                        case 6:
                                            printf("Exiting Admin page...\n");
                                            adminExit = 1;
                                            break;
                                        default:
                                            printf("\033[1;31m"); // Set text color to red
                                            printf("Incorrect choice, try again." "\xF0\x9F\x98\x94 " "\n"); // Unicode representation of the "pensive face" emoji
                                            printf("\033[0m"); // Reset text color to default
                                            break;
                                    }
                                }
                            } else {
                                printf("\033[1;31m"); // Set text color to red
                                printf("Invalid username or password. Please try again." "\xF0\x9F\x98\x94 " "\n");  // Unicode representation of the "pensive face" emoji
                                printf("\033[0m"); // Reset text color to default
                                
                            }
                            break;
                        }

                        case 3:
                            registerExit = 1;
                            break;

                        default:
                            printf("\033[1;31m"); // Set text color to red
                            printf("Invalid choice. Please try again." "\xE2\x98\xB9\xEF\xB8\x8F " "\n"); // Unicode representation of the "white frowning face" emoji
                            printf("\033[0m"); // Reset text color to default
                            break;
                    }
                }
                break;
            }

            case 2: {
                int tu_choice;
                int tutorExit = 0;
                
                if (tutorLogin()) {
                    while (!tutorExit) {
                        printf("\033[1;36m"); // Set text color to cyan
                        printf("\n\nWelcome to Tutor page..." "\xF0\x9F\x91\xA9\xE2\x80\x8D\xF0\x9F\x8F\xAB " "\xF0\x9F\x91\xA8\xE2\x80\x8D\xF0\x9F\x8F\xAB" "\n"); // Unicode representation of the "woman teacher" emoji AND  Unicode representation of the "man teacher" emoji
                        printf("\033[0m"); // Reset text color to default
                        printf("Select function:\n");
                        printf("1. View sessions\n");
                        printf("2. Exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &tu_choice);
    
                        switch (tu_choice) {
                            case 1:
                                printf("Viewing Tutor session...\n");
                                tutorViewSessions();
                                break;
    
                            case 2:
                                printf("Exiting Tutor page...\n");
                                tutorExit = 1;
                                break;
    
                            default:
                                printf("\033[1;31m"); // Set text color to red
                                printf("Incorrect choice, try again." "\xF0\x9F\x99\x83 "); // Unicode representation of the "upside-down face" emoji
                                printf("\033[0m"); // Reset text color to default
                                break;
                        }
                    }
                }    
                break;
            }

            case 3: {
                int st_choice;
                int student_Exit = 0;
                
                if (studentLogin()) {
                    while (!student_Exit) {
                        printf("\033[1;36m"); // Set text color to cyan
                        printf("\n\nWelcome to student page..." "\xF0\x9F\x91\xA9\xE2\x80\x8D\xF0\x9F\x92\xBB " "\xF0\x9F\xA7\x91\xE2\x80\x8D\xF0\x9F\x92\xBB" "\n"); // Unicode representation of the "woman technologist" emoji AND Unicode representation of the "person technologist" emoji
                        printf("\033[0m"); // Reset text color to default
                        printf("Select function:\n");
                        printf("1. Enroll\n");
                        printf("2. View sessions\n");
                        printf("3. Exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &st_choice);
    
                        switch (st_choice) {
                            case 1:
                                printf("Student enrolling by themself...\n\n");
                                studentEnroll();
                                break;
    
                            case 2:
                                printf("Viewing student's session...\n");
                                studentViewSessions();
                                break;
    
                            case 3:
                                printf("Exiting Student page...\n");
                                student_Exit = 1;
                                break;
    
                            default:
                                printf("\033[1;31m"); // Set text color to red
                                printf("Incorrect choice, try again." "\xF0\x9F\x98\x94 " "\n"); // Unicode representation of the "pensive face" emoji
                                printf("\033[0m"); // Reset text color to default
                                break;
                        }
                    }
                }
                break;
            }

            case 4:
                printf("Goodbye see you later..." "\xF0\x9F\x91\x8B "); // Unicode representation of the "waving hand" emoji
                mainExit = 1;
                break;

            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Incorrect choice, try again." "\xE2\x98\xB9\xEF\xB8\x8F "  "\n"); // Unicode representation of the "white frowning face" emoji
                printf("\033[0m"); // Reset text color to default
                break;
        }
    }

    return 0;
}
