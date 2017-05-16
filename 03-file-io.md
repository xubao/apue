# 文件描述符 File Descriptors

每一个打开的文件都是通过fd来引用。

POSIX 在"unistd.h"中定义了3个常量表示标准输入、标准输出和标准错误。
```
/* Standard file descriptors.  */
#define STDIN_FILENO    0       /* Standard input.  */
#define STDOUT_FILENO   1       /* Standard output.  */
#define STDERR_FILENO   2       /* Standard error output.  */
```
fd的限制：0 ~ OPEN_MAX-1。OPEN_MAX表示每个进程能打开的最大文件数，查看如下：
```
printf("_SC_OPEN_MAX: %ld\n", sysconf(_SC_OPEN_MAX));  
```
在Ubuntu 14.04下，OPEN_MAX为1024

# open(), close(), read(), write(), lseek()函数
具体的用法
```
#include <fcntl.h>
#include <unistd.h>

int open(const char *path, int oflag, .../mode_t mode/);
// 成功返回fd, 失败返回-1
// oflag : O_RDONLY, O_WRONLY, O_RDRW, O_EXEC, O_APPEND, O_CREAT, OTRUNC

int close(int fd);
// 成功返回0， 失败返回-1

off_t lseek(int fd, off_t offsest, int whence);
// whence可为SEEK_SET, SEEK_CUR, SEEK_END， 对于SEEK_CUR和SEE_END，

off_t currpos = lseek(fd, 0, SEEK_CUR);
// 获得当前offset

ssize_t read(int fd, void *buf, size_t nbytes);
// 成功返回字节数，文件末尾返回0，失败返回-1

ssize_t write(int fd, void *buf, size_t nbytes);
// 成功返回字节数，失败返回-1
```

# 文件共享
process table entry ( fd (fd flags, file pointer))
file table entry (file status flag, current file offset, v-node pointer)
v-node table entry(file information such as file size)


# dup(), dup2(), sync(), fsync(), fcntl(), ioctl 函数
```
#include <unistd.h>

int dup(int fd);
// 成功返回fd（可用的最小fd），错误返回-1

int dup2(int fd, int fd2);
// 指定新的fd2的值，成功刚返回fd2, 错误返回-1
// fd和fd2共享file table entry

int fsync(int fd);
void sync(void);

int fcntl(int fd, int cmd, ... /* int arg */);
// 改变已打开文件的属性：fd flags(FD_CLOEXEC), file status（read, write, append)
// 复制一个已存在的fd

#include <unistd.h>
#include <sys/ioctl.h>
int ioctl(int fd, int request, ...);
```

# /dev/fd
