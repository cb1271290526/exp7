#ifndef  _TREE_FOREST_H_
#define  _TREE_FOREST_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

constexpr auto MAXLEN = 100;
typedef char datatype;
using namespace std;

/*双亲表示的树（森林）定义、算法开始----------------------------------------------*/

typedef struct pNode
{
	datatype data;  //结点数据域
	int parent;  //父结点指针（下标）

}pTnode;  //双亲表示的树（森林）结点结构

typedef struct pTree
{
	pTnode node[MAXLEN];  //结点数组
	int n;  //结点总数
}pTree;  //双亲表示的树（森林）

/*函数声明----------------------------------------------------------------------*/
void Parent_tree_initial(pTree& pT);  			//初始化
void skip_line(ifstream& file, string& line);	//跳过空行注释行
bool Parent_tree_from_filedata(pTree& pT);		//文本数据录入，构建双亲表示的树（森林）
void Parent_delspace(string& str);				//删除左边空格
/*-----------------------------------------------------------------------------*/

//初始化
void Parent_tree_initial(pTree& pT)  //初始化
{
	pT.n = 0;
	cout << "双亲表示初始化成功..." << endl;
}

//跳过空行注释行
void skip_line(ifstream& file, string& line)
{
	//跳过空行、注释行
	while ((bool)getline(file, line) != false)
	{
		if (line.empty() || line.find("//") != string::npos)
			continue;
		else
			return ;  //非注释行、非空行，跳出循环
	}
	cout << "文件数据出错" << endl;
	file.close();
}

//删除左边空格
void Parent_delspace(string& str)
{
	if (str.empty())
		return ;
    str.erase(0, str.find_first_not_of(" "));
}

