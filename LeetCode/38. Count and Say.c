char* countAndSay(int n) {
    char A[5000]="1";
    char B[5000]="1";
    char* str,*stack,*park;
    char len = 49;
    int position = 0;
    str = A;
    stack = B;

    for(int i=1,j=0;i<n;++i,position = 0)
    {
        for(j=0;str[j]!='\0';++j)
        {
            if(str[j]!=str[j+1])
            {
                stack[position]=len;
                stack[++position]=str[j];
                ++position;
                len = 49;
            }
            else
                ++len;
        }
        stack[position]='\0';
        park = str;
        str = stack;
        stack = park ;  
    }
    return str;
}