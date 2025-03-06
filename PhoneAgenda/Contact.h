#pragma once
#include <string>
#include <afxstr.h>  


class Contact
{
private:
    int id;
    CString firstName;
    CString lastName;
    CString phone;

public:

    Contact();
    Contact(int id, CString firstName, CString lastName, CString phone);
    
    int GetID() const;
    CString GetFirstName() const;
    CString GetLastName() const;
    CString GetPhone() const;
    CString ToString() const;

};