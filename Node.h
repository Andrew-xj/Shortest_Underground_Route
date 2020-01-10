
/*
	Node.h
	Finished By XJ on 2019��4��30��23:09:37
*/

#pragma once
#include <iostream>

struct ArcNode;

struct VertexNode {				// ����վ
	std::string name;			// վ����
	ArcNode* line[6];			// ǰ���ͺ�̻�����
	int r;						// ��ǰվ�㻡��������
	int exchange;				// �Ƿ񻻳�
};

struct ArcNode {				// �����
	VertexNode *start, *end;	// ���˵���վ
	double distance;			// վ�����(km)
	std::string line;			// ��������
};