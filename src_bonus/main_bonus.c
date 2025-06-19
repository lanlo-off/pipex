/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:23:30 by llechert          #+#    #+#             */
/*   Updated: 2025/06/19 05:34:10 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	i = 2 + here_doc;//i vaut donc 2 ou 3 car cmd0 est soit av[2] soit av[3]
	if (do_first_cmd(av, envp, pipefd[0], here_doc) == -1)//premier enfant pour recupere les infos dans l'infile
		return (-1);
	i++;
	while (i < ac - 2)//toutes les iterations entre la premiere et la derniere
	{
		if (prepare_child(av, envp, pipefd, i, here_doc) == -1)
			return (-1);
		i++;
	}
	if (do_last_cmd(av, envp, pipefd, i, here_doc) == -1)//dernier enfant, voir si on prend pipefd[0] ou pipefd[1] selon i % 2 et here doc
		return (-1);// on peut gaire un exit -1 si fail et exit 0 si success dans last_cmd a la place pour gagner 2 lignes
	wait_children(i, here_doc);
	return (0);
}

// void	wait_children(int i, int here_doc)
// {
// 	int	j;

// 	j = 0;
// 	(void)i;
// 	(void)here_doc;
// 	(void)j;
// 	// while (j < i - here_doc)
// 	// {
// 	// 	wait(NULL);
// 	// 	j++;
// 	// }
// 	wait(NULL);
// }

int	is_here_doc(char *str)
{
	return (ft_strcmp(str, "here_doc") == 0);
}