#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "case_plateau.h"
#include "plateau.h"
typedef struct element_snake
{
    case_plateau emplacement_element;

} element_snake;
typedef struct snake
{
    int thread_id; // numéro de id
    int longeur; // longeur du snake
    int score; // score personnel du snake
    int nombre_obstacle_toucher; //Nombre d'obstacle touché
    char sens; //z vers haut ,q vers gauche, s vers bas, d vers droite
    int taille_max; // taille max du snake
    element_snake element_queu;
    element_snake element_tete;
   // element_snake* tmp_elm;
    bool vivant;
    case_plateau cible_snake; // la cible du snake peu être différente

    element_snake * elements; // [nombre de point 0 = tete]
    long vitesse;



} snake;

void * create_snake(void* data);
element_snake* snake_init_case(snake *snake,plateau *p);
void snake_init(snake *snake,plateau *p);
int snake_move(snake *snake,plateau *p);
void refreshSnake(plateau* p,snake *s,snake ancien_snake);
void snake_position_initial(snake *s,plateau* p);
int get_score_fruit(char fruit);
void change_sens_random(snake *snake,plateau *p);
void change_sens_ia(snake *snake,plateau *p);

#endif // SNAKE_H_INCLUDED
