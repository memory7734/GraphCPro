#include"Graph.h"
#include<iostream>
using namespace std;
void CGraph::Init(void)
{
	m_nVexNum = 0;							//������Ϊ0
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			m_aAdjMatrix[i][j] = 0;			//��ʼ������Ȩ��Ϊ0
}
int CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//��������
		return false;
	}
	m_aVexs[m_nVexNum++] = sVex;			//���붥��
	return m_nVexNum;
}
int CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		//�±�Խ��
		return false;
	}
	//����ߵ���Ϣ
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
		//�õ��ߵ���Ϣ
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
static int cnt = 0;//��¼�������·����
void CGraph::DFS(int nVex, bool bVisted[], int &nIndex, PathList &pList)
{
	bVisted[nVex] = true;				//��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;		//���ʶ���nVex
	if (nIndex == m_nVexNum)
	{
		//�����ǰ����������·��
		cout << "·��" << ++cnt << ":";
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
				bVisted[i] = false;		//�˻���һ����ָ�֮ǰ��Ϣ
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
	bool fin[MAX_VERTEX_NUM];		//�ѻ�����·��
	int dist[MAX_VERTEX_NUM];		//��nVexStart����ǰ�����̾���
	int prev[MAX_VERTEX_NUM];		//�洢��һ����
	//��ʼ������
	for (int i = 0; i < m_nVexNum; i++)
	{
		fin[i] = false;
		if (m_aAdjMatrix[nVexStart][i] != 0)
			dist[i] = m_aAdjMatrix[nVexStart][i];
		else
			dist[i] = INT_MAX;	//��û��·���ĵ���Ȩ��Ϊ����
		if (dist[i] == INT_MAX)
			prev[i] = -1;		
		else
			prev[i] = nVexStart;//����·��������һ����ΪnVexStart
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
				v = i;			//��ȡδ������·������Сֵ��
				min = dist[i];	//��ȡδ������·������Сֵ
			}
		}
		fin[v] = true;
		for (int i = 0; i < m_nVexNum; ++i)
			if ((!fin[i]) && (dist[v] + m_aAdjMatrix[v][i] < dist[i]) &&(m_aAdjMatrix[v][i]!=0))
			{
				dist[i] = dist[v] + m_aAdjMatrix[v][i];	//�������·��
				prev[i] = v;							//�洢��һ����
			}
	}
	int num = 0, last = nVexEnd;
	//��¼·���еı���
	while (prev[last] != nVexStart)
	{
		num++;
		last = prev[last];
	}
	last = nVexEnd;
	//����·����Ϣ
	while (num >= 0)
	{
		aPath[num].vex2 = last;
		aPath[num].vex1 = prev[last];
		aPath[num].weight = m_aAdjMatrix[last][prev[last]];
		last = prev[last];
		num--;
	}
	return dist[nVexEnd];		//�������·������
}
int CGraph::FindMinTree(Edge aPath[])
{
	int lowcost[MAX_VERTEX_NUM] = { 0 };	//��̾���
	bool addVexNew[MAX_VERTEX_NUM] = { true };//�ѻ����̾���ĵ�
	int prev[MAX_VERTEX_NUM] = { 0 };		//֮ǰ��
	int length = 0;
	//��ʼ�����鲢Ĭ����ʼ����Ϊ0��
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
			//����·����Ϣ
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //��v��Vnew��
			length += lowcost[v];                             //����·������֮��
			for (int i = 0; i<m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_aAdjMatrix[v][i]<lowcost[i]) && (m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_aAdjMatrix[v][i];                     //��ʱv�����Vnew ��Ҫ����lowcost
					prev[i] = v;										//�洢��һ����
				}
			}
		}
	}
	return length;
}