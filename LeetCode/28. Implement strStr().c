//对比了别人的0ms,惭愧惭愧
int strStr(char* haystack, char* needle) {
    if(!*needle)
        return 0;
    for(int i=0,j=0;haystack[i]!='\0';++i,j=0)
    {
        while(haystack[i+j]==needle[j])
        {
            if(needle[++j]=='\0') 
                    return i;
        }
    }
    return -1;
}