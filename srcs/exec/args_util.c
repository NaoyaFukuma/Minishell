/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:07:44 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/25 03:28:30 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**convert_args(t_command *cmd);

bool	token_to_args(t_command *cmd, char ***args)
{
	if (ft_strcmp(cmd->args->comp, "export") == 0)
		expander(&cmd->args, true);
	else
		expander(&cmd->args, false);
	*args = convert_args(cmd);
	if (*args[0] == NULL)
		return (false);
	return (true);
}

static char	**convert_args(t_command *cmd)
{
	char			**args;
	t_token_list	*now_token;
	size_t			argc;
	size_t			i;

	argc = 0;
	now_token = cmd->args;
	while (now_token && ++argc)
		now_token = now_token->next;
	args = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!args)
		util_put_cmd_err_and_exit("in convert_args");
	now_token = cmd->args;
	i = -1;
	while (++i < argc)
	{
		args[i] = ft_strdup(now_token->comp);
		if (!args[i])
			util_put_cmd_err_and_exit("in convert_args");
		now_token = now_token->next;
	}
	args[i] = NULL;
	return (args);
}
