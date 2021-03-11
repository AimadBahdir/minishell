/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:26:39 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/11 12:06:13 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_string(char *s)
{
	int i;

	i = -1;
	while (s != NULL && s[++i])
		write(1, &s[i], 1);
}

int		new_check(char **line2)
{
	if (line2[0][0] == '|' || line2[0][0] == ';'
	|| line2[0][0] == '>' || line2[0][0] == '<')
	{
		free(*line2);
		return (-1);
	}
	return (0);
}

int		join_new_line_check_read_more(char **line, char **line2)
{
	char	*temp;
	int		len;

	temp = *line;
	*line = ft_strjoin(*line, *line2);
	free(temp);
	len = ft_strlen(*line2);
	if (line2[0][len - 1] != '|' && valid_option(*line2, len - 1) == 1)
	{
		free(*line2);
		return (1);
	}
	return (0);
}

int		read_more(char **line)
{
	int		len;
	char	*line2;

	len = ft_strlen(*line);
	if (check_syntax(*line) == -1)
		return (-1);
	if (line[0][len - 1] == '|' && valid_option(*line, len - 1) == 1)
	{
		while (1)
		{
			write_string("> ");
			if (lsh_read_line_and_trim(&line2) == -1)
				return (-1);
			if (new_check(&line2) == -1)
				return (-1);
			if (line2[0] != '\0')
				if (join_new_line_check_read_more(line, &line2) == 1)
					return (1);
			free(line2);
		}
	}
	return (1);
}

int		lsh_read_line_and_trim(char **line)
{
	char *temp;

	if (get_next_line(0, line) == -1)
		return (-1);
	temp = *line;
	*line = ft_trim(*line);
	free(temp);
	return (0);
}

int		valid_option(char *line, int start)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (start > 0 && line[start - i] == '\\')
	{
		j++;
		i++;
	}
	if (j % 2 == 0)
		return (1);
	return (0);
}

int		greater_less(int start_arg, char *line)
{
	t_params.vld_der = 1;
	if ((line[start_arg] == '>' && line[start_arg + 1] == '>')
	|| (line[start_arg] == '<' && line[start_arg + 1] == '<'))
	{
		return (start_arg + 2);
	}
	else if ((line[start_arg] == '>') || (line[start_arg] == '<'))
	{
		return (start_arg);
	}
	return (-1);
}

int		cut_quotation(int start, char *line, int end)
{
	int i;

	i = 1;
	while (1)
	{
		if (line[start + i] == '\"' && valid_option(line, start + i) == 1)
			break ;
		i++;
	}
	i++;
	if (line[start + i] == '\0' || line[start + i] == ' '
	|| line[start + i] == '<' || line[start + i] == '>' || start + i > end)
		return (start + i);
	else
	{
		while (line[start + i] != '\0' && line[start + i] != ' '
		&& line[start + i] != '<' && line[start + i] != '>' && start + i < end)
		{
			if (line[start + i] == '\"' && valid_option(line, start + i) == 1)
				return (cut_quotation(start + i, line, end));
			i++;
		}
		return (start + i);
	}
}

int		cut_apostrophe(int start, char *line, int end)
{
	int i;

	i = 1;
	while (line[start + i] != '\'')
	{
		if (start + i > end)
			return (-1);
		i++;
	}
	i++;
	if (line[start + i] == '\0' || line[start + i] == ' '
	|| line[start + i] == '<' || line[start + i] == '>' || start + i > end)
		return (start + i);
	else
	{
		while (line[start + i] != '\0' && line[start + i] != ' '
		&& line[start + i] != '<' && line[start + i] != '>' && start + i < end)
		{
			if (line[start + i] == '\'' && valid_option(line, start + i) == 1)
				return (cut_apostrophe(start + i, line, end));
			i++;
		}
		return (start + i);
	}
}

