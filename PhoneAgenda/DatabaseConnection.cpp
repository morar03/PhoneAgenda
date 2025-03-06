#include "pch.h"
#include "DatabaseConnection.h" 

DatabaseConnection::DatabaseConnection() : isConnected(false)
{
}

DatabaseConnection::~DatabaseConnection()
{
    if (isConnected)
    {
        CloseConnection();
    }
}

bool DatabaseConnection::OpenConnection(const CString& dsn, const CString& user, const CString& password)
{
    try
    {
        CString connectionString;
        connectionString.Format(_T("DSN=%s;UID=%s;PWD=%s;"), dsn, user, password);

        database.OpenEx(connectionString, CDatabase::noOdbcDialog);
        isConnected = true;

        return true;
    }
    catch (CDBException* e)
    {
        AfxMessageBox(e->m_strError);
        e->Delete();
        return false;
    }
}

void DatabaseConnection::CloseConnection()
{
    if (isConnected)
    {
        database.Close();
        isConnected = false;
    }
}

bool DatabaseConnection::ExecuteQuery(const CString& query)
{
    try
    {
        CRecordset recordset(&database);
        recordset.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);
        return true;
    }
    catch (CDBException* e)
    {
        AfxMessageBox(e->m_strError);
        e->Delete();
        return false;
    }
}

bool DatabaseConnection::CreateContactsTable()
{
    if (isConnected) {
        try
        {
            CString createTableSQL = _T(
                "IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Contacts' AND xtype='U') "
                "CREATE TABLE Contacts ("
                "ID INT IDENTITY(1,1) NOT NULL, "
                "FirstName VARCHAR(100), "
                "LastName VARCHAR(100), "
                "Phone VARCHAR(20), "
                "PRIMARY KEY (ID)"
                ");"
            );
            database.ExecuteSQL(createTableSQL);
            return true;
        }
        catch (CDBException* e)
        {
            AfxMessageBox(e->m_strError);
            e->Delete();
            return false;
        }

    }
    return false;
}

bool DatabaseConnection::AddContact(const CString& firstName, const CString& lastName, const CString& phone)
{
    if (isConnected)
    {
        try
        {
            CString insertSQL;
            insertSQL.Format(_T(
                "INSERT INTO Contacts (FirstName, LastName, Phone) "
                "VALUES ('%s', '%s', '%s');"
            ), firstName, lastName, phone);

            database.ExecuteSQL(insertSQL);
            return true;
        }
        catch (CDBException* e)
        {
            AfxMessageBox(e->m_strError);
            e->Delete();
            return false;
        }
    }
    return false;
}


bool DatabaseConnection::LoadContacts(std::vector<Contact>& contacts)
{
    if (isConnected)
    {
        try
        {
            contacts.clear();

            CString selectSQL = _T("SELECT ID, FirstName, LastName, Phone FROM Contacts;");

            CRecordset recordset(&database);
            recordset.Open(CRecordset::forwardOnly, selectSQL, CRecordset::readOnly);

            while (!recordset.IsEOF())
            {
                
                CString idStr, firstName, lastName, phone;

                recordset.GetFieldValue(_T("ID"), idStr);
                recordset.GetFieldValue(_T("FirstName"), firstName);
                recordset.GetFieldValue(_T("LastName"), lastName);
                recordset.GetFieldValue(_T("Phone"), phone);

                int id = _ttoi(idStr);

                Contact contact(id, firstName, lastName, phone);

                contacts.push_back(contact);

                recordset.MoveNext();
            }

            return true;
        }
        catch (CDBException* e)
        {
            AfxMessageBox(e->m_strError);
            e->Delete();
            return false;
        }
    }

    return false;
}

bool DatabaseConnection::DeleteContact(int contactID)
{
    if (isConnected)
    {
        try
        {
            CString deleteSQL;
            deleteSQL.Format(_T("DELETE FROM Contacts WHERE ID = %d;"), contactID);

            database.ExecuteSQL(deleteSQL);
            return true;
        }
        catch (CDBException* e)
        {
            AfxMessageBox(e->m_strError);
            e->Delete();
            return false;
        }
    }
    return false;
}

bool DatabaseConnection::UpdateContact(int contactID, const CString& firstName, const CString& lastName, const CString& phone)
{
    if (isConnected)
    {
        try
        {
            CString updateSQL;
            updateSQL.Format(_T("UPDATE Contacts SET FirstName = '%s', LastName = '%s', Phone = '%s' WHERE ID = %d;"),
                firstName, lastName, phone, contactID);

            database.ExecuteSQL(updateSQL);
            return true;
        }
        catch (CDBException* e)
        {
            AfxMessageBox(e->m_strError);
            e->Delete();
            return false;
        }
    }
    return false;
}