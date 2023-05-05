#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct game_node {
        char *title;
        char *genre;
        int year;
        float rating;
        struct game_node* next;
        struct dlc_node* dlc_head;
    }GameNode;

    typedef struct dlc_node {
        char *title;
        float price;
        struct dlc_node *next;
    }DLCNode;

    typedef struct{
        GameNode *head;
    }GameLinkedList;


GameNode insert_game_at_end(GameLinkedList *game_list);
GameNode delete_game_by_title(GameLinkedList *game_list);
void print_games(GameLinkedList *game_list);
void sort_games_by_rating(GameLinkedList *game_list);
DLCNode insert_dlc_at_end(GameLinkedList *game_list);
DLCNode delete_dlc_by_title(GameLinkedList *game_list);
void print_dlcs_for_game(GameLinkedList *game_list);


int main()
{
    GameLinkedList game_list = { NULL };
    int choice=0;
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
            insert_game_at_end(&game_list);
            printf("\n");
            goto loop;
            break;

            case 2:
            delete_game_by_title(&game_list);
            printf("\n");
            goto loop;
            break;

            case 3:
            print_games(&game_list);
            printf("\n");
            goto loop;
            break;

            case 4:
            sort_games_by_rating(&game_list);
            printf("\n");
            goto loop;
            break;

            case 5:
            insert_dlc_at_end(&game_list);
            printf("\n");
            goto loop;
            break;

            case 6:
            delete_dlc_by_title(&game_list);
            printf("\n");
            goto loop;
            break;

            case 7:
            print_dlcs_for_game(&game_list);
            printf("\n");
            goto loop;
            break;



            

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        getchar();
    }

    return 0;
};

GameNode insert_game_at_end(GameLinkedList *game_list)
{
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
        getchar();

        game_node->year = user_input_year;

        printf("Enter game rating (out of 10): ");
        float user_input_rating = 0;
        scanf("%f", &user_input_rating);
        getchar();

        game_node->rating = user_input_rating;

    
        game_node->next = NULL;
        if (game_list->head == NULL) {
            game_list->head = game_node;
        } else {
            GameNode *current_node = game_list->head;
            while (current_node->next != NULL) {
                current_node = current_node->next;
            }
            current_node->next = game_node;
        }

        printf("Game inserted successfully.\n");
}



   GameNode delete_game_by_title(GameLinkedList *game_list)
{
        printf("Delete a game\n");
        printf("Enter game title that you wish to delete: ");
        char user_title_input[100];
        fgets(user_title_input, 100, stdin);
        

        GameNode *current_node = game_list->head;
        GameNode *prev_node = NULL;
        int found = 0;

        while (current_node != NULL) {
            if (strcmp(current_node->title, user_title_input) == 0) {
                found = 1;
                break;
            }
            prev_node = current_node;
            current_node = current_node->next;
        }

        if (found) {
            if (prev_node == NULL) {
                game_list->head = current_node->next;
            } else {
                prev_node->next = current_node->next;
            }

            free(current_node->title);
            free(current_node->genre);
            free(current_node);
            printf("Game deleted successfully.\n");
        } else {
            printf("There is no such game in the library.\n");
        }
            printf("\n");
}

void print_games(GameLinkedList *game_list)
{
    printf("Games in the library:\n");
    GameNode *current_node = game_list->head;

    if (current_node == NULL) {
        printf("The library has no games.\n");
        return;
    }

    while (current_node != NULL) {
        printf("-%s\n", current_node->title);
        current_node = current_node->next;
    }
}

void sort_games_by_rating(GameLinkedList *game_list) {
    GameNode *current_node = game_list->head;

    // Count the number of games in the list
    int num_games = 0;
    while (current_node != NULL) {
        num_games++;
        current_node = current_node->next;
    }

    // Put the games in an array
    GameNode **games_array = malloc(num_games * sizeof(GameNode *));
    current_node = game_list->head;
    int i = 0;
    while (current_node != NULL) {
        games_array[i++] = current_node;
        current_node = current_node->next;
    }

    // Sort the array based on the rating
    for (int i = 0; i < num_games - 1; i++) {
        for (int j = i + 1; j < num_games; j++) {
            if (games_array[i]->rating < games_array[j]->rating) {
                GameNode *temp = games_array[i];
                games_array[i] = games_array[j];
                games_array[j] = temp;
            }
        }
    }

    // Print the sorted list of games
    printf("Games sorted by rating:\n");
    for (int i = 0; i < num_games; i++) {
        printf("- %s (%0.1f)\n", games_array[i]->title, games_array[i]->rating);
    }

    // Free the memory allocated for the array
    free(games_array);
}


DLCNode insert_dlc_at_end(GameLinkedList *game_list) {
    printf("Enter game title: ");
    char buffer[100];
    fgets(buffer, 100, stdin);

    DLCNode *dlc_node = malloc(sizeof(DLCNode));
    dlc_node->title = malloc(strlen(buffer) + 1);
    strcpy(dlc_node->title, buffer);

    GameNode *current_node = game_list->head;

    if (current_node != NULL) {
        if (strcmp(current_node->title, buffer) == 0) {
            printf("Enter DLC title :");
            char* user_input = malloc(100 * sizeof(char));
            fgets(user_input, 100, stdin);
            strcpy(dlc_node->title, user_input);
            free(user_input);

            printf("Enter DLC price :");
            float dlc_price = 0;
            scanf("%f", &dlc_price);
            dlc_node->price = dlc_price;

        } else {
            printf("There is no such game in the library.");
        }
    }
}



DLCNode delete_dlc_by_title(GameLinkedList *game_list) {
    printf("Enter game title: ");
    char buffer[100];
    fgets(buffer, 100, stdin);

    // find the game with the specified title
    GameNode *game_node = game_list->head;
    while (game_node != NULL && strcmp(game_node->title, buffer) != 0) {
        game_node = game_node->next;
    }

    // if the game is not found, print an error message and return
    if (game_node == NULL) {
        printf("No such game in library.\n");
        DLCNode dlc_node = { NULL };
        return dlc_node;
    }

    printf("Enter DLC title: ");
    fgets(buffer, 100, stdin);

    // find the DLC node with the specified title
    DLCNode *dlc_node = game_node->dlc_head->next;
    DLCNode *prev_node = game_node->dlc_head;
    int found = 0;
    while (dlc_node != NULL && strcmp(dlc_node->title, buffer) != 0) {
        prev_node = dlc_node;
        dlc_node = dlc_node->next;
    }

    // if the DLC node is not found, print an error message and return
    if (dlc_node == NULL) {
        printf("Sorry, no such DLC title in the game.\n");
        DLCNode dlc_node = { NULL };
        return dlc_node;
    }

    // remove the DLC node from the linked list
    prev_node->next = dlc_node->next;

    // free the memory occupied by the DLC node
    free(dlc_node->title);
    free(dlc_node);

    printf("DLC deleted successfully.\n");

    // return the deleted DLC node
    return *dlc_node;
}




