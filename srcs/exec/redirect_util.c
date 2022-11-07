// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   redirect_util.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/05 00:11:52 by nfukuma           #+#    #+#             */
// /*   Updated: 2022/11/06 23:38:16 by nfukuma          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
// #include "minishell.h"
//
// bool	redirects(t_cmd *cmd)
// {
// 	t_redirect	*redir;
// 	char		*origin_file;
//
// 	redir = cmd->redirects;
// 	while (redir)
// 	{
// 		origin_file = ft_strdup(redir->filename->comp);
// 		expand_tokens(&redir->filename);
// 		if (!origin_file)
// 			util_put_cmd_err_and_exit("in redirects");
// 		if (!check_redirect(redir, origin_file))
// 		{
// 			free(origin_file);
// 			cleanup_redirects(cmd);
// 			return (false);
// 		}
// 		free(origin_file);
// 		redir = redir->next;
// 	}
// 	return (true);
// }
