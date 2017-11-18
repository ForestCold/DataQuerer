#include "MyDelete.h"
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

//MyDelete的实现


#define nTableSize  200000//哈希表大小

//string filePath[30];

typedef struct _MPQHASHTABLE//哈希表中的记录（一列，目前是char型）
{    
int bExists;
int count;
}MPQHASHTABLE;

MPQHASHTABLE       HashTable[nTableSize];//密码存储哈希表（存储哈希密码）

int toIntDelete(string str){
	int result=0;
	for (int i=0;i<(int)str.length();i++){
		if (str[i]>='0'&&str[i]<='9')
			result=result*10+str[i]-'0';
		else break;
	}
	return result;
}

int StrtoInt(string str){
	int result=0;
	for (int i=0;i<2;i++)
	{
		result=result*10+str[i];
	}
	return result;
}

struct Record{
	string address,estate;
	string fas,allAttribute;
	int price,area,year;
	int num;
	char fasAttrubute[80];
	char hashAttrubute[10];
	Record(){}
	Record(string _address,string _estate,string _price,string _area,string _year){
		address=_address;
		estate=_estate;
		price=toIntDelete(_price);
		area=toIntDelete(_area);
		year=toIntDelete(_year);
		allAttribute=_address+" "+_estate+" "+_price+" "+_area+" "+_year;
		fas=_address+_estate;
		const char *fasAttrubute = fas.c_str();
		hashAttrubute[0] = _address[1]+_address[3]+_address[1]+_address[3];
		hashAttrubute[1] = _address[2]+_address[0]+_address[2]+_address[1];
		hashAttrubute[2] = _address[3]+_address[0]+_address[2]+_address[0];
		hashAttrubute[3] = _address[1]+_address[3]+_address[2]+_address[0];
	}
	bool operator < (const Record &o ) const {
		return num<o.num; 
	}
	bool operator == (const Record &o ) const {
		return num==o.num; 
	}
	bool operator > (const Record &o ) const {
		return num>o.num; 
	}
	bool operator >= (const Record &o ) const {
		return num>=o.num; 
	}
	
}Deletedata[nTableSize];

//char            data[nTableSize][nMaxStrLen];//记录哈希表（存储整条记录）

class CHashForMpq
{
public:
    int insert_record(Record record)
    {
		 bool wh=true;
         const int HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;//定义哈希类型
         /*计算lpszString字符串经过解析后应该放入或者查询各表的数据*/
         unsigned int nHash = HashString(record.hashAttrubute);//生成要放入hash表中的数据
         unsigned int nHashStart = nHash % nTableSize;//计算起始查询位置
         unsigned int nHashPos = nHashStart;//初始化实际查询到的位置
		 //if(nHashPos>nTableSize)
			 //cout<<"超过哈希表的范围啦";
         while(HashTable[nHashPos].bExists==1&&wh)//发生了碰撞
         { 
			 if (record.fas==Deletedata[nHashPos].fas)
			 {
				 HashTable[nHashPos].count++;
				 Deletedata[nHashPos].area+=record.area;
				 Deletedata[nHashPos].year+=record.year;
				 Deletedata[nHashPos].price+=record.price;
				 wh=false;
                 //原始数据发生了重复，将总价、面积、年份进行累加，同时count加1
			 }
             else 
			 {
                 nHashPos = (nHashPos + 1) % nTableSize;//说明数据没有重复，但原来的位置上有数据，也就是发生了碰撞的情况，所以将实际位置偏移
			 }
         }
         /*插入的情况*/
         if (HashTable[nHashPos].bExists ==0)//如果没有发生碰撞
         {   
				 Deletedata[nHashPos].allAttribute=record.allAttribute;//放入data表中（存储整条记录）
                 HashTable[nHashPos].bExists = 1;//表示这个位置有记录了
				 Deletedata[nHashPos].fas=record.fas;
				 HashTable[nHashPos].count=1;
          } 
          return nHashPos;
     }
private:
    unsigned long HashString(char *lpszFileName)
    { 
		unsigned int hash = 5381 ; 
        while (*lpszFileName) 
        { 
             hash += (hash << 5 ) + (*lpszFileName ++ ); 
        } 
        return (hash & 0x7FFFFFFF ); 
	}
};


void MyDelete(string *DeletefilePath,int fileCount)
{
    CHashForMpq cHashForMpq;
	for(int j=0;j< nTableSize;j++)
	{
		HashTable[j].bExists=0;
		HashTable[j].count=0;
	}
	
	//int fileCount=0;
	//cout<<"输入文件数量"<<endl;
	//cin>>fileCount;
	//cout<<"输入文件名"<<endl;
	//for (int i=0;i<fileCount;i++){
	//	cin>>filePath[i];
	//	filePath[i]="dataset//"+filePath[i]+".txt";
	//}
	string address,estate,price,area,year;

	for (int i=0;i<fileCount;i++)
	{
	    ifstream fin(DeletefilePath[i]);//将文件名存成数组
	    //cout<<"deal "<<filePath[i]<<endl;
		for(int m=0;!fin.eof();m++)
       {
	       fin>>address>>estate>>price>>area>>year;
	       cHashForMpq.insert_record(Record(address,estate,price,area,year));
	   }
	   ofstream fout(DeletefilePath[i]);
	   for(int n=0;n<nTableSize;n++)
	   {
		   if( HashTable[n].bExists==1)
		   {
			    Deletedata[n].area=int(Deletedata[n].area/HashTable[n].count);
			    Deletedata[n].price=int(Deletedata[n].price/HashTable[n].count);
			    Deletedata[n].year=int(Deletedata[n].year/HashTable[n].count);
			    fout<<Deletedata[n].allAttribute<<endl;//将数据写回
		    }
	    }
	   for(int j=0;j< nTableSize;j++)
	{
		HashTable[j].bExists=0;
		HashTable[j].count=0;
	}
	  // cout<<"finished";
	}
}