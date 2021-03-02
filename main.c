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
    inpt6->command[0] = ft_strdup("cat");
    // inpt6->command[1] = ft_strdup("KO");
    inpt6->command[1] = NULL;
    inpt6->pipe = 1;
    inpt6->next = NULL;

    inpt5  = malloc(sizeof(*inpt5));
    inpt5->command = malloc(3 * sizeof(char *));
    inpt5->command[0] = ft_strdup("env");
    inpt5->command[1] = ft_strdup(" >");
    inpt5->command[2] = ft_strdup("KO");
    inpt5->command[3] = NULL;
    inpt5->command[1][0] = 27;
    inpt5->pipe = 0;
    inpt5->next = inpt6;

    inpt4  = malloc(sizeof(*inpt4));
    inpt4->command = malloc(3 * sizeof(char *));
    inpt4->command[0] = ft_strdup("echo");
    inpt4->command[1] = ft_strdup("Start");
    inpt4->command[2] = NULL;
    inpt4->pipe = 0;
    inpt4->next = inpt5;

    inpt3  = malloc(sizeof(*inpt3));
    inpt3->command = malloc(3 * sizeof(char *));
    inpt3->command[0] = ft_strdup("echo");
    inpt3->command[1] = ft_strdup("Start");
    inpt3->command[2] = NULL;
    inpt3->pipe = 1;
    inpt3->next = inpt4;

    inpt2  = malloc(sizeof(*inpt2));
    inpt2->command = malloc(3 * sizeof(char *));
    inpt2->command[0] = ft_strdup("echo");
    inpt2->command[1] = ft_strdup("Start");
    inpt2->command[2] = NULL;
    inpt2->pipe = 0;
    inpt2->next = inpt3;

    inpt1  = malloc(sizeof(*inpt1));
    inpt1->command = malloc(3 * sizeof(char *));
    inpt1->command[0] = ft_strdup("echo");
    inpt1->command[1] = ft_strdup("Start");
    inpt1->command[2] = NULL;
    inpt1->pipe = 0;
    inpt1->next = inpt2;
    
    
    inpt  = malloc(sizeof(*inpt));
    inpt->command = malloc(3 * sizeof(char *));
    inpt->command[0] = ft_strdup("echo");
    inpt->command[1] = ft_strdup("Start");
    inpt->command[2] = NULL;
    inpt->pipe = 0;
    inpt->next = inpt1;

    // int fds[2];
    // int fds2 = -1;
    // int i = -1;
    // int id;
    // int id2;
    // pipe(fds);
    // while (++i < 2)
    // {
    //     id = fork();
    //     if (id == 0)
    //     {
    //         if (fds2 == -1)
    //         {
    //             close(fds[0]);
    //             dup2(fds[1], STDOUT_FILENO);
    //             // write(fds[1], "IKHSS", 5);
    //             close(fds[1]);
    //         }
    //         else
    //         {
    //             char *buff;
    //             buff = malloc(11);
    //             buff[10] = '\0';
    //             dup2(fds2, STDIN_FILENO);
    //             // read(STDIN_FILENO, buff, 11);
    //             // printf(">> |%s|\n", buff);
    //             id2 =  fork();
    //             if (id2 == 0)
    //             {
    //                 printf("inpt3->command[0]  : %s", inpt3->command[0]);
    //                 execve(inpt3->command[0], NULL, t_g.envp);
    //                 exit(0);
    //             }
    //             close(fds2);
    //         }
    //         exit(0);
    //     }
    //     else
    //     {
    //         wait(NULL);
    //         if (fds2 == -1)
    //             fds2 = dup(fds[0]);
    //         else
    //             close(fds2);
    //         close(fds[0]);
    //         close(fds[1]);
    //     }
    // }

    ft_execute(&envlst, inpt);
}