int		cut_outher(int start_arg, char *line, int end, int *i)
{
	while (start_arg + *i < end)
	{
		if ((line[start_arg + *i] == '>' || line[start_arg + *i] == '<')
		&& valid_option(line, start_arg + *i) == 1)
			return (0);
		else if ((line[start_arg + *i] == '\"' || line[start_arg + *i] == '\'')
		&& valid_option(line, start_arg + *i) == 1)
			return (1);
		else if (line[start_arg + *i] == ' '
		&& valid_option(line, start_arg + *i) == 1)
			return (0);
		*i = *i + 1;
	}
	return (0);
}

int		get_end_arg(int start_arg, char *line, int end)
{
	int i;
	int value;

	i = 0;
	t_params.vld_der = 0;
	while (start_arg + i < end)
	{
		while (line[start_arg + i] == ' ' && start_arg + i < end)
			i++;
		if (valid_option(line, start_arg + i) == 1
		&& (line[start_arg + i] == '>' || line[start_arg + i] == '<'))
			return (greater_less(start_arg + i, line));
		else if (valid_option(line, start_arg + i) == 1
		&& line[start_arg + i] == '\"')
			return (cut_quotation(start_arg + i, line, end));
		else if (line[start_arg + i] == '\'')
			return (cut_apostrophe(start_arg + i, line, end));
		else
		{
			if (cut_outher(start_arg + i, line, end, &i) == 0)
				break ;
			continue;
		}
	}
	return (start_arg + i);
}

int		get_number_args(t_gargs **gargs)
{
	t_gargs	*ptr_list_shell;
	int		x;

	x = 0;
	ptr_list_shell = *gargs;
	if (ptr_list_shell == NULL)
		return (0);
	else
	{
		while (ptr_list_shell != NULL)
		{
			ptr_list_shell = ptr_list_shell->next;
			x++;
		}
	}
	return (x);
}

int		gestion_args(char *line, int start, int end, t_gargs **gargs)
{
	int i;
	int start_arg;
	int end_arg;

	i = 0;
	while (start + i < end && i >= 0)
	{
		while (line[start + i] == ' ')
			i++;
		if (start + i >= end)
			break ;
		start_arg = start + i;
		end_arg = get_end_arg(start_arg, line, end);
		if (end_arg == -1)
			return (-1);
		ft_lstadd_back_arg(gargs, ft_lstnew_args(start_arg,
		end_arg, t_params.vld_der));
		if (end_arg - start_arg == 0)
			i += 1;
		else
			i += end_arg - start_arg;
	}
	return (get_number_args(gargs));
}

int		is_nbr_car(char c)
{
	int i;

	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

char	*get_env(char *s)
{
	t_env *env;

	env = NULL;
	ft_setenv(&env, t_params.env);
	return (getenval(env, s));
}

int		checkpath_apostrophe(t_cargs **args, char *s, int i)
{
	while (s[i] != '\0' && s[i] != '\'')
	{
		ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
		i++;
	}
	return (i);
}

int		checkpath_backslash(t_cargs **args, char *s, int i, int in_quotation)
{
	if (in_quotation == 1)
	{
		if (s[i] != '\"' && s[i] != '\\')
			ft_lstcargsadd_back(args, ft_lstcargsnew('\\'));
	}
	ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
	return (i);
}

int		checkpath_quotation(t_cargs **args, char *s, int i)
{
	while (s[i] != '\"' && valid_option(s, i) == 1)
	{
		if (s[i] == '\\')
			i = checkpath_backslash(args, s, i + 1, 1);
		else if (s[i] == '$')
			i = checkpath_dollar(args, s, i + 1);
		else
		{
			ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
			i++;
		}
	}
	return (i);
}

int		checkpath_question_mark(t_cargs **args, int i)
{
	ft_lstcargsadd_back(args, ft_lstcargsnew('@'));
	ft_lstcargsadd_back(args, ft_lstcargsnew('?'));
	return (i);
}

int		checkpath_dollar(t_cargs **args, char *s, int i)
{
	if (s[i] == '?')
		return (checkpath_question_mark(args, i));
	else if (ft_isnumber(s[i]) == 0 && ft_alpha(s[i]) == 0)
		ft_lstcargsadd_back(args, ft_lstcargsnew('$'));
	else if (ft_isnumber(s[i]) == 1)
		return (i);
	else if (ft_alpha(s[i]) == 1 || s[i] == '_')
		ft_lstcargsadd_back(args, ft_lstcargsnew('@'));
	ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
	return (i);
}

char	*get_word_free(t_cargs **args)
{
	t_cargs *ptr_args;
	t_cargs *ptr_args2;
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * get_len_list(*args) + 1);
	ptr_args = *args;
	while (ptr_args != NULL)
	{
		ptr[i++] = ptr_args->c;
		ptr_args = ptr_args->next;
	}
	ptr[i] = '\0';
	ptr_args2 = *args;
	while (ptr_args2 != NULL)
	{
		ptr_args = ptr_args2;
		ptr_args2 = ptr_args2->next;
		free(ptr_args);
	}
	return (ptr);
}

