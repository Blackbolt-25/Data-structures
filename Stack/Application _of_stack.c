#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE 100

typedef struct stack
{
    char arr[MAX_SIZE];
    int top;
}STACK;

typedef struct stack2
{
    int arr[MAX_SIZE];
    int top;
}STACK_2;

void push(STACK* start,char data)
{
    start->arr[++start->top]=data;
}

char pop(STACK* start)
{
    return start->arr[start->top--];
}

void display(STACK* start)
{
    for(int i=0;i<start->top+1;i++)
        printf("%c",start->arr[i]);
    printf("\n");
}

int cmp(char data1,char data2)
{
    if(data2=='(' || data2=='[' || data2=='{')
        return 0;
    else if(data1=='^' && data2=='^')
        return 1;
    else if((data1=='*' || data1=='/' || data1=='%') && (data2!='+' && data2!='-'))
        return 1;
    else if(data1=='+' || data1=='-')
        return 1;
    else
        return 0;
}

int cmp2(char data1,char data2)
{
    if(data2=='(' || data2=='[' || data2=='{')
        return 0;
    else if(data1=='^' && data2!='^')
        return 1;
    else if((data1=='*' || data1=='/' || data1=='%') && (data2=='^'))
        return 1;
    else if((data1=='+' || data1=='-') && (data2!='+' && data2!='-'))
        return 1;
    else
        return 0;
}

void initialize(STACK* p)
{
    p->top=-1;
}

void initialize_int(STACK_2* p)
{
    p->top=-1;
}

char equi(char s)
{
    if(s==']')
        return '[';
    else if(s=='}')
        return '{';
    else if(s==')')
        return '(';
    else if(s=='(')
        return ')';
    else if(s=='[')
        return ']';
    else 
        return '}';
}

void infix_postfix(char* str,STACK* ans,STACK* operator)
{
    for(int i=0;i<strlen(str);i++)
        {
            if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='^' || str[i]=='/' || str[i]=='%')
            {
                while(operator->top!=-1 && cmp(str[i],operator->arr[operator->top]))
                    push(ans,pop(operator));
                push(operator,str[i]);
            }
            else if(isalnum(str[i]))
                push(ans,str[i]);
            else if (str[i]=='(' || str[i]=='[' || str[i]=='{')
                push(operator,str[i]);
            else if(str[i]==']' || str[i]==')' || str[i]=='}')
            {
                if(operator->top==-1)
                {
                    printf("Wrong use of parenthesis\n");
                    return;
                }
                char temp=pop(operator);
                while(temp!=equi(str[i]) && operator->top!=-1)
                {
                    push(ans,temp);
                    temp=pop(operator);
                }
                if(temp!=equi(str[i]))
                {
                    printf("%c %c\n",temp,str[i]);
                    return;
                }
            }
            else
            {
                printf("The expression entered is wrong\n");
                break;
            }
        }
        while(operator->top!=-1)
            push(ans,pop(operator));
        printf("The postfix expression is:-\n");
        display(ans);
}


void reverse(char *str)
{
    int temp;
    int left=0;
    int right=strlen(str)-1;
    while (left<right)
    {
        int temp=str[left];
        str[left]=str[right];
        str[right]=temp;
        left++;
        right--;
    }
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==']' || str[i]=='}' || str[i]==')')
            str[i]=equi(str[i]);
        else if(str[i]=='[' || str[i]=='{' || str[i]=='(')
            str[i]=equi(str[i]);
    }
}

