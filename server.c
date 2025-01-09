#include "server.h"
#include <stdio.h>

// stock all the message and print
// void	store_message(char received, int index)
// {

// }

int	initialized_static;

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

void store_message(char c, int *i)
{
	static char	*message;

	if (*i == 0)
	{
		message = malloc(2 * sizeof(char));
		if (!message)
		{
			exit(EXIT_FAILURE);
		}
		(message)[0] = c;
		(message)[1] = '\0';
	}
	else if (c == '\0')
	{
		ft_printf("%s\n", message);
		free(message);
		message = NULL;
		(*i) = -1;
	}
	else
		message = reallocate_message(message, c, *i);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	received_char;
	static int	bit_count;
	static int	i;

	if (initialized_static == 0)
	{
		received_char = 0;
		bit_count = 0;
		i = 0;
		initialized_static = 1;
	}
	(void)context;
		received_char <<= 1;
		if (signum == SIGUSR2)
			received_char |= 0x01;
		bit_count++;
		if (bit_count == 8)
		{
			store_message(received_char, &i);
			received_char = 0;
			bit_count = 0;
			i++;
		}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	initialized_static = 0;
	ft_printf("Server PID = %d\n", getpid());
	s_sigaction.sa_sigaction = &signal_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);	while (1)
		pause();
	return (0);
}
