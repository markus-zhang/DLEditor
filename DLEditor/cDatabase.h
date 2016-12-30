#ifndef	CDATABASE_H_
#define CDATABASE_H_

#include "DebugTool.h"
#include "sqlite3.h"
#include <vector>

class cDatabase
{
public:
	void OpenDB(std::string dbname);
	void GetIndex(std::string tablename);	// Store index in m_tableid
	// GVBDI() is to find a specific element, e.g. HP of 0Cleric
	int  GetValueByDoubleIndex(std::string colindex1, 
								std::string colvalue1,
								std::string colindex2,
								std::string tablename);
private:
	sqlite3* m_database;
	sqlite3_stmt* m_statement;
	std::vector<std::string> m_tableid;
};

#endif