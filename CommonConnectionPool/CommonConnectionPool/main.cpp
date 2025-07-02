#include <iostream>
#include "Connection.h"
#include "CommonConnectionPool.h"


using namespace std;

int main()
{
	//Connection conn;
	//char sql[1024] = { 0 };
	//sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
	//	"Zhang San", 20, "male");
	//conn.connect("127.0.0.1", 3306, "root", "adminroot", "chat");
	//conn.update(sql);

	clock_t begin = clock();
	/*ConnectionPool* cp = ConnectionPool::GetConnectionPool();*/
	//for (int i = 0; i < 1000; ++i)
	//{
	//	Connection conn;
	//	char sql[1024] = { 0 };
	//	sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
	//"Zhang San", 20, "M");
	//	shared_ptr<Connection> sp = cp->GetConnection();
	//	sp->update(sql);
	//}

	thread t1([]() {
		ConnectionPool* cp = ConnectionPool::GetConnectionPool();
		for (int i = 0;i < 1250; i++)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
				"Zhang San", 20, "M");
			shared_ptr<Connection> sp = cp->GetConnection();
			sp->update(sql);
		}
		});

	thread t2([]() {
		ConnectionPool* cp = ConnectionPool::GetConnectionPool();
		for (int i = 0;i < 1250; i++)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
				"Zhang San", 20, "M");
			shared_ptr<Connection> sp = cp->GetConnection();
			sp->update(sql);
		}
		});

	thread t3([]() {
		ConnectionPool* cp = ConnectionPool::GetConnectionPool();
		for (int i = 0;i < 1250; i++)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
				"Zhang San", 20, "M");
			shared_ptr<Connection> sp = cp->GetConnection();
			sp->update(sql);
		}
		});

	thread t4([]() {
		ConnectionPool* cp = ConnectionPool::GetConnectionPool();
		for (int i = 0;i < 1250; i++)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s',%d,'%s')",
				"Zhang San", 20, "M");
			shared_ptr<Connection> sp = cp->GetConnection();
			sp->update(sql);
		}
		});

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
	return 0;
}