#include "bptree.h"
#include "stdafx.h"

const int FILE_NUM=20+10;
extern BPTree indexBPTree;		//全局变量，b+树
//extern string filePath[FILE_NUM];



int result_pNode(Pointer tmpadd,string &Myresult,string *filePath)
{//输出节点
//	int tmpadd= n->buff[0];
	int fno=tmpadd/100000;
	int fadd=tmpadd%100000;
//	char* b;
	string fname=filePath[fno];
//	cout<<fname<<endl;
/*	FILE* hand=fopen(fname.c_str(),"r");
	for(int i=0;i<fadd;++i)
	{
		fgets(b,1024,hand);
	}
	cout<<b<<endl;
	puts("");
*/
	ifstream in;
	in.open(fname); 
	//if(!in.is_open())cout<<"open fail\n";
	string a,e,p,ar,y;
	for(int i=0;i<=fadd;++i)
	{
		in>>a>>e>>p>>ar>>y;
	}
	//cout<<"地址："<<a<<"\n小区："<<e<<"\n价格："<<p<<"\n面积："<<ar<<"\n建筑年代："<<y<<endl;
	Myresult=a+" "+e+" "+p+" "+ar+" "+y;
	return 0;
}//pNode

Pointer result_equalSearch(P_BPTree tree, KeyType k)//,Pointer* i_f=0)
{//等值查询，给出key值，查找对应的id，并返回。如果不存在该节点，返回一个负数
	int i;
	int result;
	P_BPNode r;
	r = tree->root;
//	cout<<k<<' '<<r->key[0]<<endl;
	if (k < r->key[0])	//比最小的节点小
		return -1;
	P_BPNode tmp = new BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			tmp->key[kk]=" ";
		}
	while (1)
	{
		i = r->n - 1;
		while (i >= 0 && r->key[i] > k)
			i--;

		if (r->leaf)	//是叶子，结束
			break;
		readNode(tmp, r->child[i]);
		r = tmp;
	}//while

	if (r->key[i] < k)
		return -1;
//	result = r->child[i];
	/*new*/
//	*(i_f)=r->buff[i];
	/*newend*/
	
//	delete(tmp);
	result=r->buff[i];
	tmp = NULL;
	return result;
}

int pNode(P_BPNode n);

int createIndexBPTree (char *tableName, char *attr)
{//创建B+树,并进行相应的初始化，B+树的结构体是一个全局变量。
	P_BPNode root;
	indexBPTree.root = &(BPNode());
	indexBPTree.num = 1;
	indexBPTree.start = 1;
	memcpy(indexBPTree.name, "dataset\\", sizeof("dataset\\"));
	strcat(indexBPTree.name, tableName);
	strcat(indexBPTree.name, ".");
	strcat(indexBPTree.name, attr);
	puts(indexBPTree.name);
	root = indexBPTree.root; 
	
	root->n = 0;
	root->leaf = 1;
	root->next = -1;
	root->id = 1;
	for(int kk=0;kk<2*T;++kk)
		{
			(root->key)[kk]=" ";
		}
	indexBPTree.locate = 1;

	indexBPTree.fp = fopen(indexBPTree.name, "wb");
	fwrite(&indexBPTree.num, sizeof(int),1,indexBPTree.fp);
	fwrite(&indexBPTree.locate, sizeof(int),1,indexBPTree.fp);
	writeNode(root);
	
	
	fclose(indexBPTree.fp);
	/*
	printf("原始：%d\n", indexBPTree.root->next);
	memset(indexBPTree.root,0,sizeof(P_BPNode));
	printf("memset后：%d\n", indexBPTree.root->next);
	indexBPTree.fp = fopen(indexBPTree.name,"r");
	fread(indexBPTree.root, sizeof(P_BPNode),1,indexBPTree.fp);
	fclose(indexBPTree.fp);
	printf("读取文件后：%d\n", indexBPTree.root->next);

	*/
//	delete(root);
	indexBPTree.root = NULL;
	return 0;
}


