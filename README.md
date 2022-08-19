# ClockCounter
一个带有预点击功能和远程通信功能的计时器程序，可以提供相对准确的【某个程序/功能】运行时间的计时功能
## 使用到的开源项目
 - ACI通信接口服务器基于 [Webcc](https://github.com/sprinfall/webcc) 制作
 - ACI通信接口客户端基于 [libcurl](https://github.com/curl/curl) 制作
 - LCD数字GUI库来源于 [QWidgetDemo](https://github.com/feiyangqingyun/QWidgetDemo)
 - JSON数据解析库 [JsonCPP](https://github.com/open-source-parsers/jsoncpp)
## 编译环境
 - Qt6.3.1
 - Visual Studio 2022
 - Qt VS Tools 2.9.1
## 编译流程
 1. 安装所需依赖库
```c++
vcpkg install jsoncpp libcurl
```
 2. 打开解决方案文件（.sln），生成
 3. 下载本项目Release中的quc.dll文件，与编译出的可执行文件放在一起
