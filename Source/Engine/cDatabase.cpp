#include "cDatabase.h"
#include <string>

void cDatabase::OpenDB(std::string dname)
{
	int test = sqlite3_open("entity.db", &m_database);
	if(test){
		std::cout << "Database connection failed";
	}
}

void cDatabase::GetIndex(std::string tablename)
{
	std::string command = "select * from " + tablename;
	if(sqlite3_prepare_v2(m_database, command.c_str(), 
		-1, &m_statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(m_statement);
		int result = 0;
		std::string s;
		while(true)
		{
			result = sqlite3_step(m_statement);
			
			if(result == SQLITE_ROW)	// R there row remaining?
			{
				s = (char*)sqlite3_column_text(m_statement, 0);
				m_tableid.push_back(s);
			}
			else
			{
				break;   
			}
		}
		for (size_t i=0; i<m_tableid.size(); i++)
		{
			//std::cout << m_tableid[i] << " ";
		}
		sqlite3_finalize(m_statement);
	}
	//sqlite3_close(m_database);
}

int cDatabase::GetValueByDoubleIndex(std::string colindex1,
									std::string colvalue1,
									std:: string colindex2, 
									std::string tablename)
{
	// e.g. select from enemy where id=0Cleric
	std::string command = "select * from " + tablename +
						" where " + colindex1 + "= '" +
						colvalue1 + "'";
	std::cout << command << "\n";
	int value, column;
	for (size_t i = 0; i < m_tableid.size(); i ++)
	{
		if (m_tableid[i] == colindex2) 
		{
			column = i + 1;
			std::cout << colindex2 << " is column " << column << "\n";
			break;
		}
	}

	// e.g. we want to find the HP of 0Cleric
	// First we need to know which column contains HP value
	// So we will consult m_tableid for the column of HP
	// Which is the index of HP in the vector PLUS ONE
	if(sqlite3_prepare_v2(m_database, command.c_str(), 
		-1, &m_statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(m_statement);
		std::cout << "We have a total of " << cols << " columns" << "\n";
		int result = 0;
		std::string s;
		while(true)
		{
			result = sqlite3_step(m_statement);
			
			if(result == SQLITE_ROW)	// R there row remaining?
			{
				for(int col = 0; col < cols; col++)
				{
					if (col == column -1)
					{
						s = (char*)sqlite3_column_text(
						m_statement, col);

						value = atoi(s.c_str());
						std::cout << colvalue1 << "'s " <<
								colindex2 << " is " << s << "\n";
					}
				}
				//s = (char*)sqlite3_column_text(m_statement, 0);
			}
			else
			{
				break;   
			}
		}
		sqlite3_finalize(m_statement);
	}
	//sqlite3_close(m_database);
	return value;
}