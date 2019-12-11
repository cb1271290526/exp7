#include "tree_forest.h"

int main(void)
{
	while (true)
	{
		cout << "0.退出" << endl;
		cout << "1.按先序、后序、层次遍历森林" << endl;
		cout << "2.求森林的高度" << endl;
		cout << "3.求森林结点总数" << endl;
		cout << "4.求森林叶子结点数" << endl;
		cout << "5.求森林的度" << endl;
		cout << "6.先序输出结点值及其层次号" << endl;
		cout << "7.输出广义表表示的树" << endl;

		int choice;
		csNode* T;  //二叉链表根结点
		pTree pT;  //数组树（森林）
		cout << "请输入选项：" << endl;
		cin >> choice;
		cin.sync();
		system("cls");
		switch (choice)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）
				Travel(T, 1);  //先序遍历森林
				Travel(T, 2);  //后序
				Travel(T, 3);  //层次

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 2:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				int high = 0;
				high = forest_high(T);  //求森林高度
				cout << "森林高度：" << high << "层" << endl;
				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				int Count = 0;
				Count = forest_count_node(T);  //求森林结点数
				cout << "森林结点数：" << Count << "个" << endl;

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 4:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				int leaf_num = 0;
				leaf_num = forest_count_leaf(T);  //求森林叶子数
				cout << "森林叶子数：" << leaf_num << "个" << endl;

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 5:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				int dot = 0;
				dot = forest_dot(T);
				cout << "森林的度数：" << dot << endl;

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 6:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				cout << '(' << "结点值," << "层次" << ')' << endl;  //先序输出结点值及其层次号
				forest_node_level(T, 1);
				cout << endl;

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		case 7:
		{
			while (true)
			{
				//创建双亲表示的树（森林）
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //创建二叉链表表示的树（森林）

				cout << "广义表表示的树" << endl;
				forest_general(T, 1); //输出广义表表示的树
				cout << endl;

				forest_delete(T);  //删除森林
				system("pause");
				system("cls");
			}
			break;
		}
		default:break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}
