#include "prog.h"

void creatActionTable()
{
action action0,action1,action2,action3,action4,action5,action6,action7,action8,action9,action10,action11,action12,action13,action14,action15;
action0.name = "mov";
action0.funct = 0;
action0.code = 0;
action1.name = "cmp";
action1.funct = 0;
action1.code = 1;
action2.name = "add";
action2.funct = 1;
action2.code = 2;
action3.name = "sub";
action3.funct = 2;
action3.code = 2;
action4.name = "lea";
action4.funct = 0;
action4.code = 4;
action5.name = "clr";
action5.funct = 1;
action5.code = 5;
action6.name = "not";
action6.funct = 2;
action6.code = 5;
action7.name = "inc";
action7.funct = 3;
action7.code = 5;
action8.name = "dec";
action8.funct = 4;
action8.code = 5;
action9.name = "jmp";
action9.funct = 1;
action9.code = 9;
action10.name = "bne";
action10.funct = 2;
action10.code = 9;
action11.name = "jsr";
action11.funct = 3;
action11.code = 9;
action12.name = "red";
action12.funct = 0;
action12.code = 12;
action13.name = "prn";
action13.funct = 0;
action13.code = 13;
action14.name = "rts";
action14.funct = 0;
action14.code = 14;
action15.name = "stop";
action15.funct = 0;
action15.code = 15;

actionTable[0] = action0;
actionTable[1] = action1;
actionTable[2] = action2;
actionTable[3] = action3;
actionTable[4] = action4;
actionTable[5] = action5;
actionTable[6] = action6;
actionTable[7] = action7;
actionTable[8] = action8;
actionTable[9] = action9;
actionTable[10] = action10;
actionTable[11] = action11;
actionTable[12] = action12;
actionTable[13] = action13;
actionTable[14] = action14;
actionTable[15] = action15;
}