//文本数据录入，构建双亲表示的树（森林）
bool Parent_tree_from_filedata(pTree& pT)  //文本数据录入，构建双亲表示的树（森林）
{
	string filename;
	cout << "请输入文件名（#退出）：";
	cin >> filename;
	if (filename == "#")
		return false;
	filename = "D:\\OneDrive\\code\\DS\\exp7\\tData\\" + filename;

	ifstream file(filename);
	string line;
	if (!file)
	{
		cout << "文件打开失败..."<<endl;
		system("pause");
		return false;
	}
	Parent_tree_initial(pT);

	skip_line(file, line);  //跳过

	//检验文本格式
	while(true)
	{
		if ( line.find("Tree or Forest") == string::npos)  //跳过空行、注释行等 
		{
			if (file.peek() == EOF)
			{
				cout << "文本错误" << endl;
				file.close();
				system("pause");
				return false;			
			}
			getline(file, line);
		}
		else
			break;
	}

	skip_line(file, line);  //跳过空行、注释行

	//将结点数据存入树的结点数组
	if (file.peek() != EOF)
	{
		int length;
		length = line.length();
		Parent_delspace(line);
		for (int i = 0; i < length; i++)
		{
			if (line[i] == ' ' || !((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')))  //空格及其他非法符跳过
				continue;
			pT.node[pT.n].data = line[i];
			pT.node[pT.n].parent = -1;  //父结点指针初始化为-1
			pT.n++;
		}
	}

	//循环读取边（父子队）数据
	int np, nc;
	datatype Nf, Ns;
	while (file.peek() != EOF)
	{
		string::size_type index;
		getline(file, line);
		if (line.empty() || line.find("//") != string::npos)  //跳过空行、注释行
			continue;
		Parent_delspace(line);
		index = line.find(" ");

		if (index == string::npos ||
			index == 0 ||
			line[index - 1] == ' ' ||
			line[index - 1] == ' ')
		{
			cout << "边数据错误" << endl;
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

/*双亲表示的树（森林）定义、算法结束------------------------------------------------------------------*/



/*二叉链表表示的树（森林）定义、算法开始--------------------------------------------------------------*/

typedef struct csNode
{
	datatype data;
	struct csNode* firstChild;
	struct csNode* nextSibling;
}csNode;  //二叉链表表示的树（森林）结点结构

typedef struct Queue
{
	csNode* Q;
	Queue* next;
}Queue;  //存储森林结点的队

typedef struct
{
	Queue* front;
	Queue* rear;
}Qpointer;  //队头尾指针

/*函数声明---------------------------------------------------------------------------------------------*/
void csinitial(csNode*& T);						//初始化
int firstChild(pTree& pT, int v);		 		//搜索下标为v的结点的第一个孩子结点下标
int next(pTree pT, int w);  					//搜索双亲表示中，下标w的下一个兄弟结点，返回兄弟结点的下标
void create(csNode*& T, pTree& pT, int v);		//递归创建一棵孩子兄弟链表表示的树
void createCsTree(csNode*& T, pTree pT);		//从双亲表示的树（森林）创建孩子兄弟链表表示的树（森林）
void forest_delete(csNode*& T);					//删除森林
void preTravel(csNode*& T);						//先序遍历森林
void postTravel(csNode*& T);					//后序遍历森林

/*森林所用队构建算法及层次遍历算法---------------------------------------------------------------------*/
void Queue_initial(Qpointer*& Qp);					//队初始化
bool Queue_empty(Qpointer*& Qp);					//判断队空
void Queue_enter(Qpointer*& Qp, csNode* cp);		//入队
void Queue_out(Qpointer*& Qp);						//出队
void Queue_front(Qpointer*& Qp, csNode*& cp);		//取队头指针
void Queue_delete(Qpointer*& Qp);					//销毁队
void levelTravel(csNode*& T);						//层次遍历
/*森林所用队构建算法及层次遍历算法---------------------------------------------------------------------*/

void Travel(csNode*& T, int choice);			//遍历函数集合
int forest_high(csNode*& T);					//求森林的高度
int forest_count_node(csNode*& T);				//求森林结点数
int forest_count_leaf(csNode*& T);				//求森林叶子数
int forest_dot(csNode*& T, int tag);			//求森林的度
void forest_node_level(csNode*& T, int level);	//先序输出结点值及其层次号
bool judge(csNode*& T);							//判断结点是否同时具有子结点和兄弟结点
void forest_general(csNode*& T, int tag);		//输出广义表表示的树
/*-----------------------------------------------------------------------------------------------------*/

void csinitial(csNode*& T)
{
	T = NULL;
}

//搜索下标为v的结点的第一个孩子结点下标
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

//搜索双亲表示中，下标w的下一个兄弟结点，返回兄弟结点的下标
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

//递归创建一棵孩子兄弟链表表示的树
void create(csNode*& T, pTree& pT, int v)
{
	int w;
	T = new csNode;
	T->data = pT.node[v].data;
	T->firstChild = NULL;
	T->nextSibling = NULL;
	w = firstChild(pT, v);  //搜索v的第一个孩子结点
	if (w != -1)
		create(T->firstChild, pT, w);
	w = next(pT, v);       //搜索v的下一个兄弟结点
	if (w != -1)
		create(T->nextSibling, pT, w);
}

//从双亲表示的树（森林）创建孩子兄弟链表表示的树（森林）
void createCsTree(csNode*& T, pTree pT)
{
	int i;
	csinitial(T);

	//搜索T1的第一个根结点
	for (i = 0; i < pT.n; i++)
	{
		if (pT.node[i].parent == -1)   //找到第一个根结点
			break;
	}
	if (i < pT.n)
		create(T, pT, i);
}

//删除森林
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

//先序遍历森林
void preTravel(csNode*& T)
{
	if (T != NULL)
	{
		cout << T->data << " ";
		preTravel(T->firstChild);
		preTravel(T->nextSibling);
	}
}

//后序遍历森林
void postTravel(csNode*& T)
{
	if (T != NULL)
	{
		postTravel(T->firstChild);
		cout << T->data << " ";
		postTravel(T->nextSibling);
	}
}


/*森林所用队构建算法及层次遍历算法开始---------------------------------------------------------------------*/

//队初始化
void Queue_initial(Qpointer*& Qp)
{
	Qp = new Qpointer;
	Qp->front = NULL;
	Qp->rear = NULL;
}

//判断队空
bool Queue_empty(Qpointer*& Qp)
{
	if (Qp->front == NULL && Qp->rear == NULL)
		return true;
	else
		return false;
}

//入队
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

//出队
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

//取队头指针
void Queue_front(Qpointer*& Qp, csNode*& cp)
{
	if (!Queue_empty(Qp))
	{
		cp = Qp->front->Q;
	}
	else
		cp = NULL;
}

//销毁队
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

//层次遍历森林（利用队）
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

/*森林所用队构建算法及层次遍历算法结束-----------------------------------------------------------------*/


//遍历函数集合
void Travel(csNode*& T, int choice)
{
	switch (choice)
	{
		case 1:
		{
			cout << "先序遍历森林" << endl;
			preTravel(T);
			cout<<endl;
			break;
		}
		case 2:
		{
			cout << "后序遍历森林" << endl;
			postTravel(T);
			cout<<endl;
			break;
		}
		case 3:
		{
			cout << "层次遍历森林" << endl;
			levelTravel(T);
			cout<<endl;
		}
	}
}

//求森林的高度
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

//求森林结点数
int forest_count_node(csNode*& T)
{
	int Count = 0;
	if (T != NULL)
	{
		Count = forest_count_node(T->firstChild);  //算出子森林结点数
		Count = Count + forest_count_node(T->nextSibling);  //加上同层结点森林结点数
		Count++;  //加上自身结点
	}
	return Count;
}

//求森林叶子数
int forest_count_leaf(csNode*& T)
{
	int leaf_num = 0;
	if (T != NULL)
	{
		leaf_num = forest_count_leaf(T->firstChild);  //算出子树的叶子数
		leaf_num = leaf_num + forest_count_leaf(T->nextSibling);  //加上同层结点树叶子数
		if (T->firstChild == NULL)  //无孩子结点，叶子数+1
			leaf_num++;
	}
	return leaf_num;
}

//求森林的度
int forest_dot(csNode*& T, int tag)  //tag初始值为0，当tag为0时代表当前结点是根结点
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
			dot = dot + forest_dot(T->nextSibling, tag) + tag;  //子树度数加上兄弟结点树度数
		}
	}
	return dot;
}

//先序输出结点值及其层次号
void forest_node_level(csNode*& T, int level)
{
	if (T != NULL)
	{
		cout << "(" << T->data << "," << level << "), ";
		forest_node_level(T->firstChild, level + 1);  //子结点为二叉链表父结点下一层
		forest_node_level(T->nextSibling, level);  //兄弟结点与二叉链表父结点同层
	}
}

//判断结点是否同时具有子结点和兄弟结点
bool judge(csNode*& T)
{
	if (T != NULL)
	{
		if (T->firstChild != NULL && T->nextSibling != NULL)
			return true;
	}
	return false;
}

//广义树 
void forest_general(csNode*& T, int tag)  //tag给初值1，0代表第一个子结点，1代表兄弟结点
{
	if (T != NULL)
	{
		if (T->firstChild != NULL || tag == 0)  //结点有子结点或结点为第一个子结点则将其打包
			cout << "(";
		cout << T->data;
		if (T->firstChild != NULL)  //输出子森林结点
		{
			cout << ",";
			if (judge(T->firstChild) == true)  //若是第一个子结点有子结点和兄弟结点则该结点和兄弟结点要打包
				cout << "(";
			forest_general(T->firstChild, 0);
			if (judge(T->firstChild) == true)  //第一个子结点有子结点和兄弟结点需要的“）”
				cout << ")";
			cout << ")";  //有子结点必要的“）”
		}	
		if (T->nextSibling != NULL)  //输出同层结点森林
		{
			cout << ", ";
			forest_general(T->nextSibling, 1);
		}
		if (T->firstChild == NULL && tag == 0)  //打包第一个无子的子结点及其兄弟结点
			cout << ")";
	}
}

/*二叉链表表示的树（森林）定义、算法结束-------------------------------------------------------------*/

#endif
