
/*
	main.cpp
	Finished By XJ on 2019年5月1日22:26:31
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

int main()
{
	// 生成文件指针
	ifstream f_S("Exchanging_Station(vertex).txt");
	ifstream f_A("Beijing_Underground(arc).txt");
	UGGraph UGNetwork(f_S, f_A);
	string choice;
	// 交互窗口
	do {
		cout << "请按照如下格式输入地铁站名称：起点站 终点站" << endl;
		string start, end;
		cin >> start >> end;
		if (UGNetwork.Validation(start, end)) {		// 输入异常判断
			UGNetwork.Min_Route(start, end);
		}
		else {
			cout << "是否重新输入？是：请输入 1；否则，默认退出程序。" << endl;
			cin >> choice;
			if (choice != "1") {
				break;
			}
		}
		cout << endl;
	} while (1);
}
