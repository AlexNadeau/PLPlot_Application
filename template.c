 #include <stdio.h>
 #include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "gng1106plplot.h"
#define TAILLE_MAX 500
#define G 9.81
#define density 1000
#define Nbr_Poids 5

typedef struct
{
    int n;
    double Cote;
    double Base;
    double ProfondeurI;
    double ProfondeurF;
    double Incre;
    int nbr_pas;
    double Prof[TAILLE_MAX];
    double Pression[TAILLE_MAX];
}CANAL;

void obtientEntree(CANAL *);
double getValeurPositive(char *);
void calculeAireTrapezoide (CANAL *);
double calculePression(double,double, double, double);
void plot(CANAL *);
double getMaxDouble(double *, int);
void tableau(CANAL *);
double choix1(FILE *,CANAL *);
void ouverturedeFichier(FILE *, CANAL *);
void sauvegardeFichier(FILE *, CANAL *);
void createFichier(FILE *);

void main()
{
    char ct;
    CANAL canal;
    FILE *fp;
    do
    {
        choix1(fp, &canal);
        calculeAireTrapezoide(&canal);
        plot(&canal);
        tableau(&canal);
        sauvegardeFichier(fp, &canal);
        printf("Voulez vous continuer(o/n)\n");
        fflush(stdin);
        scanf("%c", &ct);
    }while (ct == 'o');
    printf("Le programme se terminera");
}
double choix1(FILE *fp,CANAL *cnlptr )
{
    char choix;
    printf("Voulez vous utiliser les donnes dun fichier(o/n)\n");
    fflush(stdin);
    scanf("%c", &choix);
    if (choix == 'o')
    {
        ouverturedeFichier(fp, cnlptr);
    }
    else
    {
        obtientEntree(cnlptr);
    }
}
void ouverturedeFichier(FILE *fp, CANAL *cnlptr)
{
    char ch;
    int rep;
    fp =fopen("Test1.txt", "r+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        createFichier(fp);
    }
    else
    {
        printf("Fichier :\n");
        ch = fgetc(fp);
        while (ch != EOF)
            {
                printf ("%c", ch);
                ch = fgetc(fp);
            }
    }
    printf("\nQuelle donnes voulez-vous utiliser(1 a 5)\n");
    scanf("%d", &rep);
    fclose(fp);
    double a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y;
    fp = fopen("Test1.txt", "r");
    fscanf(fp, "%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  ",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m,&n,&o,&p,&q,&r,&s,&t,&u,&v,&w,&x,&y);
    fclose(fp);
    if (rep==1)
    {
        cnlptr->Cote = a;
        cnlptr->Base = b;
        cnlptr->ProfondeurI = c;
        cnlptr->ProfondeurF = d;
        cnlptr->Incre = e;
        cnlptr->n = 2 + (cnlptr->ProfondeurF - cnlptr->ProfondeurI)/cnlptr->Incre;
        printf("%lf %lf %lf %lf %lf\n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
    }
    else if (rep==2)
    {
        cnlptr->Cote = f;
        cnlptr->Base = g;
        cnlptr->ProfondeurI = h;
        cnlptr->ProfondeurF = i;
        cnlptr->Incre = j;
        cnlptr->n = 2 + (cnlptr->ProfondeurF - cnlptr->ProfondeurI)/cnlptr->Incre;
        printf("%lf %lf %lf %lf %lf\n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
    }
     else if (rep==3)
    {
        cnlptr->Cote = k;
        cnlptr->Base = l;
        cnlptr->ProfondeurI = m;
        cnlptr->ProfondeurF = n;
        cnlptr->Incre = o;
        cnlptr->n = 2 + (cnlptr->ProfondeurF - cnlptr->ProfondeurI)/cnlptr->Incre;
        printf("%lf %lf %lf %lf %lf\n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
    }
    else if (rep==4)
    {
        cnlptr->Cote = p;
        cnlptr->Base = q;
        cnlptr->ProfondeurI = r;
        cnlptr->ProfondeurF = s;
        cnlptr->Incre = t;
        cnlptr->n = 2 + (cnlptr->ProfondeurF - cnlptr->ProfondeurI)/cnlptr->Incre;
        printf("%lf %lf %lf %lf %lf\n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
    }
    else if (rep==5)
    {
        cnlptr->Cote = u;
        cnlptr->Base = v;
        cnlptr->ProfondeurI = w;
        cnlptr->ProfondeurF = x;
        cnlptr->Incre = y;
        cnlptr->n = 2 + (cnlptr->ProfondeurF - cnlptr->ProfondeurI)/cnlptr->Incre;
        printf("%lf %lf %lf %lf %lf\n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
    }
    else
    {
        printf("Erreur\n");
    }
}
void obtientEntree(CANAL *cnlPtr)
{
    cnlPtr->Cote = getValeurPositive("Donnez la distance du bord de la base du canal a la rive du canal");
    cnlPtr->Base = getValeurPositive("Donnez la largeur de la base du canal");
    do
    {
        cnlPtr->ProfondeurI = getValeurPositive("Donnez la profondeur initiale du canal");
        cnlPtr->ProfondeurF = getValeurPositive("Donnez la profondeur finale du canal");
        cnlPtr->Incre = getValeurPositive("Donnez la valeur de l'incrementation");
        cnlPtr->n = 2 + (cnlPtr->ProfondeurF - cnlPtr->ProfondeurI)/cnlPtr->Incre;
        if(cnlPtr->n > TAILLE_MAX)
            printf("L'incrementation est trop petite l'etendu des valeurs de la profondeur (%d)\n", cnlPtr->n);
        if(cnlPtr->n < 1)
            printf("La valeur de la profondeur finale doit etre plus grand que la valeur de la profondeur initiale\n");
    }while(cnlPtr->n > TAILLE_MAX || cnlPtr->n < 1);
}

double calculePression(double valeur, double cote, double base, double prof)
{
    int i;
    double fpression;
    double p;
    double h;
    double pre;
    h = valeur/Nbr_Poids;
    pre = 0;
    p=h;
    for(i = 1; i < Nbr_Poids; i = i + 1)
    {
        fpression = ((2*cote/pow(prof,2))*(pow(p,2)) + base)* (valeur-p);
        pre = pre + fpression;
        p = p + h;
    }
    pre = (density*G*h/2)*(2*pre + (base*valeur));
    pre = pre*p;

    return pre;
}

void plot(CANAL *cnlPtr)
{
    double maxAire;
    char etiquette[100];
    maxAire = getMaxDouble(cnlPtr->Pression, cnlPtr->n);
    maxAire = maxAire;
    plsdev("wingcc");
    plinit();
    plwidth(2);
    plenv(cnlPtr->ProfondeurI, cnlPtr->ProfondeurF, 0, maxAire, 0, 0);
    plcol0(GREEN);
    sprintf(etiquette, "La pression de l'eau en fonction de la profondeur");
    pllab("Profondeur (m)", "Pression(N)", etiquette);
    plcol0(RED);
    pllsty(LNGDASH_SHRTDASH);
    plline(cnlPtr->n, cnlPtr->Prof, cnlPtr->Pression);
    plptex(0.3*(cnlPtr->ProfondeurF - cnlPtr->ProfondeurI) + cnlPtr->ProfondeurI, maxAire, 0, 0, 0, "Pression");

    plend();
}

double getMaxDouble(double tbl[], int n)
{

    double max;
    int ix;
    max = -DBL_MAX;
    for(ix = 0; ix < n; ix = ix + 1)
    {
        if(max < tbl[ix]) max = tbl[ix];
    }
    return(max);
}

void tableau(CANAL *cnlPtr)
{
    int x;
    printf("%10s     %10s\n","Profondeur(m)","Pression(N)");
    for(x = 0; x <cnlPtr->n; x = x + 1)
    {
        printf("%10.2f          %10.4g\n", cnlPtr->Prof[x],cnlPtr->Pression[x]);
    }
}
void calculeAireTrapezoide(CANAL *cnlPtr)
{
    double valeur_profondeur;
    int ix;
    valeur_profondeur = cnlPtr->ProfondeurI;
    for(ix = 0; ix < cnlPtr->n; ix = ix + 1)
    {
        cnlPtr->Prof[ix] = valeur_profondeur;
        cnlPtr->Pression[ix] = calculePression(valeur_profondeur, cnlPtr->Cote, cnlPtr->Base, cnlPtr->ProfondeurF);
        valeur_profondeur = valeur_profondeur + cnlPtr->Incre;
    }
}
double getValeurPositive(char *invitation)
{
    double valeur;
    do
    {
        printf("%s: ", invitation);
        scanf("%lf",&valeur);
        if(valeur < 0.0)
            printf("La valeur doit etre plus grand que zero.\n");
    }
    while(valeur < 0.0);
    return(valeur);
}
void sauvegardeFichier(FILE *fp, CANAL *cnlptr)
{
    char rep2;
    int fok,ret;
    double a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y;
    FILE *tempfp;
    printf("Voulez vous sauvegarder vos donnes dans un fichier\n");
    fflush(stdin);
    scanf("%c", &rep2);
    if (rep2 == 'o')
        {
            printf("Dans quelle section voulez vous le sauvegarder\n");
            fflush(stdin);
            scanf("%d", &fok);
            tempfp = fopen("Temp.txt", "w+");
            fp = fopen("Test1.txt", "r");
            fscanf(fp, "%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  ",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m,&n,&o,&p,&q,&r,&s,&t,&u,&v,&w,&x,&y);
            if (fok == 1)
                {
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",f,g,h,i,j);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",k,l,m,n,o);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",p,q,r,s,t);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",u,v,w,x,y);
                    fclose(fp);
                    fclose(tempfp);
                    remove("Test1.txt");
                    rename("Temp.txt", "Test1.txt");
                }
            else if (fok==2)
                {
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",a,b,c,d,e);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",k,l,m,n,o);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",p,q,r,s,t);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",u,v,w,x,y);
                    fclose(fp);
                    fclose(tempfp);
                    remove("Test1.txt");
                    rename("Temp.txt", "Test1.txt");
                }
            else if (fok==3)
                {
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",a,b,c,d,e);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",f,g,h,i,j);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",p,q,r,s,t);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",u,v,w,x,y);
                    fclose(fp);
                    fclose(tempfp);
                    remove("Test1.txt");
                    rename("Temp.txt","Test1.txt");
                }
            else if (fok==4)
                {
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",a,b,c,d,e);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",f,g,h,i,j);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",k,l,m,n,o);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",u,v,w,x,y);
                    fclose(fp);
                    fclose(tempfp);
                    remove("Test1.txt");
                    rename("Temp.txt", "Test1.txt");
                }
            else if (fok==5)
                {
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",a,b,c,d,e);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",f,g,h,i,j);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",k,l,m,n,o);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n",p,q,r,s,t);
                    fseek(tempfp, 0, SEEK_CUR);
                    fprintf(tempfp, "%lf  %lf  %lf  %lf  %lf  \n", cnlptr->Cote, cnlptr->Base, cnlptr->ProfondeurI, cnlptr->ProfondeurF, cnlptr->Incre);
                    fclose(fp);
                    fclose(tempfp);
                    remove("Test1.txt");
                    rename("Temp.txt","Test1.txt");
                }
        }
    else
        {
            printf("Fin du programme\n");
        }
}
void createFichier(FILE *fp)
{
    double a = 5;
    printf("Un nouveau fichier appele Test1 sera cree\n");
    fp = fopen("Test1.txt","w+");
    fprintf(fp, "%lf  %lf  %lf  %lf  %lf  \n",(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a));
    fseek(fp, 0, SEEK_CUR);
    fprintf(fp, "%lf  %lf  %lf  %lf  %lf  \n",(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a));
    fseek(fp, 0, SEEK_CUR);
    fprintf(fp, "%lf  %lf  %lf  %lf  %lf  \n",(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a));
    fseek(fp, 0, SEEK_CUR);
    fprintf(fp, "%lf  %lf  %lf  %lf  %lf  \n",(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a));
    fseek(fp, 0, SEEK_CUR);
    fprintf(fp, "%lf  %lf  %lf  %lf  %lf  \n",(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a),(float)rand()/(float)(RAND_MAX/a));
    fclose(fp);
    fp = fopen("Test1.txt","r");
    printf("Nouveau fichier:\n");
    char ch = fgetc(fp);
    while (ch != EOF)
        {
            printf ("%c", ch);
            ch = fgetc(fp);
        }

    fclose(fp);
}
