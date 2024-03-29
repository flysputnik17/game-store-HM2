// Pavel Bandurin  ID:315872689
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
//func for adding a new game to the library to the end of linked list
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
        if (game_list->head == NULL) 
        {
            game_list->head = game_node;
        } else {
            GameNode *current_node = game_list->head;
            while (current_node->next != NULL) 
            {
                current_node = current_node->next;
            }
            current_node->next = game_node;
        }

        printf("Game inserted successfully.\n");
}


//func to delete a game also chaking if there is a game with that title and only after it check that there is a game with that title it will delete it
   GameNode delete_game_by_title(GameLinkedList *game_list)
{
        printf("Delete a game\n");
        printf("Enter game title that you wish to delete: ");
        char user_title_input[100];
        fgets(user_title_input, 100, stdin);
        

        GameNode *current_node = game_list->head;
        GameNode *prev_node = NULL;
        int found = 0;

        while (current_node != NULL) 
        {
            if (strcmp(current_node->title, user_title_input) == 0) {
                found = 1;
                break;
            }
            prev_node = current_node;
            current_node = current_node->next;
        }

        if (found) {
            if (prev_node == NULL) 
            {
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
//funck to print all games that in the library
void print_games(GameLinkedList *game_list)
{
    printf("Games in the library:\n");
    GameNode *current_node = game_list->head;

    if (current_node == NULL) 
    {
        printf("The library has no games.\n");
        return;
    }

    while (current_node != NULL) 
    {
        printf("-%s\n", current_node->title);
        current_node = current_node->next;
    }
}

void sort_games_by_rating(GameLinkedList *game_list) 
{
    GameNode *current_node = game_list->head;

    
    int num_games = 0;
    while (current_node != NULL) 
    {
        num_games++;
        current_node = current_node->next;
    }

    
    GameNode **games_array = malloc(num_games * sizeof(GameNode *));
    current_node = game_list->head;
    int i = 0;
    while (current_node != NULL) 
    {
        games_array[i++] = current_node;
        current_node = current_node->next;
    }

    
    for (int i = 0; i < num_games - 1; i++) 
    {
        for (int j = i + 1; j < num_games; j++) 
        {
            if (games_array[i]->rating < games_array[j]->rating) {
                GameNode *temp = games_array[i];
                games_array[i] = games_array[j];
                games_array[j] = temp;
            }
        }
    }

    
    printf("Games sorted by rating:\n");
    for (int i = 0; i < num_games; i++) 
    {
        printf("- %s (%0.1f)\n", games_array[i]->title, games_array[i]->rating);
    }
    free(games_array);
}

//func adding DLC'S for a game after it checked that there is actualy a game with that title
DLCNode insert_dlc_at_end(GameLinkedList *game_list)
{
    printf("Enter the title of the game: ");
    char buffer[100];
    fgets(buffer, 100, stdin);

    GameNode *current_node = game_list->head;
    int found = 0;

    while (current_node != NULL) 
    {
        if (strcmp(current_node->title, buffer) == 0) 
        {
            found = 1;
            break;
        }
        current_node = current_node->next;
    }

    if (found) 
    {
        printf("Enter the title of the DLC: ");
        char dlc_title[100];
        fgets(dlc_title, 100, stdin);

        printf("Enter the price of the DLC: ");
        float dlc_price = 0;
        scanf("%f", &dlc_price);
        getchar(); // consume the newline character left in the input buffer

        DLCNode *dlc_node = malloc(sizeof(DLCNode));
        dlc_node->title = malloc(strlen(dlc_title) + 1);
        strcpy(dlc_node->title, dlc_title);
        dlc_node->price = dlc_price;
        dlc_node->next = NULL;

        if (current_node->dlc_head == NULL) 
        {
            current_node->dlc_head = dlc_node;
        } else {
            DLCNode *current_dlc_node = current_node->dlc_head;
            while (current_dlc_node->next != NULL) 
            {
                current_dlc_node = current_dlc_node->next;
            }
            current_dlc_node->next = dlc_node;
        }

        printf("DLC inserted successfully.\n");
    } else {
        printf("Game not found.\n");
    }
}





//funck that delete a DLC from a game after it checked that there is a game with that title in the library
DLCNode delete_dlc_by_title(GameLinkedList *game_list) 
{
    printf("Enter game title: ");
    char buffer[100];
    fgets(buffer, 100, stdin);

 
    GameNode *game_node = game_list->head;
    while (game_node != NULL && strcmp(game_node->title, buffer) != 0) 
    {
        game_node = game_node->next;
    }

    if (game_node == NULL) 
    {
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
    while (dlc_node != NULL && strcmp(dlc_node->title, buffer) != 0) 
    {
        prev_node = dlc_node;
        dlc_node = dlc_node->next;
    }

    if (dlc_node == NULL) 
    {
        printf("Sorry, no such DLC title in the game.\n");
        DLCNode dlc_node = { NULL };
        return dlc_node;
    }
    prev_node->next = dlc_node->next;
    free(dlc_node->title);
    free(dlc_node);

    printf("DLC deleted successfully.\n");

    
    return *dlc_node;
}



//funck that print all the DLC'S a game has after it check that the game is exsist in the library
void print_dlcs_for_game(GameLinkedList *game_list)
{
    printf("Enter the title of the game: ");
    char user_title_input[100];
    fgets(user_title_input, 100, stdin);

    GameNode *current_node = game_list->head;
    int found = 0;

    while (current_node != NULL)
    {
        if (strcmp(current_node->title, user_title_input) == 0)
        {
            found = 1;
            break;
        }
        current_node = current_node->next;
    }

    if (found)
    {
        printf("DLCs for %s:\n", current_node->title);
        DLCNode *dlc_node = current_node->dlc_head;

        if (dlc_node == NULL)
        {
            printf("This game does not have any DLCs.\n");
        }
        else
        {
            while (dlc_node != NULL)
            {
                printf("- %s\n", dlc_node->title);
                dlc_node = dlc_node->next;
            }
        }
    }
    else
    {
        printf("Game not found.\n");
    }
}