void infix_prefix(char *str,STACK* ans,STACK* operator)
{
    reverse(str);
    for(int i=0;i<strlen(str);i++)
        {
            if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='^' || str[i]=='/' || str[i]=='%')
            {
                while(operator->top!=-1 && cmp2(str[i],operator->arr[operator->top]))
                    push(ans,pop(operator));
                push(operator,str[i]);
            }
            else if(isalnum(str[i]))
                push(ans,str[i]);
            else if (str[i]=='(' || str[i]=='[' || str[i]=='{')
                push(operator,str[i]);
            else if(str[i]==']' || str[i]==')' || str[i]=='}')
            {
                if(operator->top==-1)
                {
                    printf("Wrong use of parenthesis\n");
                    return;
                }
                char temp=pop(operator);
                while(temp!=equi(str[i]) && operator->top!=-1)
                {
                    push(ans,temp);
                    temp=pop(operator);
                }
                if(temp!=equi(str[i]))
                {
                    printf("Wrong use of parenthesis\n");
                    return;
                }
            }
            else
            {
                printf("The expression entered is wrong\n");
                break;
            }
        }
        while(operator->top!=-1)
            push(ans,pop(operator));
        printf("The prefix expression is:-\n");
        for(int i=ans->top;i>=0;i--)
            printf("%c",ans->arr[i]);
        printf("\n");
}

void paranthesis(char *str,STACK* ans)
{
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==')' || str[i]==']' || str[i]=='}')
            pop(ans);
        else if(str[i]=='(' || str[i]=='{' || str[i]=='[')
            push(ans,str[i]);
        else
            printf("The given string input is invalid\n");
    }
    if(ans->top==-1)
        printf("U hve entered correct string\n");
    else 
        printf("U hve entered wrong string\n");
}

int pop_2(STACK_2* a)
{
    return a->arr[a->top--];
}

int eval(int b,int a,char operator)
{
    if(operator=='+')
        return a+b;
    else if(operator=='-')
        return a-b;
    else if(operator=='*')
        return a*b;
    else if(operator=='/')
        return a/b;
    else if(operator=='%')
        return a%b;
    else
        return a^b;
}

void push_2(STACK_2* a,int b)
{
    a->arr[++a->top]=b;
}

int postfix_eval(STACK* a)
{
    STACK_2 ans;
    initialize_int(&ans);
    for(int i=0;i<=a->top;i++)
    {
        if(isdigit(a->arr[i]))
        {
            int token=a->arr[i]-'0';
            push_2(&ans,token);
        }
        else if(a->arr[i]=='+' || a->arr[i]=='-' || a->arr[i]=='*' || a->arr[i]=='%' || a->arr[i]=='^' || a->arr[i]=='/') 
        {
            int temp1=pop_2(&ans);
            int temp2=pop_2(&ans);
            int result=eval(temp1,temp2,a->arr[i]);
            push_2(&ans,result);
        }
    }
    return ans.arr[ans.top];
}

int prefix_eval(STACK* a)
{
    STACK_2 ans;
    initialize_int(&ans);
    for(int i=0;i<strlen(a->arr);i++)
    {
        if(isdigit(a->arr[i]))
        {
            int token=a->arr[i]-'0';
            push_2(&ans,token);
        }
        else if(a->arr[i]=='+' || a->arr[i]=='-' || a->arr[i]=='*' || a->arr[i]=='%' || a->arr[i]=='^' || a->arr[i]=='/') 
        {
            int temp1=pop_2(&ans);
            int temp2=pop_2(&ans);
            int result=eval(temp2,temp1,a->arr[i]);
            push_2(&ans,result);
        }
    }
    return ans.arr[ans.top];
}

int main()
{
    int choice,temp;
    printf("1.Infix to Postfix\n2.Infix to Prefix\n3.Paranthesis Evaluation\n");
    printf("Enter choice:-");scanf("%d",&choice);
    char str[100];
    STACK operator;
    STACK ans;
    initialize(&operator);initialize(&ans);
    switch (choice)
    {
    case 1:
        printf("Enter the infix expression to be evaluated:-\n");scanf("%s",str);
        infix_postfix(str,&ans,&operator);
        printf("Do u want to evaluate ur string? 1--Yes || 2--No\n");scanf("%d",&choice);
        if(choice==1)
        {
            temp=postfix_eval(&ans);
            printf("The evaluated expression is:- %d\n",temp);
        }
        break;
    case 2:
        printf("Enter the postfix expression to be evaluated:-\n");scanf("%s",str);
        infix_prefix(str,&ans,&operator);
        printf("Do u want to evaluate ur string? 1--Yes || 2--No\n");scanf("%d",&choice);
        if(choice==1)
        {
            temp=prefix_eval(&ans);
            printf("The evaluated expression is:- %d\n",temp);
        }
        break;
    case 3:
        printf("Enter the paranthesis expression to be evaluated:-\n");scanf("%s",str);
        paranthesis(str,&ans);
    default:
        break;
    }
}

