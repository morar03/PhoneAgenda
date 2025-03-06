#pragma once
#include <string>
#include <vector>
#include <afxdb.h> 
#include "Contact.h"

class DatabaseConnection
{
public:
    DatabaseConnection();
    ~DatabaseConnection();

    bool OpenConnection(const CString& dsn, const CString& user, const CString& password);
    void CloseConnection();

    bool ExecuteQuery(const CString& query);

    bool CreateContactsTable();
    bool LoadContacts(std::vector<Contact>& contacts);
    bool AddContact(const CString& firstName, const CString& lastName, const CString& phone);
    bool DeleteContact(int contactID);
    bool UpdateContact(int contactID, const CString& firstName, const CString& lastName, const CString& phone);

private:
    CDatabase database;
    bool isConnected;
};