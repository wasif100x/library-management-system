#include <stdio.h>
#include <string.h>

// Book structure
struct Book {
    int id;
    char title[50];
    char author[50];
    char publisher[50];
    char isbn[20];
    int available; // 1 for available, 0 for checked out
} books[100]; // Array to hold up to 100 books

int bookCount = 0; // Total number of books

// Function prototypes
void addBook();
void searchBook();
void checkoutBook();
void returnBook();
void reserveBook();
void renewBook();
void manageInventory();
void displayMenu();

int main() {
    int choice;
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the buffer

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: reserveBook(); break;
            case 6: renewBook(); break;
            case 7: manageInventory(); break;
            case 8: printf("Exiting program. Goodbye!\n"); return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Display menu
void displayMenu() {
    printf("\n<== Library Management System ==>\n");
    printf("1. Add a book to the library\n");
    printf("2. Search for a book\n");
    printf("3. Check out a book\n");
    printf("4. Return a book\n");
    printf("5. Reserve a book\n");
    printf("6. Renew a book\n");
    printf("7. Manage book inventory\n");
    printf("8. Exit\n");
}

// Add a new book
void addBook() {
    printf("Enter Book ID: ");
    scanf("%d", &books[bookCount].id);
    getchar(); // Clear the newline character from the buffer
    printf("Enter Title: ");
    fgets(books[bookCount].title, 50, stdin);
    strtok(books[bookCount].title, "\n"); // Remove newline character
    printf("Enter Author: ");
    fgets(books[bookCount].author, 50, stdin);
    strtok(books[bookCount].author, "\n"); // Remove newline character
    printf("Enter Publisher: ");
    fgets(books[bookCount].publisher, 50, stdin);
    strtok(books[bookCount].publisher, "\n"); // Remove newline character
    printf("Enter ISBN: ");
    fgets(books[bookCount].isbn, 20, stdin);
    strtok(books[bookCount].isbn, "\n"); // Remove newline character
    books[bookCount].available = 1; // Mark as available
    bookCount++;
    printf("Book added successfully!\n");
}

// Search for a book
void searchBook() {
    char searchIsbn[20];
    printf("Enter ISBN to search: ");
    fgets(searchIsbn, 20, stdin);
    strtok(searchIsbn, "\n"); // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, searchIsbn) == 0) {
            printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\nPublisher: %s\nAvailable: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].publisher,
                   books[i].available ? "Yes" : "No");
            return;
        }
    }
    printf("Book not found!\n");
}

// Check out a book
void checkoutBook() {
    char checkoutIsbn[20];
    printf("Enter ISBN to check out: ");
    fgets(checkoutIsbn, 20, stdin);
    strtok(checkoutIsbn, "\n"); // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, checkoutIsbn) == 0 && books[i].available) {
            books[i].available = 0; // Mark as checked out
            printf("Book checked out successfully!\n");
            return;
        }
    }
    printf("Book not available or not found!\n");
}

// Return a book
void returnBook() {
    char returnIsbn[20];
    printf("Enter ISBN to return: ");
    fgets(returnIsbn, 20, stdin);
    strtok(returnIsbn, "\n"); // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, returnIsbn) == 0 && !books[i].available) {
            books[i].available = 1; // Mark as available
            printf("Book returned successfully!\n");
            return;
        }
    }
    printf("Book not found or already returned!\n");
}

// Reserve a book
void reserveBook() {
    char reserveIsbn[20];
    printf("Enter ISBN to reserve: ");
    fgets(reserveIsbn, 20, stdin);
    strtok(reserveIsbn, "\n"); // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, reserveIsbn) == 0) {
            if (!books[i].available) {
                printf("Book reserved successfully! You'll be notified when it's available.\n");
            } else {
                printf("Book is available. No need to reserve.\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}

// Renew a book
void renewBook() {
    char renewIsbn[20];
    printf("Enter ISBN to renew: ");
    fgets(renewIsbn, 20, stdin);
    strtok(renewIsbn, "\n"); // Remove newline character

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, renewIsbn) == 0 && !books[i].available) {
            printf("Book renewed successfully!\n");
            return;
        }
    }
    printf("Book not found or cannot be renewed!\n");
}

// Manage book inventory
void manageInventory() {
    printf("\n<== Library Inventory ==>\n");
    printf("ID\tTitle\t\tAuthor\t\tPublisher\tISBN\tAvailable\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%s\t%s\t%s\t%s\t%s\n", books[i].id, books[i].title, books[i].author,
               books[i].publisher, books[i].isbn, books[i].available ? "Yes" : "No");
    }
}
