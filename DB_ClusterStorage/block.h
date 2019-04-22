#pragma once
#include<fstream>
#include<iostream>
using namespace std;
#define BLOCKSIZE 4096 
#define USED_FREE_MAXNUM 100
#define TAILER_ARRAY_MAXNUM 150
#define RECORD_MAXNUM 149

struct Header
{
	int checksum;                   //tcp
	unsigned int next;              //下一个block是否存在,在为1，不在置为0
	unsigned short unused_free;     //从未被使用过的空闲空间
	unsigned short used_free[USED_FREE_MAXNUM]; //曾被使用过的空闲空间
	unsigned short used_free_num;
};//头部有(2+2+4+2+2*100+2=)212字节

struct Tailer
{
	unsigned short directory[TAILER_ARRAY_MAXNUM];
	unsigned short arrayNum;//记录的数目
};//尾部有(2*150+2=)302字节

typedef struct record
{
	char name[5];
	char sex;
	unsigned short age;
	int sID;  //主键
	char major[12];
}Record;//每条记录有(5+1+2+4+12=)24字节

class Block
{
private:
	Header header;
	Tailer tailer;
	Record record[RECORD_MAXNUM];
	void setChecksum();
public:
	void setData();
	bool identifyChecksum();
	bool addRecord(Record &r, int blockNum);
	bool removeRecord(int sid, int blockNum);
	bool modifyRocord(Record &r, int blockNum);
	bool showRecord(int sid, int blockNum);//暂时只能按照主键查询
};

void Block::setData()
{
	header.checksum = 0;
	header.next = 0;
	header.unused_free = 0;
	for (int i = 0; i < USED_FREE_MAXNUM; i++)
	{
		header.used_free[i] = 0;
	}
	header.used_free_num = 0;
	tailer.arrayNum = 0;
	for (int i = 0; i < TAILER_ARRAY_MAXNUM; i++)
	{
		tailer.directory[i] = 0;
	}
	for (int i = 0; i < RECORD_MAXNUM; i++)
	{
		record[i] = { "",'N',0,0,"" };
	}
}

void Block::setChecksum()
{
	header.checksum = 0;
	for (int i = 0; i < tailer.arrayNum; i++)
	{	
		header.checksum += record[tailer.directory[i]].sID;
	}
}

bool Block::identifyChecksum()
{
	int checksum=0;
	for (int i = 0; i < tailer.arrayNum; i++)
	{
		checksum += record[tailer.directory[i]].sID;
	}
	if (checksum == header.checksum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Block::addRecord(Record &r, int blockNum)
{
	bool r_is = false;
	int index;
	
	for (int i = 0; i < tailer.arrayNum; i++)
	{
		index = tailer.directory[i];
		if (record[index].sID == r.sID)
		{
			r_is = true;
			break;
		}
	}
	if (r_is)
	{
		cout << "该记录已存在！" << endl;
		return true;
	}
	else//记录不在才添加
	{
		int r_index;
		if (header.used_free_num != 0)
		{
			r_index = header.used_free[header.used_free_num - 1];
			header.used_free_num--;
		}
		else
		{
			r_index = header.unused_free;
			header.unused_free++;
		}
		tailer.directory[tailer.arrayNum] = r_index;
		tailer.arrayNum++;

		if (r_index>148)
		{
			header.next = 1;
			return false;
		}
		else
		{
			//将r的内容写到文件里
			record[r_index] = r;
			setChecksum();
			return true;
		}
	}
}
bool Block::removeRecord(int sid, int blockNum)
{
	bool r_is = false;
	int r_index;
	int i;

	for (i = 0; i < tailer.arrayNum; i++)
	{
		r_index = tailer.directory[i];
		if (record[r_index].sID == sid)
		{
			r_is = true;
			break;
		}
	}
	if (r_is)
	{
		//如果要删除的记录是从未被使用的空闲空间的前一个记录，
		//则可认为该记录的空间从未被使用过
		header.used_free[header.used_free_num] = r_index;
		header.used_free_num++;
		for (int j = i; j < tailer.arrayNum-1; j++)//第i个后面的往前移动
		{
			tailer.directory[j] = tailer.directory[j + 1];
		}
		tailer.arrayNum--;
	}
	if (r_is)
	{
		cout << "该学号存在，已删除！" << endl;
		setChecksum();
		return true;
	}
	else
	{
		if (header.next == 0)
		{
			cout << "该学号不存在，输入错误！！！ 请检查您的输入" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool Block::modifyRocord(Record &r, int blockNum)
{
	bool r_is = false;
	int r_index;

	for (int i = 0; i < tailer.arrayNum; i++)
	{
		//读取文件:以tailer.directory[i]为起始位置，读取一条记录，保存到r中
		r_index = tailer.directory[i];
		if (r.sID == record[r_index].sID)
		{
			r_is = true;
			break;
		}
	}
	if (r_is)
	{
		//修改文件：将r的内容写入到文件中
		record[r_index] = r;

		return true;
	}
	else
	{
		if (header.next == 0)
		{
			cout << "您要修改的记录不在当前文件中！！！" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool Block::showRecord(int sid, int blockNum)
{
	bool r_is = false;
	int r_index;
	
	for (int i = 0; i < tailer.arrayNum; i++)
	{
		//读取文件:以tailer.directory[i]为起始位置，读取一条记录，保存到r中
		r_index = tailer.directory[i];

		if (record[r_index].sID == sid)
		{
			r_is = true;
			break;
		}
	}
	if (r_is)
	{
		cout << "name:" << record[r_index].name << "  sex:" << record[r_index].sex << "  age:" << record[r_index].age;
		cout << "  sID:" << record[r_index].sID << "  major:" << record[r_index].major << endl;
		return true;
	}
	else
	{
		if (header.next == 0)
		{
			cout << "您要查找的记录不在该文件中！！！" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}
