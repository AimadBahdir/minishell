/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:26:39 by wben-sai          #+#    #+#             */
/*   Updated: 2021/01/29 11:07:37 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

int get_command(char *line, char **command, int start, int end)
{
	int i;
	int len;
	int j;

	i = start;
	len = 0;
	while(i < end && line[i++] != ' ')
		len++;
	*command = malloc(sizeof(char *) * len + 1);
	i = 0;
	j = start + i;
	while(i < len)
	{
		command[0][i] = line[j];
		j++;
		i++;
	}
	command[0][i] = '\0'; 
	return (len);
}

int get_end_arg(int start_arg, char *line ,int end)
{
	int i;

	i = 0;
	while(start_arg + i < end)
	{
		if(line[start_arg + i] == '>' && line[start_arg + i + 1] == '>' )
			return(start_arg + i + 2);
		else if(line[start_arg + i] == '>')
			return(start_arg + i);
		else if(line[start_arg + i] == '<')
			return(start_arg + i);
		else if(line[start_arg + i] == '\"')
		{
			i++;
			while(start_arg + i < end && line[start_arg + i] != '\"')
				i++;
			if(line[start_arg + i] == '\0' || line[start_arg + i] == ' ' || line[start_arg + i] == '<' || line[start_arg + i] == '>')
				return(start_arg + i);
			else
			{
				while(line[start_arg + i] != '\0' && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>')
					i++;
				return(start_arg + i);
			}
		}
		else if(line[start_arg + i] == '\'')
		{
			i++;
			while(start_arg + i < end && line[start_arg + i] != '\'')
				i++;
			if(line[start_arg + i] == '\0' || line[start_arg + i] == ' ' || line[start_arg + i] == '<' || line[start_arg + i] == '>')
				return(start_arg + i);
			else
			{
				while(line[start_arg + i] != '\0' && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>')
					i++;
				return(start_arg + i);
			}
		}
		else
		{
			while(start_arg + i < end && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>')
			{
				if(line[start_arg + i] == '\"')
				{
					i++;
					while(start_arg + i < end && line[start_arg + i] != '\"')
						i++;
					if(line[start_arg + i] == '\0' || line[start_arg + i] == ' ' || line[start_arg + i] == '<' || line[start_arg + i] == '>')
						return(start_arg + i);
					else
					{
						while(line[start_arg + i] != '\0' && line[start_arg + i] != ' ' && line[start_arg + i] != '<' && line[start_arg + i] != '>')
							i++;
						return(start_arg + i);
					}
				}
				i++;
			}
			return(start_arg + i);
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
	while(start + i < end)
	{
		while(line[start + i] == ' ')
			i++;
		if(start + i > end)
			break;
		start_arg = start + i;
		end_arg = get_end_arg(start_arg, line , end);
		ft_lstadd_back_arg(gargs, ft_lstnew_args(start_arg, end_arg));
		i += (end_arg - start_arg) == 0 ? 1 : end_arg - start_arg;
	}
	return(get_number_args(gargs));
}

char *fill_arg(int len, int start, char *line)
{
	char *s;
	int i;
	
	i = 0;
	len = len == 0 ? 1 : len;
	s = (char *)malloc(sizeof(char *) * len + 1);
	while(len > i)
	{
		s[i] = line[start + i];
		i++;
	}
	s[i] = '\0';
	return(s);
}

void get_args(char *line, int start, int end)
{
	int i;
	int len;
	t_gargs *gargs;
	t_gargs *ptr_list_shell;
	
	gargs = NULL;
	i  = 0;
	len = gestion_args(line, start, end, &gargs);
	t_params.args = (char **)malloc(sizeof (char *) * len + 1);
	ptr_list_shell = gargs;
	while (ptr_list_shell != NULL)
	{
		len = ptr_list_shell->end - ptr_list_shell->start;
		t_params.args[i] = (char *)fill_arg(len, ptr_list_shell->start, line);
		ptr_list_shell = ptr_list_shell->next;
		write_string("|");
		write_string(t_params.args[i]);
		write_string("|");
		write_string("\n");
		i++;
	}
	
}

void get_param_list_shell(t_inputs **list_shell, char *line, int start, int end)
{
	char *command;
	char *option;
	
	if(line[start] != '>' || line[start] != '<')
	{
		start += get_command(line, &command, start, end);
		//start += get_option();
		get_args(line, start, end);
		
	}
}

void get_start_and_end_events(char **words_line, char *line, t_inputs **list_shell)
{
	int	i;
	int	start;
	int end;

	i = -1;
	start = 0;
	while(++i <= strlen(line))
	{
		if (line[i] == ';' || line[i] == '|' || line[i] == '\0')
		{
			end = i;
			get_param_list_shell(list_shell, line, start, end);
			start = end +1;
		}
	}
}

void lsh_split_line(char *line, t_inputs **list_shell)
{
	char **words_line;
	
	words_line = ft_split(line, ' ');
	if (words_line && number_of_words_in_table(words_line) >= 2)
		get_start_and_end_events(words_line, line, list_shell);
	else if (number_of_words_in_table(words_line) == 1)
		ft_lstadd_back(list_shell, ft_lstnew(words_line[0], NULL, NULL, 0));
	else
		write_string("Empty line");
}

void lsh_loop(void)
{
	char *line;
	t_inputs *list_shell;
	
	list_shell = NULL;
	while (1)
	{
		write_string("Shell--> ");
		lsh_read_line_and_trim(&line);
		if(strcmp("exit", line) == 0)
			break;
		lsh_split_line(line, &list_shell);
		free(line);
	}
}

int main(int argc, char **argv)
{
  lsh_loop();
  
  return 0;
}