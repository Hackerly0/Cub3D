/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:23:06 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/18 11:10:38 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**grep_print(char **qa, t_cub *cub)
{
	qa = grab_questions();
	draw_centered_text(cub, qa);
	return (qa);
}

void	print_statment_win(void)
{
	printf("\n");
	printf("\033[1;32m");
	printf("██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗\n");
	printf("╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║\n");
	printf(" ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║\n");
	printf("  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║\n");
	printf("   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║\n");
	printf("   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝\n");
	printf("\033[0m\n");
	printf("\033[1;37m\033[1;34m===>>  CONGRATULATIONS!");
	printf("YOU'VE ESCAPED THE MAZE!  <<===\033[0m\n\n");
	printf("\033[1;36m");
	printf("You've answered all questions correctly and found your way out.\n");
	printf("               Well done, brave adventurer!\033[0m\n");
}

void	print_statment(void)
{
	printf("\n\033[1;31m");
	printf("██████╗  \033[1;33m ██████╗  \033[1;32m ██████╗  ");
	printf("\033[1;36m██████╗\n");
	printf("\033[1;31m██╔══██╗ \033[1;33m██╔═══██╗ \033[1;32m██╔═══██╗ ");
	printf("\033[1;36m██╔══██╗\n");
	printf("\033[1;31m██║  ██║ \033[1;33m██║   ██║ \033[1;32m██║   ██║ ");
	printf("\033[1;36m██████╔╝\n");
	printf("\033[1;31m██║  ██║ \033[1;33m██║   ██║ \033[1;32m██║   ██║ ");
	printf("\033[1;36m██╔══██╗\n");
	printf("\033[1;31m██████╔╝ \033[1;33m╚██████╔╝ \033[1;32m╚██████╔╝ ");
	printf("\033[1;36m██║  ██║\n");
	printf("\033[1;31m╚═════╝  \033[1;33m ╚═════╝  \033[1;32m ╚═════╝  ");
	printf("\033[1;36m╚═╝  ╚═╝\033[0m\n\n");
	printf("\033[1;34m===>>  WELCOME TO THE BRAIN CHALLENGE!  <<===\033[0m");
	printf("\n\n\033[1;36mEach door hides a question, ");
	printf("each answer opens a path.\n");
	printf("      Think fast... are you ready to start?\033[0m\n");
}

void	print_statment_lose(void)
{
	printf("\n\n");
	printf("\033[0;31m██╗      ██████╗ ███████╗███████╗██████╗ \033[0m\n");
	printf("\033[0;31m██║     ██╔═══██╗██╔════╝██╔════╝██╔══██╗\033[0m\n");
	printf("\033[0;31m██║     ██║   ██║███████╗█████╗  ██████╔╝\033[0m\n");
	printf("\033[0;31m██║     ██║   ██║╚════██║██╔══╝  ██╔══██╗\033[0m\n");
	printf("\033[0;31m███████╗╚██████╔╝███████║███████╗██║  ██║\033[0m\n");
	printf("\033[0;31m╚══════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝\033[0m\n");
}
