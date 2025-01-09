/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:33:47 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/09 10:34:02 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

// send each bytes using SIGUR1 for 0 and SIGUSR2 for 1

int	g_signal;

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

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (argc != 3 || !argv[2][0])
	{
		ft_printf("Invalid arguments");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, &signal_handler);
	message = argv[2];
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
