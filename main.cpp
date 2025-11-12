#include <iostream>
#include <stdio.h> // input and out library

int main() {

    // DATA STORAGE
    char username[50];
    char student_name[50];
    int roll_no;
    int marks;

    // INPUTS and DATA COLLECTION
    printf("Welcome to student management system\n");
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Welcome to student management system: %s \n", username);

    printf("Enter your student name: ");
    scanf("%s", student_name);

    printf("Enter student roll number: ");
    scanf("%d", &roll_no);

    printf("Enter Student Marks:  ");
    scanf("%d", &marks);

    // LOOP TO CHECK IF STUDENT PASSED OR FAILED
    if (marks > 40) {
        printf("Student: %s with roll number: %d passed with score of %d", student_name, roll_no, marks);
    } else {
        printf("Student: %s with roll number: %d failed with score of %d", student_name, roll_no, marks);
    }

    return 0;
}