# 此文件
此文件对实模式下BIOS介绍



# LBA28位地址和CHS之间的转换
cylinder = LBAStart/36,
head = (LBAStart - LBAStart/36*36)/18,
sector = (LBAStart%18) + 1
设硬盘的CHS参数为C,H,S； 任意CHS地址为(cylinder,head,sector)三元组
[]C []H []S
磁盘最大总容量就是C*H*S
使用进位的思想来计算。先把sector参数规范化：sector_std=sector-1
LBA = (cylinder*H + head)*S + sector_std
每一步都是先计算该步的进位数量，然后向下进行
逆向计算：sector_std=LBA%S
        head = LBA/S%H
        cylinder=LBA/S/H


# 13h中断
参考：http://blog.sina.com.cn/s/blog_5028978101008wk2.html
ah=功能号，02h表示读扇区

####功能02H  
功能描述：读扇区 
入口参数：AH＝02H 
AL＝扇区数 
CH＝柱面 
CL＝扇区 
DH＝磁头 
DL＝驱动器，00H~7FH：软盘；80H~0FFH：硬盘 
ES:BX＝缓冲区的地址 
出口参数：CF＝0——操作成功，AH＝00H，AL＝传输的扇区数，否则，AH＝状态代码，参见功能号01H中的说明 

####功能08H  
功能描述：读取驱动器参数 
入口参数：AH＝08H 
DL＝驱动器，00H~7FH：软盘；80H~0FFH：硬盘 
出口参数：CF＝1——操作失败，AH＝状态代码，参见功能号01H中的说明，否则，
BL  ＝01H — 360K 
    ＝02H — 1.2M 
    ＝03H — 720K 
    ＝04H — 1.44M 
CH＝柱面数的低8位 
CL的位7-6＝柱面数的高2位 
CL的位5-0＝扇区数 
DH＝磁头数 
DL＝驱动器数 
ES:DI＝磁盘驱动器参数表地址

####扩展功能（LBA模式）
http://blog.csdn.net/startexcel/article/details/8017113
数据结构：
.byte  16   //此数据结构的尺寸，必须为16
.byte  0     //保留
.word  ?    //传输的扇区数目
.int   ?    //内存缓冲区的地址（段：偏移，高两个字节段，低两个字节偏移）
.quad   ?   //LBA起始扇区号
扩展读的功能
  入口:AH＝42H
     DL＝驱动器号（硬盘是80H）
     DS:SI＝磁盘地址包（即前面的数据结构的地址）
  出口:成功则 CF＝0, AH＝0
     失败则 CF＝1, AH＝错误码

扩展写的功能
  入口:AH＝43H
     AL ＝0 (不校验)
       ＝1（校验）
     DL＝驱动器号
     DS：SI＝磁盘地址包
  出口:成功则 CF＝0, AH＝0
     失败则 CF＝1, AH＝错误码
   注：一般取AL＝0。

