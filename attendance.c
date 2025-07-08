#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student 
{
    int roll;
    char name[50];
};

struct Attendance 
{
    int roll;
    char date[15];
    char status[10];
};

void addStudent() 
{
    FILE *fp = fopen("students.txt", "a");
    struct Student s;

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar(); // Clear input buffer
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove newline

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudents() 
{
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    printf("\n--- Student List ---\n");
    while (fread(&s, sizeof(s), 1, fp)) 
    {
        printf("Roll: %d | Name: %s\n", s.roll, s.name);
    }
    fclose(fp);
}

void markAttendance() {
    FILE *fp = fopen("students.txt", "r");
    FILE *afp = fopen("attendance.txt", "a");

    struct Student s;
    struct Attendance a;
    char date[15];

    printf("Enter date (dd-mm-yyyy): ");
    getchar(); // Clear buffer
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0; // Remove newline

    while (fread(&s, sizeof(s), 1, fp)) 
    {
        a.roll = s.roll;
        strcpy(a.date, date);

        printf("Mark attendance for %s (Roll %d) (P/A): ", s.name, s.roll);
        char ch;
        scanf(" %c", &ch);
        strcpy(a.status, (ch == 'P' || ch == 'p') ? "Present" : "Absent");

        fwrite(&a, sizeof(a), 1, afp);
    }

    fclose(fp);
    fclose(afp);
    printf("Attendance marked for date %s.\n", date);
}

void viewAttendanceReport() 
{
    FILE *sfp = fopen("students.txt", "r");
    struct Student s;

    printf("\n--- Attendance Report ---\n");

    while (fread(&s, sizeof(s), 1, sfp)) 
    {
        printf("\nRoll: %d | Name: %s\n", s.roll, s.name);
        printf("Date\t\tStatus\n");

        FILE *afp = fopen("attendance.txt", "r");
        struct Attendance a;

        while (fread(&a, sizeof(a), 1, afp)) 
        {
            if (a.roll == s.roll) 
            {
                printf("%s\t%s\n", a.date, a.status);
            }
        }
        fclose(afp);
    }
    fclose(sfp);
}

int main()
{
    int choice;
    while (1) 
    {
        printf("\n===== Student Attendance System =====\n");
        printf("1. Add Student\n2. View Students\n3. Mark Attendance\n4. View Attendance Report\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: markAttendance(); break;
            case 4: viewAttendanceReport(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
