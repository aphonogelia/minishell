/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:44 by hruiz-fr          #+#    #+#             */
/*   Updated: 2024/10/17 10:34:15 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// protect if no PATH ?!...
char	*get_cmd_path(t_xnode *node, t_shell *ms)
{
	char	*cmd_path;
	char	*tmp;
	char	**path_table;
	int		i;
	char	*path;

	if (node->argv[0][0] == '.' || node->argv[0][0] == '/')
		return (node->argv[0]);
	path = get_env_value("PATH", ms);
	path_table = ft_split(path, ':');
	free(path);
	i = -1;
	while (path_table[++i])
	{
		tmp = ft_strjoin(path_table[i], "/");
		cmd_path = ft_strjoin(tmp, node->argv[0]);
		free(tmp);
		if (!access(cmd_path, F_OK))
		{
			free_array(path_table);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (free_array(path_table));
}
