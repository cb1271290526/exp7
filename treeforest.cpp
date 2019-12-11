#include "tree_forest.h"

int main(void)
{
	while (true)
	{
		cout << "0.�˳�" << endl;
		cout << "1.�����򡢺��򡢲�α���ɭ��" << endl;
		cout << "2.��ɭ�ֵĸ߶�" << endl;
		cout << "3.��ɭ�ֽ������" << endl;
		cout << "4.��ɭ��Ҷ�ӽ����" << endl;
		cout << "5.��ɭ�ֵĶ�" << endl;
		cout << "6.����������ֵ�����κ�" << endl;
		cout << "7.���������ʾ����" << endl;

		int choice;
		csNode* T;  //������������
		pTree pT;  //��������ɭ�֣�
		cout << "������ѡ�" << endl;
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
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�
				Travel(T, 1);  //�������ɭ��
				Travel(T, 2);  //����
				Travel(T, 3);  //���

				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 2:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				int high = 0;
				high = forest_high(T);  //��ɭ�ָ߶�
				cout << "ɭ�ָ߶ȣ�" << high << "��" << endl;
				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				int Count = 0;
				Count = forest_count_node(T);  //��ɭ�ֽ����
				cout << "ɭ�ֽ������" << Count << "��" << endl;

				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 4:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				int leaf_num = 0;
				leaf_num = forest_count_leaf(T);  //��ɭ��Ҷ����
				cout << "ɭ��Ҷ������" << leaf_num << "��" << endl;

				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 5:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				int dot = 0;
				dot = forest_dot(T);
				cout << "ɭ�ֵĶ�����" << dot << endl;

				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 6:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				cout << '(' << "���ֵ," << "���" << ')' << endl;  //����������ֵ�����κ�
				forest_node_level(T, 1);
				cout << endl;

				forest_delete(T);  //ɾ��ɭ��
				system("pause");
				system("cls");
			}
			break;
		}
		case 7:
		{
			while (true)
			{
				//����˫�ױ�ʾ������ɭ�֣�
				if (Parent_tree_from_filedata(pT) == false)
					break;
				createCsTree(T, pT);  //�������������ʾ������ɭ�֣�

				cout << "������ʾ����" << endl;
				forest_general(T, 1); //���������ʾ����
				cout << endl;

				forest_delete(T);  //ɾ��ɭ��
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
