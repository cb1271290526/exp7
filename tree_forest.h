#ifndef  _TREE_FOREST_H_
#define  _TREE_FOREST_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

constexpr auto MAXLEN = 100;
typedef char datatype;
using namespace std;

/*˫�ױ�ʾ������ɭ�֣����塢�㷨��ʼ----------------------------------------------*/

typedef struct pNode
{
	datatype data;  //���������
	int parent;  //�����ָ�루�±꣩

}pTnode;  //˫�ױ�ʾ������ɭ�֣����ṹ

typedef struct pTree
{
	pTnode node[MAXLEN];  //�������
	int n;  //�������
}pTree;  //˫�ױ�ʾ������ɭ�֣�

/*��������----------------------------------------------------------------------*/
void Parent_tree_initial(pTree& pT);  			//��ʼ��
void skip_line(ifstream& file, string& line);	//��������ע����
bool Parent_tree_from_filedata(pTree& pT);		//�ı�����¼�룬����˫�ױ�ʾ������ɭ�֣�
void Parent_delspace(string& str);				//ɾ����߿ո�
/*-----------------------------------------------------------------------------*/

//��ʼ��
void Parent_tree_initial(pTree& pT)  //��ʼ��
{
	pT.n = 0;
	cout << "˫�ױ�ʾ��ʼ���ɹ�..." << endl;
}

//��������ע����
void skip_line(ifstream& file, string& line)
{
	//�������С�ע����
	while ((bool)getline(file, line) != false)
	{
		if (line.empty() || line.find("//") != string::npos)
			continue;
		else
			return ;  //��ע���С��ǿ��У�����ѭ��
	}
	cout << "�ļ����ݳ���" << endl;
	file.close();
}

//ɾ����߿ո�
void Parent_delspace(string& str)
{
	if (str.empty())
		return ;
    str.erase(0, str.find_first_not_of(" "));
}