//Using linked list.

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<ctype.h>


// //Structure for a linked list.
// typedef struct node
// {
//     char data;
//     struct node *next;
// }NODE;

// int precedence(char a)
// {
//     if(a=='^')
//         return 2;
//     else if(a=='*' || a=='/' || a=='%')
//         return 1;
//     else if(a=='+' || a=='-')
//         return 0;
//     else if(a=='(' || a=='{' || a=='[' )    
//         return -1;
//     else 
//         return -2;
// }

// void push(NODE** start,char a)
// {
//     if(*start==NULL)
//     {
//         NODE* newnode=(NODE*)malloc(sizeof(NODE));
//         newnode->data=a;
//         newnode->next=NULL;
//         *start=newnode;
//     }
//     else 
//     {   
//         NODE* newnode=(NODE*)malloc(sizeof(NODE));
//         newnode->data=a;
//         newnode->next=*start;
//         *start=newnode;
//     }
// }

// char pop(NODE** start)
// {
//     if(*start==NULL)
//         return 'N';
//     else
//     {
//         char value=(*start)->data;
//         NODE* temp=*start;
//         *start=(*start)->next;
//         free(temp);
//         return value;
//     }
// }

// char inverse(char a)
// {
//     if(a==')')
//         return '(';
//     else if(a=='}')
//         return '{';
//     else
//         return '[';    
// }

// void reverse(NODE** start)
// {
//     NODE* back=NULL;
//     NODE* head=*start;
//     NODE* pass=(*start)->next;
//     while(pass!=NULL)
//     {
//         head->next=back;
//         back=head;
//         head=pass;
//         pass=pass->next;
//     }
//     head->next=back;
//     if(head!=NULL)
//         *start=head;
// }

// void display(NODE** start)
// {
//     if(*start==NULL)
//         printf("The queue is empty\n");
//     else
//     {
//         NODE* temp=*start;
//         while(temp!=NULL)
//         {
//             printf("%c",temp->data);
//             temp=temp->next;
//         }
//     }
// }

// void infix_postfix(char* question) 
// {
//     char value;
//     NODE* ans=NULL;
//     NODE* operator=NULL;
//     for(int i=0;i<strlen(question);i++)
//     {   
//         if(isalnum(question[i]))
//             push(&ans,question[i]);
//         else
//         {
//             if(question[i]=='(' || question[i]=='{' || question[i]=='[' || isdigit(question[i]))
//                 push(&operator,question[i]);
//             else if(question[i]==')' || question[i]=='}' || question[i]==']')
//             {
//                 value=pop(&operator);
//                 while(value!=inverse(question[i]))
//                 {
//                     push(&ans,value);
//                     value=pop(&operator);
//                 }
//             }
//             else if(precedence(question[i])==-2)
//             {
//                 printf("Invalid expression entered");
//                 return;
//             }
//             else
//             {
//                 if(operator==NULL || precedence(question[i])>precedence(operator->data))
//                     push(&operator,question[i]);
//                 else if(precedence(question[i])<=precedence(operator->data))
//                 {
//                     value=pop(&operator);
//                     push(&ans,value);
//                     push(&operator,question[i]);
//                 }
//             }
//         }
//     }
//     while(operator!=NULL)
//     {
//         value=pop(&operator);
//         push(&ans,value);
//     }
//     reverse(&ans);
//     display(&ans);
// }

// int main()
// {
//     infix_postfix("a*(b+c)^n");
// }
