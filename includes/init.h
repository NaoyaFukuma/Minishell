/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:24:35 by nfukuma           #+#    #+#             */
/*   Updated: 2022/10/27 14:16:46 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "libft.h"
# include <stdbool.h>           // for type bool
# include <sys/stat.h>          // for stat()


// in init_shell.c
void	init_minishell(void);
void	init_pwd(void);
void	init_oldpwd(void);

#endif
