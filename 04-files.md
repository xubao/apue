# ���̵�set-user-id

ÿ��������6����ص�ID
real user ID, real group ID
effective user ID, effective group ID, supplementary group IDs
saved set-user-ID, saved set-group-ID

real user ID ��ָ�ý�����˭�����ġ��������̷���ĳ���ļ�ʱ��������effective uesr id����Ƿ���Ȩ�޷��ʡ�
effective user ID һ���real user ID ��ͬ��������ļ�����������set-user-id bit����ִ������ļ�ʱ�����̵�effective uer id���ڸ��ļ���owner id.
 
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
ִ�н����
```
$ ll
total 16
-rwxrwxr-x 1 xubao xubao 8752 5��  18 10:27 a.out
$ ./a.out 
real user id is 1000
effective user id is 1000
//�Ե�ǰ�û�ִ��a.out, real user id��effective user id���ǵ�ǰ�û�id 1000

$ sudo ./a.out 
real user id is 0
effective user id is 0
//��rootִ��a.out, real user id��effective user id����rootid 0

$ sudo chown test a.out 
$ ll                                          
total 16
-rwxrwxr-x 1 test  xubao 8752 5��  18 10:27 a.out
//�ı�a.out��ownerΪtest�û�

$ ./a.out 
real user id is 1000
effective user id is 1000
$ sudo ./a.out 
real user id is 0
effective user id is 0
//���һ����

$ sudo chmod u+s a.out 
$ ll
total 16
-rwsrwxr-x 1 test  xubao 8752 5��  18 10:27 a.out
//����a.out��set-user-id bit
                            
$ ./a.out 
real user id is 1000
effective user id is 1001
$ sudo ./a.out 
real user id is 0
effective user id is 1001
//real use id��ִ�г�����û�id����effective user id��a.out��owner id
```