#pragma once
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <fstream>
#include "MyIndex.h"
#include "stdafx.h"

using namespace std;

#define T 3			//b+���Ķ���
#define KeyType string
#define Pointer int
//�ڵ�ṹ��
typedef struct BPNode
{
	unsigned int id;//��¼����ڵ����ļ����еı��
	unsigned int n;	//��¼����ڵ��ж��ٸ��ؼ���
	int leaf;		//�ж��Ƿ�Ϊҳ�ڵ�
	KeyType key[2*T];//�ؼ��֣�����Ӧÿ�����ӽڵ���йؼ�����С�Ĺؼ��֣�
	Pointer child[2*T];//ָ�룬��¼ÿ���������ļ��ĵڼ���λ��
	Pointer next;//ָ�룬����¼��һ���ֵ�
	Pointer buff[2*T];//ָ�룬��¼���ļ��е�λ��
//	Pointer dup[2*T];	//�ظ�key����һ���ڵ�
	BPNode()
	{
		id=0;
		n=0;
		leaf=0;
		for(int i=0;i<2*T;++i)
		{
			key[i]=" ";
		}
	}
}BPNode,*P_BPNode;

//���Ľṹ��
typedef struct BPTree
{
	P_BPNode root;
	unsigned int locate;//��¼���ڵ�����ļ��еı�ţ���id
	unsigned int num;	//��¼���ж��ٸ��ڵ�
	char name[100];		//���ڴ洢B+���Ľڵ��ļ�������
	FILE *fp;			//��д��name�ļ�ʱ��ʹ��
	int start;		//��С���������ڵ�Ҷ�ڵ�
}BPTree,*P_BPTree;


extern BPTree indexBPTree;		//ȫ�ֱ�����b+��


int writeNode(P_BPNode w);
int readNode(P_BPNode r, Pointer id);
int pNode(P_BPNode n);
int createIndexBPTree (char *tableName, char *attr);
int splitBPNode (P_BPNode p, P_BPNode c, int i);
int insertBPNodeNotFull(P_BPNode s, KeyType k, unsigned int id,Pointer infilepos);
Pointer equalSearch(P_BPTree tree, KeyType k);//,Pointer* i_f=0);
int rangeSearch (P_BPTree tree, KeyType low, KeyType high);
int insertKeyInBPTree (P_BPTree tree, KeyType k, Pointer id,Pointer _infile);
int initIndexBPTree(char *tableName, char *attr);
int endBPTree();
int pNode(P_BPNode n);
int replaceKeyInBPTree(P_BPTree tree, KeyType oldkey, KeyType newkey);
int adjustToDel(P_BPNode p, P_BPNode x, unsigned int i);
KeyType delKeyInBPNode(P_BPNode p, KeyType k);
int delKeyInBPTree(P_BPTree tree, KeyType k);
Pointer result_equalSearch(P_BPTree tree, KeyType k);
int result_pNode(Pointer tmpadd,string &Myresult,string *filePath);