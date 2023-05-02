#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct game_node {
        char *title;
        char *genre;
        int year;
        float rating;
        struct game_node* next;
        struct dlc_head* dlc_head;
    }GameNode;

    typedef struct dlc_node {
        char *title;
        float price;
        struct dlc_node *next;
    }DLCNode;

    typedef struct{
        GameNode *head;
    }GameLinkedList;


int main()
{
    int choice;
loop:
    printf("Welcome to the Game Library!\n");
    printf("----------------------------\n");
    printf("1.Insert a game\n");
    printf("2.Delete a game\n");
    printf("3.Print all games\n");
    printf("4.Sort games by rating\n");
    printf("5.Insert DLC for a game\n");
    printf("6.Delete DLC for a game\n");
    printf("7.Print DLC for a game\n");
    printf("8.Exit\n");
    printf("\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);
    
    getchar();

    
    while (choice != 8)
    {
        switch (choice)
        {
            case 1:
                printf("Enter game title: ");
                char buffer[100];
                fgets(buffer, 100, stdin);

                GameNode *game_node = malloc(sizeof(GameNode));
                game_node->title = malloc(strlen(buffer) + 1);
                strcpy(game_node->title, buffer);

                printf("Enter game genre: ");
                fgets(buffer, 100, stdin);

                game_node->genre = malloc(strlen(buffer) + 1);
                strcpy(game_node->genre, buffer);
                

                printf("Enter year of release: ");
                int user_input_year = 0;
                scanf("%d", &user_input_year);
                

                game_node->year = user_input_year;

                printf("Enter game rating (out of 10): ");
                float user_input_rating = 0;
                scanf("%f", &user_input_rating);
                
                
                game_node->rating = user_input_rating;
                printf("Game inserted successfully.\n");
                printf("\n");
                goto loop;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);
        // consume the newline character left in the input buffer
        getchar();
    }

    return 0;
};
