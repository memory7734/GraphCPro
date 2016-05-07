#include"Tourism.h"
#include"Graph.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static CGraph m_Graph;
bool CreateGraph(void)
{
	cout << "==== 创建景区景点图 ====" << endl;
	char buffer[20];
	fstream inVex ;
	inVex.open("Vex.txt", ios::in);		//打开Vex文档
	fstream inEdge;
	inEdge.open("Edge.txt", ios::in);	//打开Edge文档
	inVex.getline(buffer, 3, '\n');		//读入第一行顶点数
	int vexNum = atoi(buffer);
	cout << "项目顶点数：" << vexNum << endl;
	Vex vex;
	m_Graph.Init();
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		inVex.getline(buffer, 3, '\n');		//读入顶点编号
		vex.num = atoi(buffer);
		inVex.getline(vex.name, 20, '\n');	//读入顶点名
		inVex.getline(vex.desc, 1024, '\n');//读入顶点描述
		m_Graph.InsertVex(vex);				//插入顶点
		cout << vex.num << "-" << vex.name << endl;
	}
	Edge edge; 
	cout << "----- 边 -----" << endl;
	while (inEdge.good())
	{
		inEdge.getline(buffer, sizeof(buffer), '\n');//读入边信息
		char* p = strtok(buffer," \n");
		edge.vex1 = atoi(p);				//读入第一个顶点
		p = strtok(NULL, " \n");
		edge.vex2 = atoi(p);				//读入第二个顶点
		p = strtok(NULL, " \n");
		edge.weight = atoi(p);				//读入权重
		m_Graph.InsertEdge(edge);			//插入边
		cout <<"<v"<< edge.vex1 << ",v" << edge.vex2 <<"> "<< edge.weight << endl;
	}
	inVex.close();							//关闭流
	inEdge.close();
	return true;
}
void GetSpotInfo(void)
{
	cout << "==== 查询景点信息 ====" << endl;
	Vex vex;
	//获得每个顶点信息并输出
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
	//获得与顶点相关的边
	int edgenum=m_Graph.FindEdge(nVex, edge);
	for (int i = 0; i < edgenum; i++)
	{
		cout <<char( 'A' + nVex) << "区->" <<char( 'A' + edge[i].vex2 )<< "区 " << edge[i].weight << "m" << endl;
	}
}
void TravelPath(void)
{
	cout << "==== 旅游景点导航 ====" << endl;
	Vex vex;
	//获得每个顶点信息并输出
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "请输入起始点编号：";
	int beginNum;
	cin >> beginNum;
	PathList pList = (PathList)malloc(sizeof(Path));
	cout << "导游路线为：" << endl;
	m_Graph.DFSTraverse(beginNum, pList);
}
void FindShortPath(void)
{
	cout << "==== 搜索最短路径 ====" << endl;
	Vex vex;
	//获得每个顶点信息并输出
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	int nVexStart, nVexEnd;
	cout << "请输入起点的编号：";
	cin >> nVexStart;
	cout << "请输入终点的编号：";
	cin >> nVexEnd;
	Edge aPath[MAX_VERTEX_NUM];
	int shortPath=m_Graph.FindShortPath(nVexStart, nVexEnd, aPath);
	cout << "最短路线为：" ;
	int i = 0;
	while (i< m_Graph.GetVexnum())
	{
		if (aPath[i].vex1 != aPath[i].vex2)
			cout << m_Graph.GetVex(aPath[i].vex1).name << "->";
		else
		{
			cout << m_Graph.GetVex(aPath[i-1].vex2).name << endl;
			break;
		}
		i++;
	}
	cout << "最短距离为：" << shortPath << endl;
}
void DesignPath(void)
{
	cout << "==== 铺设电路规则 ====" << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	Edge aPath[MAX_VERTEX_NUM];
	int length = m_Graph.FindMinTree(aPath);
	for (int i = 0; (i < m_Graph.GetVexnum()) && (aPath[i].vex1 != aPath[i].vex2); i++)
	{
		cout << m_Graph.GetVex(aPath[i].vex1).name << " - " << m_Graph.GetVex(aPath[i].vex2).name << "   " << aPath[i].weight << "m" << endl;
	}
	cout << "铺设电路的总长度为：" << length << endl;
}