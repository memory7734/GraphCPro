#include"Graph.h"
void CGraph::Init(void)
{
	//CGraph myCGraph =  CGraph();
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			m_aAdjMatrix[i][j] = 0;
	m_nVexNum = 0;
}
int CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return false;
	}
	m_aVexs[m_nVexNum++] = sVex; 
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
