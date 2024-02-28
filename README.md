# 交通灯控制系统

## C51模拟交通灯信号控制

***导入hex文件请见目录***```C51/Objects/lights.hex```  
下载文件请见Release ~~(在界面右侧)~~

### 功能实现

- [x] 使用6个led模拟两个独立的交通灯三色信号
- [x] 使用4位数码管显示AB两灯的倒计时时间
- [x] 已按照题目要求完成交通灯的轮替循环  
~~精确显示倒计时~~  
~~模拟车流量，阈值触发~~  
~~行人按钮~~  
~~紧急按钮~~  

---

### 交通灯示意图

| **A_red** | **A_yellow** | **A_green** | **N/A** | **B_red** | **B_yellow** | **B_green** | **N/A** |
|:---------:|:------------:|:-----------:|:-------:|:---------:|:------------:|:-----------:|:-------:|
|    led1   |     led2     |     led3    |   led4  |    led5   |     led6     |     led7    |   led8  |

## ESP32控制交通灯信号

### 功能实现

- [x] 使用6个led模拟两个独立的交通灯三色信号
- [x] 使用4位数码管显示AB两灯的倒计时时间
- [x] 已按照题目要求完成交通灯的轮替循环
- [x] 精确显示倒计时
- [x] 模拟车流量，阈值触发
- [x] 行人按钮
- [x] 紧急按钮
