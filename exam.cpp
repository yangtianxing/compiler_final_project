#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>


using namespace std;

typedef struct 
{
	int codebegin;
	int codeend;
	int correct;
	int wrong;
	string id1;
	string id2;
	string id3;
	int id4;
	int istrue;

}enode,*elist;
typedef struct
{
	string id1;
	string id2;
	string id3;
	string id4;
}copyfor;

enode result[50];
enode e[50];
copyfor co[10];
copyfor c[10];

void init(enode &e)
{
	e.codebegin=0;
	e.codeend=0;
	e.correct=0;
	e.wrong=0;
	e.istrue=0;
	e.id2=e.id3="";
	e.id1="j";
}
void initcopy(copyfor &e)
{
	e.id1=e.id2=e.id3=e.id4="";
}


void emit(enode &e,int &nextstart)
{
	result[nextstart-100].codebegin=e.codebegin;
	result[nextstart-100].codeend=e.codeend;
	result[nextstart-100].correct=e.correct;
	result[nextstart-100].wrong=e.wrong;
	result[nextstart-100].id1=e.id1;
	result[nextstart-100].id2=e.id2;
	result[nextstart-100].id3=e.id3;
	result[nextstart-100].id4=e.id4;
	result[nextstart-100].istrue=1;
	nextstart++;

}

void emitgoto(int &nextstart)
{
	result[nextstart-100].id1="j";
	result[nextstart-100].id2="-";
	result[nextstart-100].id3="-";
	result[nextstart-100].id4=0;
	result[nextstart-100].istrue=0;
	nextstart++;

}

void backpatch(int &a,int &b)
{
	a=b;
}

void  mergelist(int begin,int &a,int &b)
{
	a=b=begin;
}

void processE5(enode &e,int &nextstart)
{
	e.correct=nextstart;
	e.codebegin=nextstart;
	e.wrong=nextstart+1;
	emit(e,nextstart);
	emitgoto(nextstart);
}

void processE2(enode &e,enode &e1,enode &e2,int &nextstart)
{
	backpatch(e1.correct,e2.codebegin);
	e1.codebegin=e.codebegin;
	e2.correct=e.correct;
	mergelist(e.wrong,e1.wrong,e2.wrong);
}
void processE1(enode &e,enode &e1,enode &e2,int &nextstart)
{
	backpatch(e1.wrong,e2.codebegin);
	e1.codebegin=e.codebegin;
	mergelist(e.correct,e1.correct,e2.correct);
	e2.wrong=e.wrong;
}

void begin(int length)
{
	for(int i=0;i!=length;i++)
	{
		if(result[i].istrue==1)
			result[i].id4=e[i/2].correct;
			
		else
			result[i].id4=e[i/2].wrong;
		
	}
}


void show(int length)
{
	for(int i=0;i!=length;i++)
		cout<<i+100<<"    "<<"( "<<result[i].id1<<" ,"<<result[i].id2<<" ,"<<
		result[i].id3<<" ,"<<result[i].id4<<" )"<<endl;
}
/*
void linklist(e,e1,e2)
{

}
*/
void fornextand(int nextstart)
{
	e[nextstart-102].correct=nextstart;
	e[nextstart-102].wrong=nextstart+1;
	mergelist(e[nextstart-102].wrong,e[0].wrong,e[1].wrong);
}

void fornextor(int nextstart)
{
	e[nextstart-102].correct=nextstart;
	e[nextstart-102].wrong=nextstart+1;
	mergelist(e[nextstart-102].correct,e[0].correct,e[1].correct);
}

void fornextdo(int nextstart)
{
	e[nextstart-102].correct=nextstart;
	e[nextstart-102].wrong=nextstart+3;
	mergelist(e[nextstart-102].wrong,e[0].wrong,e[1].wrong);


}
void showdo(int nextstart)
{
	for(int i=0;i!=2;i++)
		cout<<nextstart+i<<"    "<<"( "<<co[i].id1<<" ,"<<co[i].id2<<" ,"<<
		co[i].id3<<" ,"<<co[i].id4<<" )"<<endl;
	cout<<nextstart+2<<"    ( j ,- ,- ,100 )"<<endl;

}

string process(string input)
{
	input.erase(0,5);
	int pos=input.find('(');
	input.erase(pos,1);
	pos=input.find(')');
	input.erase(pos,1);
	return input;
}

