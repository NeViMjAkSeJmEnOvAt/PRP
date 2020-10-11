/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Michal Kurečka
 *
 * Created on 11. října 2020, 15:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VSTUP "skoky.txt"
#define VYSTUP "skoky.html"
#define BUFFER 100
#define ODDELENI ";\n"

typedef struct
{
    char jmeno[20];
    char prijmeni[20];
    char datumNarozeni[20];
    char stat[5];
    int delka;
    char tymy[10];
} ZAVODNICI;
float prumer(ZAVODNICI *zavodnici, int pocetZarazenych, int pocetZavodniku)
{
    float celkovyPocet = 0;
    int x = 0;
    float prumernaDelka = 0;

    for (; x < pocetZavodniku; x++)
    {
        if (strcmp(zavodnici[x].tymy, "ANO") == 0)
        {
            celkovyPocet += zavodnici[x].delka;
        }
    }
    prumernaDelka = celkovyPocet / pocetZarazenych;
    return prumernaDelka;
}
void vypis(int pocetZavodniku, int pocetNezarazenych, int nejdelsiSkok, float prumernaDelka, ZAVODNICI *zavodnici, int indexJmena)
{
    printf("Pocet zavodniku je %d\n", pocetZavodniku);
    printf("Pocet zavodniku v nezarazenych tymech je %d\n", pocetNezarazenych);
    printf("Nejdelsi skok %d metru dosahl %s %s z %s \n", nejdelsiSkok, zavodnici[indexJmena].jmeno, zavodnici[indexJmena].prijmeni, zavodnici[indexJmena].stat);
    printf("Prumerna delka skoku zavodniku v tymech je %f\n", prumernaDelka);
}

int main(int argc, char **argv)
{
    int pocetZavodniku = 0;
    int pocetNezarazenych = 0;
    int nejdelsiSkok = 0;
    int indexJmena = 0;
    int promenna1 = 0;
    int promenna2;
    int pocetZarazenych = 0;
    char *pch;
    char *ne = "NE";
    int x = 0;
    int y = 0;
    int z = 0;
    float prumernaDelka;

    ZAVODNICI *zavodnici = NULL;
    char buffer[BUFFER];
    FILE *soubor;
    FILE *vystup;

    soubor = fopen(VSTUP, "r");
    vystup = fopen(VYSTUP, "w");
    if (soubor == NULL)
    {
        printf("Soubor %s se neotevrel!\n", VSTUP);
        return (EXIT_FAILURE);
    }
    while (fgets(buffer, BUFFER, soubor) != NULL)
    {
        if (promenna1 > 0)
        {
            zavodnici = (ZAVODNICI *)realloc(zavodnici, promenna1 * sizeof(ZAVODNICI));
            promenna2 = 0;
            pch = strtok(buffer, ODDELENI);
            while (pch != NULL)
            {
                switch (promenna2)
                {
                case 0:
                    strcpy(zavodnici[promenna1 - 1].prijmeni, pch);
                    break;
                case 1:
                    strcpy(zavodnici[promenna1 - 1].jmeno, pch);
                    break;
                case 2:
                    strcpy(zavodnici[promenna1 - 1].datumNarozeni, pch);
                    break;
                case 3:
                    strcpy(zavodnici[promenna1 - 1].stat, pch);
                    break;
                case 4:
                    zavodnici[promenna1 - 1].delka = atoi(pch);
                    break;
                case 5:
                    strcpy(zavodnici[promenna1 - 1].tymy, pch);
                    break;
                }

                pch = strtok(NULL, ODDELENI);
                promenna2++;
            }
            pocetZavodniku++;
        }
        promenna1++;
    }
    promenna1--;
    for (x = 0; x < pocetZavodniku; x++)
    {
        if (strcmp(zavodnici[x].tymy, ne) == 0)
        {
            pocetNezarazenych++;
        }
    }
    for (x = 0; x < pocetZavodniku; x++)
    {
        if (zavodnici[x].delka > nejdelsiSkok)
        {
            nejdelsiSkok = zavodnici[x].delka;
            indexJmena = x;
        }
    }
    pocetZarazenych = pocetZavodniku - pocetNezarazenych;
    prumernaDelka = prumer(zavodnici, pocetZarazenych, pocetZavodniku);
    vypis(pocetZavodniku, pocetNezarazenych, nejdelsiSkok, prumernaDelka, zavodnici, indexJmena);

    /////// HMTL ////////////ú
    fprintf(vystup, "<h2> Tym CESKA REPUBLIKA \n</h2>");
    fprintf(vystup, "<table>\n");
    fprintf(vystup, "<tr>\n");
    fprintf(vystup, "<th>Poradove cislo</th>\n");
    fprintf(vystup, "<th>jmeno</th>\n");
    fprintf(vystup, "<th>Prijmeni</th>\n");
    fprintf(vystup, "<th>Datum narozeni</th>\n");
    fprintf(vystup, "<th>delka skoku</th>\n");
    fprintf(vystup, "</tr>\n");
    for (int a = 0; a < pocetZavodniku; a++)
    {
        if (strcmp(zavodnici[a].stat, "CZE") == 0)
        {
            if (strcmp(zavodnici[a].tymy, "ANO") == 0)
            {
                z++;
                fprintf(vystup, "<tr>\n");
                fprintf(vystup, "<td> %d </td>\n", z);
                fprintf(vystup, "<td> %s </td>\n", zavodnici[a].jmeno);
                fprintf(vystup, "<td> %s </td>\n", zavodnici[a].prijmeni);
                fprintf(vystup, "<td> %s </td>\n", zavodnici[a].datumNarozeni);
                fprintf(vystup, "<td> %d </td>\n", zavodnici[a].delka);
                fprintf(vystup, "</tr>\n");
            }
        }
    }
    fprintf(vystup, "</table>\n");

    if (fclose(soubor) == EOF)
    {
        printf("Soubor %s se nepodarilo uzavrit\n", VSTUP);
    }
    if (fclose(vystup) == EOF)
    {
        printf("Soubor %s se nepodarilo uzavrit\n", VYSTUP);
    }
    else
    {
        printf("Soubor %s byl usepne vytvoren!\n", VYSTUP);
    }
    return 0;
}