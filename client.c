/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:33:47 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/13 12:14:32 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_signal;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal = 1;
}

void	wait_signal(void)
{
	int	wait;

	wait = 0;
	while (g_signal == 0)
	{
		usleep(100);
		wait++;
		if (wait >= 5000)
		{
			ft_printf("Sending signal took too long");
			exit(EXIT_FAILURE);
		}
	}
}

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_signal = 0;
		if (c & (1 << i))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		wait_signal();
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
	if (server_pid <= 0 || kill(server_pid, SIGUSR1) == -1)
	{
		ft_printf("PID is not valid");
		return (1);
	}
	usleep(100);
	signal(SIGUSR1, &signal_handler);
	message = argv[2];
	i = -1;
	while (message[++i])
		send_char(server_pid, message[i]);
	send_char(server_pid, '\0');
	return (0);
}
