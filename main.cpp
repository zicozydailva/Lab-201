#include <iostream>
#include <stdio.h> // input and out library

int main() {

    char username[50];
    char student_name[50];
    int roll_no;
    int marks;

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

    return 0;
}