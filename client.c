/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 07:52:55 by oidrissi          #+#    #+#             */
/*   Updated: 2021/06/18 07:23:35 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* uint8_t is a 8bits integer = 1 byte
** left bitshifting through 128 decimal, representing all
** unicode chars 
**
** right bitshifting back, basically count/2^n where n
** takes 1, 2, 3 and so on...
** 1 char is 1 byte
*/

void	send_char(int pid, unsigned char byte)
{
	uint8_t	count;

	count = 1 << 7;
	while (count)
	{
		if (byte & count)
		{
			if (kill(pid, SIGUSR1) == -1)
				perror("bad pid\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				perror("bad pid\n");
		}
		count >>= 1;
		usleep(100);
	}
}

/* action takes the pid and the message, and sends characters to that pid */

void	action(char *str_pid, char *msg)
{
	int	pid;

	pid = atoi(str_pid);
	while (*msg)
	{
		send_char(pid, *msg);
		++msg;
	}
	send_char(pid, *msg);
}

void	sent(int sig)
{
	(void)sig;
	write(1, "Data successfully sent.\n", 24);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		signal(SIGUSR1, sent);
		action(argv[1], argv[2]);
	}
	else
	{
		write(1, "Try: ./client [server-pid] [msg]\n", 33);
		exit(0);
	}
	return (0);
}
