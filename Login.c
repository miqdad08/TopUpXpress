#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define USERNAME_LEN 30
#define PASSWORD_LEN 30
#define FILENAME "users.txt"

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

// Function to check if a password is valid
int isValidPassword(const char *password) {
    int length = strlen(password);
    int hasSymbol = 0, hasDigit = 0;

    // Check for password length
    if (length <= 8) {
        return 0;
    }

    // Check for at least one symbol and one digit
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) {
            hasDigit = 1;
        } else if (!isalnum(password[i])) {
            hasSymbol = 1;
        }
    }

    return hasSymbol && hasDigit;
}

void registerUser() {
    User user;
    FILE *file = fopen(FILENAME, "a");  // Open file for appending

    if (!file) {
        perror("Unable to open file");
        return;
    }

    printf("Enter username: ");
    scanf("%s", user.username);

    // Loop until a valid password is entered
    while (1) {
        printf("Enter password: ");
        scanf("%s", user.password);

        if (isValidPassword(user.password)) {
            break;  // Password is valid, exit the loop
        } else {
            printf("Invalid password! It must be longer than 8 characters, contain at least one symbol, and one digit.\n");
        }
    }

    fprintf(file, "%s %s\n", user.username, user.password);  // Save user data
    fclose(file);

    printf("Registration successful!\n");
}

int loginUser() {
    User user;
    char inputUsername[USERNAME_LEN];
    char inputPassword[PASSWORD_LEN];
    FILE *file = fopen(FILENAME, "r");  // Open file for reading

    if (!file) {
        perror("Unable to open file");
        return 0;
    }

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, inputPassword) == 0) {
            fclose(file);
            printf("Login successful!\n");
            return 1;  // Successful login
        }
    }

    fclose(file);
    printf("Login failed! Invalid username or password.\n");
    return 0;  // Failed login
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
