/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:18:14 by nfukuma           #+#    #+#             */
/*   Updated: 2022/11/25 10:31:22 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENV_NAME 0
#define ENV_VALUE 1
#define TMP 2
#define RES 3

static void				expander_init(t_expander *exper, char *src_str, bool ex_flag);
static t_token_status	get_token_status(t_token_status state,
							t_token_type type);
static void				env_expand(t_expander *exper);

char	*expand_env(char *src_str, bool ex_flag)
{
	t_expander	exper;

	if (!src_str)
		return (NULL);
	expander_init(&exper, src_str, ex_flag);
	while (exper.str[exper.str_i])
	{
		exper.type = get_token_type(exper.str[exper.str_i]);
		exper.status = get_token_status(exper.status, exper.type);
		if (exper.type == CHAR_BACKSLASH && exper.str[exper.str_i + 1] \
			&& ft_strchr("\\\'\"$", exper.str[exper.str_i + 1]))
			exper.str_i++;
		else if (exper.str[exper.str_i] == '$' \
			&& (exper.status == NOT_QUOTED || exper.status == D_QUOTED))
			env_expand(&exper);
		exper.str_i++;
	}
	return (exper.str);
}

static void	expander_init(t_expander *exper, char *src_str, bool ex_flag)
{
	exper->str = ft_strdup(src_str);
	if (!exper->str)
		util_put_cmd_err_and_exit("in expander_init");
	exper->str_i = 0;
	exper->status = NOT_QUOTED;
	exper->ex_flag = ex_flag;
}

static t_token_status	get_token_status(t_token_status state,
										t_token_type type)
{
	if (state == NOT_QUOTED)
	{
		if (type == CHAR_D_QUOTE)
			return (D_QUOTED);
		if (type == CHAR_QUOTE)
			return (QUOTED);
	}
	else if (state == D_QUOTED && type != CHAR_D_QUOTE)
		return (D_QUOTED);
	else if (state == QUOTED && type != CHAR_QUOTE)
		return (QUOTED);
	return (NOT_QUOTED);
}

static void	clean_up_free(char **vars, char *env_value, t_expander *exper)
{
	free(vars[ENV_VALUE]);
	free(vars[ENV_NAME]);
	exper->str_i = ft_strlen(vars[TMP]) - 1;
	free(vars[TMP]);
	free(env_value);
	free(exper->str);
	exper->str = vars[RES];
}

static void	env_expand(t_expander *exper)
{
	char	*vars[4];
	char	*env_value;
	size_t	after_env_name_i;

	vars[ENV_NAME] = set_env_name(&exper->str[exper->str_i + 1]);
	if (ft_strlen(vars[ENV_NAME]) == 0)
	{
		ft_safe_free_single_ptr((void **)&vars[ENV_NAME]);
		return ;
	}
	exper->str[exper->str_i] = '\0';
	env_value = set_env_value(vars[ENV_NAME]);
	after_env_name_i = exper->str_i + ft_strlen(vars[ENV_NAME]) + 1;
	vars[ENV_VALUE] = create_esc_val(env_value, exper);
	if (!vars[ENV_VALUE])
		util_put_cmd_err_and_exit("env_expand");
	vars[TMP] = ft_strjoin(exper->str, vars[ENV_VALUE]);
	if (!vars[TMP])
		util_put_cmd_err_and_exit("env_expand");
	vars[RES] = ft_strjoin(vars[TMP], &exper->str[after_env_name_i]);
	if (!vars[RES])
		util_put_cmd_err_and_exit("env_expand");
	clean_up_free(vars, env_value, exper);
}
