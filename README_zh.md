FOS( Fast Operating System )
==========
[![Build Status](https://secure.travis-ci.org/php/php-src.png?branch=master)](https://travis-ci.org/dreamflyforever/fos)

FOS是一款全新的开源实时操作系统(RTOS)。支持优先级抢占，FIFO(先进先出)，RR（时间片轮)
三种调度算法。

它具备高度轻便可移植性(移植到不同的硬件平台)，代码清晰，模块化，低耦合，可读性强。
同时也适用于硬件资源非常紧缺的情况，可以裁剪内核为FSM(有限状态机),仅仅200B的内存
占用空间。

由于FOS底层对接了LINUX的用户栈，线程切换接口，心跳定时器，网络/dev/tap,用户可以在
linux平台上直接运行FOS，单步调试FOS，可以很方便清楚的看到FOS的线程调度，锁使用的具
体情况，极度高效学习操作系统原理。

---------------------------------------------------------------------------

**快速搭建**  
下载源码到linux平台，直接make，不需要任何库依赖，FOS还支持scons的构建方式，可以直接
执行scons(系统需要安装scons)，生成的fos就可以直接运行，因为用到了linux的NAT方式，执
行fos时候用sudo最高执行权限。所以只要系统支持make和gcc，就可以运行FOS。

---------------------------------------------------------------------------

**源码结构**

 * kernel                   :      内核代码，包括线程管理，信号量，互斥锁，任务调度算法, 定时器，消息队列，设备管理, 内存管理, 事件驱动管理
 * app                      :      用户层逻辑代码
 * cpu                      :      芯片移植代码，包括线程栈，任务切换，定时器，中断，数据类型
 * libc                     :      基本的C库
 * middleware               :      组建，包括key-value存储，shell命令行，UIP网络协议
 * SConstruct and config.py :      构建系统工具
 * start_or1ksim.sh         :      or1ksim芯片模拟器运行

---------------------------------------------------------------------------

**文档**  
[文档中心](https://blog.csdn.net/oYangShanJin)

---------------------------------------------------------------------------

**贡献**  
杨善锦(Jim) 

License: GPL. 

任何问题欢迎联系 <1150660744@qq.com> or 微信 : dreamflyforever.