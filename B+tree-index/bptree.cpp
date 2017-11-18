#include "bptree.h"
#include "stdafx.h"

const int FILE_NUM=20+10;
extern BPTree indexBPTree;		//ȫ�ֱ�����b+��
//extern string filePath[FILE_NUM];



int result_pNode(Pointer tmpadd,string &Myresult,string *filePath)
{//����ڵ�
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
	//cout<<"��ַ��"<<a<<"\nС����"<<e<<"\n�۸�"<<p<<"\n�����"<<ar<<"\n���������"<<y<<endl;
	Myresult=a+" "+e+" "+p+" "+ar+" "+y;
	return 0;
}//pNode

Pointer result_equalSearch(P_BPTree tree, KeyType k)//,Pointer* i_f=0)
{//��ֵ��ѯ������keyֵ�����Ҷ�Ӧ��id�������ء���������ڸýڵ㣬����һ������
	int i;
	int result;
	P_BPNode r;
	r = tree->root;
//	cout<<k<<' '<<r->key[0]<<endl;
	if (k < r->key[0])	//����С�Ľڵ�С
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

		if (r->leaf)	//��Ҷ�ӣ�����
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
{//����B+��,��������Ӧ�ĳ�ʼ����B+���Ľṹ����һ��ȫ�ֱ�����
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
	printf("ԭʼ��%d\n", indexBPTree.root->next);
	memset(indexBPTree.root,0,sizeof(P_BPNode));
	printf("memset��%d\n", indexBPTree.root->next);
	indexBPTree.fp = fopen(indexBPTree.name,"r");
	fread(indexBPTree.root, sizeof(P_BPNode),1,indexBPTree.fp);
	fclose(indexBPTree.fp);
	printf("��ȡ�ļ���%d\n", indexBPTree.root->next);

	*/
//	delete(root);
	indexBPTree.root = NULL;
	return 0;
}


int splitP_BPNode (P_BPNode p, P_BPNode c, int i)
{//�ڵ�ķ��ѣ�Ҫ��p�ڵ����ٻ��ܲ���һ���ڵ㣬c�ڵ������ģ���nΪ2*T;
	int j;
	P_BPNode b=new BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			b->key[kk]="";
		}
	b->leaf = c->leaf;
	b->n = T;
	b->id = indexBPTree.num+1;	//Ϊb��ֵid�ţ����ڱ�ʾ�ýڵ㣬��ͬʱid�ž�������ڵ����ļ���λ��
	b->next = c->next;			//Ϊb��next��ֵ����ԭ����c�ڵ��next
	//��c�ڵ�ĺ�벿�ֹؼ��ָ��Ƹ�b
	for (j = 0; j < T; j++)
	{
		b->key[j] = c->key[j+T];
		b->child[j] = c->child[j+T];
		b->buff[j]=c->buff[j+T];
//		b->dup[j]=c->dup[j+T];
	}

	//����b�ڵ�Ķ�ӦԪ���Ѿ��������ˣ�������Ҫд���ļ�

	indexBPTree.num++;
	c->n = T;	//c�ڵ�Ĺؼ�����Ŀ����
	c->next = b->id;



	//��p�ڵ��i֮��Ľڵ����
	for (j = p->n - 1; j > i; j--)
	{
		p->key[j+1] = p->key[j];
		p->child[j+1] = p->child[j];
		p->buff[j+1]=p->buff[j];
//		p->dup[j+1]=p->dup[j];
	}
	
	//��b�ڵ����p��
	p->key[i+1] = b->key[0];
	p->child[i+1] = b->id;
	p->buff[i+1]=b->buff[0];
//	p->dup[i+i]=b->dup[0];

	p->n++;	//p�ؼ��ָ�����һ
	//д��p
	writeNode(p);
	writeNode(c);
	writeNode(b);
//	free(b);
	return 0;
}//splitP_BPNode


int insertP_BPNodeNotFull(P_BPNode s, KeyType k, unsigned int id,Pointer infilepos)
{//���룬Ҫ��s�ڵ㲻������

	int i = s->n-1;

	if (s->leaf)
	{//Ҷ�ڵ㣬�ҵĺ��ʵ�λ��
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
		{//�����Ԫ����С��������Ԫ�ز����һ���ڵ㣬���޸Ķ�Ӧ��key
			i++;
			s->key[i] = k;
		}
		writeNode(s);
		readNode(tmp, s->child[i]);		//��ȡ��Ӧ��
		if (tmp->n == 2*T)
		{
			splitP_BPNode(s, tmp, i);
			if (k > s->key[i+1])
				i++;
			readNode(tmp, s->child[i]);		//���¶�ȡ�����д��Ż�	
		}
		insertP_BPNodeNotFull(tmp, k, id,infilepos);
//		free(tmp);
	}
	
	return 0;
}

Pointer equalSearch(P_BPTree tree, KeyType k)//,Pointer* i_f=0)
{//��ֵ��ѯ������keyֵ�����Ҷ�Ӧ��id�������ء���������ڸýڵ㣬����һ������
	int i;
	int result;
	P_BPNode r;
	r = tree->root;
//	cout<<k<<' '<<r->key[0]<<endl;
	if (k < r->key[0])	//����С�Ľڵ�С
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

		if (r->leaf)	//��Ҷ�ӣ�����
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
{//��Χ���ң�keyֵ���ڵ���low��С�ڵ���high�����ط�Χ�ڵĸ�����
	unsigned int i;
	P_BPNode r= tree->root;
	Pointer *result;
	P_BPNode tmp = P_BPNode();
	for(int kk=0;kk<2*T;++kk)
		{
			tmp->key[kk]=" ";
		}

	if (high < low)	//low <= high�������н��
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
		if (r->leaf)	//��Ҷ�ӣ�����
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
{//�����в���ڵ�
	P_BPNode r;
	r= tree->root;
//	cout<<k<<endl;
	if (equalSearch(tree, k) > 0)
	{
		//printf("Ԫ���Ѵ��ڣ�");
		return -1;
	}


	if ((tree->root)->n == 2*T)
	{//���ڵ����ˣ����·�����ڵ㣬�����г�ʼ��
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
		//���µĸ�д�����
		writeNode(s);
	
		tree->num++;
	
		writeNode(r);

		splitP_BPNode (s, r, 0);

		//����Ϊs�����Խ��¸�copy��tree->rootָ����ָ����ڴ档��tree->root��һֱָ��һƬ�����˵��ڴ棬��ʱ�̱��������������ڵ㣩
		memcpy(tree->root, s, sizeof(BPNode));
		tree->locate = s->id;

		insertP_BPNodeNotFull(s, k, id,_infile);
//		free(s);	//�ͷ��ڴ�		
	}
	else
		insertP_BPNodeNotFull(r, k, id,_infile);
	return 0;
}//insertP_BPNode

int initIndexBPTree(char *tableName, char *attr)
{//��ʼ��BPTree������Ӧ�ļ���fp��¼��Ϊroot�����ڴ���Դ洢һ���ڵ���ڴ棬��������ڵ�
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
{//��������������
	fseek(indexBPTree.fp, 0, SEEK_SET);
	fwrite(&indexBPTree.num, sizeof(int),1,indexBPTree.fp);
	fwrite(&indexBPTree.locate, sizeof(int),1,indexBPTree.fp);
//	free(indexBPTree.root);
	fclose(indexBPTree.fp);
	return 0;
}

int pNode(P_BPNode n)
{//����ڵ�
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
