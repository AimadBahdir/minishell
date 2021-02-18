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
    t_env *envlst;
    envlst = NULL;
    ft_setenv(&envlst, envp);
    char **command = malloc(2 * sizeof(char *));
    command[0] = ft_strdup("export");
    command[1] = NULL;
    ft_execmd(&envlst, command);
    // command[2][0] = 27;
    // command[3][0] = 27;
    // command[5][0] = 27;
    // command[7][0] = 27;
    // command[9][0] = 27;
    // if (chk_directions(command))
    //     gdirections(&envlst, command);
    // else
    command[0] = ft_strdup("env");
    ft_execmd(&envlst, command);
}