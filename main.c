#include "minishell.h"

void handel_c()
{
    printf("ctrl + c\n");
}
void handel_d()
{
    printf("ctrl + d\n");
}
void handel_b()
{
    printf("ctrl + \\\n");
}

int main(int argc, char **argv, char **envp)
{
    argv = NULL;
    argc = 0;
    signal(SIGINT, handel_c);
    t_env *envlst;
    envlst = NULL;
    t_g.envp = envp;
    ft_setenv(&envlst, envp);

    t_inputs    *inpt;
    t_inputs    *inpt1;
    t_inputs    *inpt2;
    t_inputs    *inpt3;
    t_inputs    *inpt4;
    t_inputs    *inpt5;
    t_inputs    *inpt6;
    t_inputs    *inpt7;


    inpt7  = malloc(sizeof(*inpt7));
    inpt7->command = malloc(2 * sizeof(char *));
    inpt7->command[0] = ft_strdup("cat");
    // inpt7->command[1] = ft_strdup("Start");
    inpt7->command[1] = NULL;
    inpt7->pipe = 0;
    inpt7->next = NULL;

    inpt6  = malloc(sizeof(*inpt6));
    inpt6->command = malloc(2 * sizeof(char *));
    inpt6->command[0] = ft_strdup("sort");
    inpt6->command[1] = NULL;
    inpt6->pipe = 0;
    inpt6->next = NULL;

    inpt5  = malloc(sizeof(*inpt5));
    inpt5->command = malloc(2 * sizeof(char *));
    inpt5->command[0] = ft_strdup("ls");
    inpt5->command[1] = NULL;
    inpt5->pipe = 1;
    inpt5->next = inpt7;

    inpt4  = malloc(sizeof(*inpt4));
    inpt4->command = malloc(5 * sizeof(char *));
    inpt4->command[0] = ft_strdup("echo");
    inpt4->command[1] = ft_strdup("-nnn");
    inpt4->command[2] = ft_strdup("env");
    inpt4->command[3] = ft_strdup("env");
    // inpt4->command[1] = ft_strdup("Print5");
    inpt4->command[4] = NULL;
    inpt4->pipe = 0;
    inpt4->next = NULL;

    inpt3  = malloc(sizeof(*inpt3));
    inpt3->command = malloc(3 * sizeof(char *));
    inpt3->command[0] = ft_strdup("echo");
    inpt3->command[1] = ft_strdup("$?");
    inpt3->command[2] = NULL;
    inpt3->command[1][0] = 24;
    inpt3->pipe = 0;
    inpt3->next = NULL;

    inpt2  = malloc(sizeof(*inpt2));
    inpt2->command = malloc(5 * sizeof(char *));
    inpt2->command[0] = ft_strdup("./rr");
    inpt2->command[1] = NULL;
    inpt2->pipe = 0;
    inpt2->next = inpt3;

    inpt1  = malloc(sizeof(*inpt1));
    inpt1->command = malloc(4 * sizeof(char *));
    inpt1->command[0] = ft_strdup("chmod");
    inpt1->command[1] = ft_strdup("000");
    inpt1->command[2] = ft_strdup("rr");
    // inpt1->command[2] = ft_strdup("NUM");
    inpt1->command[3] = NULL;
    inpt1->pipe = 0;
    inpt1->next = inpt2;
    
    
    inpt  = malloc(sizeof(*inpt));
    inpt->command = malloc(4 * sizeof(char *));
    inpt->command[0] = ft_strdup("echo");
    inpt->command[1] = ft_strdup(">");
    inpt->command[2] = ft_strdup("rr");
    inpt->command[3] = NULL;
    inpt->command[1][0] = 14;
    inpt->pipe = 0;
    inpt->next = inpt1;

    ft_execute(&envlst, inpt);
}