char	*checkpath(char *s)
{
	t_cargs	*args;
	int		i;

	i = 0;
	args = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			i = checkpath_apostrophe(&args, s, i + 1);
		else if (s[i] == '\\')
			i = checkpath_backslash(&args, s, i + 1, 0);
		else if (s[i] == '\"')
			i = checkpath_quotation(&args, s, i + 1);
		else if (s[i] == '$')
			i = checkpath_dollar(&args, s, i + 1);
		else
			ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
		i++;
	}
	return (get_word_free(&args));
}

char	*fill_arg(int len, int start, char *line, int vldder)
{
	char	*s;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (len == 0)
		len++;
	s = (char *)malloc(sizeof(char ) * len + 1);
	while (len > i)
	{
		if (vldder == 1 && line[start + i] == '>' && line[start + i - 1] != '>')
			s[j++] = '@';
		else if (vldder == 1 && line[start + i] == '<')
			s[j++] = '@';
		else
			s[j++] = line[start + i];
		i++;
	}
	s[j] = '\0';
	temp = s;
	s = checkpath(s);
	free(temp);
	return (s);
}

void	change_position(t_gargs **gargs, int i)
{
	int		x;
	t_gargs	*ptr_list_shell;

	ptr_list_shell = *gargs;
	x = 0;
	while (x < i)
	{
		ptr_list_shell = ptr_list_shell->next;
		x++;
	}
	echonge_list_args(&ptr_list_shell);
}

void	check_more(t_gargs *gargs, char *line, int len, int norm)
{
	int i;
	int j;

	i = 0;
	gestion_fill_arg(gargs, line, len);
	j = number_of_words_in_table(t_params.args);
	if (norm == 1)
	{
		j = j - 2;
		echonge_list_args(&gargs);
		free_table_args();
		gestion_fill_arg(gargs, line, len);
	}
	while (i < j)
	{
		if (t_params.args[i][0] == '@')
		{
			change_position(&gargs, i);
			free_table_args();
			gestion_fill_arg(gargs, line, len);
			j = j - 2;
			i = 0;
		}
		i++;
	}
}

void	free_table_args(void)
{
	int i;

	i = 0;
	if (t_params.args != NULL)
	{
		while (t_params.args[i] != NULL)
			free(t_params.args[i++]);
		free(t_params.args);
	}
}

void	gestion_fill_arg(t_gargs *gargs, char *line, int len)
{
	t_gargs	*ptr_list_shell;
	int		i;

	i = 0;
	ptr_list_shell = gargs;
	t_params.args = (char **)malloc(sizeof(char *) * len + 1);
	while (ptr_list_shell != NULL)
	{
		len = ptr_list_shell->end - ptr_list_shell->start;
		t_params.args[i] = (char *)fill_arg(len,
		ptr_list_shell->start, line, ptr_list_shell->vld_der);
		ptr_list_shell = ptr_list_shell->next;
		i++;
	}
	t_params.args[i] = NULL;
}

