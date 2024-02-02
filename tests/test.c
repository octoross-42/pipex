/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:06:27 by octoross          #+#    #+#             */
/*   Updated: 2024/01/24 00:51:47 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(void)
{
    int fd[2];
    int status;

    // printf("fd1 = %d, fd2 = %d\n", fd[0], fd[1]);
    if(pipe(fd) == -1)
	{
        printf("\nError: Could not create a pipe!\n");
        exit(-1);
    }

    // printf("fd1 = %d, fd2 = %d\n", fd[0], fd[1]);
    int cpid = fork();

    if(cpid == -1)
	{
        printf("\nError: Could not fork!\n");
        exit(-1);
    }

    if(cpid == 0)
	{
		printf("cpid 1 = %d\n", cpid);
        char toSend[] = "Hello educative user! <3";
        write(fd[1], toSend, strlen(toSend));
        printf("Child: Data sent to parent!\n");
        exit(0);
    }
    else{
        waitpid(-1, NULL, WEXITED);
        // wait(NULL);
		printf("\ncpid 2 = %d in buffer size %d\n", cpid, BUFSIZ);
        char toRecieve[BUFSIZ];
        read(fd[0], toRecieve, BUFSIZ);
        printf("Parent: Data from child = %s\n\n", toRecieve);
        exit(0);
    }
}
