#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exo1.h"

void entrer (char adresse[100])
{
    printf("entrer l'adresse :");
    scanf("%s",adresse);
}
void msr (char masque[100])
{
    printf("entrer la masque de sous réseau :");
    scanf("%s",masque);
}

void separer (char adresse[100],char masque[100])
{
    int i=0;
    int chiffre1, chiffre2, chiffre3, chiffre4;
    int octet1, octet2, octet3, octet4;
    char* token = strtok(adresse, ".");

    if (token != NULL)
    {
        chiffre1 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL) 
    {
        chiffre2 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL)
    {
        chiffre3 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL)
    {
        chiffre4 = atoi(token);
        i++;
    }
    if ( i > 4 || chiffre1 > 255 || chiffre2 > 255 || chiffre3 > 255 || chiffre4 > 255 || !(chiffre1 >= 0 && chiffre2 >= 0 && chiffre3 >= 0 && chiffre4 >= 0))
    {
        printf("Ce n'est pas un adresse IP !");
        exit(1);
    }
        if (chiffre1 >= 0 && chiffre2 >= 0 && chiffre3 >= 0 && chiffre4 >= 0)
        {
             printf("C'est un adresse IP   ");
                if (chiffre1 <= 127 && chiffre1 > 0)
                {
                    printf("de classe A\n");

                    msr (masque);
                    char* resultatBinaire = adresseIPEnBinaire(masque);
                    printf("L'adresse masque de sous reseau est %s en binaire est %s\n", masque, resultatBinaire);
                    test_msr (resultatBinaire);
                    printf("\n Masque de sous réseaux par défaut : 255.0.0.0");
                    printf("\nAdresse Broadcast : %d.255.255.255\n",chiffre1);
                    printf("Nombre de machines qui peuvent se connecter : 16777214\n");
                
                }

                if (chiffre1 >127 && chiffre1 <= 191)
                {
                    printf("de classe B\n");

                    msr (masque);
                    char* resultatBinaire = adresseIPEnBinaire(masque);
                    printf("L'adresse masque de sous reseau est %s en binaire est %s\n", masque, resultatBinaire);
                    test_msr (resultatBinaire);
                    printf("\n Masque de sous réseaux par défaut : 255.255.0.0");
                    printf("Adresse du Réseau : %d.%d.0.0",chiffre1,chiffre2);
                    printf("\nAdresse Broadcast : %d.%d.255.255\n",chiffre1,chiffre2);
                    printf("Nombre de machines qui peuvent se connecter : 65534\n");
                }
                if (chiffre1 >191 && chiffre1 <= 223)
                {
                    printf("de classe C\n");

                    msr (masque);
                    char* resultatBinaire = adresseIPEnBinaire(masque);
                    printf("L'adresse masque de sous reseau est %s en binaire est %s\n", masque, resultatBinaire);
                    test_msr (resultatBinaire);
                    printf("\n Masque de sous réseaux par défaut : 255.255.255.0");
                    printf("Adresse du Réseau : %d.%d.%d.0\n",chiffre1,chiffre2,chiffre3);
                    printf("Adresse Broadcast : %d.%d.%d.255\n",chiffre1,chiffre2,chiffre3);
                    printf("Nombre de machines qui peuvent se connecter : 254\n");
                }

                if (chiffre1 >223 && chiffre1 <= 239)
                {
                    printf("de classe D\n");
                }
                if (chiffre1 >239)
                {
                    printf("de classe E\n");
                }
        }
}

char* octetEnBinaire(int octet)
{
    char* binaire = (char*)malloc(9 * sizeof(char));
    if (binaire == NULL)
    {
        printf("Erreur d'allocation ! ");
        exit(1);
    }

    binaire[8] = '\0';
    for (int i = 0; i < 8; i++) {
        binaire[7 - i] = (octet & (1 << i)) ? '1' : '0';
    }
    return binaire;
}

char* adresseIPEnBinaire(char masque[100])
{
    char* resultat = (char*)malloc(35 * sizeof(char)); 
    if (resultat == NULL)
    {
        perror("Erreur d'allocation");
        exit(1);
    }
    resultat[0] = '\0';

    int octets[4];
    if (sscanf(masque, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]) != 4) {
        printf("Format invalide.\n\n");
        free(resultat);
        exit(1);
    }

    for (int i = 0; i < 4; i++) {
        char* binaire = octetEnBinaire(octets[i]);
        strcat(resultat, binaire);
        if (i < 3) {
            strcat(resultat, ".");
        }
        free(binaire);
    }

    return resultat;
}


void test_msr (char tab[33])
{
    int i;
    int oui = 0;

    for (i = 0; i < 32; i++) 
    {
        if (tab[i] == '0' && tab[i+1] == '1')
        {
            if (!oui) {
                printf("Masque de sous réseau invalide !\n");
                oui = 1;
            }
        }
    }
    
}
