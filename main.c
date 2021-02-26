/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:26:39 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/26 16:14:12 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_string(char *s)
{
	int i;

	i = -1;
	while(s != NULL && s[++i])
		write(1, &s[i],1);
}

void lsh_read_line_and_trim(char **line)
{
	char *temp;

	if(get_next_line(0, line) == -1)
		write_string("Error in GNL");
	temp = *line;
	*line = ft_trim(*line);
	free(temp);
}

int valid_option(char *line , int start)
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
	valid = (j % 2 == 0 )? 1: 0;
	return(valid);
}

int greater_less(int start_arg, char *line) 
{
	t_params.vld_der = 1;
	if((line[start_arg] == '>' && line[start_arg + 1] == '>') || (line[start_arg] == '<' && line[start_arg + 1] == '<'))
	{
		return (start_arg + 2);
	}
	else if((line[start_arg] == '>') || (line[start_arg] == '<'))
	{
		return(start_arg);
	}
	return(-1);
}

int cut_quotation(int start_arg, char *line, int end)
{
	int i;

	i = 1;
	while(1)
	{
		if(line[start_arg + i] == '\"' && valid_option(line, start_arg + i) == 1)
			break;
		if(start_arg + i > end)
			return (-1);
		i++;
	}
	i++;
	if(line[start_arg + i] == '\0' || line[start_arg + i] == ' ' || line[start_arg + i] == '<' || line[start_arg + i] == '>' || start_arg + i > end) 
		return(start_arg + i);
	else
	{
		while(line[start_arg + i] != '\0' && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>' && start_arg + i < end)
		{
			if(line[start_arg + i] == '\"' && valid_option(line, start_arg + i) == 1)
				return(cut_quotation(start_arg + i, line, end)); 
			i++;
		}
		return(start_arg + i);
	}
}

int cut_apostrophe(int start_arg, char *line, int end)
{
	int i;

	i = 1;
	while(line[start_arg + i] != '\'')
	{
		if(start_arg + i > end)
			return (-1);
		i++;
	}
	i++;
	if(line[start_arg + i] == '\0' || line[start_arg + i] == ' ' || line[start_arg + i] == '<' || line[start_arg + i] == '>' || start_arg + i > end) 
		return(start_arg + i);
	else
	{
		while(line[start_arg + i] != '\0' && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>' && start_arg + i < end)
		{
			if(line[start_arg + i] == '\'' && valid_option(line, start_arg + i) == 1)
				return(cut_apostrophe(start_arg + i, line, end)); 
			i++;
		}
		return(start_arg + i);
	}
}

int cut_outher(int start_arg, char *line, int end, int *i)
{
	while (start_arg + *i < end)
	{
		if((line[start_arg + *i] == '>' || line[start_arg + *i] == '<') && valid_option(line, start_arg + *i) == 1)
			return(0);
		else if((line[start_arg + *i] == '\"' || line[start_arg + *i] == '\'') && valid_option(line, start_arg + *i) == 1)
			return(1);
		else if(line[start_arg + *i] == ' ' && valid_option(line, start_arg + *i) == 1)
			return(0);
		*i = *i + 1;
	}
	return(0);
}

int get_end_arg(int start_arg, char *line ,int end)
{
	int i;
	int value;

	i = 0;
	t_params.vld_der = 0;
	while(start_arg + i < end)
	{
		while(line[start_arg + i] == ' ' && start_arg + i < end)
			i++;
		if(valid_option(line, start_arg + i) == 1 && (line[start_arg + i] == '>' || line[start_arg + i] == '<'))
			return(greater_less(start_arg + i, line));
		else if(valid_option(line, start_arg + i) == 1 && line[start_arg + i] == '\"')
			return(cut_quotation(start_arg +i ,line, end));
		else if(line[start_arg + i] == '\'')
			return(cut_apostrophe(start_arg +i ,line, end));
		else
		{
			if(cut_outher(start_arg + i, line, end, &i) == 0)
				break;
			continue;
		}
	}
	return(start_arg + i);
}

int get_number_args(t_gargs **gargs)
{
	t_gargs *ptr_list_shell;
	int x;

	x = 0;
	ptr_list_shell = *gargs;
	if (ptr_list_shell == NULL)
		return(0);
	else
	{
		while (ptr_list_shell != NULL)
		{
			ptr_list_shell = ptr_list_shell->next;
			x++;
		}
	}
	return(x);
}

int gestion_args(char *line, int start, int end, t_gargs **gargs)
{
	int i;
	int start_arg;
	int end_arg;

	i = 0;
	while(start + i < end && i >= 0)
	{
		while(line[start + i] == ' ')
			i++;
		if(start + i >= end)
			break;
		start_arg = start + i;
		end_arg = get_end_arg(start_arg, line , end);
		if(end_arg == -1)
			return(-1);
		ft_lstadd_back_arg(gargs, ft_lstnew_args(start_arg, end_arg, t_params.vld_der));
		i += (end_arg - start_arg) == 0 ? 1 : end_arg - start_arg;
	}
	return(get_number_args(gargs));
}

int is_nbr_car(char c)
{
	int i;
	if((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) )
		return 1;
	return(0);
}

char *get_env(char *s)
{
	t_env *env;

	env = NULL;
	ft_setenv(&env, t_params.env);
	return (getenval(env,s));
}

char *check_path(char *s)
{
	int i;
	int x;
	int j;
	t_cargs *args;
	t_cargs *ptr_list_shell;
	char *temp;
	char *temp2;
	char *ptr;

	i = 0;
	x = 0;
	j = 0;
	args = NULL;
	while(s[i])
	{
		if(s[i] == '\'' || s[i] == '\"' || s[i] == '\\')
		{
			if(s[i] == '\'')
			{
				i++;
				while(s[i] != '\0' && s[i] != '\'')
				{
					ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
					i++;
				}
			}
			else if(s[i] == '\\')
			{
				i++;
				ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
			}
			else if(s[i] == '\"')
			{
				i++;
				while(s[i] != '\0')
				{
					if(s[i] == '\\')
					{
						if(s[i + 1] == '\\' || s[i + 1] == '\"')
							ft_lstcargsadd_back(&args, ft_lstcargsnew(s[++i]));
						else if(s[i + 1] != '$')
							ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
					}
					else if(s[i] == '\"')
					{
						break;
					}
					else if(s[i] == '$')
					{
						//----------------
						if(valid_option(s, i) == 1)
						{
							x = 1;
							while(is_nbr_car(s[i + x]) == 1)
							{
								j++;
								x++;
							}
							if(temp != NULL)
								free(temp);
							temp = ft_substr(s, i + 1, j);
							if(s[i + 1] == '?')
							{
								x = -1;
								if(temp != NULL)
									free(temp);
								temp = ft_itoa(t_params.question_nbr);
								while(temp[++x] != '\0')
									ft_lstcargsadd_back(&args, ft_lstcargsnew(temp[x]));
							}
							temp2 = temp;
							temp = get_env(temp);
							if(temp2 != NULL)
								free(temp2);
							x = 0;
							while(temp != NULL && temp[x] != '\0')
								ft_lstcargsadd_back(&args, ft_lstcargsnew(temp[x++]));
							if(temp == NULL && (s[i + 1] == ' ' || s[i + 1] == '\0'))
							{
								ft_lstcargsadd_back(&args, ft_lstcargsnew('$'));
							}
							else if(ft_isnumber(s[i + 1]) == 1 || s[i + 1] == '?')
								i +=1;
							else
								i += j;
						}
						else
							ft_lstcargsadd_back(&args, ft_lstcargsnew('$'));
						//----------------------
					}
					else
						ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
					i++;
				}
			}
		}
		else if(s[i] == '$')
		{
			//----------------
			if(valid_option(s, i) == 1)
			{
				x = 1;
				while(is_nbr_car(s[i + x]) == 1)
				{
					j++;
					x++;
				}
				if(temp != NULL)
					free(temp);
				temp = ft_substr(s, i + 1, j);
				if(s[i + 1] == '?')
				{
					x = -1;
					if(temp != NULL)
						free(temp);
					temp = ft_itoa(t_params.question_nbr);
					while(temp[++x] != '\0')
						ft_lstcargsadd_back(&args, ft_lstcargsnew(temp[x]));
				}
				temp2 = temp;
				temp = get_env(temp);
				if(temp2 != NULL)
					free(temp2);
				x = 0;
				while(temp != NULL && temp[x] != '\0')
					ft_lstcargsadd_back(&args, ft_lstcargsnew(temp[x++]));
				if(temp == NULL && (s[i + 1] == ' ' || s[i + 1] == '\0'))
				{
					ft_lstcargsadd_back(&args, ft_lstcargsnew('$'));
				}
				else if(ft_isnumber(s[i + 1]) == 1 || s[i + 1] == '?')
					i +=1;
				else
					i += j;
			}
			else
				ft_lstcargsadd_back(&args, ft_lstcargsnew('$'));
			//----------------------
		}
		else
			ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
		i++;
	}
	if(temp != NULL)
		free(temp);
	i = 0;
	ptr_list_shell = args;
	ptr = malloc(sizeof(char) * get_len_list(ptr_list_shell) + 1);
	while (ptr_list_shell != NULL)
	{
		ptr[i++] = ptr_list_shell->c;
		ptr_list_shell = ptr_list_shell->next;
	}
	ptr[i] = '\0';
	while (args != NULL)
	{
		ptr_list_shell = args;
        args = args->next;
        free(ptr_list_shell);
	}
	return(ptr);
}

char *fill_arg(int len, int start, char *line, int vld_der)
{
	char *s;
	char *temp;
	int i;
	int j;
	
	i = 0;
	j = 0;
	len = len == 0 ? 1 : len;
	len = (vld_der == 1) ? len + 1 : len;
	s = (char *)malloc(sizeof(char ) * len + 1);
	if(vld_der == 1)
	{
		s[j++] = '@'; 
		len--;
	}
	while(len > i)
	{
		s[j] = line[start + i];
		j++;
		i++;
	}
	s[j] = '\0';
	temp = s;
	s = check_path(s);
	free(temp);
	return(s);
}

void change_position(t_gargs **gargs, int i)
{
	int x;
	t_gargs *ptr_list_shell;

	ptr_list_shell = *gargs;
	x = 0;
	while(x < i)
	{
		ptr_list_shell = ptr_list_shell->next;
		x++;
	}
	echonge_list_args(&ptr_list_shell);
}

void check_more(t_gargs *gargs, char *line, int len, int norm)
{
	int i;
	int j;
	t_gargs *ptr_list_shell;

	ptr_list_shell = gargs;
	i = 0;
	//free_table_args();
	gestion_fill_arg(gargs, line, len);
	j = number_of_words_in_table(t_params.args);
	if(norm == 1)
	{
		j = j -2;
		echonge_list_args(&ptr_list_shell);
		free_table_args();
		gestion_fill_arg(gargs, line, len);
	}
	while(i < j)
	{
		if(strcmp(t_params.args[i], "@>") == 0)
		{
			change_position(&ptr_list_shell, i);
			free_table_args();
			gestion_fill_arg(gargs, line, len);
			j = j - 2;
			i = 0;
		}
		i++;
	}
}

void free_table_args()
{
	int i;

	i = 0;
	if(t_params.args != NULL)
	{
		while (t_params.args[i] != NULL)
			free(t_params.args[i++]);
		free(t_params.args);
	}
}

void gestion_fill_arg(t_gargs *gargs, char *line, int len)
{
	t_gargs *ptr_list_shell;
	int i;

	i = 0;
	ptr_list_shell = gargs;
	t_params.args = (char **)malloc(sizeof (char *) * len + 1);
	while (ptr_list_shell != NULL)
	{
		len = ptr_list_shell->end - ptr_list_shell->start;
		t_params.args[i] = (char *)fill_arg(len, ptr_list_shell->start, line, ptr_list_shell->vld_der);
		ptr_list_shell = ptr_list_shell->next;
		i++;
	}
	t_params.args[i] = NULL;
}

int get_args(char *line, int start, int end, int norm)
{
	int i;
	int len;
	t_gargs *gargs;
	t_gargs *ptr_list_shell;
	
	gargs = NULL;
	i  = 0;
	len = gestion_args(line, start, end, &gargs);
	if(len == -1)
		return(-1);
	check_more(gargs, line, len, norm);
	while (gargs != NULL)
	{
		ptr_list_shell = gargs;
		gargs = gargs->next;
		free(ptr_list_shell);
	}
	return(1);
}

int get_param_list_shell(t_inputs **list_shell, char *line, int start, int end)
{
	int i;

	i = 0;
	while(line[start + i] == ' ')
		i++;
	if(line[start + i] != '>' && line[start + i] != '<')
	{
		if(get_args(line, start, end, 0) == -1)
			return(-1);
	}
	else
		if(get_args(line, start, end, 1) == -1)
			return(-1);
	return(1);
}


int valid_quotation(char *line , int start, int open)
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
	valid = (j % 2 == 0 )? 1: 0;
	if((valid && !open) || (!valid && open))
		return(1);
	return(0);
}

int get_start_and_end_events(char *line, t_inputs **list_shell)
{
	int	i;
	int	start;
	int end;
	int open;
	int pipe;

	i = -1;
	start = 0;
	open = 0;
	while(++i <= strlen(line))
	{
		if(line[i] == '\"' || line[i] == '\'')
		{
			open = valid_quotation(line, i, open);
			if(line[i] == '\"' && open == 1)
			{
				i++;
				open = 0;
				while(1)
				{
					if(line[i] == '\"' && valid_option(line, i) == 1)
					{
						open = 0;
						break;
					}
					if (line[i] == '\0')
					{
						t_params.error_text = "Empty line there is no supplement \"\n";
						return(-1);
					}
					i++;
				}
			}
			else if(line[i] == '\'' && open == 1)
			{
				i++;
				while(line[i] != '\'' && line[i] != '\0')
					i++;
				open = 0;
			}
		}
		if ((line[i] == ';' || line[i] == '|' || line[i] == '\0') && open == 0)
		{
			if(line[i] == '\0' && ((line[i - 1] == '>' || line[i - 1] == '<') && valid_option(line, i - 1) == 1))
			{
				t_params.error_text = "bash: syntax Error 1 \n";
				return(-1);
			}	
			pipe = (line[i] == '|') ? 1 : 0;
			end = i;
			if(get_param_list_shell(list_shell, line, start, end) == -1)
				return(-1);
			ft_lstadd_back(list_shell, ft_lstnew(t_params.args,pipe));
			if(line[i] == ';' && line[i + 1] == '\0')
				break;
			start = end +1;
		}
	}
	return(1);
}

int lsh_split_line(char *line, t_inputs **list_shell)
{
	if(get_start_and_end_events(line, list_shell) == -1)
			return (-1);
	return(1);
}

int get_end_index(char *line, int i)
{
	if(line[i] == '\"')
	{
		i++;
		while(1 && line[i] != '\0')
		{
			if(line[i] == '\"' && valid_option(line, i) == 1)
				return(i);
			i++;
		}
		if(line[i] == '\0')
			t_params.error_text = "There is no supplement \"\n";
	}
	else if(line[i] == '\'')
	{
		i++;
		while(1 && line[i] != '\0')
		{
			if(line[i] == '\'')
				return(i);
			i++;
		}
		if(line[i] == '\0')
			t_params.error_text = "There is no supplement \'\n";
	}
	return(-1);
}

int error_msg()
{
	t_params.error_text = "bash: syntax Error 2\n";
	return(-1);
}

int pass_spe(char *line, int i)
{
	while(line[i] == ' ')
	{
		if(line[i] == '\0')
			break;
		i++;
	}
	return(i);
}


int check_syntax(char *line)
{
	int i;
	
	i = 0;
	while(line[i] != '\0')
	{
		if(line[0] == ';' || line[0] == '|')
			return(error_msg());
		if((line[i] == '\'' || line[i] == '\"') && valid_option(line, i) == 1)
		{
			i = get_end_index(line, i);
		}
		if(i == -1)
			return(-1);
		if((line[i] == '|' || line[i] == ';') && valid_option(line, i) == 1)
		{
			i = pass_spe(line, i + 1);
			if(line[i] == '|' || line[i] == ';')
				return(error_msg());
			i--;
		}
		else if((line[i] == '>' && line[i + 1] == '>') && valid_option(line, i) == 1)
		{
			i = pass_spe(line, i + 2);
			if(line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
				return(error_msg());
			i--;
		}
		else if((line[i] == '<' && line[i + 1] == '<') && valid_option(line, i) == 1)
		{
			i = pass_spe(line, i + 2);
			if(line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
				return(error_msg());
			i--;
		}
		else if (line[i] == '>' && valid_option(line, i) == 1)
		{
			if(i + 1 == pass_spe(line, i + 1))
			{
				if(line[i + 1] == '|' || line[i + 1] == ';' || line[i + 1] == '<')
					return(error_msg());
			}
			else
			{
				i = pass_spe(line, i + 1);
				if(line[i] == '|' || line[i] == ';' || line[i] == '<' || line[i] == '>')
					return(error_msg());
				i--;
			}
				
		}
		else if (line[i] == '<' && valid_option(line, i) == 1)
		{
			if(i + 1 == pass_spe(line, i + 1))
			{
				if(line[i + 1] == '|' || line[i + 1] == ';' || line[i + 1] == '>')
					return(error_msg());
			}
			else
			{
				i = pass_spe(line, i + 1);
				if(line[i] == '|' || line[i] == ';' || line[i] == '<' || line[i] == '>')
					return(error_msg());
				i--;
			}
		}
		else if (line[i] == '\\' && valid_option(line, i) == 1 && line[i + 1] == '\0')
			return(error_msg());
		i++;
	}
	return(1);
}

void test_print(t_inputs *list_shell)
{
	int i;
	int j;
	t_inputs *ptr_list_shell;
	
	j = 0;
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		printf("--------------------------\n");
		j = 0;
		while(ptr_list_shell->command[j] != NULL)
		{
			printf("command : |%s|\n",ptr_list_shell->command[j]);
			j++;
		}
		printf("pipe : %d\n",ptr_list_shell->pipe);
		printf("--------------------------\n");
		ptr_list_shell = ptr_list_shell->next;
	}
	printf("\n\n\n");
	free_table_args();
	ptr_list_shell = list_shell;
	while (list_shell != NULL)
	{
		ptr_list_shell = list_shell;
		list_shell = list_shell->next;
		free(ptr_list_shell);
	}
}

int check_syntax_list(t_inputs *list_shell)
{
	int i;
	int pipe;
	t_inputs *ptr_list_shell;
	
	i = 0;
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		pipe = ptr_list_shell->pipe;
		if(pipe == 1 && ptr_list_shell->command[0] == NULL)
			return(-1);
		ptr_list_shell = ptr_list_shell->next;
		if(ptr_list_shell != NULL && pipe == 1 && ptr_list_shell->command[0] == NULL)
			return(-1);
	}
	return(1);
}

void lsh_loop(void)
{
	char *line;
	t_inputs *list_shell;
	int errors;
	
	list_shell = NULL;
	while (1)
	{
		errors = 0;
		write_string("bash-1.0$ ");
		lsh_read_line_and_trim(&line);
		if(line[0] != '\0')
		{
			if(check_syntax(line) != -1)
				errors = lsh_split_line(line, &list_shell);
			else
			{
				write_string(t_params.error_text);
				continue;
			}
			if (errors == -1)
				write_string(t_params.error_text);
			else
			{
				if(check_syntax_list(list_shell) != -1)
					test_print(list_shell);
				else
					write_string("bash: syntax Error 3\n");
				list_shell = NULL;
			}
		}
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{

	t_params.env = envp;
	t_params.question_nbr = 45;
	lsh_loop();
	return 0;
}
