//---------------------------------------------------------------------------

#ifndef DataBaseQueryCreatorClassH
#define DataBaseQueryCreatorClassH
//---------------------------------------------------------------------------
class QueryClass
{

private:
protected:
public:
//	LicenseTable License;

	void InitValues();
	UnicodeString CreateTable(UnicodeString TableName);
	UnicodeString Insert(UnicodeString TableName , int id = 1);
	UnicodeString Update(UnicodeString TableName , int id = 1);
	UnicodeString Select(UnicodeString TableName , int id = 1);
	UnicodeString query;
};
//---------------------------------------------------------------------------
#endif

