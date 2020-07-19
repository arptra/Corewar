# План на 19 июля Игорь:
- написать free_VM.
- привести код для парсинга игроков к Норме.
- обсудить визуализатор с Алиной.


# VM

## Checker usage

`$ python3 checker.py --start <number-of-cicles-to-start-comparing> --end <number-of-cicles-before-game-will-stopped> <path/to/.cor/file/N1> <path/to/.cor/file/N2> ...`

Example:

`$ python3 checker.py cor-mac/zork.cor cor-mac/batman.cor --start 10 --end 99`

`--end` flag responsible for number of cicles. After execution this number of cicles game will be stopped and memory will be dumped into stdout.
If `--end` not given, it will be placed to 10 cicles.

`--start` flag responsible for number of cicles when checker start to compare output your's and default corewars.
If `--start` not given, it will be placed equals to end.

Checker will recompile project by his own, you sholdn't do anything else.

## How to use
`make`
`./vm 42.cor`
and displey magic header
`0ea83f3`

## TODO
1. how to know number of bites in magic header? right now they are hardcoded as a 4, but it could be another number...
2. 
