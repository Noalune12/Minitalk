#include <sys/time.h>

void store_message(char c, int *i)
{
	static char *message;
	struct timeval start_time, end_time;
	long seconds, useconds;
	double elapsed_time;

	// Mesurer le temps de l'enregistrement du message
	gettimeofday(&start_time, NULL); // Enregistrer le début

	if (*i == 0)
	{
		message = malloc(2 * sizeof(char));
		if (!message)
			exit(EXIT_FAILURE);
		message[0] = c;
		message[1] = '\0';
	}
	else if (c == '\0') // Si on a atteint la fin du message
	{
		ft_printf("%s\n", message); // Afficher le message
		free(message);
		message = NULL;
		(*i) = -1;
	}
	else
	{
		message = reallocate_message(message, c, *i);
	}

	// Calculer le temps écoulé pour cette opération
	gettimeofday(&end_time, NULL); // Enregistrer la fin
	seconds = end_time.tv_sec - start_time.tv_sec;
	useconds = end_time.tv_usec - start_time.tv_usec;

	// Si la microseconde est négative, ajuster
	if (useconds < 0)
	{
		seconds--;
		useconds += 1000000;
	}

	elapsed_time = seconds + useconds / 1000000.0; // Calcul du temps total
	printf("Temps pris pour stocker et afficher le message: %.6f secondes.\n", elapsed_time);
}
