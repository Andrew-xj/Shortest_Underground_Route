
/*
	Node.h
	Finished By XJ on 2019年4月30日23:09:37
*/

#pragma once
#include <iostream>

struct ArcNode;

struct VertexNode {				// 地铁站
	std::string name;			// 站点名
	ArcNode* line[6];			// 前驱和后继弧数组
	int r;						// 当前站点弧结点的数量
	int exchange;				// 是否换乘
};

struct ArcNode {				// 弧结点
	VertexNode *start, *end;	// 两端地铁站
	double distance;			// 站间距离(km)
	std::string line;			// 地铁线名
};