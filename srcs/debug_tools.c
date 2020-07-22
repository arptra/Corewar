#include "../incl/parse.h"
#include "stdio.h"

void	print_vm(t_vm *vm)
{
	printf("cycles:%d\n",vm->cycle);
	printf("cycles_to_die:%d\n",vm->cycle_to_die);
	printf("cycles_after_check:%d\n",vm->cycle_left);
	printf("check_num:%d\n",vm->checks);
	printf("cursors_num:%d\n",vm->cars_num);
	printf("lives_num:%d\n",vm->lives);
}

void	print_cursor(t_vm *vm)
{
	t_carriage	*cur;
	int 		i;

	cur = vm->head;
	while (cur)
	{
		printf("cursor_id:%d\n",cur->num);
		printf("carry:%d\n", cur->carry);
		printf("last_live:%d\n",cur->last_live);
		printf("cycles_to_exec:%d\n",cur->cycle_to_exec + 1);
		printf("pc:%d\n",cur->pc);
		//printf("step:%d\n",cur->move);
		i = 0;
		while (i < 16)
		{
			printf("r_%d:%d\n", i, cur->registers[i]);
			i++;
		}
		i = 0;
		printf("a:");
		while (i < MEM_SIZE)
		{
			printf("%x ",vm->arena[i]);
			i++;
		}
		printf("\n");
		if (vm->debug - 1 == 0)
			printf("o:%x\n",cur->op_code);
		cur = cur->next;
	}
}

void	print_cur(t_vm *vm, int num)
{
	t_carriage *cur;
	int i;

	cur = vm->head;
	while (cur && cur->num != num)
		cur = cur->next;
	if (cur != NULL) {
		printf("cursor_id:%d\n", cur->num);
		printf("carry:%d\n", cur->carry);
		printf("last_live:%d\n", cur->last_live);
		printf("cycles_to_exec:%d\n", cur->cycle_to_exec + 1);
		printf("pc:%d\n", cur->pc);
		//printf("step:%d\n",cur->move);
		i = 0;
		while (i < 16) {
			printf("r_%d:%d\n", i, cur->registers[i]);
			i++;
		}
		if (vm->debug - 1 == 0)
			printf("o:%x\n", cur->op_code);
	}
}

void	debug_info(t_vm *vm)
{
	if (vm->debug - 1 == 0)
	{
		print_vm(vm);
		print_cursor(vm);
	}
	vm->debug--;
	if (vm->debug == 0)
		exit(0);
}