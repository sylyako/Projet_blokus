#include "reseau.h"


/* Initialisation du serveur*/
void init_serveur (int *socket_serveur, struct sockaddr_in *adresse_serveur) {
	*socket_serveur = socket(AF_INET, SOCK_STREAM, 0);

	adresse_serveur->sin_family = AF_INET;
	adresse_serveur->sin_port = htons(9001);
	adresse_serveur->sin_addr.s_addr = INADDR_ANY;

	bind(*socket_serveur, (struct sockaddr *) adresse_serveur, sizeof (*adresse_serveur));

}

/*Ajoute les données des clients dans les sockets clients*/
void ajout_clients(int * socket_serveur,int socket_client [], int nbj_max) {
    int i;
    char message_attente [] = "En attente des autres joueurs ...", message_tt_present [] = "Tous les joueurs sont présents !";

    for (i = 0; i < nbj_max; i++) {
        socket_client [i] = accept (*socket_serveur, NULL, NULL);
        if ( i < nbj_max - 2){
            //send(socket_client[i], message_attente, sizeof(message_attente), 0);
            printf("Il manque encore %i %s\n", nbj_max - 2 - i, nbj_max - 2 - i > 1 ? "joueurs":"joueur");
        }else {
            for (i = 0; i < nbj_max; i++)  {
                 send(socket_client[i], message_tt_present, sizeof(message_tt_present), 0);
	    	 
	    }
	    
        }
    }
}


/*Connexion à un serveur via une IP à entrer et un port fixe*/
int connexion_serveur ( int *socket_client, struct sockaddr_in *server_address) {
	int i, statut;
	char  adresse_serveur [15];

	server_address->sin_family = AF_INET;
	server_address->sin_port = htons(9001);

	printf("Entrez l'adresse IP du serveur : ");
	scanf("%s", adresse_serveur);
	#ifdef WIN32
		server_address->sin_addr.s_addr = inet_addr(adresse_serveur);
	#elif (linux)
		inet_aton(adresse_serveur, &server_address->sin_addr);
	#endif

	statut = connect(*socket_client, (struct sockaddr *) server_address, sizeof(*server_address));

	return statut;
}






/*Envoie l'état du plateau à tous les joueurs qui ne sont pas le serveur*/
void envoyer_plateau_clients (int socket_client [], int taille_plateau, t_case (*plateau) [taille_plateau], int nbj_max) {
    int i;

    for(i = 0; i < nbj_max; i++)
         envoyer_plateau(socket_client [i], taille_plateau, plateau);
}

/*Fonction utilisée par le client pour envoyer le nouvel état du plateau au serveur*/
void envoyer_plateau (int socket_client, int taille_plateau, t_case (*plateau) [taille_plateau]) {

	send(socket_client, plateau, sizeof(t_case) * (taille_plateau * taille_plateau), 0);
}

/*Envoi du numéro attribué par le serveur au client*/
void envoyer_numero (int socket_client, int numero) {
	send(socket_client, (const void *) numero, sizeof(numero), 0);
}

/*Réception du nouveau plateau*/
void nv_plateau (int socket_client, int taille_plateau, t_case (*plateau) [taille_plateau]) {
    while (!recv(socket_client, plateau, sizeof(t_case) * (taille_plateau *taille_plateau), 0));
}
