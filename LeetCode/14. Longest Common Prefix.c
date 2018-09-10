char* longestCommonPrefix(char** strs, int strsSize) {
    int i=0,len=-1,undiff=1;
    //把input看作矩阵，i为行，len为列，undiff比较到不同时变为0
    do{
        ++len;
        for(i=0;i<strsSize;++i)
        {
            if(*(*(strs+0)+len)!=*(*(strs+i)+len)||*(*(strs+i)+len)=='\0')
            {
                undiff=0;
                break;
            }
        }
    }while(*(*strs+len)!='\0'&&undiff);
    *(*strs+len)='\0';
    return *strs;
}