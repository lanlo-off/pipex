/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/06/19 05:37:46 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		i;
	
	if (ac < 5)
		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
	if(is_here_doc(av[1]))
	{
		//gerer here doc + limiter
	}
	
	return (0);
}
