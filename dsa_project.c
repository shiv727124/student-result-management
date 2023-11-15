#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    char studentClass[10];
    char section;
    struct MarksStack* marksStack;
    struct Student* next;
};

struct MarksStack {
    int marks;
    struct MarksStack* next;
};

struct Student* head = NULL;

void push(struct MarksStack** top, int marks) {
    struct MarksStack* newMarks = (struct MarksStack*)malloc(sizeof(struct MarksStack));
    newMarks->marks = marks;
    newMarks->next = *top;
    *top = newMarks;
}

void insert(char name[], int rollNumber, char studentClass[], char section, int marksDDCO, int marksDSA, int marksAFLL, int marksSDS) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->studentClass, studentClass);
    newStudent->section = section;

    if (head == NULL || head->rollNumber >= newStudent->rollNumber) {
        newStudent->next = head;
        head = newStudent;
    } else {
        struct Student* current = head;
        while (current->next != NULL && current->next->rollNumber < newStudent->rollNumber) {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;
    }

    newStudent->marksStack = NULL;
    push(&(newStudent->marksStack), marksDDCO);
    push(&(newStudent->marksStack), marksDSA);
    push(&(newStudent->marksStack), marksAFLL);
    push(&(newStudent->marksStack), marksSDS);
}

void display() {
    struct Student* ptr = head;
    printf("\nStudent Information:\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-11s | %-6s | %-7s | %-4s | %-4s | %-4s | %-4s |\n", "Name", "Roll Number", "Class", "Section", "DDCO", "DSA", "AFLL", "SDS");
    printf("-------------------------------------------------------------------------------------\n");
    while (ptr != NULL) {
        printf("| %-20s | %-11d | %-6s | %-7c | ", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section);
        struct MarksStack* marksPtr = ptr->marksStack;
        while (marksPtr != NULL) {
            printf("%-4d | ", marksPtr->marks);
            marksPtr = marksPtr->next;
        }
        printf("\n");
        ptr = ptr->next;
    }
    printf("-------------------------------------------------------------------------------------\n");
}

void searchByRollNo(int rollNumber) {
    struct Student* ptr = head;
    while (ptr != NULL) {
        if (ptr->rollNumber == rollNumber) {
            printf("\nStudent Information:\n");
            printf("Name: %s, Roll Number: %d, Class: %s, Section: %c, Marks: ", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section);
            struct MarksStack* marksPtr = ptr->marksStack;
            while (marksPtr != NULL) {
                printf("%d ", marksPtr->marks);
                marksPtr = marksPtr->next;
            }
            printf("\n");
            return;
        }
        ptr = ptr->next;
    }
    printf("Student not found.\n");
}

void showToppers() {
    printf("\nSubject Toppers:\n");
    int highestDDCO = 0, highestDSA = 0, highestAFLL = 0, highestSDS = 0;
    struct Student* ptr = head;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        if (marksPtr->marks > highestDDCO) {
            highestDDCO = marksPtr->marks;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks > highestDSA) {
            highestDSA = marksPtr->marks;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks > highestAFLL) {
            highestAFLL = marksPtr->marks;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks > highestSDS) {
            highestSDS = marksPtr->marks;
        }
        ptr = ptr->next;
    }

    ptr = head;
    int countDDCO = 0, countDSA = 0, countAFLL = 0, countSDS = 0;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        if (marksPtr->marks == highestDDCO) {
            printf("DDCO Topper:     %s  (Roll Number: %d      Class: %s       Section: %c         Marks: %d)\n", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section, highestDDCO);
            countDDCO++;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks == highestDSA) {
            printf("DSA Topper:     %s  (Roll Number: %d      Class: %s       Section: %c         Marks: %d)\n", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section, highestDSA);
            countDSA++;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks == highestAFLL) {
            printf("AFLL Topper:    %s  (Roll Number: %d      Class: %s       Section: %c         Marks: %d)\n", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section, highestAFLL);
            countAFLL++;
        }
        marksPtr = marksPtr->next;
        if (marksPtr->marks == highestSDS) {
            printf("SDS Topper:     %s  (Roll Number: %d      Class: %s       Section: %c         Marks: %d)\n", ptr->name, ptr->rollNumber, ptr->studentClass, ptr->section, highestSDS);
            countSDS++;
        }
        ptr = ptr->next;
    }

    if (countDDCO > 1) {
        printf("%d students share the top position in DDCO.\n", countDDCO);
    }
    if (countDSA > 1) {
        printf("%d students share the top position in DSA.\n", countDSA);
    }
    if (countAFLL > 1) {
        printf("%d students share the top position in AFLL.\n", countAFLL);
    }
    if (countSDS > 1) {
        printf("%d students share the top position in SDS.\n", countSDS);
    }
}

