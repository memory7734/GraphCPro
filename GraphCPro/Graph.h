#pragma once
#define MAX_VERTEX_NUM 20
struct Vex
{
	int num;			//������
	char name[20];		//��������
	char desc[1024];	//�������
};
struct Edge
{
	int vex1;			//�ߵĵ�һ������
	int vex2;			//�ߵĵڶ�������
	int weight;			//Ȩֵ
};
typedef struct Path
{
	int vexs[20];			//����һ��·��
	Path *next=nullptr;		//��һ��·��
} *PathList;
class CGraph
{
private:
	int m_aAdjMatrix[20][20];										//�ڽӾ���
	Vex m_aVexs[20];												//������Ϣ����
	int m_nVexNum;													//��ǰͼ�Ķ������
public:
	void Init(void);												//��ʼ��ͼ�ṹ
	int InsertVex(Vex sVex);										//�����㱣�浽�ڽӾ���
	int InsertEdge(Edge sEdge);										//���߱��浽�ڽӾ���
	Vex GetVex(int nVex);											//��ѯָ��������Ϣ
	int FindEdge(int nVex, Edge aEdge[]);							//��ѯ��ָ�����������ı�
	int GetVexnum(void);											//��ȡ��ǰ������
	void DFS(int nVex, bool bVisted[],int &nIndex,PathList &pList);	//�����������
	void DFSTraverse(int nVex, PathList &pList);					//���������������
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);	//Ѱ����������·��
	int FindMinTree(Edge aPath[]);									//Ѱ����С������
};


