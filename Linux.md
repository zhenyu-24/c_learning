## 基础命令
### cd命令
进行工作路径的切换
..: 表示当前目录的上一级目录, 使用cd .. 或者 cd ../都可以
. : 表示当前目录, 使用 .或者./都可以, cd .不会切换目录

### ls命令
打印指定的文件信息, 如果是目录, 显示对应目录中有哪些子文件

ls添加 -l参数（就是 list 的意思）我们就可以看到文件的详细信息了, 里边的信息量还是非常大的, 其中包括: 文件类型, 文件所有者对文件的操作权限, 文件所属组用户对文件的操作权限, 其他人对文件的操作权限, 硬链接计数, 文件所有者, 文件所属组, 文件大小, 文件的修改日期, 文件名

### mkdir命令
目录的创建分为两种, 一种是创建单个目录, 另一种是一次性创建多层目录, 使用的命令是mkdir, 后边参数是要创建的目录的名字, 如果是多层目录需要添加参数-p。

### rm命令
rm: 可以删除文件也可以删除目录, 如果删除的的是目录, 需要加参数 -r, 意思是递归(recursion)
rm命令还有另外两个经常使用的参数:
- i: 删除的时候给提示
- f: 强制删除文件, 没有提示直接删除并且不能恢复, 慎用

### cp命令
cp 就是copy, 拷贝, 使用这个命令可以拷贝文件也可以拷贝目录
```
# 拷贝目录需要参数 -r
# 场景1: 目录A, 通过拷贝得到不存在的目录B
$ cp 目录A 目录B -r

# 场景2: 目录A存在的, 目录B也是存在的, 执行下边的拷贝 ==> 目录A会被拷贝并将其放到目录B中
$ cp 目录A 目录B -r

# 场景3: 把A目录里的某一个或者多个文件拷贝到B目录中
$ cp A/a.txt B	# 拷贝 A目录中的 a.txt 到目录B中
$ cp A/* B -r	# 拷贝 A目录中的所有文件到目录B中, 不能确定A目录中是否有子目录, 因此需要加 -r
```

### mv命令
mv 就是move, 这个Linux命令既能移动文件所在目录也可以给文件改名。

### vim命令
查看文件内容

### 链接的创建
链接分两种类型: 软连接和硬链接。软连接相当于windows中的快捷方式，硬链接前边也已经介绍过了文件并不会进行拷贝，只是多出一个新的文件名并且硬链接计数会加1。
```
# 语法: ln -s 源文件路径 软链接文件的名字(可以带路径)

# 查看目录文件
[root@VM-8-14-centos ~/luffy]# ll
total 8
drwxr-xr-x 3 root root 4096 Jan 25 17:27 get
-rw-r--r-- 1 root root   37 Jan 25 17:26 onepiece.txt

# 给 onepiece.txt 创建软连接, 放到子目录 get 中
[root@VM-8-14-centos ~/luffy]# ln -s /root/luffy/onepiece.txt get/link.lnk  
[root@VM-8-14-centos ~/luffy]# ll get
total 4
lrwxrwxrwx 1 root root   24 Jan 25 17:27 link.lnk -> /root/luffy/onepiece.txt
drwxr-xr-x 2 root root 4096 Jan 24 21:37 onepiece
```
```
# 语法: ln 源文件 硬链接文件的名字(可以带路径)

# 创建硬链接文件, 放到子目录中
[root@VM-8-14-centos ~/luffy]# ln onepiece.txt get/link.txt

# 查看链接文件和硬链接计数, 从 1 --> 2
[root@VM-8-14-centos ~/luffy]# ll get
total 8
lrwxrwxrwx 1 root root   24 Jan 25 17:27 link.lnk -> /root/luffy/onepiece.txt
-rw-r--r-- 2 root root   37 Jan 25 17:26 link.txt
drwxr-xr-x 2 root root 4096 Jan 24 21:37 onepiece
```

