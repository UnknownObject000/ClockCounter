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
## Release使用说明
### 运行环境
 - 由于[Qt6.0开始不再支持Windows 7和Windows 8.x](https://www.qt.io/blog/qt6-development-hosts-and-targets)，此程序的Release版本只能在Windows 10/11系统下运行。
 - GUI绘制需要DirectX 12支持。
### 软件使用说明
 - 由于需要一次额外点击来转移窗口焦点，在设置预点击次数时需要多设置一次。（例如单击应设置为2次，双击为3次）
 - 右键单击【获取预点击坐标】按钮可以调出远程通信设置。
 - 远程通信时由客户端完成预点击，发送请求给服务端，由服务端计时。
 - 客户端通信启动时可能会导致程序崩溃，目前原因仍未查明。遇到此问题可以尝试再次启动程序，一般2-3次即可解决。
 - 远程通信使用时确保先开启服务端通信并重置服务端计时器，否则可能导致客户端无法与服务端建立连接或导致客户端崩溃。
