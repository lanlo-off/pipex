/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:23:44 by llechert          #+#    #+#             */
/*   Updated: 2025/07/03 11:23:24 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	t_cmd	**tab_cmds;
	
	if (argc < 5)
		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
	args = ft_calloc(1, sizeof(t_args));
	if (!args)
		return (1);//bon code de sortie ??
	fill_args(args, argc, argv, envp);
	tab_cmds = init_cmds(args);
	if (!tab_cmds)
		return (1);
}

void	fill_args(t_args *args, int argc, char **argv, char **envp)
{
	args->heredoc = (ft_strcmp(argv[1], "here_doc") == 0);
	args->nb_cmd = argc - 3 - args->heredoc;
	args->av = argv;
	args->env = envp;
}

t_cmd	**init_cmds(t_args *args)
{
	t_cmd	**tab_cmds;
	t_cmd	*tmp;
	int		i;

	i = 0;
	tab_cmds = ft_calloc(args->nb_cmd ,sizeof(t_cmd));
	if (!tab_cmds)
		return (NULL);
	(*tab_cmds) = fill_cmd(tab_cmds, *tab_cmds, args, i);
	while (i < args->nb_cmd)
	{
		tmp = *tab_cmds;
		i++;
	}
}

t_cmd	*fill_cmd(t_cmd **tab_cmds, t_args *args, int i)
{
	t_cmd	*new;

	new->cmd_nb = i;
	new->cmd = args->av[i + 2 + args->heredoc];
	new->cmd_split = ft_split(new->cmd, ' ');
	new->path = get_path(new->cmd_split[0], args->env);
	if (!new->cmd_nb && !(args->heredoc))
		new->fd_in = open_file(args->av[1], "in", args->heredoc);
	else if (!new->cmd_nb)//sous entendu on a here doc et on est a la premiere cmd
		new->fd_in = 0;//a voir
	else
		new->fd_in = -1;//jsp si ca sera disponible au moment ou on appelle la fonction donc = -1 pour l'initialisation
	if (i == args->nb_cmd)
		new->fd_out = open_file(args->av[args->nb_cmd + 2 + args->heredoc], "out", args->heredoc);
	else
		new->fd_out = -1;
	new->pid = -1;
	new->exit_status = -1;
	ft_lstadd_back(tab_cmds, new);
	return (new);
}

// t_cmd	*fill_cmd(t_cmd **tab_cmds, t_cmd *cmds, t_args *args, int i)
// {
// 	t_cmd	*tmp;

// 	if (*tab_cmds)
// 		tmp = ft_lstlast((t_list*)(*tab_cmds));
// 	else
// 		tmp = NULL;
// 	cmds->cmd_nb = i;
// 	cmds->cmd = args->av[i + 2 + args->heredoc];
// 	cmds->cmd_split = ft_split(cmds->cmd, ' ');
// 	cmds->path = get_path(cmds->cmd_split[0], args->env);
// 	if (!cmds->cmd_nb && !(args->heredoc))
// 		cmds->fd_in = open_file(args->av[1], "in", args->heredoc);
// 	else if (!cmds->cmd_nb)//sous entendu on a here doc et on est a la premiere cmd
// 		cmds->fd_in = 0;//a voir
// 	else
// 		cmds->fd_in = tmp->fd_out;//jsp si ca sera disponible au moment ou on appelle la fonction, sinon faire = -1 pour l'initialisation
// 	if (i == args->nb_cmd)
// 		cmds->fd_out = open_file(args->av[args->nb_cmd + 2 + args->heredoc], "out", args->heredoc);
// 	else
// 		cmds->fd_out = -1;
// 	cmds->pid = -1;
// 	cmds->exit_status = -1;
// 	ft_lstadd_back(tab_cmds, cmds);
// 	return (cmds);
// }