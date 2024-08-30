/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:08:14 by eviala            #+#    #+#             */
/*   Updated: 2024/08/30 10:13:30 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		argc;
	char	*infile_char;
	char	*outfile_char;
	char	**env;
	char	**argv;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int		cmd_nbrs;
	int		pipe_nbrs;
	int		*pipe;
	int		idx;
}			t_pipex;

#endif
