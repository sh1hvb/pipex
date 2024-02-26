#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include<sys/wait.h>

char *get_pathi(char *env[] );char *check_cmd(char **splited , char *av);void exec(char *av , char **env , int fd);

void child_process(int *fds, char *av[], char *env[]) {
    int fd;

    if (!fds) {
        perror("not valid!");
        exit(1); 
    }

    if (dup2(fds[0], 0) == -1) {
        perror("dup2 child");
        close(fds[0]);
        exit(1); 
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("open child");
        close(fds[0]);
        exit(1);
    }

    if (dup2(fd, 1) == -1) {
        perror("dup2 child");
        close(fd);
        exit(1);
    }

    exec(av[3], env, fds[0]); 
    perror("execve"); 
    exit(2); 
}

void parent_process(int *fds, char *av[], char *env[]) {
    int fd;

    if (!fds) {
        perror("not valid!");
        exit(1);
    }
    fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open parent");
        close(fds[1]);
        exit(1);
    }
    if (dup2(fd, 0) == -1) {
        perror("dup2 parent 0");
        close(fds[1]);
        exit(1);
    }
    if (dup2(fds[1], 1) == -1) {
        perror("dup2 parent 1");
        close(fd);
        exit(1);
    }
    printf("hhh par\n");

    exec(av[2], env, fds[0]); 
    perror("execve");
    exit(2);
}

void exec(char *av, char **env, int fd) {
    if (!av || !env) {
        perror("not valid!");
        exit(1);
    }

    printf("hhhh\n");
    char *path = ft_substr(get_pathi(env), 5, 50);
    char **splited = ft_split(path, ':');
    char **cmd = ft_split(av, ' ');

    char *cmd1 = check_cmd(splited, cmd[0]);
    printf("%scmd :\n", cmd1);

    if (cmd1) {
        if (execve(cmd1, cmd, env) == -1) {
            perror("execve");
            exit(2);
        }
    } else {

        fprintf(stderr, "Error: command '%s' not found\n", cmd[0]);
        exit(1);
    }

    free(path); 
    // ft_free(splited); 
    // ft_free(cmd);
}

int main(int ac, char *av[], char *env[]) {
    int fds[2];
    int pid;
	char **p =ft_split(get_pathi(env) , ' ');
	char **k =ft_split(av[2], ' ');
printf("%s\n", check_cmd(env,k[0]));
    if (ac < 5) {
        exit(1);
    }

    if (pipe(fds) == -1) {
        perror("pipe:");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

	if(!pid)
		child_process(fds ,av, env);
	else
		parent_process(fds , av , env);
		wait(NULL);
}

char *check_cmd(char **splited, char *av) {
    int i = 0;
    while (splited[i]) {
        char *cmd_path = ft_strjoin(ft_strjoin(splited[i], "/"), av);
            if (access(cmd_path, X_OK) == 0) {
            return cmd_path;
        }
        free(cmd_path);
        
        i++;
    }
    return NULL;
}

char *get_pathi(char *env[]) {
    int i = 0;
    char *path_string = NULL;
    while (env[i]) {
        if (ft_strnstr(env[i], "PATH=", 5)) {
            path_string = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
            break;
        }
        i++;
    }
    return path_string;
}