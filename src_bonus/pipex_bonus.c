/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:27 by llechert          #+#    #+#             */
/*   Updated: 2025/06/18 17:23:29 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_cmd(char **av, char **envp, int *pipefd, int i)
{
	int	pid;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)//on fait la cmd 1
	{
		ft_putstr_fd("Entering child process\n", 2);//a suppr
		do_child(pipefd, av, envp);
	}
	else if (pid > 0)//on part sur la suite
	{
		
	}
}

void	do_child(int *pipefd, char **av, char **envp)
{
	int	fd;

	printf("CHILD || PID: %d, Parent PID: %d\n", getpid(), getppid());//a suppr
	fd = open_file(av[1], "in");
	dup2(fd, 0);//on lit depuis infile
	dup2(pipefd[1], 1);//on ecrit sur la sortie du pipe ==> comme ca le process parent pourra lire ce qui vient du pipe
	close(pipefd[0]);//on ferme le cote lecture du pipe
	// close(pipefd[1]);
	// close(fd);
	exec_cmd(av[2], envp);
}

void	do_parent(int *pipefd, char **av, char **envp)
{
	int	fd;
	int	pid;

	printf("PARENT || PID: %d, Parent PID: %d\n", getpid(), getppid());//a suppr
	pid = fork();
	if (pid == 0)
	{
		fd = open_file(av[4], "out");
		dup2(pipefd[0], 0);//on lit depuis le pipe
		close(pipefd[1]);//on ferme la sortie du pipe (la ou on ecrit)
		dup2(fd, 1);//on ecrit sur l'outfile ==> comme ca le process parent pourra ecrire dans l'outfile
		// close(pipefd[0]);
		// close(fd);
		exec_cmd(av[3], envp);
	}
	else
	{
		// wait(NULL);
		// wait(NULL);
		// close(pipefd[0]);
		// close(pipefd[0]);
		// close(pipefd[1]);
	}
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');//on separe la commande des options eventuelles
	if (cmd_split == NULL)
	{
		ft_putstr_fd("Command empty: ", 2);
		exit(-1);
	}
	path = get_path(cmd_split[0], envp);//
	if (execve(path, cmd_split, envp) == -1)//si la commande n'existe pas
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_tab(cmd_split);
		free(path);
		exit(0);
	}
}