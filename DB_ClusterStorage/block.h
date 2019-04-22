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
	unsigned int next;              //��һ��block�Ƿ����,��Ϊ1��������Ϊ0
	unsigned short unused_free;     //��δ��ʹ�ù��Ŀ��пռ�
	unsigned short used_free[USED_FREE_MAXNUM]; //����ʹ�ù��Ŀ��пռ�
	unsigned short used_free_num;
};//ͷ����(2+2+4+2+2*100+2=)212�ֽ�

struct Tailer
{
	unsigned short directory[TAILER_ARRAY_MAXNUM];
	unsigned short arrayNum;//��¼����Ŀ
};//β����(2*150+2=)302�ֽ�

typedef struct record
{
	char name[5];
	char sex;
	unsigned short age;
	int sID;  //����
	char major[12];
}Record;//ÿ����¼��(5+1+2+4+12=)24�ֽ�

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
	bool showRecord(int sid, int blockNum);//��ʱֻ�ܰ���������ѯ
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
		cout << "�ü�¼�Ѵ��ڣ�" << endl;
		return true;
	}
	else//��¼���ڲ����
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
			//��r������д���ļ���
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
		//���Ҫɾ���ļ�¼�Ǵ�δ��ʹ�õĿ��пռ��ǰһ����¼��
		//�����Ϊ�ü�¼�Ŀռ��δ��ʹ�ù�
		header.used_free[header.used_free_num] = r_index;
		header.used_free_num++;
		for (int j = i; j < tailer.arrayNum-1; j++)//��i���������ǰ�ƶ�
		{
			tailer.directory[j] = tailer.directory[j + 1];
		}
		tailer.arrayNum--;
	}
	if (r_is)
	{
		cout << "��ѧ�Ŵ��ڣ���ɾ����" << endl;
		setChecksum();
		return true;
	}
	else
	{
		if (header.next == 0)
		{
			cout << "��ѧ�Ų����ڣ�������󣡣��� ������������" << endl;
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
		//��ȡ�ļ�:��tailer.directory[i]Ϊ��ʼλ�ã���ȡһ����¼�����浽r��
		r_index = tailer.directory[i];
		if (r.sID == record[r_index].sID)
		{
			r_is = true;
			break;
		}
	}
	if (r_is)
	{
		//�޸��ļ�����r������д�뵽�ļ���
		record[r_index] = r;

		return true;
	}
	else
	{
		if (header.next == 0)
		{
			cout << "��Ҫ�޸ĵļ�¼���ڵ�ǰ�ļ��У�����" << endl;
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
		//��ȡ�ļ�:��tailer.directory[i]Ϊ��ʼλ�ã���ȡһ����¼�����浽r��
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
			cout << "��Ҫ���ҵļ�¼���ڸ��ļ��У�����" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
}
