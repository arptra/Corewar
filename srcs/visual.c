#include "../incl/parse.h"

void print_add_player(t_vm *vm, int cycle, const int player_id, const char *name, int address)
{
	uint8_t *arena;

	printf("p%c%d%c%d%c%s%c%d%c", sep, cycle, sep, player_id, sep, name, sep, address, sep);
	arena = &vm->arena[address];
	while (*arena != 0)
	{
		print_byte_by_ptr(arena);
		(*arena)++;
	}
	printf("\n");
}

// печатать при создании коретки
// cycle номер текущего цикла
// player_id игрок которому пренадлежит каретка
// carriage_id каретки надо отличать друг от друга, в качестве id можно использовыть адрес их структур
// address абсолютный адресс памяти где будет стартовать каретка
void print_add_carriage(t_vm *vm, int player_id)
{
	printf("c%c%d%c%d%c%d%c%d\n", sep, vm->cycle, sep, player_id, sep, vm->car->num, sep, vm->car->pc);
}

// печать при смерти карретки
// cycle номер текущего цикла
// player_id айди игрока которому пренадлежала каретка
// carriage_id айди карретки
void print_kill_carriage(t_vm *vm, t_carriage *car)
{
	printf("k%c%d%c%d%c%d\n", sep, vm->cycle, sep, car->p->cnum, sep, car->num);
}

// печать при перемещении каретки
// cycle номер текущего цикла
// player_id айди игрока которому пренадлежала каретка
// carriage_id айди карретки
// offset относитьльный сдвиг - на сколько байт относительно прошлого положения переместилась каретка
void print_move_carriage(t_vm *vm, const int player_id, int offset)
{
	printf("m%c%d%c%d%c%d%c%d\n", sep, vm->cycle, sep, player_id, sep, vm->car->num, sep, offset);
}

// печать при записи в память игроком значения регистра (инструкция st или sti)
// cycle номер текущего цикла
// player_id айди игрока который пишет в память
// address абсолютный адресс первого байта
// значение 4х байтового регистра
void print_write_memory(t_vm *vm, int player_id, int address, int32_t reg_value)
{
	printf("w%c%d%c%d%c%d%c%08X\n", sep, vm->cycle, sep, player_id, sep, address, sep, reg_value);
}

// печать при объявлении победителя
// cycle номер текущего цикла
// player_id айди игрока который выжил
void print_declare_winner(t_vm *vm)
{
	printf("e%c%d%c%d\n", sep, vm->cycle, sep, vm->last_live->cnum);
}