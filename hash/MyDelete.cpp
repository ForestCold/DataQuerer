#include "MyDelete.h"
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

//MyDelete��ʵ��


#define nTableSize  200000//��ϣ���С

//string filePath[30];

typedef struct _MPQHASHTABLE//��ϣ���еļ�¼��һ�У�Ŀǰ��char�ͣ�
{    
int bExists;
int count;
}MPQHASHTABLE;

MPQHASHTABLE       HashTable[nTableSize];//����洢��ϣ���洢��ϣ���룩

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

//char            data[nTableSize][nMaxStrLen];//��¼��ϣ���洢������¼��

class CHashForMpq
{
public:
    int insert_record(Record record)
    {
		 bool wh=true;
         const int HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;//�����ϣ����
         /*����lpszString�ַ�������������Ӧ�÷�����߲�ѯ���������*/
         unsigned int nHash = HashString(record.hashAttrubute);//����Ҫ����hash���е�����
         unsigned int nHashStart = nHash % nTableSize;//������ʼ��ѯλ��
         unsigned int nHashPos = nHashStart;//��ʼ��ʵ�ʲ�ѯ����λ��
		 //if(nHashPos>nTableSize)
			 //cout<<"������ϣ��ķ�Χ��";
         while(HashTable[nHashPos].bExists==1&&wh)//��������ײ
         { 
			 if (record.fas==Deletedata[nHashPos].fas)
			 {
				 HashTable[nHashPos].count++;
				 Deletedata[nHashPos].area+=record.area;
				 Deletedata[nHashPos].year+=record.year;
				 Deletedata[nHashPos].price+=record.price;
				 wh=false;
                 //ԭʼ���ݷ������ظ������ܼۡ��������ݽ����ۼӣ�ͬʱcount��1
			 }
             else 
			 {
                 nHashPos = (nHashPos + 1) % nTableSize;//˵������û���ظ�����ԭ����λ���������ݣ�Ҳ���Ƿ�������ײ����������Խ�ʵ��λ��ƫ��
			 }
         }
         /*��������*/
         if (HashTable[nHashPos].bExists ==0)//���û�з�����ײ
         {   
				 Deletedata[nHashPos].allAttribute=record.allAttribute;//����data���У��洢������¼��
                 HashTable[nHashPos].bExists = 1;//��ʾ���λ���м�¼��
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
	//cout<<"�����ļ�����"<<endl;
	//cin>>fileCount;
	//cout<<"�����ļ���"<<endl;
	//for (int i=0;i<fileCount;i++){
	//	cin>>filePath[i];
	//	filePath[i]="dataset//"+filePath[i]+".txt";
	//}
	string address,estate,price,area,year;

	for (int i=0;i<fileCount;i++)
	{
	    ifstream fin(DeletefilePath[i]);//���ļ����������
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
			    fout<<Deletedata[n].allAttribute<<endl;//������д��
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