int		get_args(char *line, int start, int end, int norm)
{
	int		i;
	int		len;
	t_gargs	*gargs;
	t_gargs	*ptr_list_shell;

	gargs = NULL;
	i = 0;
	len = gestion_args(line, start, end, &gargs);
	if (len == -1)
		return (-1);
	check_more(gargs, line, len, norm);
	while (gargs != NULL)
	{
		ptr_list_shell = gargs;
		gargs = gargs->next;
		free(ptr_list_shell);
	}
	return (1);
}

int		get_param_list_shell(char *line, int start, int end)
{
	int i;

	i = 0;
	while (line[start + i] == ' ')
		i++;
	if (line[start + i] != '>' && line[start + i] != '<')
	{
		if (get_args(line, start, end, 0) == -1)
			return (-1);
	}
	else
	{
		if (get_args(line, start, end, 1) == -1)
			return (-1);
	}
	return (1);
}

int		valid_quotation(char *line, int start, int open)
{
	int i;
	int j;
	int valid;

	i = 1;
	j = 0;
	while (start > 0 && line[start - i] == '\\')
	{
		j++;
		i++;
	}
	if (j % 2 == 0)
		valid = 1;
	else
		valid = 0;
	if ((valid && !open) || (!valid && open))
		return (1);
	return (0);
}

int		get_start_and_end_args(char *lne, t_inputs **list_shell)
{
	int i;
	int	start;
	int pipe;

	i = -1;
	start = 0;
	while (1)
	{
		if ((lne[++i] == '\"' || lne[i] == '\'') && valid_option(lne, i) == 1)
			i = get_end_index(lne, i);
		else if (((lne[i] == ';' || lne[i] == '|')
		&& valid_option(lne, i) == 1) || lne[i] == '\0')
		{
			pipe = 0;
			if (lne[i] == '|')
				pipe = 1;
			if (get_param_list_shell(lne, start, i) == -1)
				return (-1);
			ft_lstadd_back(list_shell, ft_lstnew(t_params.args, pipe));
			if ((lne[i] == ';' && lne[i + 1] == '\0') || lne[i] == '\0')
				break ;
			start = i + 1;
		}
	}
	return (1);
}

int		lsh_split_line(char *line, t_inputs **list_shell)
{
	if (get_start_and_end_args(line, list_shell) == -1)
		return (-1);
	return (1);
}

int		get_end_index(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (1 && line[i] != '\0')
		{
			if (line[i] == '\"' && valid_option(line, i) == 1)
				return (i);
			i++;
		}
		if (line[i] == '\0')
			t_params.error_text = "There is no supplement \"\n";
	}
	else if (line[i] == '\'')
	{
		i++;
		while (1 && line[i] != '\0')
		{
			if (line[i] == '\'')
				return (i);
			i++;
		}
		if (line[i] == '\0')
			t_params.error_text = "There is no supplement \'\n";
	}
	return (-1);
}

int		error_msg(void)
{
	t_params.error_text = "bash: syntax Error 2\n";
	return (-1);
}

