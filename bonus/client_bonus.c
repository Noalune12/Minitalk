/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:36:31 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/15 09:05:13 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

int	g_signal = 0;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal = 1;
	if (signum == SIGUSR2)
		ft_printf("message received\n");
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
	g_signal = 0;
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

int	check_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (ft_isdigit(pid[i]) == 0)
			return (0);
		i++;
	}
	return (1);
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
	if (server_pid <= 0 || check_pid(argv[1]) == 0
		|| kill(server_pid, SIGUSR1) == -1)
	{
		ft_printf("PID is not valid");
		return (1);
	}
	signal(SIGUSR1, signal_handler);
	wait_signal();
	signal(SIGUSR2, signal_handler);
	message = argv[2];
	i = -1;
	while (message[++i])
		send_char(server_pid, message[i]);
	send_char(server_pid, '\0');
	return (0);
}
