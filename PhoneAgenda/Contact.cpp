#include "pch.h"
#include "Contact.h"


Contact::Contact()
    : id(0), firstName(_T("")), lastName(_T("")), phone(_T(""))
{
}

Contact::Contact(int id, CString firstName, CString lastName, CString phone)
    :id(id), firstName(firstName), lastName(lastName), phone(phone)
{
}

CString Contact::GetFirstName() const
{
    return firstName;
}

CString Contact::GetLastName() const
{
    return lastName;
}

CString Contact::GetPhone() const
{
    return phone;
}

int Contact::GetID() const
{
    return id;
}

CString Contact::ToString() const
{
    return firstName + _T(" ") + lastName + _T(" - ") + phone;
}