//�ı�����¼�룬����˫�ױ�ʾ������ɭ�֣�
bool Parent_tree_from_filedata(pTree& pT)  //�ı�����¼�룬����˫�ױ�ʾ������ɭ�֣�
{
	string filename;
	cout << "�������ļ�����#�˳�����";
	cin >> filename;
	if (filename == "#")
		return false;
	filename = "D:\\OneDrive\\code\\DS\\exp7\\tData\\" + filename;

	ifstream file(filename);
	string line;
	if (!file)
	{
		cout << "�ļ���ʧ��..."<<endl;
		system("pause");
		return false;
	}
	Parent_tree_initial(pT);

	skip_line(file, line);  //����

	//�����ı���ʽ
	while(true)
	{
		if ( line.find("Tree or Forest") == string::npos)  //�������С�ע���е� 
		{
			if (file.peek() == EOF)
			{
				cout << "�ı�����" << endl;
				file.close();
				system("pause");
				return false;			
			}
			getline(file, line);
		}
		else
			break;
	}

	skip_line(file, line);  //�������С�ע����

	//��������ݴ������Ľ������
	if (file.peek() != EOF)
	{
		int length;
		length = line.length();
		Parent_delspace(line);
		for (int i = 0; i < length; i++)
		{
			if (line[i] == ' ' || !((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')))  //�ո������Ƿ�������
				continue;
			pT.node[pT.n].data = line[i];
			pT.node[pT.n].parent = -1;  //�����ָ���ʼ��Ϊ-1
			pT.n++;
		}
	}

	//ѭ����ȡ�ߣ����Ӷӣ�����
	int np, nc;
	datatype Nf, Ns;
	while (file.peek() != EOF)
	{
		string::size_type index;
		getline(file, line);
		if (line.empty() || line.find("//") != string::npos)  //�������С�ע����
			continue;
		Parent_delspace(line);
		index = line.find(" ");

		if (index == string::npos ||
			index == 0 ||
			line[index - 1] == ' ' ||
			line[index - 1] == ' ')
		{
			cout << "�����ݴ���" << endl;
			file.close();
			system("pause");
			return false;
		}
		else
		{
			Nf = line[index - 1];
			Ns = line[index + 1];
			cout << Nf << " ";
			cout << Ns << endl;
		}

		for (np = 0; np < pT.n; np++)
		{
			if (pT.node[np].data == Nf)
				break;
		}
		for (nc = 0; nc < pT.n; nc++)
		{
			if (pT.node[nc].data == Ns)
				break;
		}
		pT.node[nc].parent = np;
	}

	file.close();
	return true;
}

/*˫�ױ�ʾ������ɭ�֣����塢�㷨����------------------------------------------------------------------*/



/*���������ʾ������ɭ�֣����塢�㷨��ʼ--------------------------------------------------------------*/

typedef struct csNode
{
	datatype data;
	struct csNode* firstChild;
	struct csNode* nextSibling;
}csNode;  //���������ʾ������ɭ�֣����ṹ

typedef struct Queue
{
	csNode* Q;
	Queue* next;
}Queue;  //�洢ɭ�ֽ��Ķ�

typedef struct
{
	Queue* front;
	Queue* rear;
}Qpointer;  //��ͷβָ��

/*��������---------------------------------------------------------------------------------------------*/
void csinitial(csNode*& T);						//��ʼ��
int firstChild(pTree& pT, int v);		 		//�����±�Ϊv�Ľ��ĵ�һ�����ӽ���±�
int next(pTree pT, int w);  					//����˫�ױ�ʾ�У��±�w����һ���ֵܽ�㣬�����ֵܽ����±�
void create(csNode*& T, pTree& pT, int v);		//�ݹ鴴��һ�ú����ֵ������ʾ����
void createCsTree(csNode*& T, pTree pT);		//��˫�ױ�ʾ������ɭ�֣����������ֵ������ʾ������ɭ�֣�
void forest_delete(csNode*& T);					//ɾ��ɭ��
void preTravel(csNode*& T);						//�������ɭ��
void postTravel(csNode*& T);					//�������ɭ��

/*ɭ�����öӹ����㷨����α����㷨---------------------------------------------------------------------*/
void Queue_initial(Qpointer*& Qp);					//�ӳ�ʼ��
bool Queue_empty(Qpointer*& Qp);					//�ж϶ӿ�
void Queue_enter(Qpointer*& Qp, csNode* cp);		//���
void Queue_out(Qpointer*& Qp);						//����
void Queue_front(Qpointer*& Qp, csNode*& cp);		//ȡ��ͷָ��
void Queue_delete(Qpointer*& Qp);					//���ٶ�
void levelTravel(csNode*& T);						//��α���
/*ɭ�����öӹ����㷨����α����㷨---------------------------------------------------------------------*/

void Travel(csNode*& T, int choice);			//������������
int forest_high(csNode*& T);					//��ɭ�ֵĸ߶�
int forest_count_node(csNode*& T);				//��ɭ�ֽ����
int forest_count_leaf(csNode*& T);				//��ɭ��Ҷ����
int forest_dot(csNode*& T, int tag);			//��ɭ�ֵĶ�
void forest_node_level(csNode*& T, int level);	//����������ֵ�����κ�
bool judge(csNode*& T);							//�жϽ���Ƿ�ͬʱ�����ӽ����ֵܽ��
void forest_general(csNode*& T, int tag);		//���������ʾ����
/*-----------------------------------------------------------------------------------------------------*/

void csinitial(csNode*& T)
{
	T = NULL;
}

//�����±�Ϊv�Ľ��ĵ�һ�����ӽ���±�
int firstChild(pTree& pT, int v)
{
	int w;
	if (v == -1)
		return -1;
	for (w = 0; w < pT.n; w++)
	{
		if (pT.node[w].parent == v)
			return w;
	}
	return -1;
}

//����˫�ױ�ʾ�У��±�w����һ���ֵܽ�㣬�����ֵܽ����±�
int next(pTree pT, int w)
{
	int i;
	for (i = w + 1; i < pT.n; i++)
	{
		if (pT.node[w].parent == pT.node[i].parent)
			return i;
	}
	return -1;
}

//�ݹ鴴��һ�ú����ֵ������ʾ����
void create(csNode*& T, pTree& pT, int v)
{
	int w;
	T = new csNode;
	T->data = pT.node[v].data;
	T->firstChild = NULL;
	T->nextSibling = NULL;
	w = firstChild(pT, v);  //����v�ĵ�һ�����ӽ��
	if (w != -1)
		create(T->firstChild, pT, w);
	w = next(pT, v);       //����v����һ���ֵܽ��
	if (w != -1)
		create(T->nextSibling, pT, w);
}

//��˫�ױ�ʾ������ɭ�֣����������ֵ������ʾ������ɭ�֣�
void createCsTree(csNode*& T, pTree pT)
{
	int i;
	csinitial(T);

	//����T1�ĵ�һ�������
	for (i = 0; i < pT.n; i++)
	{
		if (pT.node[i].parent == -1)   //�ҵ���һ�������
			break;
	}
	if (i < pT.n)
		create(T, pT, i);
}

//ɾ��ɭ��
void forest_delete(csNode*& T)
{
	if (T != NULL)
	{
		forest_delete(T->firstChild);
		forest_delete(T->nextSibling);
		delete T;
		T = NULL;
	}
}

//�������ɭ��
void preTravel(csNode*& T)
{
	if (T != NULL)
	{
		cout << T->data << " ";
		preTravel(T->firstChild);
		preTravel(T->nextSibling);
	}
}

//�������ɭ��
void postTravel(csNode*& T)
{
	if (T != NULL)
	{
		postTravel(T->firstChild);
		cout << T->data << " ";
		postTravel(T->nextSibling);
	}
}


/*ɭ�����öӹ����㷨����α����㷨��ʼ---------------------------------------------------------------------*/

//�ӳ�ʼ��
void Queue_initial(Qpointer*& Qp)
{
	Qp = new Qpointer;
	Qp->front = NULL;
	Qp->rear = NULL;
}

//�ж϶ӿ�
bool Queue_empty(Qpointer*& Qp)
{
	if (Qp->front == NULL && Qp->rear == NULL)
		return true;
	else
		return false;
}

//���
void Queue_enter(Qpointer*& Qp,  csNode* cp)
{
	if (cp == NULL)
		return;
	Queue* r;
	r = new Queue;
	r->Q = cp;
	if (Qp->front == NULL)
	{
		Qp->front = r;
		Qp->rear = r;
		Qp->rear->next = NULL;
	}
	else
	{
		r->next = Qp->rear->next;
		Qp->rear->next = r;
		Qp->rear = Qp->rear->next;
	}
}

//����
void Queue_out(Qpointer*& Qp)
{
	if (!Queue_empty(Qp))
	{
		Queue* f;
		f = Qp->front;
		Qp->front = Qp->front->next;
		if (Qp->front == NULL)
			Qp->rear = Qp->front;
		delete f;
	}
}

//ȡ��ͷָ��
void Queue_front(Qpointer*& Qp, csNode*& cp)
{
	if (!Queue_empty(Qp))
	{
		cp = Qp->front->Q;
	}
	else
		cp = NULL;
}

//���ٶ�
void Queue_delete(Qpointer*& Qp)
{
	while (Qp != NULL && Qp->front != NULL)
	{
		Qp->rear = Qp->front->next;
		delete Qp->front;
		Qp->front = Qp->rear;
	}
	if (Qp != NULL)
	{
		delete Qp;
		Qp = NULL;
	}
}

//��α���ɭ�֣����öӣ�
void levelTravel(csNode*& T)
{
	if (T == NULL)
	{
		return ;
	}
	csNode* cp;
	Qpointer* Qp;
	Queue_initial(Qp);
	cp = T;
	do
	{
		while (cp != NULL)
		{
			Queue_enter(Qp, cp);
			cp = cp->nextSibling;
		}
		if (Queue_empty(Qp))
			break;
		Queue_front(Qp, cp);
		Queue_out(Qp);
		cout << cp->data << " ";
		cp = cp->firstChild;
	}while (true);
	Queue_delete(Qp);
}

/*ɭ�����öӹ����㷨����α����㷨����-----------------------------------------------------------------*/


//������������
void Travel(csNode*& T, int choice)
{
	switch (choice)
	{
		case 1:
		{
			cout << "�������ɭ��" << endl;
			preTravel(T);
			cout<<endl;
			break;
		}
		case 2:
		{
			cout << "�������ɭ��" << endl;
			postTravel(T);
			cout<<endl;
			break;
		}
		case 3:
		{
			cout << "��α���ɭ��" << endl;
			levelTravel(T);
			cout<<endl;
		}
	}
}

//��ɭ�ֵĸ߶�
int forest_high(csNode*& T)
{
	int h1 = 0;
	int h2 = 0;
	if (T != NULL)
	{
		h1 = forest_high(T->firstChild);
		if(T->firstChild != NULL)
			h2 = forest_high(T->firstChild->nextSibling);
		if (h1 > h2)
			return h1 + 1;
		else
			return h2 + 1;
	}
	return h1;
}

//��ɭ�ֽ����
int forest_count_node(csNode*& T)
{
	int Count = 0;
	if (T != NULL)
	{
		Count = forest_count_node(T->firstChild);  //�����ɭ�ֽ����
		Count = Count + forest_count_node(T->nextSibling);  //����ͬ����ɭ�ֽ����
		Count++;  //����������
	}
	return Count;
}

//��ɭ��Ҷ����
int forest_count_leaf(csNode*& T)
{
	int leaf_num = 0;
	if (T != NULL)
	{
		leaf_num = forest_count_leaf(T->firstChild);  //���������Ҷ����
		leaf_num = leaf_num + forest_count_leaf(T->nextSibling);  //����ͬ������Ҷ����
		if (T->firstChild == NULL)  //�޺��ӽ�㣬Ҷ����+1
			leaf_num++;
	}
	return leaf_num;
}

//��ɭ�ֵĶ�
int forest_dot(csNode*& T, int tag)  //tag��ʼֵΪ0����tagΪ0ʱ����ǰ����Ǹ����
{
	int dot = 0;
	if (T != NULL)
	{
		if (T->firstChild != NULL)
		{
			dot = forest_dot(T->firstChild, 1) + 1;
		}
		if (T->nextSibling != NULL)
		{
			dot = dot + forest_dot(T->nextSibling, tag) + tag;  //�������������ֵܽ��������
		}
	}
	return dot;
}

//����������ֵ�����κ�
void forest_node_level(csNode*& T, int level)
{
	if (T != NULL)
	{
		cout << "(" << T->data << "," << level << "), ";
		forest_node_level(T->firstChild, level + 1);  //�ӽ��Ϊ�������������һ��
		forest_node_level(T->nextSibling, level);  //�ֵܽ��������������ͬ��
	}
}

//�жϽ���Ƿ�ͬʱ�����ӽ����ֵܽ��
bool judge(csNode*& T)
{
	if (T != NULL)
	{
		if (T->firstChild != NULL && T->nextSibling != NULL)
			return true;
	}
	return false;
}

//������ 
void forest_general(csNode*& T, int tag)  //tag����ֵ1��0�����һ���ӽ�㣬1�����ֵܽ��
{
	if (T != NULL)
	{
		if (T->firstChild != NULL || tag == 0)  //������ӽ�����Ϊ��һ���ӽ��������
			cout << "(";
		cout << T->data;
		if (T->firstChild != NULL)  //�����ɭ�ֽ��
		{
			cout << ",";
			if (judge(T->firstChild) == true)  //���ǵ�һ���ӽ�����ӽ����ֵܽ����ý����ֵܽ��Ҫ���
				cout << "(";
			forest_general(T->firstChild, 0);
			if (judge(T->firstChild) == true)  //��һ���ӽ�����ӽ����ֵܽ����Ҫ�ġ�����
				cout << ")";
			cout << ")";  //���ӽ���Ҫ�ġ�����
		}	
		if (T->nextSibling != NULL)  //���ͬ����ɭ��
		{
			cout << ", ";
			forest_general(T->nextSibling, 1);
		}
		if (T->firstChild == NULL && tag == 0)  //�����һ�����ӵ��ӽ�㼰���ֵܽ��
			cout << ")";
	}
}

/*���������ʾ������ɭ�֣����塢�㷨����-------------------------------------------------------------*/

#endif
