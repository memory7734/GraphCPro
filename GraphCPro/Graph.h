#pragma once
#define MAX_VERTEX_NUM 20
struct Vex
{
	int num;			//景点编号
	char name[20];		//景点名字
	char desc[1024];	//景点介绍
};
struct Edge
{
	int vex1;			//边的第一个顶点
	int vex2;			//边的第二个顶点
	int weight;			//权值
};
class CGraph
{
private:
	int m_aAdjMatrix[20][20];		//邻接矩阵
	Vex m_aVexs[20];				//顶点信息数组
	int m_nVexNum;					//当前图的顶点个数
public:
	void Init(void);						//初始化图结构
	int InsertVex(Vex sVex);				//将顶点保存到邻接矩阵
	int InsertEdge(Edge sEdge);			//将边保存到邻接矩阵
	Vex GetVex(int nVex);					//查询指定顶点信息
	int FindEdge(int nVex, Edge aEdge[]);	//查询与指定顶点相连的边
	int GetVexnum(void);					//获取当前顶点数
};


