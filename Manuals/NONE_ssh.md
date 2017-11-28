# 此文件
对OpenSSH说明，
来自info ssh

# ssh是什么
ssh客户端能够登录远程机器能够在该远程主机上执行命令，它是为了两个主机安全通信而建立的。简单地说，ssh是一个安全的telnet, 用于满足一个用户远程登录另一个计算机的需求。
ssh不同于telnet的地方是，其配置乍看起来比较复杂。但是其实道理很简单，你可以不用配置ssh就能远程登录。配置过程只是一个认证方式的修改。使用ssh最简单的方式，也是首先推荐的基本验证方式，是密码登录，通过在你的主机上命令行输入： ssh USER@B, 其中USER是主机B上的用户名，你必须有这个用户名的密码，B代表IP地址。
输入后，首次登录ssh会询问是否将主机的key写入known_hosts文件，输入yes；然后就是输入密码登录即可。

# 使用密钥登录配置步骤
情况：主机A，以用户U的身份登录到主机B
前提：主机A有ssh客户端， 主机B开启sshd服务，主机B有用户U

步骤1：主机A上ssh-keygen生成密钥对文件id_rsa,id_rsa.pub
步骤2：将id_rsa.pub的内容复制到主机B用户U的~/.ssh/authorized_keys尾部
步骤3：主机B确保authorized_keys的权限是600,使用chmod 600 ~/.ssh/authorized_keys
步骤4：主机A登录，输入 ssh U@B, U用户名，B主机B的ip地址

如果出现首次登录的警告，选择yes

注：已经在ubuntu上验证，但cygwin不能

# 在cygwin上配置sshd
注：cygwin上ssh的主要问题是，尽管经过很多正确的配置，仍然不能正常登录用户。cygwin可能对登录用户有限制。
1.管理员模式打开cygwin(版本：2017年11月),运行ssh-host-config,全部yes即可
2.修改/etc/sshd_config文件，如下： 【管理员模式】
```bash
PermitRootLogin prohibit-password
StrictModes no

PubkeyAuthentication yes

AuthorizedKeysFile  .ssh/authorized_keys


HostbasedAuthentication yes
PasswordAuthentication yes
PermitEmptyPasswords yes
```
3.更新/etc/passwd文件，获取用户信息, mkpasswd -l >/etc/passwd，然后查看/etc/passwd文件，看到所有用户
3.5 删除 ~/.ssh文件夹
4.对其中的每一个用户，依次尝试修改其密码，比如修改为123123,  passwd USER
5.对于4中尝试的一个用户，现在使用ssh登录： ssh USER@localhost, 出现yes/no选择yes
6.输入刚才的密码，此例为123123，如果确认密码没有输入错误，出现了 'Permission denied..'之类的字样，则这个用户不可行
7.重复4~6，直到找到一个可行的用户
8.如果找到一个可行用户，在输入密码后就会进入ssh界面：
```
      ____________________,             ______________________________________
   .QQQQQQQQQQQQQQQQQQQQQQQQL_         |                                      |
 .gQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ__   |                                      |
 gQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ==   |                    _.---.)           |
 QQQQQQQQQQQQQQQQQQQQQQQQQQQF=         |          (^--^)_.-"      `;          |
 QQQQQQQQQ================!            |          ) ee (           |          |
 QQQQQQQQ                              |         (_.__._)         /           |
 QQQQQQQQ                              |           `--',        ,'            |
 QQQQQQQQ     ~"jjj__,                 |            jgs )_|--')_|             |
 QQQQQQQQ       "jjjjjjjjjj___         |                ""'   ""'             |
 QQQQQQQQ        ~jjjjjjjjjjjjjjjjj__  |                                      |
 QQQQQQQQ        _jjjjjjjjjjjjjj/~~~~  |      The Hippo says: Welcome to      |
 QQQQQQQQ      .{jjjjjjj/~~~~~         |                             _        |
 QQQQQQQQ     .{/~~~~`                 |  ____  _   _   ____  _ _ _ (_) ____  |
 QQQQQQQQ                              | / ___)| | | | / _  || | | || ||  _ \ |
 QQQQQQQQ                              |( (___ | |_| |( (_| || | | || || | | ||
 QQQQQQQQQL_______________,            | \____) \__  | \___ | \___/ |_||_| |_||
 QQQQQQQQQQQQQQQQQQQQQQQQQQQL___       |        (___/  (____|                 |
 4QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ___  |                                      |
 (=QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ====   |       -.-. -.-- --. .-- .. -.        |
   (QQQQQQQQQQQQQQQQQQQQQQQQF=         |______________________________________|
```
在此例中，该用户名为cyg,passwd文件对应行如下：cyg:*:197612:197121:U-FULTONPC\cyg,S-1-5-21-3968254413-2947885272-698408679-1004:/home/cyg:/bin/bash
9.如果失败了，尝试在windows中新建一个普通用户，然后再从3开始重新运行


# 认证
OpenSSH客户端支持SSH协议2
可供认证的方法有：基于GSSAPI,基于主机,基于公钥，基于 chanllenge response,基于密码。 如果没有指定，上面的验证方法依次被尝试。

基于主机的认证如下工作：如果请求登陆的主机在服务器的/etc/hosts.equiv或者/etc/shosts.equiv中，并且用户名称在两台机器上都是相同的；
或者~/.rhosts|~/.shosts存在于远程主机中并且包含请求主机和请求用户，则用户可以登录。

基于公钥的认证如下：公钥加密系统使用不同的密钥来加密和解密数据。每个用户创建一对公钥和私钥用于认证。服务器知道公钥，但是只有用户知道私钥（使用DSA,ECDSA,Ed25519或者RSA加密算法）。文件~/.ssh/authorized_keys列出所有的允许登陆的公钥。当用户登录认证时，客户端会告诉服务器它所希望使用的密钥对。服务器端检查相应的公钥是否已经认证，然后接受登录。
用户通过ssh-keygen来创建密钥对，会创建私钥在~/.ssh/id_XXX文件中，私钥在~/.ssh/id_XXX.pub中。用户创建密钥之后应当将公钥复制到远程主机上的~/.ssh/authorized_keys中（同样是自己的目录）。这样，用户就可以不用密码进行登录。

# 文件
~/.ssh/authorized_keys  所有的可用于登录本机的公共密钥(DSA,ECDSA,RSA)，该文件的格式有 man 8 sshd描述
~/.ssh/config           每个用户自己的配置，文件格式在man 5 ssh_config中约定

~/.ssh/id_rsa
~/.ssh/id_dsa
~/.ssh/id_XXX
        包含用于验证的私钥。这些文件的内容应当是私密的。如果该文件的权限不是仅拥有者自己可操作，则ssh会忽略这个不安全的文件
~/.ssh/id_rsa.pub
~/.ssh/id_dsa.pub
~/.ssh/id_XXX.pub
        包含公钥，可公开
~/.ssh/known_hosts
        包含一系列不在主机的hosts列表中的、但是已被用户登陆过的主机
/etc/ssh_config
        所有用户共享的配置文件