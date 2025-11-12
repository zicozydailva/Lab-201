#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef struct {
    char name[50];
    int roll_no;
    float marks;
} Student;

// Function declarations
void addStudent(Student **students, int *count);
void displayStudents(Student *students, int count);
void modifyStudent(Student *students, int count);
void removeStudent(Student **students, int *count);
void saveToFile(Student *students, int count);
void loadFromFile(Student **students, int *count);
void searchStudent(Student *students, int count);
void calculateAverage(Student *students, int count);
void sortStudents(Student *students, int count, int ascending);

int main() {
    char username[50];
    int choice;
    Student *students = nullptr;
    int count = 0;

    printf("Welcome to the Student Management System\n");
    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Hello, %s! Let's manage student records.\n\n", username);

    // Load any previously saved records
    loadFromFile(&students, &count);

    do {
        printf("\n========= MENU =========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Modify Student\n");
        printf("4. Remove Student\n");
        printf("5. Search Student\n");
        printf("6. Calculate Average Marks\n");
        printf("7. Sort Students (1=Asc, 0=Desc)\n");
        printf("8. Save and Exit\n");
        printf("========================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(&students, &count); break;
            case 2: displayStudents(students, count); break;
            case 3: modifyStudent(students, count); break;
            case 4: removeStudent(&students, &count); break;
            case 5: searchStudent(students, count); break;
            case 6: calculateAverage(students, count); break;
            case 7: {
                int order;
                printf("Enter 1 for ascending or 0 for descending: ");
                scanf("%d", &order);
                sortStudents(students, count, order);
                break;
            }
            case 8:
                saveToFile(students, count);
                printf("Records saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    free(students);
    return 0;
}

// -----------------------------------------------------------
// Add a new student record
void addStudent(Student **students, int *count) {
    *students = (Student *) realloc(*students, (*count + 1) * sizeof(Student));
    if (!*students) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    Student *newStudent = &(*students)[*count];
    printf("Enter name: ");
    getchar(); // clear leftover newline
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = 0;

    printf("Enter roll number: ");
    scanf("%d", &newStudent->roll_no);

    printf("Enter marks: ");
    scanf("%f", &newStudent->marks);

    (*count)++;
    printf("✅ Student added successfully!\n");
}

// -----------------------------------------------------------
// Display all students
void displayStudents(Student *students, int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-5s %-25s %-10s\n", "Roll", "Name", "Marks");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-25s %-10.2f\n", students[i].roll_no, students[i].name, students[i].marks);
    }
}

// -----------------------------------------------------------
// Modify a student's record
void modifyStudent(Student *students, int count) {
    int roll;
    printf("Enter roll number to modify: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll) {
            printf("Enter new name: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            printf("✅ Record updated successfully.\n");
            return;
        }
    }
    printf("❌ Student not found.\n");
}

// -----------------------------------------------------------
// Remove a student record
void removeStudent(Student **students, int *count) {
    int roll;
    printf("Enter roll number to remove: ");
    scanf("%d", &roll);

    for (int i = 0; i < *count; i++) {
        if ((*students)[i].roll_no == roll) {
            for (int j = i; j < *count - 1; j++)
                (*students)[j] = (*students)[j + 1];
            (*count)--;

            *students = (Student *) realloc(*students, (*count) * sizeof(Student));
            printf("✅ Student removed successfully.\n");
            return;
        }
    }
    printf("❌ Student not found.\n");
}

// -----------------------------------------------------------
// Save all student records to file
void saveToFile(Student *students, int count) {
    FILE *file = fopen("students.txt", "w");
    if (!file) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f\n", students[i].roll_no, students[i].name, students[i].marks);
    }

    fclose(file);
}

// -----------------------------------------------------------
// Load records from file at program start
void loadFromFile(Student **students, int *count) {
    FILE *file = fopen("students.txt", "r");
    if (!file) return; // file doesn’t exist yet

    Student temp;
    while (fscanf(file, "%d,%49[^,],%f\n", &temp.roll_no, temp.name, &temp.marks) == 3) {
        *students = (Student *) realloc(*students, (*count + 1) * sizeof(Student));
        (*students)[*count] = temp;
        (*count)++;
    }
    fclose(file);
}

// -----------------------------------------------------------
// Search for a student by roll number
void searchStudent(Student *students, int count) {
    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll) {
            printf("✅ Found: %s (Marks: %.2f)\n", students[i].name, students[i].marks);
            return;
        }
    }
    printf("❌ Student not found.\n");
}

// -----------------------------------------------------------
// Calculate average marks
void calculateAverage(Student *students, int count) {
    if (count == 0) {
        printf("No records to calculate average.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < count; i++)
        total += students[i].marks;

    printf("📊 Average Marks: %.2f\n", total / count);
}

// -----------------------------------------------------------
// Sort students by marks
void sortStudents(Student *students, int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((ascending && students[i].marks > students[j].marks) ||
                (!ascending && students[i].marks < students[j].marks)) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("✅ Students sorted successfully.\n");
}
