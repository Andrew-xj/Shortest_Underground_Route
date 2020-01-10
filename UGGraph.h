
/*
	UGGraph.h
	Finished By XJ on 2019��5��1��17:24:51
*/

#pragma once
#include <fstream>
#include <iostream>
#include <set>

#ifndef NODE_H
#define NODE_H

#include "Node.h"

#endif

const int S = 295;	// ����վ������294����Ϊ��֪�Ĭ�� station[0] ��ʹ��
const int R = 327;	// վ��������326����Ϊ��֪�Ĭ�� route[0] ��ʹ��
const int E = 51;	// ����վ������50����Ϊ��֪�Ĭ�� station_e[0] ��ʹ��

class UGGraph {
public:
	UGGraph(std::ifstream& f_S, std::ifstream& f_A);		// ���캯��
	bool Validation(std::string start, std::string end);	// ����������վ���Ƿ�Ϸ�
	void Min_Route(std::string start, std::string end);		// �������·��
	~UGGraph() {};											// ��������
private:
	VertexNode station[S];									// ����վ
	VertexNode station_e[E];								// ����վ
	ArcNode route[R];										// վ�����
	double arcs[E][E];										// ����������վ֮�����̾���
	int vNum, arcNum;										// ������������
	double Disk[E];											// Disk[i] ��¼��㵽���� i ��·������
	int Path[E];											// Path[i] ��¼��㵽���� i ��·��
	VertexNode* Search_Station(std::string name);			// ����վ���ڽڵ�λ��
	void Init_Station(std::ifstream& f_S);					// ��ʼ��վ����Ϣ
	void Init_Arc(std::ifstream& f_A);						// ��ʼ������Ϣ
	VertexNode* Nearest_EX(VertexNode* vertex, double& dt);	// Ѱ�ҵ�ǰ����վ���������վ
	int Search_EX_Station_Num(VertexNode* vertex);			// ���ҵ�ǰվ����ڻ���վ���е��±�
	void Init_Arcs();										// ��ʼ������վ�Ļ�����
	int FindMin(bool S[]);									// �� Disk[1..n] ��Ѱ����Сֵ
	void ShortPath(int s, int e);							// Ѱ��������վ������·��
	string Search_Line(VertexNode A, VertexNode B);			// Ѱ������������վ֮��ĵ�����
	void Print(string start, int s, string end, int e, double ds, double de);	// ��ӡ·��
};