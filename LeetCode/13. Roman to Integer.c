int romanToInt(char* s) {
    int valall=0,valsin=0,valbefore=1000;
     while(*s)
     {
         switch(*s++)
         {
             case 'I':valsin=1;break;
             case 'V':valsin=5;break;
             case 'X':valsin=10;break;
             case 'L':valsin=50;break;
             case 'C':valsin=100;break;
             case 'D':valsin=500;break;
             case 'M':valsin=1000;break;
             default:break;
         }
        if(valbefore<valsin)
        {
            valall+=valsin-valbefore-valbefore;
            //valall+=valsin-2*valbefore;
            //一个乘法的区别，就干掉20%的人，这是我能想到优化了，orz
        }
        else
        {
            valbefore=valsin;
            valall+=valsin;
        }
     }
     return valall;
}