
/*
	UGGraph.cpp
	Finished By XJ on 2019年5月1日17:24:51
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef UGGRAPH_H
#define UGGRAPH_H

#include "UGGraph.h"

#endif

const int MAX_EX_STATION = 15;
const int MAX_EX_P = 10;
const double MAX = 1000000;

UGGraph::UGGraph(ifstream & f_S, ifstream & f_A)
{
	// 初始化类
	vNum = arcNum = 0;
	Init_Station(f_S);
	Init_Arc(f_A);
	Init_Arcs();
}

bool UGGraph::Validation(std::string start, std::string end)
{
	// 保存线路数据
	bool s = false, e = false;
	for (int i = 1; i < S; i++) {
		if (station[i].name == start) s = true;
		if (station[i].name == end) e = true;
	}
	return s && e;
}

void UGGraph::Min_Route(std::string start, std::string end)
{
	// 寻找离 start 最近的换乘站
	double ds, de;
	VertexNode* vs = Nearest_EX(Search_Station(start), ds);
	VertexNode* ve = Nearest_EX(Search_Station(end), de);
	int s = Search_EX_Station_Num(vs), e = Search_EX_Station_Num(ve);
	ShortPath(s, e);
	Print(start, s, end, e, ds, de);
}

VertexNode * UGGraph::Search_Station(string name)
{
	for (int i = 1; i < S; i++) {						// 遍历所有地铁站，找到直接返回
		if (station[i].name == name) return &station[i];
	}
}

void UGGraph::Init_Station(ifstream & f_S)
{
	string name;
	int a;
	int i = 0;
	while (!f_S.eof()) {							// 初始化 地铁站 和 换乘站 信息
		f_S >> name >> a;
		station[++vNum].name = name;
		station[vNum].r = 0;
		station[vNum].exchange = a;
		if (a == 1) {
			station_e[++i].name = name;
			station_e[i].r = 0;
			station_e[i].exchange = a;
		}
	}
	f_S.close();
}

void UGGraph::Init_Arc(ifstream & f_A)
{
	string start, end, line;						// 开始站，结束站，地铁线路
	double distance;
	while (!f_A.eof()) {							// 初始化 站间弧结点 信息
		f_A >> line >> start >> end >> distance;
		distance /= 1000;
		route[++arcNum].distance = distance;
		VertexNode* s = Search_Station(start);
		VertexNode* e = Search_Station(end);
		route[arcNum].start = s;
		route[arcNum].end = e;
		route[arcNum].line = line;
		(*s).line[(*s).r++] = (&route[arcNum]);
		(*e).line[(*e).r++] = (&route[arcNum]);
	}
	f_A.close();
}

VertexNode * UGGraph::Nearest_EX(VertexNode* vertex, double& dt)
{
	if (vertex->exchange == 0) {
		// 查找所在地铁线的第一个换乘站，并存入数组 ex_station[]
		VertexNode* ex_station[6], *temp;
		int num = 0, i = 0, j;
		double distance = 0, distance_s[6], distance_min = MAX;
		while (i < (*vertex).r) {
			// 遍历一条起点线
			j = i;
			temp = vertex;
			if (temp->line[i]->start->name == temp->name) {
				while ((num - 1 != i) && (temp->line[j]->end->r != 1)) {
					if ((temp->line[j]->line == vertex->line[i]->line) && (temp->line[j]->start->name == temp->name)) {
						distance += temp->line[j]->distance;
						temp = temp->line[j]->end;
						if (temp->exchange == 1) {		// 若 temp 为换乘站，存入换乘站数组
							ex_station[num] = temp;
							distance_s[num++] = distance;
							if (distance_min > distance) {
								distance_min = distance;
							}
						}
						j = 0;
					}
					else
						j++;
				}
				distance = 0;
			}
			else {
				while ((num - 1 != i) && (temp->line[j]->start->r != 1)) {
					if ((temp->line[j]->line == vertex->line[i]->line) && temp->line[j]->end->name == temp->name) {
						distance += temp->line[j]->distance;
						temp = temp->line[j]->start;
						if (temp->exchange == 1) {		// 若 temp 为换乘站，存入换乘站数组
							ex_station[num] = temp;
							distance_s[num++] = distance;
							if (distance_min > distance) {
								distance_min = distance;
							}
						}
						j = 0;
					}
					else
						j++;
				}
				distance = 0;
			}
			i++;
		}
		for (i = num - 1; distance_s[i] != distance_min; i--);
		dt = distance_min;
		return ex_station[i];
	}
	dt = 0;
	return vertex;
}

int UGGraph::Search_EX_Station_Num(VertexNode * vertex)
{
	int i = E - 1;
	for (; station_e[i].name != vertex->name; i--);
	return i;
}

void UGGraph::Init_Arcs()
{
	ArcNode temp = route[0];
	int i, j, s = 0, e = 0;
	double distance = 0;
	string line;
	for (i = 0; i < E; i++) {		// 初始化辅助数组
		for (j = 0; j < E; j++) {
			arcs[i][j] = MAX;
		}
		Disk[i] = MAX;
	}
	i = 1;
	line = route[i].line;
	while (i < R) {
		if (route[i].line == line) {		// 是否在同一条地铁线上
			if ((route[i].start->exchange == 1) && (s == 0)) {		// 该条地铁线第一个换乘站
				s = Search_EX_Station_Num(route[i].start);
				distance = 0;
			}
			else if (route[i].end->exchange == 1) {					// 该条地铁线下一个换乘站
				distance += route[i].distance;
				e = Search_EX_Station_Num(route[i].end);
				arcs[s][e] = distance;								// 标记相邻弧之间的距离
				distance = 0;										// 归零
				s = e;												// 当前结束换乘站改为开始换乘站
				i++;												// 继续寻找该条地铁线下一个换乘站
			}
			else {													// 下一站不是换乘站
				distance += route[i].distance;
				i++;
			}
		}
		else {
			line = route[i].line;
			s = 0; e = 0;
		}
	}
}

int UGGraph::FindMin(bool S[])
{
	// 寻找两换乘站最短路径
	int k = 0;
	double min = MAX;
	for (int i = 0; i < E; i++) {
		if ((!S[i]) && (min > Disk[i])) {
			min = Disk[i];
			k = i;
		}
	}
	if (min == MAX)return -1;
	return k;
}

// 修改版迪杰特斯拉算法
void UGGraph::ShortPath(int s, int e)
{
	bool S[E];		// 判断是否找到最短路径
	int i = 0;
	for (; i < E; i++) {		// 初始化辅助数组
		S[i] = false;
		Disk[i] = arcs[s][i];
		if (Disk[i] != MAX) Path[i] = s;
		else Path[i] = -1;		// 无前驱
	}

	S[s] = true;
	Disk[s] = 0;				// 初始化 s 起点 ∈ S

	for (i = 0; i < E; i++) {
		if ((s = FindMin(S)) == -1)		// 寻找离 V0 最近的顶点
			return;
		S[s] = true;
		for (int j = 0; j < E; j++) {		// 更新辅助数组
			if (!S[j] && (Disk[j] > arcs[s][j] + Disk[s])) {
				Disk[j] = arcs[s][j] + Disk[s];
				Path[j] = s;
			}
		}
		if (s == e)return;
	}
}

string UGGraph::Search_Line(VertexNode A, VertexNode B)
{
	for (int i = 0; i < A.r; i += 2) {
		for (int j = 0; j < B.r; j += 2) {
			if (A.line[i]->line == B.line[j]->line) {
				return A.line[i]->line;
			}
		}
	}
}

void UGGraph::Print(string start, int s, string end, int e, double ds, double de)
{
	double distance;
	string middle = "", line;
	VertexNode* here = Search_Station(start);
	VertexNode* there = Search_Station(end);
	distance = Disk[e] + ds + de;
	cout << "从 " << start << " 到 " << end << " 最短地铁路径为：" << endl;
	// 输出起点到第一个换乘站
	if (start != station_e[s].name) {
		cout << here->name << " → （ " << here->line[0]->line << " ) → " << station_e[s].name << endl;
	}
	// 输出中间的换乘站
	int pre = Path[e];
	middle = station_e[pre].name +" → （ " + there->line[0]->line + " ) → " + station_e[e].name + '\n' + middle;
	while (pre != -1) {
		if (Path[pre] != -1) {
			line = Search_Line(station[Path[pre]], station[pre]);
			middle = station_e[Path[pre]].name + " → （ " + line + " ) → " + station_e[pre].name + '\n' + middle;
		}
		pre = Path[pre];
	}
	cout << middle;
	// 输出最后一个换乘站到终点
	if (end != station_e[e].name) {
		cout << station_e[e].name << " → （ " << there->line[0]->line << " ) → " << there->name << endl;
	}
	cout << "全程共约 " << distance << " KM" << endl;
}
