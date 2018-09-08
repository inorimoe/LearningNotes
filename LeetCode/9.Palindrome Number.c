bool isPalindrome(int x) {
    int revertedNum = 0;
    if (x<0)
        return 0;
    for(int cache = x;cache>0;cache /= 10)
        revertedNum = revertedNum*10+cache%10;
    if(x==revertedNum)
        return 1;
    else
        return 0;
}