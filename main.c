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

    // int pid = fork();
    // if (pid == 0) {
    //     // Child Process
    //     // execve(command[0], command, envp);
    //     // printf("ERR: %s", strerror(errno));
    // } else {
    //     //Main Process
    //     wait(NULL);
    // }
    // t_env *envlst;
    // envlst = NULL;
    // ft_setenv(&envlst, envp);
    // char **command = malloc(8 * sizeof(char *));
    // puts("PWD : ");
    // command[0] = ft_strdup("export");
    // command[1] = ft_strdup("Hello=");
    // command[2] = ft_strdup("k1=080twog0-34091=");
    // command[3] = ft_strdup("k2=29058jokwt09568]q][erq\\asdfa123@$%^#*^()**&+_");
    // command[4] = ft_strdup("k3=@$%^#*^()**&+ _");
    // command[5] = ft_strdup("k4=@$%^#*^()**&+_");
    // command[6] = ft_strdup("k5=@$%^#*^()**&+_");
    // command[7] = NULL;
    // ft_execmd(&envlst, command);
    // command[0] = ft_strdup("env");
    // ft_execmd(&envlst, command);
    // command[0] = ft_strdup("unset");
    // command[1] = ft_strdup("Hello");
    // command[2] = ft_strdup("k1");
    // command[3] = ft_strdup("k2");
    // command[4] = ft_strdup("k3");
    // command[5] = ft_strdup("k4");
    // command[6] = ft_strdup("k5");
    // ft_execmd(&envlst, command); 
    // command[0] = ft_strdup("env");
    // ft_execmd(&envlst, command);
    // puts("\n cd :");
    // command[0] = ft_strdup("cd");
    // command[1] = ft_strdup("~/Desktop");
    // ft_execmd(&envlst, command);

    // command[0] = ft_strdup("echo");
    // command[1] = ft_strdup(getenval(envlst, "PWD"));
    // ft_execmd(&envlst, command);

     signal(SIGINT, handel_c);
    // signal(SIGINT, handel_d);
    // signal(SIGINT, handel_b);

    // while (1)
    // {
    //     printf("PROCESS ID : %d\n", getpid());
    //     sleep(1);
    // }
    
    // while (envlst)
    // {
    //     printf("{ %s : %s }\n", envlst->key, envlst->val);
    //     envlst = envlst->next;
    // }
    // t_env *envlst;
    // envlst = NULL;
    // g_envp = envp;
    // ft_setenv(&envlst, envp);
    // char **command = malloc(5 * sizeof(char *));
    // command[0] = ft_strdup("unset");
    // command[1] = ft_strdup("HOME");
    // command[2] = NULL;
    // ft_execmd(&envlst, command);
    // command[0] = ft_strdup("env");
    // ft_execmd(&envlst, command);
    // command[0] = ft_strdup("cd");
    // command[1] = ft_strdup("~/Desktop");
    // command[2] = ft_strdup(" >");
    // command[3] = ft_strdup("file1");
    // command[2][0] = 27;
    // command[4] = NULL;
    // gdirections(&envlst, command);
    // command[0] = ft_strdup("env");
    // ft_execmd(&envlst, command);
    // command[0] = ft_strdup("export");
    // command[1] = NULL;
    // command[2][0] = 27;
    // command[3][0] = 27;
    // command[5][0] = 27;
    // command[7][0] = 27;
    // command[9][0] = 27;
    // if (chk_directions(command))
    //     gdirections(&envlst, command);
    // else
    // ft_execmd(&envlst, command);
    // puts("\n");
    // command[0] = ft_strdup("env");
    // ft_execmd(&envlst, command);
    t_env *envlst;
    envlst = NULL;
    g_envp = envp;
    ft_setenv(&envlst, envp);

    t_inputs    *inpt;
    t_inputs    *inpt1;
    t_inputs    *inpt2;
    t_inputs    *inpt3;

    inpt3  = malloc(sizeof(*inpt3));
    inpt3->command = malloc(5 * sizeof(char *));
    inpt3->command[0] = ft_strdup("cat");
    inpt3->command[1] = ft_strdup("f1");
    inpt3->command[2] = ft_strdup("f2");
    inpt3->command[3] = ft_strdup("f3");
    inpt3->command[4] = NULL;
    inpt3->pipe = 0;
    inpt3->next = NULL;

    inpt2  = malloc(sizeof(*inpt2));
    inpt2->command = malloc(4 * sizeof(char *));
    inpt2->command[0] = ft_strdup("env");
    inpt2->command[1] = ft_strdup(" >");
    inpt2->command[2] = ft_strdup("f3");
    inpt2->command[3] = NULL;
    inpt2->command[1][0] = 27;
    inpt2->pipe = 0;
    inpt2->next = inpt3;

    inpt1  = malloc(sizeof(*inpt1));
    inpt1->command = malloc(3 * sizeof(char *));
    inpt1->command[0] = ft_strdup("echo");
    inpt1->command[1] = ft_strdup("Hi");
    inpt1->command[2] = NULL;
    inpt1->pipe = 1;
    inpt1->next = inpt2;

    inpt  = malloc(sizeof(*inpt));
    inpt->command = malloc(3 * sizeof(char *));
    inpt->command[0] = ft_strdup("echo");
    inpt->command[1] = ft_strdup("Start");
    // inpt->command[2][0] = 27;
    // inpt->command[4][0] = 27;
    inpt->command[2] = NULL;
    inpt->pipe = 1;
    inpt->next = inpt1;

    ft_execute(&envlst, inpt);
}