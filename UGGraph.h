
/*
	UGGraph.h
	Finished By XJ on 2019年5月1日17:24:51
*/

#pragma once
#include <fstream>
#include <iostream>
#include <set>

#ifndef NODE_H
#define NODE_H

#include "Node.h"

#endif

const int S = 295;	// 地铁站数量：294，作为已知项，默认 station[0] 不使用
const int R = 327;	// 站间数量：326，作为已知项，默认 route[0] 不使用
const int E = 51;	// 换乘站数量：50，作为已知项，默认 station_e[0] 不使用

class UGGraph {
public:
	UGGraph(std::ifstream& f_S, std::ifstream& f_A);		// 构造函数
	bool Validation(std::string start, std::string end);	// 检查输入地铁站名是否合法
	void Min_Route(std::string start, std::string end);		// 查找最短路径
	~UGGraph() {};											// 析构函数
private:
	VertexNode station[S];									// 地铁站
	VertexNode station_e[E];								// 换乘站
	ArcNode route[R];										// 站间距离
	double arcs[E][E];										// 任意两换乘站之间的最短距离
	int vNum, arcNum;										// 顶点数、边数
	double Disk[E];											// Disk[i] 记录起点到顶点 i 的路径长度
	int Path[E];											// Path[i] 记录起点到顶点 i 的路径
	VertexNode* Search_Station(std::string name);			// 查找站所在节点位置
	void Init_Station(std::ifstream& f_S);					// 初始化站点信息
	void Init_Arc(std::ifstream& f_A);						// 初始化弧信息
	VertexNode* Nearest_EX(VertexNode* vertex, double& dt);	// 寻找当前地铁站的最近换乘站
	int Search_EX_Station_Num(VertexNode* vertex);			// 查找当前站结点在换乘站表中的下标
	void Init_Arcs();										// 初始化换乘站的弧数组
	int FindMin(bool S[]);									// 在 Disk[1..n] 中寻找最小值
	void ShortPath(int s, int e);							// 寻找两换乘站间的最短路径
	string Search_Line(VertexNode A, VertexNode B);			// 寻找相邻两换乘站之间的地铁线
	void Print(string start, int s, string end, int e, double ds, double de);	// 打印路径
};