int		pass_spe(char *line, int i)
{
	while (line[i] == ' ')
	{
		if (line[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int		check_syntax_redirection(char *line, int i)
{
	if (((line[i] == '>' && line[i + 1] == '>') && valid_option(line, i) == 1)
	|| ((line[i] == '<' && line[i + 1] == '<') && valid_option(line, i) == 1))
	{
		i = pass_spe(line, i + 2);
		if (line[i] == '|' || line[i] == ';'
		|| line[i] == '>' || line[i] == '<')
			return (-1);
		return (i - 1);
	}
	if (i + 1 == pass_spe(line, i + 1))
	{
		if (line[i + 1] == '|' || line[i + 1] == ';' || (line[i + 1] == '<'
		&& line[i] == '>') || (line[i + 1] == '>' && line[i] == '<'))
			return (-1);
	}
	else
	{
		i = pass_spe(line, i + 1);
		if (line[i] == '|' || line[i] == ';'
		|| line[i] == '<' || line[i] == '>')
			return (-1);
		i--;
	}
	return (i);
}

int		check_syntax_line(char *line, int i)
{
	if (line[0] == ';' || line[0] == '|')
		return (error_msg());
	if ((line[i] == '\'' || line[i] == '\"') && valid_option(line, i) == 1)
		i = get_end_index(line, i);
	if (i == -1)
		return (-1);
	if ((line[i] == '|' || line[i] == ';') && valid_option(line, i) == 1)
	{
		i = pass_spe(line, i + 1);
		if (line[i] == '|' || line[i] == ';')
			return (error_msg());
		i--;
	}
	else if ((line[i] == '>' || line[i] == '<') && valid_option(line, i) == 1)
	{
		if (line[i + 1] == '\0')
			return (error_msg());
		i = check_syntax_redirection(line, i);
		if (i == -1)
			return (error_msg());
	}
	else if (line[i] == '\\'
	&& valid_option(line, i) == 1 && line[i + 1] == '\0')
		return (error_msg());
	return (i);
}

int	check_syntax(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		i = check_syntax_line(line, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (1);
}

void	test_print(t_inputs *list_shell)
{
	int			i;
	int			j;
	t_inputs	*ptr_list_shell;

	j = 0;
	//alo aimad han timlilay aya list_shell
	printf("**************************\n");
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		printf("--------------------------\n");
		j = 0;
		while (ptr_list_shell->command[j] != NULL)
		{
			printf("command : |%s|\n", ptr_list_shell->command[j]);
			j++;
		}
		printf("pipe : %d\n", ptr_list_shell->pipe);
		printf("--------------------------\n");
		ptr_list_shell = ptr_list_shell->next;
	}
	printf("**************************\n");
	ptr_list_shell = list_shell;
	while (list_shell != NULL)
	{
		i = 0;
		while (list_shell->command[i] != NULL)
			free(list_shell->command[i++]);
		free(list_shell->command);
		ptr_list_shell = list_shell;
		list_shell = list_shell->next;
		free(ptr_list_shell);
	}
}

int		check_syntax_list(t_inputs *list_shell)
{
	int			i;
	int			pipe;
	t_inputs	*ptr_list_shell;

	i = 0;
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		pipe = ptr_list_shell->pipe;
		if (pipe == 1 && ptr_list_shell->command[0] == NULL)
			return (-1);
		ptr_list_shell = ptr_list_shell->next;
		if (ptr_list_shell != NULL && pipe == 1
		&& ptr_list_shell->command[0] == NULL)
			return (-1);
	}
	return (1);
}

int		check_line(char **line, t_inputs **list_shell)
{
	int	errors;

	errors = 0;
	if (check_syntax(*line) != -1)
		errors = lsh_split_line(*line, list_shell);
	else
	{
		write_string(t_params.error_text);
		free(*line);
		return (1);
	}
	if (errors == -1)
		write_string(t_params.error_text);
	else
	{
		if (check_syntax_list(*list_shell) != -1)
			test_print(*list_shell);
		else
			write_string("bash: syntax Error 3\n");
		*list_shell = NULL;
	}
	return (0);
}

void	lsh_loop(void)
{
	char		*line;
	t_inputs	*list_shell;

	list_shell = NULL;
	while (1)
	{
		write_string("bash-1.0$ ");
		if (lsh_read_line_and_trim(&line) == -1)
			write_string("bash: syntax Error\n");
		else if (read_more(&line) == -1)
			write_string("bash: syntax Error\n");
		else if (line[0] != '\0')
		{
			if (check_line(&line, &list_shell) == 1)
				continue;
		}
		free(line);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_params.env = envp;
	t_params.question_nbr = 45;
	lsh_loop();
	return (0);
}
