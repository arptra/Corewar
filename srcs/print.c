#include "../incl/parse.h"

void		players_intro(t_vm *vm)
{
	t_file_info *players;

	players = vm->players;
	ft_putstr("Introducing contestants...\n");
	while (players)
	{
		ft_putstr("* Player ");
		ft_putnbr(players->cnum);
		ft_putstr(", weighing ");
		ft_putnbr(players->cs);
		ft_putstr(" bytes, ");
		ft_putchar('"');
		ft_putstr(players->cn);
		ft_putchar('"');
		ft_putstr(" (");
		ft_putchar('"');
		ft_putstr(players->cc);
		ft_putchar('"');
		ft_putstr(") !\n");
		players = players->next;
	}
}