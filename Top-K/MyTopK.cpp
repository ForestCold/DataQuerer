#include "MyTopK.h"
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <set>
#include <time.h>
#include <sstream> 

using namespace std;

//MyTopK的实现

/*将string类型转化为int类型*/

int toInt(string str){
	int result=0;
	for (int i=0;i<(int)str.length();i++){
		if (str[i]>='0'&&str[i]<='9')
			result=result*10+str[i]-'0';
		else break;
	}
	return result;
}

/*==每条记录*/
struct Record3{
	string address,estate;
	string allAttribute;
	int price,area,year;
	int num;
	Record3(){}
	Record3(string _address,string _estate,string _price,string _area,string _year){
		address=_address;
		estate=_estate;
		price=toInt(_price);
		area=toInt(_area);
		year=toInt(_year);
		allAttribute=_address+" "+_estate+" "+_price+" "+_area+" "+_year;
	}
	bool operator < (const Record3 &o ) const {
		return num<o.num; 
	}
	bool operator == (const Record3 &o ) const {
		return num==o.num; 
	}
	bool operator > (const Record3 &o ) const {
		return num>o.num; 
	}
	bool operator >= (const Record3 &o ) const {
		return num>=o.num; 
	}
	
};

/*堆*/
struct Heap{
	Heap(){size=0;}
	Record3 data[3010];
	int size;
	void pushDown(int pos){
		while (pos*2+1<size){
			int c=pos*2+1;
			if (c+1<size&&data[c+1]<data[c])
				c++;
			if (data[c]>=data[pos]) break;
			swap(data[pos],data[c]);
			pos=c;
		}
	}
	void init(){
		for (int i=size/2;i>=0;i--) pushDown(i);
	}
	void addElement(Record3 x){
		if (data[0].num<x.num){
			data[0].address=x.address;
			data[0].estate=x.estate;
			data[0].num=x.num;
			data[0].price=x.price;
			data[0].area=x.area;
			data[0].year=x.year;
			data[0].allAttribute=x.allAttribute;
			pushDown(0);
		}	
	}
	void heapSort(){
		while (size>1){
			swap(data[0],data[size-1]);
			size--;
			pushDown(0);
		}
	}
	//void print(int k){
	//	for (int i=0;i<k;i++)
	//		cout<<data[i].allAttribute<<endl<<endl<<endl;
	//	cout<<endl;
	//}
};



/*==读入单个文件，返回文件记录数量*/
int readFile(ifstream &fin,string sortAttribute,Record3 *bufRecord,int readCount=0){
	string address,estate,price,area,year;
	int bound=3010;
	if (readCount!=0) bound=readCount;
	int count=0;
	for(int i=0;i<bound&&!fin.eof();i++){
		fin>>address>>estate>>price>>area>>year;
		bufRecord[i]=Record3(address,estate,price,area,year);
		if(sortAttribute=="总价")
			bufRecord[i].num =bufRecord[i].price;
		else if(sortAttribute=="总面积")
		   bufRecord[i].num =bufRecord[i].area;
		else if(sortAttribute=="建筑年代")
		   bufRecord[i].num =bufRecord[i].year;
		count++;
		//cout<<bufRecord[i].allAttribute<<endl;
	}
	return count;
}

/*==读入所有文件*/
bool dealFile(int index,string sortAttribute,string sortType,Record3 *bufRecord,Heap &hp,string *filePath){
	ifstream fin(filePath[index]);//将文件名存成数组
	//cout<<"deal "<<filePath[index]<<endl;
	if (!fin.is_open()) return false;
	while (!fin.eof()){
		int count=readFile(fin,sortAttribute,bufRecord);//读入单个文件
		for (int i=0;i<count;i++){
			Record3 toAdd;
			toAdd.address=bufRecord[i].address;
			toAdd.estate=bufRecord[i].estate;
			toAdd.num=bufRecord[i].num;
			toAdd.price=bufRecord[i].price;
			toAdd.area=bufRecord[i].area;
			toAdd.year=bufRecord[i].year;
			toAdd.allAttribute=bufRecord[i].allAttribute;
			if (sortType=="stl")//选择的是从小到大排序
				toAdd.num=-toAdd.num;		
			hp.addElement(toAdd);
		}
	}
	return true;
}
#define inf 0x3f3f3f3f
void MyTopK(int maxK,int fileCount,string filePath[],string sortType, string sortAttribute,string *MyTopKResult){
	
	Heap hp;
	Record3 bufRecord[3010];
	for (int i=0;i<maxK;i++){
		hp.data[i]=Record3();
		hp.data[i].num=-inf;
		hp.size++;
	}
	for (int i=0;i<fileCount;i++){
		bool result=dealFile(i,sortAttribute,sortType,bufRecord,hp,filePath);
		//if (!result)
			//cerr<<"文件读取失败"<<endl;
	}
	hp.heapSort();
	for (int i=0;i<maxK;i++){
			MyTopKResult[i]=hp.data[i].allAttribute;
			};
	
	//hp.print(maxK);
	//system("pause");
	//return 0;
}
