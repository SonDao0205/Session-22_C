#include<stdio.h>
#include<string.h>

typedef struct {
    char username[100];
    char password[100];
} Accounts;

Accounts accounts[100];
Accounts newAccounts;

void logIn(Accounts accounts[100], int *size, FILE *file);
void signUp(Accounts accounts[100], Accounts newAccounts, int *size, FILE *file);
void loadAccounts(Accounts accounts[100], int *size, FILE *file);
void saveAccounts(Accounts accounts[100], int *size, FILE *file);

int main() {
    FILE *file;
    int choice, size;
    loadAccounts(accounts, &size, file);

    do {                       
        printf("\n________________________\n");
        printf("             Menu\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        printf("________________________\n");
        switch (choice) {
            case 1:
                logIn(accounts, &size, file);
                break;
            case 2:
                signUp(accounts, newAccounts, &size, file);
                break;
            case 3:
                printf("Tam biet!\n");
                break;
            default:
                printf("Khong hop le! Nhap lai!\n");
                break;
        }
    } while (choice != 3);
}

void loadAccounts(Accounts accounts[100], int *size, FILE *file) {
    file = fopen("Account.bin", "rb");
    if (file == NULL) {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(accounts, sizeof(Accounts), *size, file);
    fclose(file);
}

void saveAccounts(Accounts accounts[100], int *size, FILE *file) {
    file = fopen("Account.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    fwrite(size, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Accounts), *size, file);
    fclose(file);
}

void logIn(Accounts accounts[100], int *size, FILE *file) {
    char confirmAccounts[100];
    char confirmPassword[100];
    printf("Tai Khoan: ");
    getchar();
    fgets(confirmAccounts, 100, stdin);
    confirmAccounts[strcspn(confirmAccounts, "\n")] = '\0';
    printf("Mat Khau: ");
    fgets(confirmPassword, 100, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    for (int i = 0; i < *size; i++) {
        if (strcmp(confirmAccounts, accounts[i].username) == 0 && strcmp(confirmPassword, accounts[i].password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return;
        }
    }
    printf("Tai khoan va mat khau sai!\n");
}

void signUp(Accounts accounts[100], Accounts newAccounts, int *size, FILE *file) {
    char confirmPassword[100];
    while (1) {
        printf("Tai Khoan: ");
        getchar();
        fgets(newAccounts.username, 100, stdin);
        newAccounts.username[strcspn(newAccounts.username, "\n")] = '\0';

        int flag = 0;
        for (int i = 0; i < *size; i++) {
            if (strcmp(newAccounts.username, accounts[i].username) == 0) {
                printf("Ten tai khoan da ton tai! Nhap lai!\n");
                flag = 1;
                break;
            }
        }
        if (!flag) break;
    }

    printf("Mat Khau: ");
    fgets(newAccounts.password, 100, stdin);
    newAccounts.password[strcspn(newAccounts.password, "\n")] = '\0';
    printf("Xac nhan mat khau: ");
    fgets(confirmPassword, 100, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(newAccounts.password, confirmPassword) == 0) {
        accounts[*size] = newAccounts;
        (*size)++;
        saveAccounts(accounts, size, file);
        printf("Dang ky thanh cong!\n");
    } else {
        printf("Xac nhan mat khau that bai!\n");
    }
}
