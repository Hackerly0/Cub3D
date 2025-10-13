/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 00:23:06 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/14 00:23:47 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_statment_win()
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
    printf("\033[1;37m    \033[1;34m===>>  CONGRATULATIONS! YOU'VE ESCAPED THE MAZE!  <<===\033[0m\n\n");
    printf("\033[1;36m");
    printf("        You've answered all questions correctly and found your way out.\n");
    printf("                 Well done, brave adventurer!\033[0m\n");
}

void print_statment()
{
    printf("\n");
    printf("\033[1;31m");
    printf("██████╗  \033[1;33m ██████╗  \033[1;32m ██████╗  \033[1;36m ██████╗\n");
    printf("\033[1;31m"); 
    printf("██╔══██╗ \033[1;33m██╔═══██╗ \033[1;32m██╔═══██╗ \033[1;36m██╔══██╗\n");
    printf("\033[1;31m");
    printf("██║  ██║ \033[1;33m██║   ██║ \033[1;32m██║   ██║ \033[1;36m██████╔╝\n");
    printf("\033[1;31m");
    printf("██║  ██║ \033[1;33m██║   ██║ \033[1;32m██║   ██║ \033[1;36m██╔══██╗\n");
    printf("\033[1;31m");
    printf("██████╔╝ \033[1;33m╚██████╔╝ \033[1;32m╚██████╔╝ \033[1;36m██║  ██║\n");
    printf("\033[1;31m");
    printf("╚═════╝  \033[1;33m ╚═════╝  \033[1;32m ╚═════╝  \033[1;36m╚═╝  ╚═╝\n");
    printf("\033[0m\n");
    printf("\033[1;37m    \033[1;34m===>>  WELCOME TO THE BRAIN CHALLENGE!  <<===\033[0m\n\n");
    printf("\033[1;36m");
    printf("            Each door hides a question, each answer opens a path.\n");
    printf("                   Think fast... are you ready to start?\033[0m\n");
}
