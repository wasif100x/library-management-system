#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to represent a book
struct Book {
    int id;
    char title[50];
    char author[50];
    char publisher[50];
    char isbn[20];
    int available;  // 1 if available, 0 if borrowed
} books[100];  // Array of books

int bookCount = 0;  // Keeps track of the total number of books
const char *fileName = "books.dat";  // File name for storing book data

// Function prototypes
void addBook();
void searchBook();
void checkoutBook();
void returnBook();
void reserveBook();
void renewBook();
void manageInventory();
void displayMenu();
void clearInputBuffer();
void saveBooksToFile();
void loadBooksFromFile();

int main() {
    loadBooksFromFile();  // Load books from file at the start
    int choice;
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: reserveBook(); break;
            case 6: renewBook(); break;
            case 7: manageInventory(); break;
            case 8:
                saveBooksToFile();  // Save books to file before exiting
                printf("Exiting program. Goodbye!\n");
                return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Display the menu
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

// Clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Save books to file
void saveBooksToFile() {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(books, sizeof(struct Book), bookCount, file);
    fclose(file);
    printf("Books saved to file successfully.\n");
}

// Load books from file
void loadBooksFromFile() {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
    fread(&bookCount, sizeof(int), 1, file);
    fread(books, sizeof(struct Book), bookCount, file);
    fclose(file);
    printf("Books loaded from file successfully.\n");
}

// Add a new book to the library
void addBook() {
    struct Book newBook;
    printf("Enter Book ID: ");
    if (scanf("%d", &newBook.id) != 1) {
        printf("Invalid input. Book ID should be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    printf("Enter Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    strtok(newBook.title, "\n");  // Remove newline character
    printf("Enter Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    strtok(newBook.author, "\n");  // Remove newline character
    printf("Enter Publisher: ");
    fgets(newBook.publisher, sizeof(newBook.publisher), stdin);
    strtok(newBook.publisher, "\n");  // Remove newline character
    printf("Enter ISBN: ");
    fgets(newBook.isbn, sizeof(newBook.isbn), stdin);
    strtok(newBook.isbn, "\n");  // Remove newline character
    newBook.available = 1;  // Mark as available
    books[bookCount++] = newBook;  // Add book to the array
    printf("Book added successfully!\n");
    saveBooksToFile();  // Save books to file after adding
}

// Search for a book by ISBN
void searchBook() {
    char searchIsbn[20];
    printf("Enter ISBN to search: ");
    fgets(searchIsbn, sizeof(searchIsbn), stdin);
    strtok(searchIsbn, "\n");  // Remove newline character
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

// Check out a book by ISBN
void checkoutBook() {
    char checkoutIsbn[20];
    printf("Enter ISBN to check out: ");
    fgets(checkoutIsbn, sizeof(checkoutIsbn), stdin);
    strtok(checkoutIsbn, "\n");  // Remove newline character
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, checkoutIsbn) == 0) {
            if (books[i].available) {
                books[i].available = 0;  // Mark as borrowed
                printf("Book checked out successfully!\n");
                saveBooksToFile();  // Save books to file after checkout
            } else {
                printf("Book is already checked out.\n");
            }
            return;
        }
    }
    printf("Book not available or not found!\n");
}

// Return a book by ISBN
void returnBook() {
    char returnIsbn[20];
    printf("Enter ISBN to return: ");
    fgets(returnIsbn, sizeof(returnIsbn), stdin);
    strtok(returnIsbn, "\n");  // Remove newline character
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, returnIsbn) == 0) {
            if (!books[i].available) {
                books[i].available = 1;  // Mark as available
                printf("Book returned successfully!\n");
                saveBooksToFile();  // Save books to file after return
            } else {
                printf("Book was not checked out.\n");
            }
            return;
        }
    }
    printf("Book not found or already returned!\n");
}

// Reserve a book by ISBN
void reserveBook() {
    char reserveIsbn[20];
    printf("Enter ISBN to reserve: ");
    fgets(reserveIsbn, sizeof(reserveIsbn), stdin);
    strtok(reserveIsbn, "\n");  // Remove newline character
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

// Renew a book by ISBN
void renewBook() {
    char renewIsbn[20];
    printf("Enter ISBN to renew: ");
    fgets(renewIsbn, sizeof(renewIsbn), stdin);
    strtok(renewIsbn, "\n");  // Remove newline character
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, renewIsbn) == 0) {
            if (!books[i].available) {
                printf("Book renewed successfully!\n");
                saveBooksToFile();  // Save books to file after renewal
            } else {
                printf("Book is available. No need to renew.\n");
            }
            return;
        }
    }
    printf("Book not found or cannot be renewed!\n");
}

// Display the book inventory
void manageInventory() {
    printf("\n<== Library Inventory ==>\n");
    printf("%-5s %-20s %-20s %-20s %-15s %-10s\n", "ID", "Title", "Author", "Publisher", "ISBN", "Available");
    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-20s %-20s %-20s %-15s %-10s\n", books[i].id, books[i].title, books[i].author,
               books[i].publisher, books[i].isbn, books[i].available ? "Yes" : "No");
    }
}
