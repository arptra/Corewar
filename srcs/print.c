#include "../incl/parse.h"

void		players_intro(t_vm *vm)
{
	ft_putstr("Introducing contestants...\n");
	while (vm->players)
	{
		ft_putstr("* Player ");
		ft_putnbr(vm->players->cnum);
		ft_putstr(", weighing ");
		ft_putnbr(vm->players->cs);
		ft_putstr(" bytes, ");
		ft_putchar('"');
		ft_putstr(vm->players->cn);
		ft_putchar('"');
		ft_putstr(" (");
		ft_putchar('"');
		ft_putstr(vm->players->cc);
		ft_putchar('"');
		ft_putstr(") !\n");
		vm->players = vm->players->next;
	}
	return ;
}