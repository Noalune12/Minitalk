/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:39:25 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/15 08:39:43 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

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