int splitP_BPNode (P_BPNode p, P_BPNode c, int i)
{//节点的分裂，要求p节点至少还能插入一个节点，c节点是满的，即n为2*T;
	int j;
	P_BPNode b=new BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			b->key[kk]="";
		}
	b->leaf = c->leaf;
	b->n = T;
	b->id = indexBPTree.num+1;	//为b赋值id号，用于表示该节点，，同时id号就是这个节点在文件的位置
	b->next = c->next;			//为b的next赋值，即原来的c节点的next
	//将c节点的后半部分关键字复制给b
	for (j = 0; j < T; j++)
	{
		b->key[j] = c->key[j+T];
		b->child[j] = c->child[j+T];
		b->buff[j]=c->buff[j+T];
//		b->dup[j]=c->dup[j+T];
	}

	//至此b节点的对应元素已经建立好了，但还需要写入文件

	indexBPTree.num++;
	c->n = T;	//c节点的关键字数目减半
	c->next = b->id;



	//将p节点的i之后的节点后移
	for (j = p->n - 1; j > i; j--)
	{
		p->key[j+1] = p->key[j];
		p->child[j+1] = p->child[j];
		p->buff[j+1]=p->buff[j];
//		p->dup[j+1]=p->dup[j];
	}
	
	//将b节点插入p中
	p->key[i+1] = b->key[0];
	p->child[i+1] = b->id;
	p->buff[i+1]=b->buff[0];
//	p->dup[i+i]=b->dup[0];

	p->n++;	//p关键字个数加一
	//写入p
	writeNode(p);
	writeNode(c);
	writeNode(b);
//	free(b);
	return 0;
}//splitP_BPNode


int insertP_BPNodeNotFull(P_BPNode s, KeyType k, unsigned int id,Pointer infilepos)
{//插入，要求s节点不是满的

	int i = s->n-1;

	if (s->leaf)
	{//叶节点，找的合适的位置
		while (i >= 0 && (s->key[i] > k))
		{
			s->key[i+1] = s->key[i];
			s->child[i+1] = s->child[i];
			s->buff[i+1]=s->buff[i];
	//		s->dup[i+1]=s->dup[i];
			i--;
		}

		s->key[i+1] = k;
		s->child[i+1] = id;
		s->buff[i+1]=infilepos;
//		s->dup[i+1]=-1;
		s->n++;
		writeNode(s);
	}
	else
	{
		P_BPNode tmp =new BPNode();
		for(int kk=0;kk<2*T;++kk)
		{
			tmp->key[kk]=" ";
		}
		while (i >= 0 && (s->key[i]) > k)
		{
			i--;
		}
		if (i < 0)
		{//插入的元素最小，则把这个元素插入第一个节点，并修改对应的key
			i++;
			s->key[i] = k;
		}
		writeNode(s);
		readNode(tmp, s->child[i]);		//读取对应的
		if (tmp->n == 2*T)
		{
			splitP_BPNode(s, tmp, i);
			if (k > s->key[i+1])
				i++;
			readNode(tmp, s->child[i]);		//重新读取，，有待优化	
		}
		insertP_BPNodeNotFull(tmp, k, id,infilepos);
//		free(tmp);
	}
	
	return 0;
}

Pointer equalSearch(P_BPTree tree, KeyType k)//,Pointer* i_f=0)
{//等值查询，给出key值，查找对应的id，并返回。如果不存在该节点，返回一个负数
	int i;
	int result;
	P_BPNode r;
	r = tree->root;
//	cout<<k<<' '<<r->key[0]<<endl;
	if (k < r->key[0])	//比最小的节点小
		return -1;
	P_BPNode tmp = new BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			tmp->key[kk]=" ";
		}
	while (1)
	{
		i = r->n - 1;
		while (i >= 0 && r->key[i] > k)
			i--;

		if (r->leaf)	//是叶子，结束
			break;
		readNode(tmp, r->child[i]);
		r = tmp;
	}//while

	if (r->key[i] < k)
		return -1;
	result = r->child[i];
	/*new*/
//	*(i_f)=r->buff[i];
	/*newend*/
	
//	delete(tmp);
	tmp = NULL;
	return result;
}//equalSearch

int rangeSearch (P_BPTree tree, KeyType low, KeyType high)
{//范围查找，key值大于等于low，小于等于high。返回范围内的个数，
	unsigned int i;
	P_BPNode r= tree->root;
	Pointer *result;
	P_BPNode tmp = P_BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			tmp->key[kk]=" ";
		}

	if (high < low)	//low <= high才有能有结果
		return 0;
	if (high < r->key[0])
		return 0;

	if (low < r->key[0])
		low = r->key[0];
	
	while (1)
	{
		i = r->n - 1;
		while (i >= 0 && r->key[i] > low)
			i--;
		if (r->leaf)	//是叶子，结束
			break;
		readNode(tmp, r->child[i]);
		r = tmp;
	}//while
	
	if (r->key[i] < low)
		i++;
	unsigned int num=100;
	result = (Pointer *)malloc(sizeof(Pointer)*num);

	unsigned int j = 0;

	while (1)
	{
		for (; i < r->n && r->key[i] <= high; i++)
		{
			if (j >= num)
			{
				num += 100;
				realloc(result, sizeof(Pointer)*num);
			}
			result[j++] = r->child[i];
		//	printf("sid:%d  iid: %d     id:%d\n", r->key[i],r->id, r->child[i]);
		}
		if (i <r->n || r->next < 0)
			break;
		
		readNode(tmp, r->next);
		r = tmp;
		i = 0;
	}//while 
