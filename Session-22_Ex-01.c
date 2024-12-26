#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[100];
    int age;
} Student;

void loadStudents(Student students[], int *size, FILE *file);
void saveStudents(Student students[], int size, FILE *file);
void displayStudents(Student students[], int size);
void addStudent(Student students[], int *size, FILE *file);
void editStudent(Student students[], int size, FILE *file);
void deleteStudent(Student students[], int *size, FILE *file);
void searchStudent(Student students[], int size);
void sortStudents(Student students[], int size);

int main()
{
    Student students[100];
    int size = 0;
    int choice;
    FILE *file = fopen("students.bin", "rb");
    if (file != NULL)
    {
        loadStudents(students, &size, file);
        fclose(file);
    }

    do
    {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayStudents(students, size);
            break;
        case 2:
            addStudent(students, &size, file);
            break;
        case 3:
            editStudent(students, size, file);
            break;
        case 4:
            deleteStudent(students, &size, file);
            break;
        case 5:
            searchStudent(students, size);
            break;
        case 6:
            sortStudents(students, size);
            saveStudents(students, size, file);
            break;
        case 7:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 7);

    return 0;
}

void loadStudents(Student students[], int *size, FILE *file)
{
    file = fopen("students.bin", "rb");
    if (file == NULL)
    {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(students, sizeof(Student), *size, file);
    fclose(file);
}

void saveStudents(Student students[], int size, FILE *file)
{
    file = fopen("students.bin", "wb");
    if (file == NULL)
    {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), size, file);
    fclose(file);
}

void displayStudents(Student students[], int size)
{
    if (size == 0)
    {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < size; i++)
    {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent(Student students[], int *size, FILE *file)
{
    if (*size >= 100)
    {
        printf("Danh sach sinh vien da day!\n");
        return;
    }
    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[*size] = newStudent;
    (*size)++;

    saveStudents(students, *size, file);
    printf("Them sinh vien thanh cong!\n");
}

void editStudent(Student students[], int size, FILE *file)
{
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++)
    {
        if (students[i].id == id)
        {
            printf("Nhap ten moi: ");
            getchar();
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);

            saveStudents(students, size, file);
            printf("Sua thong tin sinh vien thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void deleteStudent(Student students[], int *size, FILE *file)
{
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *size; i++)
    {
        if (students[i].id == id)
        {
            for (int j = i; j < *size - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*size)--;
            saveStudents(students, *size, file);
            printf("Xoa sinh vien thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void searchStudent(Student students[], int size)
{
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < size; i++)
    {
        if (students[i].id == id)
        {
            printf("Thong tin sinh vien:\n");
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void sortStudents(Student students[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (students[i].id > students[j].id)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Sap xep danh sach sinh vien theo ID thanh cong!\n");
}
