# 进程的set-user-id

每个进程有6个相关的ID
real user ID, real group ID
effective user ID, effective group ID, supplementary group IDs
saved set-user-ID, saved set-group-ID

real user ID 是指该进程是谁启动的。而当进程访问某个文件时，会依据effective uesr id检查是否有权限访问。
effective user ID 一般和real user ID 相同。如果该文件设置了它的set-user-id bit，则执行这个文件时，进程的effective uer id等于该文件的owner id.
 
```c
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
``` 
执行结果：
```
$ ll
total 16
-rwxrwxr-x 1 xubao xubao 8752 5月  18 10:27 a.out
$ ./a.out 
real user id is 1000
effective user id is 1000
//以当前用户执行a.out, real user id和effective user id都是当前用户id 1000

$ sudo ./a.out 
real user id is 0
effective user id is 0
//以root执行a.out, real user id和effective user id都是rootid 0

$ sudo chown test a.out 
$ ll                                          
total 16
-rwxrwxr-x 1 test  xubao 8752 5月  18 10:27 a.out
//改变a.out的owner为test用户

$ ./a.out 
real user id is 1000
effective user id is 1000
$ sudo ./a.out 
real user id is 0
effective user id is 0
//结果一样。

$ sudo chmod u+s a.out 
$ ll
total 16
-rwsrwxr-x 1 test  xubao 8752 5月  18 10:27 a.out
//设置a.out的set-user-id bit
                            
$ ./a.out 
real user id is 1000
effective user id is 1001
$ sudo ./a.out 
real user id is 0
effective user id is 1001
//real use id是执行程序的用户id，而effective user id是a.out的owner id
```