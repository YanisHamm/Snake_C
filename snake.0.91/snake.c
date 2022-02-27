#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

element_snake* snake_init_case(snake *snake, plateau *p)
{

    if(p->hauteur>p->largeur)snake->taille_max=p->largeur;
    else snake->taille_max=p->hauteur;
    element_snake* t = (element_snake*)malloc(snake->taille_max * sizeof(element_snake));
    return t;
}
void snake_init(snake *snake,plateau * p)
{
    //initial

    snake->longeur=0;
    snake->score=0;
    snake->elements=snake_init_case(snake,p);
    snake_position_initial(snake,p);
    snake->nombre_obstacle_toucher=0;
    snake->vivant=true;
    change_sens_ia(snake,p);


}

int snake_move(snake *s,plateau * p)
{

    element_snake * tmp_elm;
    if(s->longeur==0)
    {
        tmp_elm= (element_snake*) malloc(1 * sizeof(element_snake));
    }
    else
    {
        tmp_elm= (element_snake*) malloc(s->taille_max * sizeof(element_snake));
    }
    for(int i =0; i<= s->longeur; i++)
    {
        tmp_elm[i].emplacement_element=s->elements[i].emplacement_element;
    }
    if(s->sens == 's'|| s->sens == 'S') // vers le bas
    {
        s->element_tete.emplacement_element.y++;// La tete avance
        if(s->element_tete.emplacement_element.y > p->hauteur)s->element_tete.emplacement_element.y=0; // si on depasse
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide) //VIDE
        {
            s->elements[0].emplacement_element=s->element_tete.emplacement_element; //element tete au tab
            if(s->longeur >0) //si + grand que zero il y a une chaine
            {
                s->elements[s->longeur].emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
                s->element_queu.emplacement_element=s->elements[s->longeur].emplacement_element;
                tmp_elm[s->longeur].emplacement_element.snake=false;
                tmp_elm[s->longeur].emplacement_element.vide=true;
                tmp_elm[s->longeur].emplacement_element.fruit=false;
                tmp_elm[s->longeur].emplacement_element.obstacle=false;

                for(int i=1; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }
                p->position_case[tmp_elm[s->longeur].emplacement_element.y][tmp_elm[s->longeur].emplacement_element.x]=tmp_elm[s->longeur].emplacement_element;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
            else //Sinon on efface et remet a jour le plateau
            {
                s->element_queu.emplacement_element=s->element_tete.emplacement_element;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].snake=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].vide=true;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].fruit=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=false;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)   //FRUIT
        {
            char fruit =p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].lettre_fruit;
            s->score += get_score_fruit(fruit);
            s->longeur++;

            s->elements[0].emplacement_element=s->element_tete.emplacement_element;
            s->element_queu.emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
            s->elements[s->longeur].emplacement_element=s->element_queu.emplacement_element;
            for(int i=1; i<s->longeur; i++)
            {
                s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
            }

            p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            placer_fruit(p);
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle) //OBSTACLE
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y--;
            s->element_queu.emplacement_element.snake=false;
            s->element_queu.emplacement_element.vide=true;
            s->element_queu.emplacement_element.obstacle=false;
            s->element_queu.emplacement_element.fruit=false;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            s->longeur--;
            if(s->longeur == 0)s->longeur=1;
            s->element_queu.emplacement_element=tmp_elm[s->longeur].emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;

            s->nombre_obstacle_toucher++;
            if(s->nombre_obstacle_toucher == 3)
            {
                s->vivant=false;
                p->nombre_snake--;
                for(int i=0 ; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element.fruit=false;
                    s->elements[i].emplacement_element.vide=true;
                    s->elements[i].emplacement_element.snake=false;
                    s->elements[i].emplacement_element.obstacle=false;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }
                free(tmp_elm);
                return 0;
            }

            change_sens_ia(s,p);
            free(tmp_elm);
            return 1;

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.y--;
        }
    }
    else if(s->sens == 'z'|| s->sens == 'Z') // vers le haut
    {
        s->element_tete.emplacement_element.y--;
        if(s->element_tete.emplacement_element.y < 0)s->element_tete.emplacement_element.y=p->hauteur-1;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide) //VIDE
        {
            s->elements[0].emplacement_element=s->element_tete.emplacement_element;
            if(s->longeur >0)
            {
                s->elements[s->longeur].emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
                s->element_queu.emplacement_element=s->elements[s->longeur].emplacement_element;
                tmp_elm[s->longeur].emplacement_element.snake=false;
                tmp_elm[s->longeur].emplacement_element.vide=true;
                tmp_elm[s->longeur].emplacement_element.fruit=false;
                tmp_elm[s->longeur].emplacement_element.obstacle=false;

                for(int i=1; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }

                p->position_case[tmp_elm[s->longeur].emplacement_element.y][tmp_elm[s->longeur].emplacement_element.x]=tmp_elm[s->longeur].emplacement_element;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
            else
            {
                s->element_queu.emplacement_element=s->element_tete.emplacement_element;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].snake=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].vide=true;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].fruit=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=false;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)   //FRUIT
        {
            char fruit =p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].lettre_fruit;
            s->score += get_score_fruit(fruit);
           // s->element_queu.emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
            s->longeur++;
            s->elements[0].emplacement_element=s->element_tete.emplacement_element;

            s->elements[s->longeur].emplacement_element=s->element_queu.emplacement_element;
            for(int i=1; i<s->longeur; i++)
            {
                s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
            }

            p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            placer_fruit(p);
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle) //OBSTACLE
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y++;

            s->element_queu.emplacement_element.snake=false;
            s->element_queu.emplacement_element.vide=true;
            s->element_queu.emplacement_element.obstacle=false;
            s->element_queu.emplacement_element.fruit=false;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            s->longeur--;
            if(s->longeur == 0)s->longeur=1;
            s->element_queu.emplacement_element=tmp_elm[s->longeur].emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;

            s->nombre_obstacle_toucher++;
            if(s->nombre_obstacle_toucher == 3)
            {
                s->vivant=false;
                p->nombre_snake--;
                for(int i=0 ; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element.fruit=false;
                    s->elements[i].emplacement_element.vide=true;
                    s->elements[i].emplacement_element.snake=false;
                    s->elements[i].emplacement_element.obstacle=false;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }
                free(tmp_elm);
                return 0;
            }

            change_sens_ia(s,p);
            free(tmp_elm);
            return 1;
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)//SNAKE
        {
            s->element_tete.emplacement_element.y++;

        }

    }
    else if(s->sens == 'q'|| s->sens == 'Q') // vers la gauche
    {
        s->element_tete.emplacement_element.x--;
        if(s->element_tete.emplacement_element.y > p->hauteur)s->element_tete.emplacement_element.y=0;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)//VIDE
        {
            s->elements[0].emplacement_element=s->element_tete.emplacement_element;
            if(s->longeur >0)
            {
                s->elements[s->longeur].emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
                s->element_queu.emplacement_element=s->elements[s->longeur].emplacement_element;
                tmp_elm[s->longeur].emplacement_element.snake=false;
                tmp_elm[s->longeur].emplacement_element.vide=true;
                tmp_elm[s->longeur].emplacement_element.fruit=false;
                tmp_elm[s->longeur].emplacement_element.obstacle=false;

                for(int i=1; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }

                p->position_case[tmp_elm[s->longeur].emplacement_element.y][tmp_elm[s->longeur].emplacement_element.x]=tmp_elm[s->longeur].emplacement_element;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
            else
            {
                s->element_queu.emplacement_element=s->element_tete.emplacement_element;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].snake=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].vide=true;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].fruit=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=false;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit) //FRUIT
        {
            char fruit =p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].lettre_fruit;
            s->score += get_score_fruit(fruit);

            s->longeur++;
            s->element_queu.emplacement_element=tmp_elm[s->longeur-1].emplacement_element;

            s->elements[0].emplacement_element=s->element_tete.emplacement_element;

            s->elements[s->longeur].emplacement_element=s->element_queu.emplacement_element;
            for(int i=1; i<s->longeur; i++)
            {
                s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
            }

            p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            placer_fruit(p);
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle) //OBSTACLE
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y--;

            s->element_queu.emplacement_element.snake=false;
            s->element_queu.emplacement_element.vide=true;
            s->element_queu.emplacement_element.obstacle=false;
            s->element_queu.emplacement_element.fruit=false;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            s->longeur--;
            if(s->longeur == 0)s->longeur=1;
            s->element_queu.emplacement_element=tmp_elm[s->longeur].emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;

            s->nombre_obstacle_toucher++;
            if(s->nombre_obstacle_toucher == 3)
            {
                s->vivant=false;
                p->nombre_snake--;
                for(int i=0 ; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element.fruit=false;
                    s->elements[i].emplacement_element.vide=true;
                    s->elements[i].emplacement_element.snake=false;
                    s->elements[i].emplacement_element.obstacle=false;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }
                free(tmp_elm);
                return 0;
            }

            change_sens_ia(s,p);
            free(tmp_elm);
            return 1;
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)//SNAKE
        {
            s->element_tete.emplacement_element.y--;
        }
    }

    else if(s->sens == 'd' || s->sens == 'D')
    {
        s->element_tete.emplacement_element.x++;
        if(s->element_tete.emplacement_element.x >= p->largeur)s->element_tete.emplacement_element.x=0;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide) //VIDE
        {
            s->elements[0].emplacement_element=s->element_tete.emplacement_element;
            if(s->longeur >0)
            {
                s->elements[s->longeur].emplacement_element=tmp_elm[s->longeur-1].emplacement_element;
                s->element_queu.emplacement_element=s->elements[s->longeur].emplacement_element;
                tmp_elm[s->longeur].emplacement_element.snake=false;
                tmp_elm[s->longeur].emplacement_element.vide=true;
                tmp_elm[s->longeur].emplacement_element.fruit=false;
                tmp_elm[s->longeur].emplacement_element.obstacle=false;

                for(int i=1; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }

                p->position_case[tmp_elm[s->longeur].emplacement_element.y][tmp_elm[s->longeur].emplacement_element.x]=tmp_elm[s->longeur].emplacement_element;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
            else
            {
                s->element_queu.emplacement_element=s->element_tete.emplacement_element;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].snake=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].vide=true;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].fruit=false;
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=false;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)   //FRUIT
        {
            char fruit =p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].lettre_fruit;
            s->score += get_score_fruit(fruit);

            s->longeur++;
            s->element_queu.emplacement_element=tmp_elm[s->longeur-1].emplacement_element;

            s->elements[0].emplacement_element=s->element_tete.emplacement_element;

            s->elements[s->longeur].emplacement_element=s->element_queu.emplacement_element;
            for(int i=1; i<s->longeur; i++)
            {
                s->elements[i].emplacement_element=tmp_elm[i-1].emplacement_element;
                p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
            }

            p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            placer_fruit(p);
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle) //OBSTACLE
        {
            s->score -= 15;
            s->element_tete.emplacement_element.x++;

            s->element_queu.emplacement_element.snake=false;
            s->element_queu.emplacement_element.vide=true;
            s->element_queu.emplacement_element.obstacle=false;
            s->element_queu.emplacement_element.fruit=false;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;
            s->longeur--;
            if(s->longeur == 0)s->longeur=1;
            s->element_queu.emplacement_element=tmp_elm[s->longeur].emplacement_element;
            p->position_case[s->element_queu.emplacement_element.y][s->element_queu.emplacement_element.x]=s->element_queu.emplacement_element;

            s->nombre_obstacle_toucher++;
            if(s->nombre_obstacle_toucher == 3)
            {
                s->vivant=false;
                p->nombre_snake--;
                for(int i=0 ; i<s->longeur; i++)
                {
                    s->elements[i].emplacement_element.fruit=false;
                    s->elements[i].emplacement_element.vide=true;
                    s->elements[i].emplacement_element.snake=false;
                    s->elements[i].emplacement_element.obstacle=false;

                    p->position_case[s->elements[i].emplacement_element.y][s->elements[i].emplacement_element.x]=s->elements[i].emplacement_element;
                }
                free(tmp_elm);
                return 0;
            }
            free(tmp_elm);
            change_sens_ia(s,p);
            return 1;


        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)//SNAKE
        {
            s->element_tete.emplacement_element.x++;
        }

    }
    free(tmp_elm);
    change_sens_ia(s,p);
    return 1;
}
void snake_position_initial(snake *s,plateau* p)
{

    srand( time( NULL ) );
    int randomPosX ;
    int randomPosY ;
    do
    {
        randomPosX =rand()% p->largeur;
        randomPosY =rand()% p->hauteur;
    }
    while (!p->position_case[randomPosY][randomPosX].vide);

    p->position_case[randomPosY][randomPosX].fruit=false;
    p->position_case[randomPosY][randomPosX].obstacle=false;
    p->position_case[randomPosY][randomPosX].snake=true;
    p->position_case[randomPosY][randomPosX].vide=false;
    p->position_case[randomPosY][randomPosX].id_snake=s->thread_id;



    s->element_queu.emplacement_element=p->position_case[randomPosY][randomPosX];
    s->element_queu.emplacement_element.y=randomPosY;//random
    s->element_queu.emplacement_element.x=randomPosX;//random
    s->element_queu.emplacement_element.id_snake=s->thread_id;


    s->element_tete=s->element_queu;


    s->elements[0].emplacement_element.x=randomPosX;//random
    s->elements[0].emplacement_element.y=randomPosY;//random
    s->elements[0].emplacement_element.snake=true;
    s->elements[0].emplacement_element.obstacle=false;
    s->elements[0].emplacement_element.fruit=false;
    s->elements[0].emplacement_element.vide=false;
    s->elements[0].emplacement_element.id_snake=s->thread_id;


    s->element_queu.emplacement_element= p->position_case[randomPosY][randomPosX];//random




}
int get_score_fruit(char fruit)
{
    int r=0;
    switch (fruit)
    {
    case 'P' :
        r= 1;
        break;
    case 'B' :
        r= 2;
        break;
    case 'C' :
        r= 3;
        break;
    case 'F' :
        r= 5;
        break;

    }
    return r;
}
void change_sens_random(snake *s,plateau *p)
{

    int random ;
    char random_sens=' ';

    srand( time( NULL ) );
    random =rand()% 3;

    switch (random)
    {
    case 0 :
        random_sens ='d';
        break;
    case 1 :
        random_sens ='z';
        break;
    case 2 :
        random_sens ='q';
        break;
    case 3 :
        random_sens ='s';
        break;

    }
    if(random_sens == 'd' )
    {
        int x =s->element_tete.emplacement_element.x+1;
        if(x>=p->hauteur)x=0;
        if(!p->position_case[s->element_tete.emplacement_element.y][x].snake)
            s->sens=random_sens;
    }
    if(random_sens == 's')
    {
        int y=s->element_tete.emplacement_element.y+1;
        if(y>=p->largeur)y=0;
        if(!p->position_case[y][s->element_tete.emplacement_element.x].snake)
            s->sens=random_sens;
    }


    if(random_sens == 'z')
    {
        int y =s->element_tete.emplacement_element.y-1;
        if(y<0)y=p->hauteur-1;
        if(!p->position_case[y][s->element_tete.emplacement_element.x].snake)

            s->sens=random_sens;
    }

    if(random_sens == 'q')
    {
        int x = s->element_tete.emplacement_element.x-1;
        if(x<0)x=p->largeur-1;
        if(!p->position_case[s->element_tete.emplacement_element.y][x].snake)
            s->sens=random_sens;
    }

}
void change_sens_ia(snake *s,plateau *p)
{
    if(s->element_tete.emplacement_element.x-p->cible_fruit.x>0)
    {

        if(p->position_case[s->element_tete.emplacement_element.x-1][s->element_tete.emplacement_element.y].vide && !p->position_case[s->element_tete.emplacement_element.x-1][s->element_tete.emplacement_element.y].snake)
        {
            s->sens='q'; // gauche
            return;
        }
    }
    if(s->element_tete.emplacement_element.x-p->cible_fruit.x<0)
    {

        if(p->position_case[s->element_tete.emplacement_element.x+1][s->element_tete.emplacement_element.y].vide&& !p->position_case[s->element_tete.emplacement_element.x+1][s->element_tete.emplacement_element.y].snake)
        {
            s->sens='d'; //droite
            return;
        }
    }
    if(s->element_tete.emplacement_element.x-p->cible_fruit.x==0)
    {
        if(s->element_tete.emplacement_element.y-p->cible_fruit.y>0)
        {
            if(p->position_case[s->element_tete.emplacement_element.x][s->element_tete.emplacement_element.y+1].vide&& !p->position_case[s->element_tete.emplacement_element.y+1][s->element_tete.emplacement_element.y].snake)
            {
                s->sens='z'; //haut
                return;
            }
        }

        if(s->element_tete.emplacement_element.y-p->cible_fruit.y<0)
        {
            if(p->position_case[s->element_tete.emplacement_element.x-1][s->element_tete.emplacement_element.y-1].vide&& !p->position_case[s->element_tete.emplacement_element.x-1][s->element_tete.emplacement_element.y].snake)
            {
                s->sens='s';//bas
                return;
            }
        }
    }

}
