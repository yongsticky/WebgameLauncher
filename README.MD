页游通用的微端登录器
框架使用WTL+GIDPLUS+TINYXML
实现了一个小型的DirectUI界面引擎，使用Window+Control+Event+Action来搭建系统。
win32系统相关的封装在win32component，也可以自行扩展。
界面使用XML进行layout配置，事件通过XML里添加Action来进行响应
Window、Control、Event、Action都可以通过C++层面的代码来进行扩展，内置了一些常用的。
Test下面，扩展了一些Action和Control，可以作为扩展的参考代码。
作为使用系统代码，Test实现了一个游戏微端登录器。


