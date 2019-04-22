#pragma once

#include<windows.h>
#include<string>
#include<direct.h>
#include"block.h"
#include<iostream>
using namespace std;

class File
{
	Block *block;
	int free;
	string filename;
public:
	File()
	{
		block = new Block[10];
	}
	bool open(string file)
	{
		ifstream infile;
		infile.open(file, ios::in);
		if (!infile)
		{
			return false;
		}
		else
		{
			infile.close();
			filename = file;
			return true;
		}
	}
	void Init()//只能第一次创建的时候才能调用次函数
	{
		ofstream outfile;
		outfile.open(filename, ios::out);
		if (!outfile)
		{
			cout << "文件打开失败" << endl;
			exit(-1);
		}
		outfile.seekp(0, ios::beg);
		outfile << 0;
		outfile.seekp(40, ios::beg);
		for (int i = 0; i < 9; i++)
		{
			block[i].setData();
			if (!outfile.write((char *)&block[i], sizeof(Block)))
			{
				cout << "block初始化失败！！！" << endl;
			}
			outfile.seekp((40 + (i + 1)*BLOCKSIZE), ios::beg);
		}
		outfile.write((char *)&block[9], sizeof(Block));

		outfile.close();
	}
	/*
	* 创建指定大小的空文件,支持超大文件(16EB),小于4GB时, 
	* 参数dwHigh可传入0,
	* 成功返回0， 失败返回错误代码
	*/
	BOOL CreateNullFile(DWORD dwHigh, DWORD dwLow, LPCTSTR lpcszFileName)
	{
		BOOL bResult = FALSE;
		HANDLE hFile = ::CreateFile(lpcszFileName, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return (BOOL)::GetLastError();
		}

		HANDLE hFileMap = ::CreateFileMapping(hFile, NULL, PAGE_READWRITE, dwHigh, dwLow, NULL);
		if (NULL == hFileMap)
		{
			return (BOOL)::GetLastError();
		}

		::CloseHandle(hFileMap);
		::CloseHandle(hFile);

		return bResult;
	}
	int removeFile(string path)
	{
		if (!DeleteFile(path.c_str()))
		{
			cout << "文件删除失败" << endl;
		}
		return 0;
	}
	void addRecord(Record &r)
	{
		fstream fp;
		fp.open(filename, ios::in | ios::out);
		if (!fp)
		{
			cout << "文件打开失败" << endl;
		}
		fp >> free;

		//开始读取block
		fp.seekg(40, ios::beg);
		int blockNum = 0;
		fp.read((char*)&block[blockNum], sizeof(Block));
		if (!block[blockNum].identifyChecksum())
		{
			cout << "block " << blockNum << " data error!!!" << endl;
			system("pause");
			exit(-1);
		}
		while (!block[blockNum].addRecord(r, blockNum))
		{
			blockNum++;
			fp.seekg((40 + blockNum * BLOCKSIZE), ios::beg);
			fp.read((char*)&block[blockNum], sizeof(Block));
			if (!block[blockNum].identifyChecksum())
			{
				cout << "block " << blockNum << " data error!!!" << endl;
				system("pause");
				exit(-1);
			}
		}
		fp.seekp((40 + blockNum * BLOCKSIZE), ios::beg);
		fp.write((char*)&block[blockNum], sizeof(Block));

		fp.close();
	}
	void removeRecord(int sid)
	{
		fstream fp;
		fp.open(filename, ios::in | ios::out);
		if (!fp)
		{
			cout << "文件打开失败" << endl;
		}
		fp >> free;


		fp.seekg(40, ios::beg);
		int blockNum = 0;
		fp.read((char*)&block[blockNum], sizeof(Block));
		if (!block[blockNum].identifyChecksum())
		{
			cout << "block " << blockNum << " data error!!!" << endl;
			system("pause");
			exit(-1);
		}
		while (!block[blockNum].removeRecord(sid, blockNum))
		{
			blockNum++;
			fp.seekg((40 + blockNum * BLOCKSIZE), ios::beg);
			fp.read((char*)&block[blockNum], sizeof(Block));
			if (!block[blockNum].identifyChecksum())
			{
				cout << "block " << blockNum << " data error!!!" << endl;
				system("pause");
				exit(-1);
			}
		}
		fp.seekp((40 + blockNum * BLOCKSIZE), ios::beg);
		fp.write((char*)&block[blockNum], sizeof(Block));

		fp.close();
	}
	void modifyRecord(Record &r)
	{
		fstream fp;
		fp.open(filename, ios::in | ios::out);
		if (!fp)
		{
			cout << "文件打开失败" << endl;
		}
		fp >> free;
		fp.seekg(40, ios::beg);
		int blockNum = 0;
		fp.read((char*)&block[blockNum], sizeof(Block));
		if (!block[blockNum].identifyChecksum())
		{
			cout << "block " << blockNum << " data error!!!" << endl;
			system("pause");
			exit(-1);
		}
		while (!block[blockNum].modifyRocord(r, blockNum))
		{
			blockNum++;
			fp.seekg((40 + blockNum * BLOCKSIZE), ios::beg);
			fp.read((char*)&block[blockNum], sizeof(Block));
			if (!block[blockNum].identifyChecksum())
			{
				cout << "block " << blockNum << " data error!!!" << endl;
				system("pause");
				exit(-1);
			}
		}
		fp.seekp((40 + blockNum * BLOCKSIZE), ios::beg);
		fp.write((char*)&block[blockNum], sizeof(Block));

		fp.close();
	}
	void showRecord(int sid)
	{
		fstream fp;
		fp.open(filename, ios::in | ios::out);
		if (!fp)
		{
			cout << "文件打开失败" << endl;
		}
		fp >> free;
		fp.seekg(40, ios::beg);
		int blockNum = 0;
		fp.read((char*)&block[blockNum], sizeof(Block));
		if (!block[blockNum].identifyChecksum())
		{
			cout << "block " << blockNum << " data error!!!" << endl;
			system("pause");
			exit(-1);
		}
		while (!block[blockNum].showRecord(sid, blockNum))
		{
			blockNum++;
			fp.seekg((40 + blockNum * BLOCKSIZE), ios::beg);
			fp.read((char*)&block[blockNum], sizeof(Block));
			if (!block[blockNum].identifyChecksum())
			{
				cout << "block " << blockNum << " data error!!!" << endl;
				system("pause");
				exit(-1);
			}
		}
		fp.seekp((40 + blockNum * BLOCKSIZE), ios::beg);
		fp.write((char*)&block[blockNum], sizeof(Block));

		fp.close();
	}
};