#include <iostream>
#include <stdio.h>
#include <string.h>

int main() {
    // VARIABLE DECLARATION
    char username[50];
    char student_name[50];
    int roll_no;
    int marks;

    // INPUT OF FIELDS
    printf("Welcome to student management system\n");

    printf("Enter your username: ");
    scanf("%s", username); // okay here since username likely has no spaces

    printf("Welcome to student management system: %s\n", username);

    printf("Enter your student name: ");
    getchar(); // clear leftover newline from previous scanf
    fgets(student_name, sizeof(student_name), stdin);
    student_name[strcspn(student_name, "\n")] = 0; // remove trailing newline

    printf("Enter student roll number: ");
    scanf("%d", &roll_no);

    printf("Enter Student Marks: ");
    scanf("%d", &marks);

    // PASS AND FAILED CONDITIONAL CHECKS
    if (marks > 40) {
        printf("Student: %s with roll number: %d passed with score of %d\n", student_name, roll_no, marks);
    } else {
        printf("Student: %s with roll number: %d failed with score of %d\n", student_name, roll_no, marks);
    }

    return 0;
}