void scholarshipEligibility() {
    printf("\nScholarship Eligibility:\n");
    struct Student* ptr = head;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        if (marksPtr->marks > 90) {
            marksPtr = marksPtr->next;
            if (marksPtr->marks > 90) {
                marksPtr = marksPtr->next;
                if (marksPtr->marks > 90) {
                    marksPtr = marksPtr->next;
                    if (marksPtr->marks > 90) {
                        printf("Scholarship eligible student: %s (Roll Number: %d)\n", ptr->name, ptr->rollNumber);
                    }
                }
            }
        }
        ptr = ptr->next;
    }
}

void showFailures() {
    printf("\nList of Students Who Have Failed:\n");
    struct Student* ptr = head;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        if (marksPtr->marks < 33 || marksPtr->next->marks < 33 || marksPtr->next->next->marks < 33 || marksPtr->next->next->next->marks < 33) {
            printf("%s (Roll Number: %d) has failed.\n", ptr->name, ptr->rollNumber);
        }
        ptr = ptr->next;
    }
}

void showAverageMarks() {
    printf("\nAverage Marks in Each Subject:\n");
    float sumDDCO = 0, sumDSA = 0, sumAFLL = 0, sumSDS = 0;
    int count = 0;
    struct Student* ptr = head;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        sumDDCO += marksPtr->marks;
        marksPtr = marksPtr->next;
        sumDSA += marksPtr->marks;
        marksPtr = marksPtr->next;
        sumAFLL += marksPtr->marks;
        marksPtr = marksPtr->next;
        sumSDS += marksPtr->marks;
        count++;
        ptr = ptr->next;
    }
    printf("DDCO: %.2f\n", sumDDCO / count);
    printf("DSA: %.2f\n", sumDSA / count);
    printf("AFLL: %.2f\n", sumAFLL / count);
    printf("SDS: %.2f\n", sumSDS / count);
}

void showDistinctionAwardStudents() {
    printf("\nStudents Eligible for Distinction Award:\n");
    struct Student* ptr = head;
    while (ptr != NULL) {
        struct MarksStack* marksPtr = ptr->marksStack;
        if (marksPtr->marks >= 80 && marksPtr->marks <= 90) {
            marksPtr = marksPtr->next;
            if (marksPtr->marks >= 80 && marksPtr->marks <= 90) {
                marksPtr = marksPtr->next;
                if (marksPtr->marks >= 80 && marksPtr->marks <= 90) {
                    marksPtr = marksPtr->next;
                    if (marksPtr->marks >= 80 && marksPtr->marks <= 90) {
                        printf("%s (Roll Number: %d) is eligible for the distinction award.\n", ptr->name, ptr->rollNumber);
                    }
                }
            }
        }
        ptr = ptr->next;
    }
}

int main() {
    int choice;
    char name[50];
    char studentClass[10];
    char section;
    int rollNumber, marksDDCO, marksDSA, marksAFLL, marksSDS;
    while (1) {
        printf("\n1. Add a student\n");
        printf("2. Display student information\n");
        printf("3. Search by roll number\n");
        printf("4. Show subject toppers\n");
        printf("5. Scholarship eligibility\n");
        printf("6. Show Failures\n");
        printf("7. Show Average Marks in Each Subject\n");
        printf("8. Show Distinction Award Students\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter roll number: ");
                scanf("%d", &rollNumber);
                printf("Enter class: ");
                scanf("%s", studentClass);
                printf("Enter section: ");
                scanf(" %c", &section);
                printf("Enter marks for DDCO: ");
                scanf("%d", &marksDDCO);
                printf("Enter marks for DSA: ");
                scanf("%d", &marksDSA);
                printf("Enter marks for AFLL: ");
                scanf("%d", &marksAFLL);
                printf("Enter marks for SDS: ");
                scanf("%d", &marksSDS);
                insert(name, rollNumber, studentClass, section, marksDDCO, marksDSA, marksAFLL, marksSDS);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &rollNumber);
                searchByRollNo(rollNumber);
                break;
            case 4:
                showToppers();
                break;
            case 5:
                scholarshipEligibility();
                break;
            case 6:
                showFailures();
                break;
            case 7:
                showAverageMarks();
                break;
            case 8:
                showDistinctionAwardStudents();
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}