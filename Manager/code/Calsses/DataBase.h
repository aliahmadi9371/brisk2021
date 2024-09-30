//---------------------------------------------------------------------------

#ifndef DataBaseH
#define DataBaseH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DbxSqlite.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>

#include "DataBaseQueryCreatorClass.h"
//---------------------------------------------------------------------------
class DataBaseClass
{

private:
protected:
public:
	void CreateTables();
	void CreateObjects();

	void Connect();
	void Disconnect();
	void ShowSelectResults(UnicodeString TableName , int id = 1);

	bool Execute(UnicodeString query);
	void SelectExecute(UnicodeString query ,UnicodeString TableName , int id = 1);

	TSQLConnection* dbConnection;
	TSQLQuery* dbSqlQuery;
	QueryClass* myQuery;


};
//---------------------------------------------------------------------------
#endif

