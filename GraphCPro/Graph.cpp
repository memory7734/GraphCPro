#include"Graph.h"
#include<iostream>
using namespace std;
void CGraph::Init(void)
{
	m_nVexNum = 0;							//顶点数为0
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			m_aAdjMatrix[i][j] = 0;			//初始化所有权重为0
}
int CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return false;
	}
	m_aVexs[m_nVexNum++] = sVex;			//插入顶点
	return m_nVexNum;
}
int CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		//下标越界
		return false;
	}
	//插入边的信息
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}
Vex CGraph::GetVex(int nVex)
{
	return m_aVexs[nVex];
}
int CGraph::FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		//得到边的消息
		if (m_aAdjMatrix[nVex][i] != 0)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_aAdjMatrix[nVex][i];
			k++;
		}
	}
	return k;
}
int CGraph::GetVexnum(void)
{
	return m_nVexNum;
}
static int cnt = 0;//记录已输出的路径数
void CGraph::DFS(int nVex, bool bVisted[], int &nIndex, PathList &pList)
{
	bVisted[nVex] = true;				//改为已访问
	pList->vexs[nIndex++] = nVex;		//访问顶点nVex
	if (nIndex == m_nVexNum)
	{
		//输出当前满足条件的路线
		cout << "路线" << ++cnt << ":";
		for (int i = 0; i < this->GetVexnum(); i++) {
			cout << this->GetVex(pList->vexs[i]).name;
			if (i < this->GetVexnum() - 1)
				cout << "->";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_nVexNum; i++)
		{
			if ((m_aAdjMatrix[nVex][i] != 0) && (!bVisted[i]))
			{
				DFS(i, bVisted, nIndex, pList);
				bVisted[i] = false;		//退回上一顶点恢复之前信息
				nIndex--;
			}
		}
	}	
}
void CGraph::DFSTraverse(int nVex, PathList &pList)
{
	int nIndex = 0;
	bool bVisted[MAX_VERTEX_NUM] = { false };
	DFS(nVex, bVisted, nIndex,pList);
}
int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	bool fin[MAX_VERTEX_NUM];		//已获得最短路径
	int dist[MAX_VERTEX_NUM];		//从nVexStart到当前点的最短距离
	int prev[MAX_VERTEX_NUM];		//存储上一个点
	//初始化数据
	for (int i = 0; i < m_nVexNum; i++)
	{
		fin[i] = false;
		if (m_aAdjMatrix[nVexStart][i] != 0)
			dist[i] = m_aAdjMatrix[nVexStart][i];
		else
			dist[i] = INT_MAX;	//将没有路径的点设权重为无穷
		if (dist[i] == INT_MAX)
			prev[i] = -1;		
		else
			prev[i] = nVexStart;//已有路径设置上一个点为nVexStart
	}
	fin[nVexStart] = true;
	dist[nVexStart] = 0;
	prev[nVexStart] = nVexStart;
	for (int p = 0; p < m_nVexNum-1; p++)
	{
		int v=nVexStart;
		int min = INT_MAX;
		for (int i = 0; i < m_nVexNum; ++i)
		{
			if ((!fin[i]) && (dist[i]<min))
			{
				v = i;			//获取未获得最短路径的最小值点
				min = dist[i];	//获取未获得最短路径的最小值
			}
		}
		fin[v] = true;
		for (int i = 0; i < m_nVexNum; ++i)
			if ((!fin[i]) && (dist[v] + m_aAdjMatrix[v][i] < dist[i]) &&(m_aAdjMatrix[v][i]!=0))
			{
				dist[i] = dist[v] + m_aAdjMatrix[v][i];	//更新最短路径
				prev[i] = v;							//存储上一个点
			}
	}
	int num = 0, last = nVexEnd;
	//记录路径中的边数
	while (prev[last] != nVexStart)
	{
		num++;
		last = prev[last];
	}
	last = nVexEnd;
	//保存路径信息
	while (num >= 0)
	{
		aPath[num].vex2 = last;
		aPath[num].vex1 = prev[last];
		aPath[num].weight = m_aAdjMatrix[last][prev[last]];
		last = prev[last];
		num--;
	}
	return dist[nVexEnd];		//返回最短路径距离
}
int CGraph::FindMinTree(Edge aPath[])
{
	int lowcost[MAX_VERTEX_NUM] = { 0 };	//最短距离
	bool addVexNew[MAX_VERTEX_NUM] = { true };//已获得最短距离的点
	int prev[MAX_VERTEX_NUM] = { 0 };		//之前点
	int length = 0;
	//初始化数组并默认起始顶点为0点
	for (int i = 1; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[0][i] != 0)
			lowcost[i] = m_aAdjMatrix[0][i];
		else
			lowcost[i] = INT_MAX;
		addVexNew[i] = false;
	}
	for (int p = 0;p< m_nVexNum-1; p++)
	{
		int min = INT_MAX;
		int v = 0;
		for (int i = 1; i < m_nVexNum; i++)
		{
			if ((!addVexNew[i]) && lowcost[i] < min)
			{
				min = lowcost[i];
				v = i;
			}
		}
		if (v != 0)
		{
			//保存路径信息
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //将v加Vnew中
			length += lowcost[v];                             //计算路径长度之和
			for (int i = 0; i<m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_aAdjMatrix[v][i]<lowcost[i]) && (m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_aAdjMatrix[v][i];                     //此时v点加入Vnew 需要更新lowcost
					prev[i] = v;										//存储上一个点
				}
			}
		}
	}
	return length;
}