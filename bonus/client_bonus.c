#include "client_bonus.h"
#include <stdio.h>
#include <stdlib.h>

int	g_signal;
// send each bytes using SIGUR1 for 0 and SIGUSR2 for 1

void	confirm_signal(int signum)
{
	if (signum == SIGUSR2)
		ft_printf("message received\n");
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal = 1;
}

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_signal = 0;
		if (c & (1 << i))
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				ft_printf("Error sending signal");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				ft_printf("Error sending signal");
				exit(EXIT_FAILURE);
			}
		}
		while (g_signal == 0)
			usleep(100);
	}
}

int main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (argc != 3 || !argv[2][0])
	{
		ft_printf("Invalid arguments");
		return (1);
	}
	server_pid = atoi(argv[1]);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, confirm_signal);
	message = argv[2];
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	// printf("Message sent to server with PID %d\n", server_pid);
	// if (kill(server_pid, SIGUSR1) == -1)
	// {
	// 	perror("Error sending signal");
	// 	return 1;
	// }

	// printf("Signal SIGUSR1 sent to server with PID %d\n", server_pid);
	return (0);
}