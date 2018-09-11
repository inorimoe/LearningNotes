bool isValid(char* s) 
{
    char stack[3725];//栈要大于测试例子
    int top=-1;

    while(*s)
    {
        if(*s=='('||*s=='{'||*s=='['){
            stack[++top]=*s;//入栈
        }
        else if(top>=0&&*s==')'&&stack[top]=='('){//pop
            stack[top--]=0;
        }
        else if(top>=0&&*s=='}'&&stack[top]=='{'){//pop
            stack[top--]=0;
        }
        else if(top>=0&&*s==']'&&stack[top]=='['){//pop
            stack[top--]=0;
        }
        else//error
            return false;
        ++s;
    }
    if(top==-1)//确认栈是空的
        return true;
    else//栈非空
        return false;
}