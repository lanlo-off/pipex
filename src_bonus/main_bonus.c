/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/06/18 17:53:23 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2][2];
	int	here_doc;
	int	i;
	
	if (ac < 5)
	{
		ft_putstr_fd("Not enough arguments!\n", 2);
		return (0);
	}
	here_doc = is_here_doc(av[1]);//0 si non, 1 si oui ==> pour adapter la suite
	i = 2 + here_doc;
	if (first_cmd(av, envp, pipefd[0], i) == -1)//premier enfant pour recupere les infos dans l'infile
		return (-1);
	while (i < ac)//toutes les iterations entre la premiere et la derniere
	{
		if ((i - here_doc) % 2 == 0)
			do_child(av, envp, pipefd, i);//renew le pipefd[1] ??
		else
			do_something_else(av, envp, pipefd, i);//pareil mais renew pipefd[0] ??
		i++;
	}
	if (last_cmd(av, envp, pipefd[i % 2], ac) == -1)//dernier enfant, voir si on prend pipefd[0] ou pipefd[1] selon i % 2 et here doc
		return (-1);// on peut gaire un exit -1 si fail et exit 0 si success dans last_cmd a la place pour gagner 2 lignes
	return (0);
}

int	is_here_doc(char *str)
{
	return (ft_strcmp(str, "here_doc") == 0);
}