int lengthOfLastWord(char* s) {
    if(!*s)return 0;
    char* worLeft,*worRight;
    worLeft=worRight=s;
    //用单词的最右边减去单词的最左边+1
    while(*s)
    {
        if(*s!=' '&&*(s-1)==' ')
        {
            worLeft = s;
        }
        if(*s!=' '&&(*(s+1)==' '||*(s+1)=='\0'))
        {
            worRight = s;
        }
        ++s;
    }
    if(*worLeft==' ')return 0;
    //字符串如果为空白，worleft与worright会在字符串最左端不动
    return worRight-worLeft+1;
}