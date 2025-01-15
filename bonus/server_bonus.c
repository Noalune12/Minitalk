/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:35:29 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/15 08:36:22 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

int	g_signal_received = 0;

char	*reallocate_message(char *message, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		free(message);
		ft_printf("Malloc failed");
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

void	store_message(char c, int *i)
{
	static char	*message;

	if (*i == 0)
	{
		message = malloc(2 * sizeof(char));
		if (!message)
		{
			ft_printf("Malloc failed");
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

void	reinit_static(char *received_char, int *bit_count, int *i)
{
	*received_char = 0;
	*bit_count = 0;
	(*i)++;
	if (*i == 0)
		g_signal_received = 0;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	received_char = 0;
	static int	bit_count = 0;
	static int	i = 0;

	if (g_signal_received == 0)
	{
		g_signal_received = 1;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	(void)context;
	received_char <<= 1;
	if (signum == SIGUSR2)
		received_char |= 0x01;
	bit_count++;
	if (bit_count == 8)
	{
		store_message(received_char, &i);
		if (i == -1)
			kill(info->si_pid, SIGUSR2);
		reinit_static(&received_char, &bit_count, &i);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	g_signal_received = 0;
	ft_printf("Welcome to lbuisson's server\nServer PID = %d\n", getpid());
	s_sigaction.sa_sigaction = signal_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaddset(&s_sigaction.sa_mask, SIGUSR1);
	sigaddset(&s_sigaction.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
		pause();
	return (0);
}
