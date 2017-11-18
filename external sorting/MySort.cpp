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

//MySort��ʵ��



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
    int par=(k-1+s)/2;//�������ڵ�ĸ��׽ڵ�
    while (par>0){//һ·���ϵ���
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
		if(sortAttribute=="�ܼ�")
			rec.num =bufRecord6[i].price;
		else if(sortAttribute=="�����")
		   rec.num =bufRecord6[i].area;
		else if(sortAttribute=="�������")
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
    //���ð�����Ls������Ŵ�[0]~[k-1]��k������鲢���еļ�¼�鲢������鲢��
    //b[1]~b[k]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ����k������鲢���е�ǰ��¼�Ĺؼ���

    for(int i=1;i<=k; i++) { //���δ�k������鲢��
        ReadFile(i,bufRecord6[i],sortType,sortAttribute,fin);//�ӵ�i���ļ��ж����1����¼��b[i]
        if(bufRecord6[i].num==0)//��ȡʧ��ʱ�������ⲿ���ؼ���ֵΪ���
            bufRecord6[i].num=MAX_KEY;
		//cout<<bufRecord6[i].allAttribute<<endl;
    }
    CreateLoserTree(Ls,k);
    while(bufRecord6[Ls[0]].num!=MAX_KEY) { //ʤ���Ĺؼ��ֲ������ؼ���
		//cerr<<bufRecord6[Ls[0]].num<<endl;
		//cerr<<bufRecord6[Ls[0]].allAttribute<<endl;
        WriteFile(bufRecord6[Ls[0]],sortType,fout);//��ʤ����������ļ���
        ReadFile(Ls[0],bufRecord6[Ls[0]],sortType,sortAttribute,fin);//�ӱ��ΪLs[0]�Ĺ鲢���ж�����һ����¼
        if(bufRecord6[Ls[0]].num==0)//ʧ��
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
		if(sortAttribute=="�ܼ�")
			vec[count].num =vec[count].price;
		else if(sortAttribute=="�����")
			vec[count].num =vec[count].area;
		else if(sortAttribute=="�������")
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
	//cout<<"�����ļ�����"<<endl;
	//cin>>fileCount;
	//cout<<"�����ļ���"<<endl;
	//for (int i=1;i<=fileCount;i++){
	//	cin>>filePath[i];
	//	filePath[i]="dataset//"+filePath[i]+".txt";
	//}
	//cout<<"����sortType"<<endl;
	//cin>>sortType;
	//cout<<"����sortAttribute"<<endl;
	//cin>>sortAttribute;

    LoserTree Ls;
    for(int i=1; i<=k; i++) {
		//cerr<<"deal "<<i<<endl;
        strcpy(file,filePath[i-1].c_str());
        fin[i].open(file);
		doSort(file,sortType,sortAttribute);//�Ƚ�ԭ�����ļ�����
    }
	//cout<<sum<<endl;
    fout.open("result.txt");
    K_Merger(Ls,k,sortType,sortAttribute,fin,fout);//��ʼ�鲢�ļ�
    //return 0;
}
