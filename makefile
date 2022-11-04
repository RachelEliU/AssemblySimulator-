prog: prog.o passFirst.o passSecond.o checkMethods.o tabels.o commandMethods.o checkParam.o
	gcc -g -Wall prog.o passFirst.o passSecond.o checkMethods.o tabels.o commandMethods.o checkParam.o -o prog -lm
prog.o: prog.c prog.h
	gcc -c prog.c -o prog.o
passFirst.o: passFirst.c prog.h
	gcc -c passFirst.c -o passFirst.o
passSecond.o: passSecond.c prog.h
	gcc -c passSecond.c -o passSecond.o
checkMethods.o: checkMethods.c prog.h
	gcc -c checkMethods.c -o checkMethods.o
tabels.o: tabels.c prog.h
	gcc -c tabels.c -o tabels.o
commandMethods.o: commandMethods.c prog.h
	gcc -c commandMethods.c -o commandMethods.o
checkParam.o: checkParam.c prog.h
	gcc -c checkParam.c -o checkParam.o


