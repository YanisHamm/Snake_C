#include "snake.h"
#include <stdlib.h>
element_snake* snake_init_case(snake *snake, plateau *p)
{

    if(p->hauteur>p->largeur)snake->taille_max=p->largeur;
    else snake->taille_max=p->hauteur;
    element_snake* t = (element_snake*)malloc(snake->taille_max * sizeof(element_snake*));
    return t;
}
void snake_init(snake *snake,plateau * p)
{
    //initial

    snake->longeur=0;
    snake->score=0;
    snake->elements=snake_init_case(snake,p);
    snake_position_initial(snake,p);

  /*  p->position_case[snake->element_tete.emplacement_element.y+1][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+1][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+1][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+1][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+1][snake->element_tete.emplacement_element.x].lettre_fruit='P';

    p->position_case[snake->element_tete.emplacement_element.y+2][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+2][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+2][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+2][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+2][snake->element_tete.emplacement_element.x].lettre_fruit='B';

    p->position_case[snake->element_tete.emplacement_element.y+3][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+3][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+3][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+3][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+3][snake->element_tete.emplacement_element.x].lettre_fruit='C';

    p->position_case[snake->element_tete.emplacement_element.y+4][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+4][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+4][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+4][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+4][snake->element_tete.emplacement_element.x].lettre_fruit='P';



    p->position_case[snake->element_tete.emplacement_element.y+5][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+5][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+5][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+5][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+5][snake->element_tete.emplacement_element.x].lettre_fruit='F';

    p->position_case[snake->element_tete.emplacement_element.y+6][snake->element_tete.emplacement_element.x].fruit=true;
    p->position_case[snake->element_tete.emplacement_element.y+6][snake->element_tete.emplacement_element.x].obstacle=false;
    p->position_case[snake->element_tete.emplacement_element.y+6][snake->element_tete.emplacement_element.x].snake=false;
    p->position_case[snake->element_tete.emplacement_element.y+6][snake->element_tete.emplacement_element.x].vide=false;
    p->position_case[snake->element_tete.emplacement_element.y+6][snake->element_tete.emplacement_element.x].lettre_fruit='F';*/

    // todo gérer un emplacement aléatoire

    //p->position_case[0][0]=snake->position_snake[0][0][0];
    //todo gérer un sens aléatroire possible
    change_sens(snake,NULL);

}
void snake_move(snake *s,plateau * p)
{
    affiche_plateau(*p);
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
    if(s->sens == 's'|| s->sens == 'S')
    {
        s->element_tete.emplacement_element.y++;
        if(s->element_tete.emplacement_element.y >= p->hauteur)s->element_tete.emplacement_element.y=0;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)
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
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=true;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)
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
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle)
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y--;
            change_sens(s,p);

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.y--;
        }
    }
    else if(s->sens == 'z'|| s->sens == 'Z')
    {
    s->element_tete.emplacement_element.y--;
        if(s->element_tete.emplacement_element.y < 0)s->element_tete.emplacement_element.y=p->hauteur-1;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)
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
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=true;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)
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
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle)
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y++;
            change_sens(s,p);

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.y++;
        }

    }
    else if(s->sens == 'q'|| s->sens == 'Q')
    {
            s->element_tete.emplacement_element.x--;
        if(s->element_tete.emplacement_element.y >= p->hauteur)s->element_tete.emplacement_element.y=0;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)
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
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=true;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)
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
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle)
        {
            s->score -= 15;
            s->element_tete.emplacement_element.y--;
            change_sens(s,p);

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.y--;
        }
    }
    else if(s->sens == 'q'|| s->sens == 'Q')
    {
    s->element_tete.emplacement_element.x--;
        if(s->element_tete.emplacement_element.x < 0)s->element_tete.emplacement_element.x=p->largeur-1;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)
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
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=true;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)
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
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle)
        {
            s->score -= 15;
            s->element_tete.emplacement_element.x++;
            change_sens(s,p);

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.x++;
        }

    }
    else if(s->sens == 'd' || s->sens == 'D')
    {
        s->element_tete.emplacement_element.x++;
        if(s->element_tete.emplacement_element.x >= p->largeur)s->element_tete.emplacement_element.x=0;
        if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].vide)
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
                p->position_case[tmp_elm[0].emplacement_element.y][tmp_elm[0].emplacement_element.x].obstacle=true;
                p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x]=s->element_tete.emplacement_element;
            }
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].fruit)
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
        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].obstacle)
        {
            s->score -= 15;
            s->element_tete.emplacement_element.x++;
            change_sens(s,p);

        }
        else if(p->position_case[s->element_tete.emplacement_element.y][s->element_tete.emplacement_element.x].snake)
        {
            s->element_tete.emplacement_element.x++;
        }

    }
    printf("Score snake = %d \n",s->score);
    free(tmp_elm);
    change_sens(s,NULL);
    affiche_plateau(*p);
}
void snake_position_initial(snake *s,plateau* p)
{
//todo remettre random
    srand( time( NULL ) );
    int randomPosX ;
    int randomPosY ;
    do
    {
        randomPosX =rand()% p->largeur;
        randomPosY =rand()% p->hauteur;
    }
    while (p->position_case[randomPosY][randomPosX].snake &&
            !p->position_case[randomPosY][randomPosX].obstacle);
    p->position_case[randomPosY][randomPosX].fruit=false;
    p->position_case[randomPosY][randomPosX].obstacle=false;
    p->position_case[randomPosY][randomPosX].snake=true;
    p->position_case[randomPosY][randomPosX].vide=false;

    s->element_queu.emplacement_element=p->position_case[randomPosY][randomPosX];
    s->element_queu.emplacement_element.y=randomPosY;//random
    s->element_queu.emplacement_element.x=randomPosX;//random



    s->element_tete=s->element_queu;

    s->elements[0].emplacement_element.x=randomPosX;//random
    s->elements[0].emplacement_element.y=randomPosY;//random
    s->elements[0].emplacement_element.snake=true;
    s->elements[0].emplacement_element.obstacle=false;
    s->elements[0].emplacement_element.fruit=false;
    s->elements[0].emplacement_element.vide=false;
    s->element_queu.emplacement_element= p->position_case[randomPosY][randomPosX];//random



}
int get_score_fruit(char fruit)
{
    switch (fruit)
    {
    case 'P' :
        return 1;
        break;
    case 'B' :
        return 2;
        break;
    case 'C' :
        return 3;
        break;
    case 'F' :
        return 5;
        break;

    }

}
void change_sens(snake *s,plateau *p)
 {

    int random ;
        srand( time( NULL ) );
        random =rand()% 3;
         switch (random)
    {
    case 0 :
        s->sens ='d';
        break;
    case 1 :
        s->sens ='z';
        break;
    case 2 :
        s->sens ='q';
        break;
    case 3 :
        s->sens ='s';
        break;

    }




 }

