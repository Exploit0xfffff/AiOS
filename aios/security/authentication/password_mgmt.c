#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PASSWORD_LENGTH 50

// User structure to store username and password
struct User {
    char username[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

// Array to store user data
struct User users[MAX_USERS];
int userCount = 0;

// Function to register a new user
void registerUser(const char *username, const char *password) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;
        printf("User '%s' registered successfully.\n", username);
    } else {
        printf("User limit reached. Cannot register new user.\n");
    }
}

// Function to authenticate user
int authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("User '%s' authenticated successfully.\n", username);
            return 1; // User authenticated
        }
    }
    printf("Authentication failed for user '%s'.\n", username);
    return 0; // Authentication failed
}

int main() {
    // Registering users
    registerUser("user1", "pass123");
    registerUser("user2", "abc456");
    registerUser("admin", "admin@123");

    // Authentication example
    authenticateUser("user1", "pass123"); // Should authenticate successfully
    authenticateUser("user2", "wrongpass"); // Should fail authentication

    return 0;
}
