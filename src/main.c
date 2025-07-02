/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/07/02 16:51:49 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// int	main(int ac, char **av, char **envp)
// {
// 	int	i;
// 	int	fd_in;
// 	int	fd_out;
// 	int	prev_fd;
	
// 	if (ac < 5)
// 		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
// 	if (is_here_doc(av[1]))
// 	{
// 		fd_out = open_file(av[ac - 1], "out", 1);
// 		// do_here_doc(av, envp, fd_out);
// 		// prev_fd = do_first_cmd(av, envp, 3, 0)
// 	}
// 	else
// 	{
// 		fd_in = open_file(av[1], "in", 0);
// 		fd_out = open_file(av[ac - 1], "out", 0);
// 		prev_fd = do_first_cmd(av, envp, 2, fd_in);//possible de mutualiser cette ligne ainsi que fd_in = dans 
// 		//l'indentation principale en disant opne_file(here_doc = 1) renvoie fd_in = 0
// 	}
// 	i = 3 + is_here_doc(av[1]);//3 + hd car premiere commande deja effectuee au dessus ou dans do_here_doc
// 	while (i < ac - 2)
// 		prev_fd = process_child(av, envp, i++, prev_fd);
// 	do_last_cmd(av[ac - 2], envp, prev_fd, fd_out);
// 	close_fds(fd_in, fd_out);//a mon avis cette fonction pue la merde
// 	wait_children(ac - 2 - is_here_doc(av[1]));
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	here_doc;
	int	fd_in;
	int	fd_out;
	int	prev_fd;
	
	if (ac < 5)
		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
	here_doc = is_here_doc(av[1]);
	fd_in = open_file(av[1], "in", here_doc);
	fd_out = open_file(av[ac - 1], "out", here_doc);
	if (here_doc)
		prev_fd = do_here_doc(av, envp, fd_out);
	else
		prev_fd = do_first_cmd(av, envp, 2, fd_in);
	i = 3 + here_doc;//3 + hd car premiere commande deja effectuee au dessus ou dans do_here_doc
	while (i < ac - 2)
		prev_fd = process_child(av, envp, i++, prev_fd);
	do_last_cmd(av[ac - 2], envp, prev_fd, fd_out);
	close_fds(fd_in, fd_out);
	wait_children(ac - 2 - here_doc);
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

int	do_here_doc(char **av, char **envp, int fd_out)
{
	int		pipefd[2];
	pid_t	pid;
	char	*line;
	char	*limiter;
	int		lim_len;

	line = NULL;
	limiter = av[2];
	lim_len = ft_strlen(limiter);
	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)//la dedans caser un gnl(-42) pour eviter un segfault ?
		{
			ft_putstr_fd("heredoc> ", 1);
			line = get_next_line(0);
			if (!line)
				break;
			if (!ft_strncmp(line, limiter, lim_len) && line[lim_len] == '\n')
			{
				free(line);
				break;
			}
			ft_putstr_fd(line, pipefd[1]);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	else
		close(pipefd[1]);
	return (do_first_cmd(av, envp, 3, pipefd[0]));
}
