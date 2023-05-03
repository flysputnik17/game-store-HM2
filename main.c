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


void insert_game_at_end(GameLinkedList *game_list);
int delete_game_by_title(GameLinkedList *game_list);
void print_games(GameLinkedList *game_list);
void sort_games_by_rating(GameLinkedList *game_list);
void insert_dlc_at_end(GameLinkedList *game_list);


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

            case 5:
            insert_dlc_at_end(&game_list);
            printf("\n");
            goto loop;
            break;


            // case 4:
            // void sort_games_by_rating(&game_list);
            // printf("\n");
            // goto loop;
            // break;

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

void insert_game_at_end(GameLinkedList *game_list)
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



   int delete_game_by_title(GameLinkedList *game_list)
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

// void sort_games_by_rating(GameLinkedList *game_list)
// {
//     printf("Games sorted by rating:\n");
//     GameNode *current_node = game_list->head->rating;

   
    
// }

void insert_dlc_at_end(GameLinkedList *game_list)
{
    printf("Enter game title: ");
    char buffer [100];
    fgets(buffer,100,stdin);
    GameNode *current_node = game_list->head;

    DLCNode *dlc_node = malloc(sizeof(DLCNode));
    dlc_node->title = malloc(strlen(buffer) + 1);

    while(current_node != NULL)
    {
        if(strcmp(current_node->title, buffer) == 0)
        {
            printf("Enter DLC title :");
            strcpy(dlc_node->title, buffer);
            getchar();

            printf("Enter DLC price :");
            float dlc_price = 0;
            scanf("%f",&dlc_price);
            dlc_node->price = dlc_price;

            
        }else{
            printf("There is no such game in the library.");
            break;
        }
    }
    
    
}