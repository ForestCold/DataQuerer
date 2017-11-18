#include "MySort.h"
#include "stdafx.h"
#include <string>
#include <fstream>
#include<stdio.h>
#include<climits>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

//MySort的实现



const int MIN_KEY=INT_MIN;
const int MAX_KEY=INT_MAX;

//const int BUF_SIZE=30+10;
//const int FILE_NUM=20+10;
typedef int LoserTree[40];


int toInt6(string str){
	int result=0;
	for (int i=0;i<(int)str.length();i++){
		if (str[i]>='0'&&str[i]<='9')
			result=result*10+str[i]-'0';
		else break;
	}
	return result;
}
struct Record6{
	string address,estate;
	string allAttribute;
	int price,area,year;
	int num;
	Record6(){}
	Record6(string _address,string _estate,string _price,string _area,string _year){
		address=_address;
		estate=_estate;
		price=toInt6(_price);
		area=toInt6(_area);
		year=toInt6(_year);
		allAttribute=_address+" "+_estate+" "+_price+" "+_area+" "+_year;
	}
	bool operator < (const Record6 &o ) const {
		return num<o.num;
	}
	bool operator == (const Record6 &o ) const {
		return num==o.num;
	}
	bool operator > (const Record6 &o ) const {
		return num>o.num;
	}
	bool operator >= (const Record6 &o ) const {
		return num>=o.num;
	}

}bufRecord6[40];



void update(LoserTree Ls,int s,int k){
    int par=(k-1+s)/2;//待调整节点的父亲节点
    while (par>0){//一路向上调整
        if (bufRecord6[s].num>bufRecord6[Ls[par]].num){
            swap(s,Ls[par]);
        }
        par/=2;
    }
    Ls[0]=s;
	
}
void CreateLoserTree(LoserTree Ls,int k) {
	bufRecord6[k+1].num=MIN_KEY;
    for(int i=1; i<=k-1; i++)
        Ls[i]=k+1;
    for(int i=k; i>=1; i--)
        update(Ls,i,k);

}
void ReadFile(int i,Record6 &rec,string sortType,string sortAttribute,ifstream *fin) {
    string address,estate,price,area,year;
    if(fin[i].is_open()) {
        fin[i]>>address>>estate>>price>>area>>year;
        rec=Record6(address,estate,price,area,year);
		//cout<<bufRecord6[i].allAttribute<<endl;
		if(sortAttribute=="总价")
			rec.num =bufRecord6[i].price;
		else if(sortAttribute=="总面积")
		   rec.num =bufRecord6[i].area;
		else if(sortAttribute=="建筑年代")
		   rec.num =bufRecord6[i].year;
		if (sortType=="stl")
			rec.num=-rec.num;
    }
}
void WriteFile(Record6 &rec,string sortType,ostream &fout) {
	if (sortType=="stl")
		rec.num=-rec.num;
    fout<<rec.allAttribute<<endl;
}
void K_Merger(LoserTree Ls,int k,string sortType,string sortAttribute,ifstream *fin,ostream &fout) {
    //利用败者树Ls，将编号从[0]~[k-1]的k个输入归并段中的记录归并到输出归并段
    //b[1]~b[k]为败者树上的k个叶子结点，分别存入k个输入归并段中当前记录的关键字

    for(int i=1;i<=k; i++) { //依次从k个输入归并段
        ReadFile(i,bufRecord6[i],sortType,sortAttribute,fin);//从第i个文件中读入第1个记录到b[i]
        if(bufRecord6[i].num==0)//读取失败时，设置外部结点关键字值为最大
            bufRecord6[i].num=MAX_KEY;
		//cout<<bufRecord6[i].allAttribute<<endl;
    }
    CreateLoserTree(Ls,k);
    while(bufRecord6[Ls[0]].num!=MAX_KEY) { //胜出的关键字不是最大关键字
		//cerr<<bufRecord6[Ls[0]].num<<endl;
		//cerr<<bufRecord6[Ls[0]].allAttribute<<endl;
        WriteFile(bufRecord6[Ls[0]],sortType,fout);//将胜出者输出到文件中
        ReadFile(Ls[0],bufRecord6[Ls[0]],sortType,sortAttribute,fin);//从编号为Ls[0]的归并段中读入下一个记录
        if(bufRecord6[Ls[0]].num==0)//失败
            bufRecord6[Ls[0]].num=MAX_KEY;
        update(Ls,Ls[0],k);
    }
}
char file[100];
int sum=0;
void doSort(char *file,string sortType,string sortAttribute){
	//cout<<"deal"<<" "<<file<<endl;
	string address,estate,price,area,year;
	vector< Record6 >vec;
	ifstream fin(file);
	int count=0;
	while(!fin.eof()) {
        fin>>address>>estate>>price>>area>>year;
		vec.push_back(Record6(address,estate,price,area,year));
		//cout<<bufRecord6[i].allAttribute<<endl;
		if(sortAttribute=="总价")
			vec[count].num =vec[count].price;
		else if(sortAttribute=="总面积")
			vec[count].num =vec[count].area;
		else if(sortAttribute=="建筑年代")
			vec[count].num =vec[count].year;
		count++;
		//cout<<count<<endl;
    }
	sum+=count;
	//cout<<count<<endl;
	//cout<<"scanf completed"<<endl;
	if (sortType=="stl")
		sort(vec.rbegin(),vec.rend());
	else sort(vec.begin(),vec.end());
	//cout<<"sort completed"<<endl;
	fin.close();
	ofstream fout(file);
	for (int i=0;i<vec.size();i++){
		fout<<vec[i].allAttribute<<endl;
	}
	fout.close();
}
void MySort(string *filePath,int fileCount,string sortType,string sortAttribute) {
	ifstream fin[40];
	ofstream fout;
	//filePath[1]="dataset//baoshan.txt";
	//filePath[2]="dataset//changning.txt";
	int k=fileCount;
	//cout<<"输入文件数量"<<endl;
	//cin>>fileCount;
	//cout<<"输入文件名"<<endl;
	//for (int i=1;i<=fileCount;i++){
	//	cin>>filePath[i];
	//	filePath[i]="dataset//"+filePath[i]+".txt";
	//}
	//cout<<"输入sortType"<<endl;
	//cin>>sortType;
	//cout<<"输入sortAttribute"<<endl;
	//cin>>sortAttribute;

    LoserTree Ls;
    for(int i=1; i<=k; i++) {
		//cerr<<"deal "<<i<<endl;
        strcpy(file,filePath[i-1].c_str());
        fin[i].open(file);
		doSort(file,sortType,sortAttribute);//先将原本的文件排序
    }
	//cout<<sum<<endl;
    fout.open("result.txt");
    K_Merger(Ls,k,sortType,sortAttribute,fin,fout);//开始归并文件
    //return 0;
}
