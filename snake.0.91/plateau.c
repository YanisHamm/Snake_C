#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plateau.h"
#include "snake.h"
void get_argument(int argc, char **argv, plateau *p)
{

    int hauteur =0;
    int largeur =0;
    int nombre_snake =0;
    int niveau =0;
    int c;

    opterr=0;
    while ((c = getopt(argc,argv,"n:m:s:l:"))!=-1)
        switch (c)
        {
        case 'n' :
            //printf("option %c ,value %s \n",c,optarg);
            hauteur =atoi(optarg);
            break;
        case 'm' :
            //printf("option %c ,value %s \n",c,optarg);
            largeur =atoi(optarg);
            break;
        case 's' :
            //  printf("option %c ,value %s \n",c,optarg);
            nombre_snake =atoi(optarg);
            break;
        case 'l' :
            //  printf("option %c ,value %s \n",c,optarg);
            niveau =atoi(optarg);
            if(niveau >4)niveau=4;
            if(niveau <1)niveau=1;
            break;
        case '?' :
            if (optopt == 'c')
                fprintf (stderr,
                         "Option -%c requires an argument. \n",optopt);
            else if (isprint(optopt))
                fprintf(stderr,"Unknow Option '-%c'. \n",optopt);
            else
                fprintf(stderr, "Unknow option character '\\x%x'. \n",optopt);
        default:
            abort();
        }
    //remplissage de la structure plateau
    if(hauteur<=0  || largeur <=0 || nombre_snake <=0 || niveau <=0 || niveau > 4)
    {
        printf("Saisie invalide ou sans argument lancement du jeux par defaut... \n");
        p->hauteur=25;
        p->largeur=25;
        p->nombre_snake=2;
        p->niveau=1;
        p->position_case=mappage_plateau(*p);
        remplir_plateau(p);
        printf("Create Game....\n");
        return;
    }
    p->hauteur=hauteur;
    p->largeur=largeur;
    p->nombre_snake=nombre_snake;
    p->niveau=niveau;

    printf("Create Game....\n");

    p->position_case=mappage_plateau(*p);
    remplir_plateau(p);

}
void affiche_plateau(plateau p,void *snak)
{



    int i=0;
    int j=0;
    for(i=0; i<p.hauteur; i++)
    {
        printf("\n");
        if(i<10)printf("[%d] ",i);

        else printf("[%d]",i);
        for(j=0; j<p.largeur; j++)
        {
            if(p.position_case[i][j].vide == true)
            {
                if(j<10)printf("[ ]");
                else printf("[  ]");
            }
            else if(p.position_case[i][j].snake == true)
            {

                if(j<10)printf("[%d]",p.position_case[i][j].id_snake);
                else printf("[%d ]",p.position_case[i][j].id_snake);
            }
            else if(p.position_case[i][j].fruit==true)
            {
                if(j<10)printf("[%c]",p.position_case[i][j].lettre_fruit);
                else printf("[%c ]",p.position_case[i][j].lettre_fruit);
            }
            else
            {
                if(j<10)printf("[O]");
                else printf("[O ]");
            }
        }
    }
    printf("\n");
    printf("[ ] ");
    for(j=0; j<p.largeur; j++)
    {
        printf("[%d]",j);
    }
    printf("\n");


}
case_plateau** mappage_plateau(plateau p)
{
    case_plateau** map= NULL;
    map=(case_plateau**)malloc(p.hauteur*sizeof(case_plateau*));
    for(int j =0; j<p.hauteur; j++)
    {
        map[j]=(case_plateau*)malloc(p.largeur*sizeof(case_plateau));
    }
    for(int i =0; i<p.hauteur; i++)
    {
        for(int j =0; j<p.largeur; j++)
        {
            map[i][j].obstacle=false;
            map[i][j].snake=false;
            map[i][j].vide=true;
            map[i][j].fruit=false;
            map[i][j].x=j;
            map[i][j].y=i;
            //map[i][j].idsnake=666;

        }
    }
    return map;
}
void remplir_plateau(plateau *p)
{

    switch (p->niveau)
    {
    case 1:

        break;

    case 2:

        for(int i =0; i<p->hauteur; i++)
        {
            for(int j =0; j<p->largeur; j++)
            {
                if(i == p->hauteur -1 || j == p->largeur -1 || i==0 || j==0)
                {
                    p->position_case[i][j].obstacle=true;
                    p->position_case[i][j].vide=false;
                    p->position_case[i][j].fruit=false;
                    p->position_case[i][j].snake=false;

                }
            }
        }
        break;
    case 3:

        p->position_case[2][2].obstacle=true;
        p->position_case[2][2].vide=false;
        p->position_case[2][3].obstacle=true;
        p->position_case[2][3].vide=false;
        p->position_case[3][3].obstacle=true;
        p->position_case[3][3].vide=false;
        p->position_case[3][2].obstacle=true;
        p->position_case[3][2].vide=false;

        p->position_case[2][p->largeur-2-1].obstacle=true;
        p->position_case[2][p->largeur-2-1].vide=false;
        p->position_case[2][p->largeur-3-1].obstacle=true;
        p->position_case[2][p->largeur-3-1].vide=false;
        p->position_case[3][p->largeur-3-1].obstacle=true;
        p->position_case[3][p->largeur-3-1].vide=false;
        p->position_case[3][p->largeur-2-1].obstacle=true;
        p->position_case[3][p->largeur-2-1].vide=false;

        p->position_case[p->hauteur-2-1][p->largeur-2-1].obstacle=true;
        p->position_case[p->hauteur-2-1][p->largeur-2-1].vide=false;
        p->position_case[p->hauteur-2-1][p->largeur-3-1].obstacle=true;
        p->position_case[p->hauteur-2-1][p->largeur-3-1].vide=false;
        p->position_case[p->hauteur-3-1][p->largeur-3-1].obstacle=true;
        p->position_case[p->hauteur-3-1][p->largeur-3-1].vide=false;
        p->position_case[p->hauteur-3-1][p->largeur-2-1].obstacle=true;
        p->position_case[p->hauteur-3-1][p->largeur-2-1].vide=false;

        p->position_case[p->hauteur-2-1][2].obstacle=true;
        p->position_case[p->hauteur-2-1][2].vide=false;
        p->position_case[p->hauteur-2-1][3].obstacle=true;
        p->position_case[p->hauteur-2-1][3].vide=false;
        p->position_case[p->hauteur-3-1][3].obstacle=true;
        p->position_case[p->hauteur-3-1][3].vide=false;
        p->position_case[p->hauteur-3-1][2].obstacle=true;
        p->position_case[p->hauteur-3-1][2].vide=false;


        break;
    case 4:

        p->position_case[2][2].obstacle=true;
        p->position_case[2][2].vide=false;
        p->position_case[2][3].obstacle=true;
        p->position_case[2][3].vide=false;
        p->position_case[3][3].obstacle=true;
        p->position_case[3][3].vide=false;
        p->position_case[3][2].obstacle=true;
        p->position_case[3][2].vide=false;

        p->position_case[2][p->largeur-2-1].obstacle=true;
        p->position_case[2][p->largeur-2-1].vide=false;
        p->position_case[2][p->largeur-3-1].obstacle=true;
        p->position_case[2][p->largeur-3-1].vide=false;
        p->position_case[3][p->largeur-3-1].obstacle=true;
        p->position_case[3][p->largeur-3-1].vide=false;
        p->position_case[3][p->largeur-2-1].obstacle=true;
        p->position_case[3][p->largeur-2-1].vide=false;

        p->position_case[p->hauteur-2-1][p->largeur-2-1].obstacle=true;
        p->position_case[p->hauteur-2-1][p->largeur-2-1].vide=false;
        p->position_case[p->hauteur-2-1][p->largeur-3-1].obstacle=true;
        p->position_case[p->hauteur-2-1][p->largeur-3-1].vide=false;
        p->position_case[p->hauteur-3-1][p->largeur-3-1].obstacle=true;
        p->position_case[p->hauteur-3-1][p->largeur-3-1].vide=false;
        p->position_case[p->hauteur-3-1][p->largeur-2-1].obstacle=true;
        p->position_case[p->hauteur-3-1][p->largeur-2-1].vide=false;

        p->position_case[p->hauteur-2-1][2].obstacle=true;
        p->position_case[p->hauteur-2-1][2].vide=false;
        p->position_case[p->hauteur-2-1][3].obstacle=true;
        p->position_case[p->hauteur-2-1][3].vide=false;
        p->position_case[p->hauteur-3-1][3].obstacle=true;
        p->position_case[p->hauteur-3-1][3].vide=false;
        p->position_case[p->hauteur-3-1][2].obstacle=true;
        p->position_case[p->hauteur-3-1][2].vide=false;




        for(int i =0; i<p->hauteur; i++)
        {
            for(int j =0; j<p->largeur; j++)
            {
                if(i == p->hauteur -1 || j == p->largeur -1 || i==0 || j==0)
                {
                    p->position_case[i][j].obstacle=true;
                    p->position_case[i][j].vide=false;
                    p->position_case[i][j].fruit=false;
                    p->position_case[i][j].snake=false;

                }
            }
        }
        break;
    }
}
void placer_fruit(plateau *p)
{
    srand( time( NULL ) );
    int randomPosX ;
    int randomPosY ;
    char fruit;
    int randomFruit ;
    do
    {
        randomPosX =rand()% p->largeur;
        randomPosY =rand()% p->hauteur;
    }
    while (!p->position_case[randomPosX][randomPosY].vide);
    p->position_case[randomPosX][randomPosY].fruit=true;
    p->position_case[randomPosX][randomPosY].obstacle=false;
    p->position_case[randomPosX][randomPosY].snake=false;
    p->position_case[randomPosX][randomPosY].vide=false;



    randomFruit =rand()% 4;
    switch (randomFruit)
    {
    case 0 :
        fruit = 'P';
        break;
    case 1 :
        fruit ='B';
        break;
    case 2 :
        fruit = 'C';
        break;
    case 3 :
        fruit ='F';
        break;
    default :
        fruit =' ';

    }
    p->position_case[randomPosX][randomPosY].lettre_fruit=fruit;
    p->cible_fruit=p->position_case[randomPosX][randomPosY];



}
