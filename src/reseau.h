#ifdef WIN32

#include <winsock2.h>

#elif (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structures.h"

static void init(void)
{
#ifdef WIN32
   WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      puts("WSAStartup failed !");
      exit(EXIT_FAILURE);
   }
#endif
}

static void end(void)
{
#ifdef WIN32
   WSACleanup();
#endif
}

void init_serveur (int *socket_serveur, struct sockaddr_in *adresse_serveur);
void ajout_clients(int * socket_serveur,int socket_client [], int nbj_max);
int connexion_serveur ( int *socket_client, struct sockaddr_in *server_address);
void envoyer_plateau_clients (int socket_client [], int taille_plateau, t_case (*plateau) [taille_plateau], int nbj_max);
void envoyer_plateau (int socket_client, int taille_plateau, t_case (*plateau) [taille_plateau]);
void nv_plateau (int socket_client, int taille_plateau, t_case (*plateau) [taille_plateau]);
void envoyer_numero (int socket_client, int numero);
