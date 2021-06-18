/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:24:54 by oidrissi          #+#    #+#             */
/*   Updated: 2021/06/18 07:13:55 by oidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_stack			g_to_print = {{0}, 1 << 7, 0, 0};

void	activebit(int sig, siginfo_t *content, void *unuseful)
{
	(void)sig;
	(void)unuseful;
	(void)content;
	if (!g_to_print.bit)
	{
		g_to_print.bit = 1 << 7;
		++(g_to_print.byte);
	}
	g_to_print.msg[g_to_print.byte] += g_to_print.bit;
	g_to_print.bit >>= 1;
}

void	nullbit(int sig, siginfo_t *content, void *unuseful)
{
	(void)sig;
	(void)unuseful;
	if (!g_to_print.bit)
	{
		g_to_print.bit = 1 << 7;
		++(g_to_print.byte);
	}
	g_to_print.bit >>= 1;
	if (!g_to_print.msg[g_to_print.byte] && !g_to_print.bit)
	{
		g_to_print.received = 1;
		kill(content->si_pid, SIGUSR1);
	}
}

int	handler(void)
{
	while (1)
	{
		pause();
		if (g_to_print.received)
		{
			write(1, g_to_print.msg, ft_strlen(g_to_print.msg));
			ft_bzero(g_to_print.msg, SIZE);
			g_to_print.byte = 0;
			g_to_print.bit = 1 << 7;
			if (g_to_print.received)
				write(1, "\n", 1);
			g_to_print.received = 0;
			write(1, "DATA WAS RECEIVED\n", 18);
		}
	}
	return (1);
}

/*  The sigaction() system call is used to change the action taken by
	**							a process on receipt of a specific signal.
	** sigaction (SIGNUM, action, old_action)
	**	The sigaction structure is defined as something like:
    **     struct sigaction {
	**		void     (*sa_handler)(int);
	**		void     (*sa_sigaction)(int, siginfo_t *, void *);
    **		sigset_t   sa_mask;
    **		int        sa_flags;
    **		void     (*sa_restorer)(void);
    **      };
	** Printing the active bits will lead us to the null bit at the end,
	** signaling that we've iterated through all the characters
	** thus g_to_print.received = 1;
	** pause() causes the calling process (or thread) to sleep until a
    ** signal is delivered that either terminates the process or causes
	** the invocation of a signal-catching function.
*/

int	main(void)
{
	struct sigaction	active_bit_action;
	struct sigaction	null_bit_action;

	active_bit_action.sa_sigaction = activebit;
	null_bit_action.sa_sigaction = nullbit;
	active_bit_action.sa_flags = SA_ONSTACK;
	null_bit_action.sa_flags = SA_ONSTACK;
	if (sigaction(SIGUSR1, &active_bit_action, NULL) != 0)
		perror("signal error\n");
	if (sigaction(SIGUSR2, &null_bit_action, NULL) != 0)
		perror("signal error\n");
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	ft_bzero(g_to_print.msg, SIZE);
	handler();
}