int main()
{
	int nextstart=100;
	string input,resource;
	cout<<"本程序为while控制语句的翻译，输入格式如下"<<endl;
	cout<<"while(a<b or c<d) do x=x+1#,#为结束符，do可省"<<endl;
	cout<<"请输入测试表达式(假设翻译四元式的下两句分别对应真出口与假出口)"<<endl;
	getline(cin,resource);
	input=process(resource);

	cout<<input<<endl;
	init(e[0]);
	init(e[1]);
	init(e[2]);
	int pos1=input.find("and");
	int pos2=input.find("or");
	int posdo=input.find("do");
	if(pos1==-1&&pos2==-1)
	{
		if(posdo==-1)
		{
			cout<<"没有与或表达式，简单翻译"<<endl;
			if(input.size()>2)
			{
				e[0].id1+=input[1];
				e[0].id2=input[0];
				e[0].id3=input[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;

			}
			processE5(e[0],nextstart);
			fornextor(nextstart);

			int length=nextstart-100;
			begin(length);

			show(length);
		}
		else
		{
			initcopy(co[0]);
			initcopy(co[1]);
			int finddo=input.find_first_of("do");
			if(finddo>2)
			{
				e[0].id1+=input[1];
				e[0].id2=input[0];
				e[0].id3=input[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;

			}
			processE5(e[0],nextstart);
			input.erase(0,posdo+3);
			co[0].id1=input[3];
			co[0].id2=input[2];
			co[0].id3=input[4];
			co[0].id4="T1";

			co[1].id1=input[1];
			co[1].id2=co[0].id4;
			co[1].id3="-";
			co[1].id4=input[0];
			fornextdo(nextstart);

			int length=nextstart-100;
			begin(length);

			show(length);
			showdo(nextstart);
		}

		
	}

	else if(pos2==-1)//and
	{
		if(posdo==-1)
		{
			string sub1=input.substr(0,pos1);
			if(sub1.size()>2)
			{
				e[0].id1+=sub1[1];
				e[0].id2=sub1[0];
				e[0].id3=sub1[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;


			}
			processE5(e[0],nextstart);
			input.erase(0,pos1);
			input.erase(0,4);
			pos1=input.find('#');
			sub1=input.substr(0,pos1);
			if(sub1.size()>1)
			{
			
				e[1].id1+=sub1[1];
				e[1].id2=sub1[0];
				e[1].id3=sub1[2];
				e[1].id4=0;
			}
			else
			{
				e[1].id1="j=";
				e[1].id2=input[0];
				e[1].id3="0";
				e[1].id4=0;

			}
			processE5(e[1],nextstart);
			fornextand(nextstart);
			processE2(e[2],e[0],e[1],nextstart);
		

			int length=nextstart-100;
			begin(length);

			show(length);
		}
		else
		{
			initcopy(co[0]);
			initcopy(co[1]);
			string sub1=input.substr(0,pos1);
			if(sub1.size()>2)
			{
				e[0].id1+=sub1[1];
				e[0].id2=sub1[0];
				e[0].id3=sub1[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;


			}
			processE5(e[0],nextstart);
			input.erase(0,pos1);
			input.erase(0,4);
			pos1=input.find("do");
			sub1=input.substr(0,pos1);
			if(sub1.size()>2)
			{
			
				e[1].id1+=sub1[1];
				e[1].id2=sub1[0];
				e[1].id3=sub1[2];
				e[1].id4=0;
			}
			else
			{
				e[1].id1="j=";
				e[1].id2=input[0];
				e[1].id3="0";
				e[1].id4=0;

			}
			processE5(e[1],nextstart);
			input.erase(0,pos1+3);
			co[0].id1=input[3];
			co[0].id2=input[2];
			co[0].id3=input[4];
			co[0].id4="T1";

			co[1].id1=input[1];
			co[1].id2=co[0].id4;
			co[1].id3="-";
			co[1].id4=input[0];
			fornextdo(nextstart);
			processE2(e[2],e[0],e[1],nextstart);
		

			int length=nextstart-100;
			begin(length);

			show(length);
			showdo(nextstart);
		}
	}



	else if(pos1==-1)//or
	{
		if(posdo==-1)
		{
			string sub1=input.substr(0,pos2);
			if(sub1.size()>2)
			{
				e[0].id1+=sub1[1];
				e[0].id2=sub1[0];
				e[0].id3=sub1[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;

			}
			processE5(e[0],nextstart);
			input.erase(0,pos2);
			input.erase(0,3);
			pos2=input.find('#');
			sub1=input.substr(0,pos2);
			if(sub1.size()>2)
			{
				e[1].id1+=sub1[1];
				e[1].id2=sub1[0];
				e[1].id3=sub1[2];
				e[1].id4=0;

			}
			else
			{
				e[1].id1="j=";
				e[1].id2=input[0];
				e[1].id3="0";
				e[1].id4=0;

			}
			processE5(e[1],nextstart);
			fornextor(nextstart);

			processE1(e[2],e[0],e[1],nextstart);
			int length=nextstart-100;
			begin(length);

			show(length);
		}
		else
		{
			initcopy(co[0]);
			initcopy(co[1]);
			string sub1=input.substr(0,pos2);
			if(sub1.size()>2)
			{
				e[0].id1+=sub1[1];
				e[0].id2=sub1[0];
				e[0].id3=sub1[2];
				e[0].id4=0;
			}
			else
			{
				e[0].id1="j=";
				e[0].id2=input[0];
				e[0].id3="0";
				e[0].id4=0;

			}
			processE5(e[0],nextstart);
			input.erase(0,pos2);
			input.erase(0,3);
			pos2=input.find("do");
			sub1=input.substr(0,pos2);
			if(sub1.size()>1)
			{
				e[1].id1+=sub1[1];
				e[1].id2=sub1[0];
				e[1].id3=sub1[2];
				e[1].id4=0;

			}
			else
			{
				e[1].id1="j=";
				e[1].id2=input[0];
				e[1].id3="0";
				e[1].id4=0;

			}
			processE5(e[1],nextstart);
			input.erase(0,pos2+3);
			co[0].id1=input[3];
			co[0].id2=input[2];
			co[0].id3=input[4];
			co[0].id4="T1";

			co[1].id1=input[1];
			co[1].id2=co[0].id4;
			co[1].id3="-";
			co[1].id4=input[0];
			fornextdo(nextstart);
			processE1(e[2],e[0],e[1],nextstart);
			int length=nextstart-100;
			begin(length);

			show(length);
			showdo(nextstart);
		}

	}
	return 0;
}

