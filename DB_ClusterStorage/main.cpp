#include"File.h"

int main(int argc, char *argv[])
{
	File file;
	
	/*if (file.CreateNullFile(0, 41000, TEXT("my_db_1")))
	{
		cout << "文件创建失败！！！" << endl;
	}*/
	if (!file.open("my_db_1"))
	{
		cout << "文件不存在！！！" << endl;
		system("pause");
		return 0;
	}
	//file.Init();

	//file.removeFile("my_db");
	

	/*Record r[3];
	r[0] = { "fzs",'M',20,201704024,"computer" };
	r[1] = { "wlq",'F',20,201704023,"chemical" };
	r[2] = { "lxy",'F',25,201304022,"chinese" };
	file.addRecord(r[0]);
	file.addRecord(r[1]);
	file.addRecord(r[2]);*/

	file.showRecord(201704024);
	file.showRecord(201704023);
	file.showRecord(201304022);
	
	//file.removeRecord(201704024);
	//file.showRecord(201704024);
	
	/*Record r1 = { "lxy",'F',20,201304022,"English" };
	file.addRecord(r1);
	file.showRecord(201304022);*/

	system("pause");
	return 0;
}