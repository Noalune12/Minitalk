#include "server.h"
#include <stdio.h>

// stock all the message and print
// void	store_message(char received, int index)
// {

// }

char *reallocate_message(char *message, char c, int len)
{
	char *ret;
	int i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		free(message);
		exit(EXIT_FAILURE);
	}
	while (message[i])
	{
		ret[i] = message[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(message);
	return (ret);
}

void store_message(char c, int *i, char **message)
{
	if (*i == 0)
	{
		*message = malloc(2 * sizeof(char));
		if (!*message)
		{
			exit(EXIT_FAILURE);
		}
		(*message)[0] = c;
		(*message)[1] = '\0';
	}
	else if (c == '\0')
	{
		printf("Message reçu : %s\n\n", *message);
		free(*message);
		*message = NULL;
		(*i) = -1;
	}
	else
	{
		*message = reallocate_message(*message, c, *i);
	}
	printf("message = %s\n", *message);
}

unsigned char reverse_bits(unsigned char b)
{
	unsigned char	ret = 0;
	unsigned		byte_len = 8;

	while (byte_len--)
	{
		ret = (ret << 1) | (b & 1);
		b >>= 1;
	}
	return (ret);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char received_char = 0;
	static int bit_count = 0;
	char reversed;
	static int i = 0;
	static char	*message;

	// message = NULL;
	(void)context;
	(void)info;
	// printf("Signal %d reçu\n", signum);
	if (signum == SIGUSR1) // 0
		// received_char &= ~(1 << bit_count);
	{
		received_char <<= 1;
		received_char |= 0x00;
	}
	else if (signum == SIGUSR2) // 1
	{
		received_char <<= 1;
		received_char |= 0x01;
	}
		// received_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		printf("i = %d\n", i);
		reversed = reverse_bits(received_char);
		// printf("message before storing = '%s'\n\n", message);
		store_message(reversed, &i, &message);
		// printf("Caractère reçu : %c\n", reversed);
		received_char = 0;
		bit_count = 0;
		i++;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_printf("Server PID = %d\n", getpid());
	s_sigaction.sa_sigaction = &signal_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
		pause();
	return (0);
}
