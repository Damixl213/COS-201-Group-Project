#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100
#define PASSING_THRESHOLD 40


char calculate_grade() {
    int score;
    if (score > 79 && score <= 100) {
        return 'A';
    } else if (score > 69 && score <= 79) {
        return 'B';
    } else if (score > 59 && score <= 69) {
        return 'C';
    } else if (score > 49 && score <= 59) {
        return 'D';
    } else if (score >= 0 && score <= 49) {
        return 'F';
    } else {
        return 'I'; // Invalid score indicator
    }
}

typedef struct {
    char name[50];
    int rollNumber;
    int marks;
} Student;

Student *students = NULL;
int studentCount = 0;
int maxStudents = 10;

void greetUser() {
    char name[100];
    printf("Welcome to the Student Record System!\n");
    printf("Please enter your name: ");
    scanf("%99s", name);
    printf("Hello, %s!\n", name);
    
    int age;
    printf("Your age: ");
    scanf("%d", &age);
    if (age < 17) {
        printf("You are too young to for this program.\n");
        exit(1);
    } 
    else if (age > 17) {
        printf("You are welcome to the program.\n");
    }
    else {
        printf("You are welcome to the program.\n");
    }
}

void addStudent() {
    if (studentCount >= maxStudents) {
        maxStudents *= 2;
        students = realloc(students, maxStudents * sizeof(Student));
        if (students == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    Student newStudent;
    printf("Enter student firstname: ");
    scanf("%49s", newStudent.name);
    printf("Enter student lastname: ");
    scanf("%49s", newStudent.name + strlen(newStudent.name));
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter marks: ");
    scanf("%d", &newStudent.marks);

    students[studentCount++] = newStudent;
    printf("Student added successfully.\n");
}

void modifyStudent() {
    int rollNumber;
    printf("Enter roll number of the student to modify: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new marks: ");
            scanf("%d", &students[i].marks);
            printf("Student information updated.\n");
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("Student Records:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %d", students[i].name, students[i].rollNumber, students[i].marks);
        if (students[i].marks >= PASSING_THRESHOLD) {
            printf(" (Pass)\n");
        } else {
            printf(" (Fail)\n");
        }
    }
}

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %d\n", students[i].name, students[i].rollNumber, students[i].marks);
    }

    fclose(file);
    printf("Student records saved to file.\n");
}

void loadStudentsFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    studentCount = 0;
    while (fscanf(file, "%s %d %d", students[studentCount].name, &students[studentCount].rollNumber, &students[studentCount].marks) != EOF) {
        studentCount++;
        if (studentCount >= maxStudents) {
            maxStudents *= 2;
            students = realloc(students, maxStudents * sizeof(Student));
            if (students == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }
    }

    fclose(file);
    printf("Student records loaded from file.\n");
}

void searchStudent() {
    int rollNumber;
    printf("Pleae enter the student roll number : ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Student found:\n");
            printf("Name: %s, Roll Number: %d, Marks: %d", students[i].name, students[i].rollNumber, students[i].marks);
            if (students[i].marks >= PASSING_THRESHOLD) {
                printf(" (Pass)\n");
            } else {
                printf(" (Fail)\n");
            }
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber, "please try again 😥.\n");
}

void calculateAverageMarks() {
    if (studentCount == 0) {
        printf("No students to calculate average marks.\n");
        return;
    }

    int totalMarks = 0;
    for (int i = 0; i < studentCount; i++) {
        totalMarks += students[i].marks;
    }

    float averageMarks = (float)totalMarks / studentCount;
    printf("Average marks of all students: %.2f\n", averageMarks);
}

int compareMarksAsc(const void *a, const void *b) {
    return ((Student *)a)->marks - ((Student *)b)->marks;
}

int compareMarksDesc(const void *a, const void *b) {
    return ((Student *)b)->marks - ((Student *)a)->marks;
}

void sortStudents() {
    int choice;
    printf("Sort by marks:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        qsort(students, studentCount, sizeof(Student), compareMarksAsc);
        printf("Students sorted by marks in ascending order.\n");
    } else if (choice == 2) {
        qsort(students, studentCount, sizeof(Student), compareMarksDesc);
        printf("Students sorted by marks in descending order.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

int main() {
    students = malloc(maxStudents * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    greetUser();

    int choice;
    do {
        printf("\nStudent Record System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Modify Student\n");
        printf("3. Display Students\n");
        printf("4. Save Students to File\n");
        printf("5. Load Students from File\n");
        printf("6. Search Student\n");
        printf("7. Calculate Average Marks\n");
        printf("8. Sort Students by Marks\n");
        printf("9. calculate your Gp\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                modifyStudent();
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                saveStudentsToFile();
                break;
            case 5:
                loadStudentsFromFile();
                break;
            case 6:
                searchStudent();
                break;
            case 7:
                calculateAverageMarks();
                break;
            case 8:
                sortStudents();
                break;
            case 9:
                calculate_grade();
                break;
            case 10:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    free(students);
    return 0;
}