#include"Tourism.h"
#include"Graph.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static CGraph m_Graph;
int char2int(char* ch)
{
	int num = 0, i = 0, temp;
	while (true)
	{
		temp = (int)(ch[i] - '0');
		if (temp >= 0 && temp < 10)
		{
			num *= 10;
			num += temp;
		}
		else
			return num;
		i++;
	}
	
}
bool CreateGraph(void)
{
	cout << "==== 创建景区景点图 ====" << endl;
	char buffer[20];
	fstream inVex ;
	inVex.open("Vex.txt", ios::in);
	fstream inEdge;
	inEdge.open("Edge.txt", ios::in);
	inVex.getline(buffer, 3, '\n');
	int vexNum = (int)(buffer[0] - '0');
	cout << "项目顶点数：" << vexNum << endl;
	Vex vex;
	m_Graph.Init();
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		inVex.getline(buffer, 3, '\n');
		vex.num = (int)(buffer[0] - '0');
		inVex.getline(vex.name, 20, '\n');
		inVex.getline(vex.desc, 1024, '\n');
		m_Graph.InsertVex(vex);
		cout << vex.num << "-" << vex.name << endl;
	}
	Edge edge; 
	cout << "----- 边 -----" << endl;
	while (inEdge.good())
	{
		inEdge.getline(buffer, 20, '\n');
		char* p = strtok(buffer," \n");
		edge.vex1 = char2int(p);
		p = strtok(NULL, " \n");
		edge.vex2 = char2int(p);
		p = strtok(NULL, " \n");
		edge.weight = char2int(p);
		m_Graph.InsertEdge(edge);
		cout <<"<v"<< edge.vex1 << ",v" << edge.vex2 <<"> "<< edge.weight << endl;
	}
	inVex.close();
	inEdge.close();
	return true;
}
void GetSpotInfo(void)
{
	cout << "==== 查询景点信息 ====" << endl;
	Vex vex;
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "请输入想要查询的景点编号：";
	int nVex;
	cin >> nVex;
	vex = m_Graph.GetVex(nVex);
	cout << vex.name << endl;
	cout << vex.desc << endl;
	cout << "----- 周边景区 -----" << endl;
	Edge edge[20];
	int edgenum=m_Graph.FindEdge(nVex, edge);
	for (int i = 0; i < edgenum; i++)
	{
		cout <<char( 'A' + nVex) << "区->" <<char( 'A' + edge[i].vex2 )<< "区 " << edge[i].weight << "m" << endl;
	}
}