//	free(tmp);
	tmp = NULL;
	return j;
}//rangeSearch

int insertKeyInBPTree (P_BPTree tree, KeyType k, Pointer id,Pointer _infile)
{//向树中插入节点
	P_BPNode r;
	r= tree->root;
//	cout<<k<<endl;
	if (equalSearch(tree, k) > 0)
	{
		//printf("元素已存在！");
		return -1;
	}


	if ((tree->root)->n == 2*T)
	{//根节点满了，重新分配根节点，并进行初始化
		P_BPNode s =new BPNode();
		for(int kk=0;kk<2*T;++kk)
		{
			s->key[kk]=" ";
		}
		s->leaf = 0;
		s->n = 1;
		s->key[0] = r->key[0];
		s->child[0] = r->id;
		s->id = tree->num + 1;
		s->buff[0]=_infile;
		s->next = -1;
		//将新的根写入磁盘
		writeNode(s);
	
		tree->num++;
	
		writeNode(r);

		splitP_BPNode (s, r, 0);

		//根变为s，所以将新根copy到tree->root指针所指向的内存。（tree->root将一直指向一片开辟了的内存，且时刻保存树根的整个节点）
		memcpy(tree->root, s, sizeof(BPNode));
		tree->locate = s->id;

		insertP_BPNodeNotFull(s, k, id,_infile);
//		free(s);	//释放内存		
	}
	else
		insertP_BPNodeNotFull(r, k, id,_infile);
	return 0;
}//insertP_BPNode

int initIndexBPTree(char *tableName, char *attr)
{//初始化BPTree，打开相应文件，fp记录；为root分配内存可以存储一个节点的内存，并读入根节点
	indexBPTree.root =new BPNode();
	indexBPTree.start = 1;

	memcpy(indexBPTree.name, "dataset\\", sizeof("dataset\\"));
	strcat(indexBPTree.name, tableName);
	strcat(indexBPTree.name, ".");
	strcat(indexBPTree.name, attr);
	indexBPTree.fp = fopen(indexBPTree.name, "rb+");
	fread(&indexBPTree.num,sizeof(int),1, indexBPTree.fp);
	fread(&indexBPTree.locate,sizeof(int),1,indexBPTree.fp);

	readNode(indexBPTree.root, indexBPTree.locate);
	return 0;
}

int endBPTree()
{//将建立的树结束
	fseek(indexBPTree.fp, 0, SEEK_SET);
	fwrite(&indexBPTree.num, sizeof(int),1,indexBPTree.fp);
	fwrite(&indexBPTree.locate, sizeof(int),1,indexBPTree.fp);
//	free(indexBPTree.root);
	fclose(indexBPTree.fp);
	return 0;
}

int pNode(P_BPNode n)
{//输出节点
	int tmpadd= n->buff[0];
	int fno=tmpadd/100000;
	int fadd=tmpadd%100000;
	char* b;
	//string fname=filePath[fno];
/*	FILE* hand=fopen(fname.c_str(),"r");
	for(int i=0;i<fadd;++i)
	{
		fgets(b,1024,hand);
	}
	cout<<b<<endl;
	puts("");
*/
	ifstream in;
	char* str;
//	in.open(fname); 
	for(int i=0;i<fadd;++i)
	{
		in.getline(str, 500);
	}
	puts(str);
	return 0;
}//pNode




int writeNode(P_BPNode w)
{
	fseek(indexBPTree.fp, sizeof(BPNode)*((w)->id - 1) + 2*sizeof(int), SEEK_SET);
	fwrite(w, sizeof(BPNode),1,indexBPTree.fp);

	return 0;
}

int readNode(P_BPNode r, Pointer id)
{
	fseek(indexBPTree.fp, (sizeof(BPNode))*(id - 1) + 2*sizeof(int), SEEK_SET);
	fread(r, (sizeof(BPNode)),1,indexBPTree.fp);
	return 0;
}
