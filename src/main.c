/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:23:44 by llechert          #+#    #+#             */
/*   Updated: 2025/07/03 19:12:49 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	t_cmd	*tab_cmds;
	
	if (argc < 5)
		return (ft_putstr_fd("Not enough arguments!\n", 1), 0);
	args = ft_calloc(1, sizeof(t_args));
	if (!args)
		return (1);//bon code de sortie ??
	fill_args(args, argc, argv, envp);
	tab_cmds = init_cmds(args);
	if (!tab_cmds)
		return (1);
	pipex(tab_cmds, args);
	close_fds(tab_cmds[0].fd_in, tab_cmds[args->nb_cmd - 1].fd_out);
	wait_children(tab_cmds, args->nb_cmd);
	free_cmds(tab_cmds, args->nb_cmd);
	free(args);
	return (0);
}

void	fill_args(t_args *args, int argc, char **argv, char **envp)
{
	args->heredoc = (ft_strcmp(argv[1], "here_doc") == 0);
	args->nb_cmd = argc - 3 - args->heredoc;
	args->av = argv;
	args->env = envp;
}

t_cmd	*init_cmds(t_args *args)
{
	t_cmd	*tab_cmds;
	int		i;

	i = 0;
	tab_cmds = ft_calloc(args->nb_cmd ,sizeof(t_cmd));
	if (!tab_cmds)
		return (NULL);
	while (i < args->nb_cmd)
	{
		tab_cmds[i] = fill_cmd(tab_cmds, args, i);
		i++;
	}
	return(tab_cmds);
}

t_cmd	fill_cmd(t_cmd *tab_cmds, t_args *args, int i)
{
	t_cmd	new;

	new.cmd_nb = i;
	new.cmd = args->av[i + 2 + args->heredoc];
	new.cmd_split = ft_split(new.cmd, ' ');
	if (ft_strchr(new.cmd_split[0], '/') == NULL)
		new.path = get_path(new.cmd_split[0], args->env);
	else
		new.path = new.cmd_split[0];
	new.fd_in = 0;
	new.fd_out = 0;
	if (!i)//premiere cmd
		new.fd_in = open_infile(args->av[1], args->heredoc);
	// else if (i == args->nb_cmd - 1)//derniere cmd
	// 	new.fd_out = open_outfile(args->av[args->nb_cmd + 2 + args->heredoc], args->heredoc);
	if (new.fd_in < 0)// || new.fd_out < 0)//ils sont initialises a 0 donc ok
		exit_error(tab_cmds, args, i + 1, 1);//i + 1 car on prend la commande en cours egalement
	return (new);
}

int	wait_children(t_cmd *tab_cmds, int nb_cmd)//a verfier
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(tab_cmds[i].pid, &tab_cmds[i].exit_status, 0);
		if (WIFEXITED(tab_cmds[i].exit_status) != 0 && WEXITSTATUS(tab_cmds[i].exit_status) != 0)
		{
			ft_putstr_fd("cmd nb ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(" exit code : ", 2);
			ft_putnbr_fd(WEXITSTATUS(tab_cmds[i].exit_status), 2);
			ft_putchar_fd('\n', 2);
		}
		i++;
	}
	return (0);
}