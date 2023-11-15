#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

// User structure to store user information
struct User {
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int age;
    // Other user-related information can be added here
};

// Array to store user data
struct User users[MAX_USERS];
int userCount = 0;

// Function to register a new user
void registerUser(const char *username, const char *email, int age) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].email, email);
        users[userCount].age = age;
        userCount++;
        printf("User '%s' registered successfully.\n", username);
    } else {
        printf("User limit reached. Cannot register new user.\n");
    }
}

// Function to display user information
void displayUser(const char *username) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username: %s\n", users[i].username);
            printf("Email: %s\n", users[i].email);
            printf("Age: %d\n", users[i].age);
            return;
        }
    }
    printf("User '%s' not found.\n", username);
}

int main() {
    // Registering users
    registerUser("user1", "user1@example.com", 25);
    registerUser("user2", "user2@example.com", 30);
    registerUser("admin", "admin@example.com", 35);

    // Displaying user information
    printf("User information:\n");
    displayUser("user1");
    displayUser("user2");
    displayUser("admin");
    displayUser("unknown_user"); // Not found

    return 0;
}
