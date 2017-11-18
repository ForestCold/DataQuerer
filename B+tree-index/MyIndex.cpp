#include "MyIndex.h"
#include "bptree.h"
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

//MyIndex的实现



BPTree indexBPTree;		//全局变量，b+树

const int N5=10000+10;
const int BUF_SIZE5=10000+10;
//const int FILE_NUM=20+10;	
//int INFILE[20]={0};	//记录每个文件的tuple个数
//string filePath[FILE_NUM];
//bool IDXTYPE[6]={0,1,1,0,0,0};//标记索引对象
//int fileCount=0;
//int Sum=0;
/*将string类型转化为int类型*/
int toInt5(string str){
	int result=0;
	for (int i=0;i<(int)str.length();i++){
		if (str[i]>='0'&&str[i]<='9')
			result=result*10+str[i]-'0';
		else break;
	}
	return result;
}

/*==每条记录*/
struct Record5{
	string address,estate,o_price,o_area,o_year;
	string allAttribute;
	int price,area,year;
	int num;
	Record5(){}
	Record5(string _address,string _estate,string _price,string _area,string _year){
		address=_address;
		estate=_estate;
		price=toInt5(_price);
		area=toInt5(_area);
		year=toInt5(_year);
		o_price=_price;
		o_area=_area;
		o_year=_year;

		allAttribute=_address+" "+_estate+" "+_price+" "+_area+" "+_year;
	}
	bool operator < (const Record5 &o ) const {
		return num<o.num; 
	}
	bool operator == (const Record5 &o ) const {
		return num==o.num; 
	}
	bool operator > (const Record5 &o ) const {
		return num>o.num; 
	}
	bool operator >= (const Record5 &o ) const {
		return num>=o.num; 
	}
	
}bufRecord5[BUF_SIZE5];



int readFile(ifstream &fin,int &Sum,int readCount=0){
	string address,estate,price,area,year;
	int bound=BUF_SIZE5;
	int count=0;
	if (readCount!=0) bound=readCount;
	for(int i=0;i<bound&&!fin.eof();i++){
		fin>>address>>estate>>price>>area>>year;
		bufRecord5[Sum++]=Record5(address,estate,price,area,year);
		count++;
		//cout<<bufRecord5[i].allAttribute<<endl;
	}
	fin.close();
	return count;
}


void makeIndex(int fileCount,bool *IDXTYPE,int *INFILE)
{
	int cnt=0;
	
	for(int i=0;i<fileCount;++i)
	{
		//cout<<INFILE[i]<<endl;
		for(int j=0;j<INFILE[i];++j)
		{	
			++cnt;
			string store="";
			if(IDXTYPE[1]==1)
				store+=(bufRecord5[cnt-1]).address;
			if(IDXTYPE[2]==1)
				store+=(bufRecord5[cnt-1]).estate;
			if(IDXTYPE[3]==1)
				store+=(bufRecord5[cnt-1]).o_price;
			if(IDXTYPE[4]==1)
				store+=(bufRecord5[cnt-1]).o_area;
			if(IDXTYPE[5]==1)
				store+=(bufRecord5[cnt-1]).o_year;

			insertKeyInBPTree(&indexBPTree,store,cnt,i*100000+j);
			
		}
	}

	//cout<<"索引建立成功\n";
}


int dealFile(int index,string *filePath,int &Sum){
	//ifstream fin("dataset\\"+filePath[index]+".txt");//将文件名存成数组
	//cout<<"dealing with "<<filePath[index]<<endl;
	ifstream fin(filePath[index]);
	int count=-1;
	if (!fin.is_open()) return -1;
	while (!fin.eof()){
		count=readFile(fin,Sum);//读入单个文件		
	}
	return count;
}




void MyIndex(string *filePath,int fileCount,string findk,bool *IDXTYPE,string &Myresult)
{
	int Sum=0;
	int INFILE[20]={0};
	//string findk="阳曲路1388弄城投世纪名城";
	//string filePath[30];
	//filePath[0]="dataset//baoshan.txt";
	//filePath[1]="dataset//changning.txt";
	//int fileCount=2;
	//string Myresult="";
	createIndexBPTree("house","dat");
	initIndexBPTree("house", "dat");
	//bool IDXTYPE[6]={0,1,1,0,0,0};
	//cout<<"输入文件数量"<<endl;
	//cin>>fileCount;
	//cout<<"输入文件名"<<endl;
	//for (int i=0;i<fileCount;i++)
	//	cin>>filePath[i];
	Sum=0;
	for (int i=0;i<fileCount;i++){
		int result=dealFile(i,filePath,Sum);
		if (result<0)
		{
			//cerr<<"文件读取失败"<<endl;
			//return -1;
		}
		else INFILE[i]=result;
	}
//	cout<<"输入需要建索引的属性(至少两个):\n"<<endl;
	
	makeIndex(fileCount,IDXTYPE,INFILE);
	//cout<<"输入要查询的键值：";
	//cin>>findk;
	int s = result_equalSearch(&indexBPTree, findk);
//	P_BPNode tmp1=new BPNode();
//	readNode(tmp1,s);
	result_pNode(s,Myresult,filePath);
	//cout<<Myresult;
	//return 0;
}