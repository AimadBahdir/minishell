#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    argv = NULL;
    argc = 0;
    char **command = malloc(7 * sizeof(char *));
    command[0] = ft_strdup("export");
    command[1] = ft_strdup("KEY1=VAL1");
    command[2] = ft_strdup("KE*Y2=VAL2");
    command[3] = ft_strdup("KEY3=VAL3");
    command[4] = ft_strdup("KEY4=VAL4");
    command[5] = ft_strdup("KEY5=VAL5");
    command[6] = NULL;

    // int pid = fork();
    // if (pid == 0) {
    //     // Child Process
    //     // execve(command[0], command, envp);
    //     // printf("ERR: %s", strerror(errno));
    // } else {
    //     //Main Process
    //     wait(NULL);
    // }
    t_env *envlst;
    envlst = NULL;
    ft_setenv(&envlst, envp);
    ft_execmd(&envlst, command);
    command[0] = ft_strdup("env");
    ft_execmd(&envlst, command);
    command[0] = ft_strdup("unset");
    command[1] = ft_strdup("KEY1");
    command[2] = ft_strdup("KE*Y2");
    command[3] = ft_strdup("KEY3");
    command[4] = ft_strdup("KEY4");
    command[5] = ft_strdup("KEY5");
    command[6] = NULL;
    ft_execmd(&envlst, command);
    command[0] = ft_strdup("env");
    ft_execmd(&envlst, command);
    // while (envlst)
    // {
    //     printf("{ %s : %s }\n", envlst->key, envlst->val);
    //     envlst = envlst->next;
    // }
}