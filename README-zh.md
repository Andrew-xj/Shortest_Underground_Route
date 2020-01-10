地铁最短路径查找
===============================

## 其他语言：

README  [英文](https://github.com/Andrew-xj/Shortest_Underground_Route/tree/master) | 中文

## 项目介绍：

本项目是基于经典迪杰特斯拉最短路径算法用C++实现的地铁网最短路径查找程序，该项目用于完成本科课程实验。

## 项目特点：

本项目将地铁站和站间距等数据分别放在两个txt文件中（以本项目为例："Beijing_Underground(arc).txt" 和 "Exchanging_Station(vertex).txt"），只需更改文件中对应数据，即可生成各地不同的地铁网。程序运行过程中，地铁网自动构建，只需输入“始发站”和“终点站”，即可完成线路查找。

## 目录结构描述：

├── README.md                           // 英文 help

├── README-zh.md                        // 中文 help

├── Shortest Underground Route.cpp      // 主程序

├── pch.h                               // 预编译头文件

├── pch.cpp

├── Node.h                              // 结点类头文件

├── UGGraph.h                           // 地铁网头文件

├── UGGraph.cpp                         // 地铁网源文件

├── Beijing_Underground(arc).txt        // 地铁站间距离数据（弧数据）

├── Exchanging_Station(vertex).txt      // 地铁站数据（结点数据）

## 环境依赖：

无

## 部署步骤：

直接在CMD中运行“Shortest Underground Route.cpp”即可。
