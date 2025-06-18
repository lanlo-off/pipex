/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:46:27 by llechert          #+#    #+#             */
/*   Updated: 2025/06/18 21:35:10 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// int	do_first_last(char **av, char **envp, int **pipefd, int i, int here_doc)
// {
// 	int	pid;

// 	if (pipe(pipefd) == -1)
// 		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (ft_putstr_fd("Could not fork!\n", 2), -1);
// 	else if (pid == 0 && i - here_doc == 2)//on fait la cmd 0
// 	{
// 		ft_printf("Entering first child process i = %i: cmd[%i]\n", i, i - 2 * here_doc);//a suppr
// 		do_first_cmd(av, envp, pipefd[0], here_doc);
// 	}
// 	else if (pid == 0)//derniere commande qui ecrit dans outfile
// 	{
// 		ft_printf("Entering last child process i = %i: cmd[%i]\n", i, i - 2 * here_doc);//a suppr
// 		do_last_cmd(pipefd, av, envp, i, here_doc);
// 	}
// 	else if (pid > 0)//on part sur la suite du programme
// 	{
// 		return (0);//close des trucs ? Free des trucs ?
// 	}
// }

int	do_first_cmd(char **av, char **envp, int *pipefd, int here_doc)
{
	int	fd;
	int	pid;

	if (pipe(pipefd) == -1)
		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);	
	else if (pid == 0)
	{
		ft_printf("FIRST CHILD || PID: %d, Parent PID: %d\n", getpid(), getppid());//a suppr
		if (here_doc == 0)//est ce que ca va marcher quand here_doc == 1 donc qu'on veut taper quelque chose ?
		{
			fd = open_file(av[1], "in", here_doc);
			dup2(fd, 0);//on lit depuis infile
		}
		dup2(pipefd[1], 1);//on ecrit sur la sortie du pipe ==> comme ca le process parent pourra lire ce qui vient du pipe
		close(pipefd[0]);//on ferme le cote lecture du pipe
		exec_cmd(av[2 + here_doc], envp);//Comment faire pour que la commande lise depuis l'entree standard ?
	}
	else//on part sur la suite du programme
	{
		// close(pipefd[1]);
		// close(fd);
		return (0);//close des trucs ? Free des trucs ?
	}
	return (0);
}

// int	prepare_last_cmd(char **av, char **envp, int **pipefd, int i, int here_doc)
// {
// 	int	pid;

// 	if (i % 2 == 0)
// 	{
// 		if (pipe(pipefd[]) == -1)
// 			return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
// 	}
// 	else
// 	{
// 		if (pipe(pipefd[]) == -1)
// 			return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		return (ft_putstr_fd("Could not fork!\n", 2), -1);
// 	else if (pid == 0)//derniere commande qui ecrit dans outfile
// 	{
// 		ft_printf("Entering last child process i = %i: cmd[%i]\n", i, i - 2 * here_doc);//a suppr
// 		do_last_cmd(av, envp, pipefd, i, here_doc);
// 	}
// 	else if (pid > 0)//on termine
// 	{
// 		return (0);//close des trucs ? Free des trucs ?
// 	}
// }

int	do_last_cmd(char **av, char **envp, int pipefd[2][2], int i, int here_doc)
{
	int	fd;
	int	pid;
	
	ft_printf("Entering last child process i = %i: cmd[%i]\n", i, i - 2 * here_doc);//a suppr
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)//derniere commande qui ecrit dans outfile
	{
		ft_printf("LAST CHILD || PID: %d, Parent PID: %d\n", getpid(), getppid());//a suppr
		fd = open_file(av[i + 1], "out", here_doc);//a priori i = ac - 2 ici toujours
		if (i % 2 == 0)
		{
			dup2(pipefd[1][0], 0);
			close(pipefd[1][1]);
		}
		else
		{
			dup2(pipefd[0][0], 0);//on lit depuis le pipe
			close(pipefd[0][1]);//on ferme la sortie du pipe (la ou on ecrit)
		}
		dup2(fd, 1);//on ecrit sur l'outfile ==> comme ca le process parent pourra ecrire dans l'outfile
		exec_cmd(av[i], envp);
	}
	else//on termine
	{
		return (0);//close des trucs ? Free des trucs ?
	}
	// close(pipefd[0]);
	// close(fd);
	return (0);
}

int	prepare_child( char **av, char **envp, int pipefd[2][2], int i, int here_doc)
{
	ft_printf("Entering child process i = %i: cmd[%i]\n", i, i - 2 - here_doc);
	if (i % 2 == 1)
	{
		if (pipe(pipefd[1]) == -1)
			return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
		do_child_odd(av, envp, pipefd, i, here_doc);
	}
	else
	{
		if (pipe(pipefd[0]) == -1)
			return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
		do_child_even(av, envp, pipefd, i, here_doc);
	}
	return (0);
}

int do_child_odd(char **av, char **envp, int pipefd[2][2], int i, int here_doc)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)
	{
		ft_printf("Entering child odd process i = %i: cmd[%i]\n", i, i - 2 - here_doc);//a suppr
		dup2(pipefd[0][0], 0);//pipe dans lequel la commande a ecrit
		close(pipefd[0][1]);//on va rien y ecrire dans celui-la
		dup2(pipefd[1][1], 1);//pipe ou on va ecrire (qu'on vient de renew)
		close(pipefd[1][0]);//Pas besoin d'y lire quoi que ce soit
		exec_cmd(av[i], envp);//verifier le i
	}
	else if (pid > 0)//on part sur la suite du programme
	{
		// close(pipefd[1]);
		return (0);//close des trucs ? Free des trucs ?
	}
	return (0);
}

int	do_child_even(char **av, char **envp, int pipefd[2][2], int i, int here_doc)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Could not fork!\n", 2), -1);
	else if (pid == 0)
	{
		ft_printf("Entering child odd process i = %i: cmd[%i]\n", i, i - 2 - here_doc);//a suppr
		dup2(pipefd[1][0], 0);//pipe dans lequel la commande a ecrit
		close(pipefd[1][1]);//on va rien y ecrire dans celui-la
		dup2(pipefd[0][1], 1);//pipe ou on va ecrire (qu'on vient de renew)
		close(pipefd[0][0]);//Pas besoin d'y lire quoi que ce soit
		exec_cmd(av[i], envp);//verifier le i
	}
	else if (pid > 0)//on part sur la suite du programme
	{
		// close(pipefd[1]);
		return (0);//close des trucs ? Free des trucs ?
	}
	return (0);
}


// int	do_cmd(char **av, char **envp, int *pipefd, int i, int here_doc)
// {
// 	int	pid;

// 	if (i - here_doc == 2)
// 		do_first(av, envp, pipefd[0], i, here_doc);
// 	else if ((i - here_doc) % 2 == 0)
// 	{
		
// 	}
// 	if (pipe(pipefd) == -1)
// 		return (ft_putstr_fd("Could not create pipe!\n", 2), -1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (ft_putstr_fd("Could not fork!\n", 2), -1);
// 	else if (pid == 0)//on fait la cmd 1
// 	{
// 		ft_printf("Entering child process [%i]\n", i - 1 - here_doc);//a suppr
// 		do_first(pipefd, av, envp, i);
// 	}
// 	else if (pid > 0)//on part sur la suite du programme
// 	{
// 		return (0);//close des trucs ? Free des trucs ?
// 	}
// }