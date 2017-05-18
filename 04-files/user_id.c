#include <unistd.h>
#include <stdio.h>

void print_user_id()
{
       printf("real user id is %d\n", getuid());
       printf("effective user id is %d\n", geteuid());     
}

int main()
{
       print_user_id();
       return 0;
}
