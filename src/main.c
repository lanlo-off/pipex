/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/06/17 17:31:36 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];
	int	pid;
	
	if (ac != 5)
	{
		ft_putstr_fd("Wrong arguments : infile, cmd1, cmd2, outfile\n", 2);
		return (0);
	}
	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	printf("MAIN || PID: %d, Parent PID: %d\n", getpid(), getppid());//a suppr
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)//on fait la cmd 1
	{
		ft_putstr_fd("Entering child process\n", 2);//a suppr
		do_child(pipefd, av, envp);
	}
	else if (pid > 0)//on fait la cmd 2
	{
		ft_putstr_fd("Entering parent process\n", 2);//a suppr
		do_parent(pipefd, av, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
