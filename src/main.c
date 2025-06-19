/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/06/19 15:03:05 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	prev_fd;
	
	if (ac < 5)
		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
	if (is_here_doc(av[1]))
	{
		fd_out = open_file(av[ac - 1], "out", 1);
		// do_here_doc(av, envp, fd_out);
		// prev_fd = do_first_cmd(av, envp, 3, 0)
	}
	else
	{
		fd_in = open_file(av[1], "in", 0);
		fd_out = open_file(av[ac - 1], "out", 0);
		prev_fd = do_first_cmd(av, envp, 2, fd_in);
	}
	i = 3 + is_here_doc(av[1]);//3 + hd car premiere commande deja effectuee au dessus ou dans do_here_doc
	while (i < ac - 2)
		prev_fd = process_child(av, envp, i++, prev_fd);
	do_last_cmd(ac, av, envp, prev_fd, fd_out);//quand tu arrives ici, le dup2(pipefd[0], 0) du dernier chil est encore effectif
	close_fds(fd_in, fd_out);//a mon avis cette fonction pue la merde
	wait_children(ac - 2 - is_here_doc(av[1]));
	return (0);
}

int	is_here_doc(char *str)
{
	return (ft_strcmp(str, "here_doc") == 0);
}

void	wait_children(int nb_cmd)
{
	int	j;

	j = 0;
	while (j < nb_cmd)
	{
		wait(NULL);
		j++;
	}
}

// int	do_here_doc(char **av, char **envp, int fd_out)
// {
	
// }
