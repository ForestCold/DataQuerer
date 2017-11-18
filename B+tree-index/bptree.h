#pragma once
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <fstream>
#include "MyIndex.h"
#include "stdafx.h"

using namespace std;

#define T 3			//b+树的度数
#define KeyType string
#define Pointer int
//节点结构体
typedef struct BPNode
{
	unsigned int id;//记录这个节点在文件的中的编号
	unsigned int n;	//记录这个节点有多少个关键字
	int leaf;		//判断是否为页节点
	KeyType key[2*T];//关键字（及对应每个孩子节点的中关键字最小的关键字）
	Pointer child[2*T];//指针，记录每个孩子在文件的第几个位置
	Pointer next;//指针，，记录下一个兄弟
	Pointer buff[2*T];//指针，记录在文件中的位置
//	Pointer dup[2*T];	//重复key的下一个节点
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

//树的结构体
typedef struct BPTree
{
	P_BPNode root;
	unsigned int locate;//记录根节点的在文件中的标号，即id
	unsigned int num;	//记录共有多少个节点
	char name[100];		//用于存储B+树的节点文件的名字
	FILE *fp;			//打开写入name文件时，使用
	int start;		//最小的数据所在的叶节点
}BPTree,*P_BPTree;


extern BPTree indexBPTree;		//全局变量，b+树


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