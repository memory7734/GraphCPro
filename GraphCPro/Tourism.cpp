#include"Tourism.h"
#include"Graph.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static CGraph m_Graph;
bool CreateGraph(void)
{
	cout << "==== ������������ͼ ====" << endl;
	char buffer[20];
	fstream inVex ;
	inVex.open("Vex.txt", ios::in);		//��Vex�ĵ�
	fstream inEdge;
	inEdge.open("Edge.txt", ios::in);	//��Edge�ĵ�
	inVex.getline(buffer, 3, '\n');		//�����һ�ж�����
	int vexNum = atoi(buffer);
	cout << "��Ŀ��������" << vexNum << endl;
	Vex vex;
	m_Graph.Init();
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < vexNum; i++)
	{
		inVex.getline(buffer, 3, '\n');		//���붥����
		vex.num = atoi(buffer);
		inVex.getline(vex.name, 20, '\n');	//���붥����
		inVex.getline(vex.desc, 1024, '\n');//���붥������
		m_Graph.InsertVex(vex);				//���붥��
		cout << vex.num << "-" << vex.name << endl;
	}
	Edge edge; 
	cout << "----- �� -----" << endl;
	while (inEdge.good())
	{
		inEdge.getline(buffer, sizeof(buffer), '\n');//�������Ϣ
		char* p = strtok(buffer," \n");
		edge.vex1 = atoi(p);				//�����һ������
		p = strtok(NULL, " \n");
		edge.vex2 = atoi(p);				//����ڶ�������
		p = strtok(NULL, " \n");
		edge.weight = atoi(p);				//����Ȩ��
		m_Graph.InsertEdge(edge);			//�����
		cout <<"<v"<< edge.vex1 << ",v" << edge.vex2 <<"> "<< edge.weight << endl;
	}
	inVex.close();							//�ر���
	inEdge.close();
	return true;
}
void GetSpotInfo(void)
{
	cout << "==== ��ѯ������Ϣ ====" << endl;
	Vex vex;
	//���ÿ��������Ϣ�����
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int nVex;
	cin >> nVex;
	vex = m_Graph.GetVex(nVex);
	cout << vex.name << endl;
	cout << vex.desc << endl;
	cout << "----- �ܱ߾��� -----" << endl;
	Edge edge[20];
	//����붥����صı�
	int edgenum=m_Graph.FindEdge(nVex, edge);
	for (int i = 0; i < edgenum; i++)
	{
		cout <<char( 'A' + nVex) << "��->" <<char( 'A' + edge[i].vex2 )<< "�� " << edge[i].weight << "m" << endl;
	}
}
void TravelPath(void)
{
	cout << "==== ���ξ��㵼�� ====" << endl;
	Vex vex;
	//���ÿ��������Ϣ�����
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	cout << "��������ʼ���ţ�";
	int beginNum;
	cin >> beginNum;
	PathList pList = (PathList)malloc(sizeof(Path));
	cout << "����·��Ϊ��" << endl;
	m_Graph.DFSTraverse(beginNum, pList);
}
void FindShortPath(void)
{
	cout << "==== �������·�� ====" << endl;
	Vex vex;
	//���ÿ��������Ϣ�����
	for (int i = 0; i < m_Graph.GetVexnum(); i++)
	{
		vex = m_Graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	int nVexStart, nVexEnd;
	cout << "���������ı�ţ�";
	cin >> nVexStart;
	cout << "�������յ�ı�ţ�";
	cin >> nVexEnd;
	Edge aPath[MAX_VERTEX_NUM];
	int shortPath=m_Graph.FindShortPath(nVexStart, nVexEnd, aPath);
	cout << "���·��Ϊ��" ;
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
	cout << "��̾���Ϊ��" << shortPath << endl;
}
void DesignPath(void)
{
	cout << "==== �����·���� ====" << endl;
	cout << "��������������֮�������·��" << endl;
	Edge aPath[MAX_VERTEX_NUM];
	int length = m_Graph.FindMinTree(aPath);
	for (int i = 0; (i < m_Graph.GetVexnum()) && (aPath[i].vex1 != aPath[i].vex2); i++)
	{
		cout << m_Graph.GetVex(aPath[i].vex1).name << " - " << m_Graph.GetVex(aPath[i].vex2).name << "   " << aPath[i].weight << "m" << endl;
	}
	cout << "�����·���ܳ���Ϊ��" << length << endl;
}