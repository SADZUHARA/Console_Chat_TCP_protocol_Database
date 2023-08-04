#include "User.h"
void  Registration(vector<Person>& A)
{
    string email;
    string Password;
    cout << "Registration stage" << endl;
    cout << "Enter Email: ";
    cin >> email;
    int n = 0;//@ symbol search counter in email
    try
    {
        for (int i = 0; i < email.length(); i++)
        {
            if (email[i] == '@') { n++; };
        };
        if (n == 0) { throw "The Email must have @ "; };

        if (find_email(email) == 0) { throw "This Email already registered "; };

        Send_Message(email);
        cout << endl;
        cout << "Enter Name: ";
        string Name;
        cin >> Name;
        cout << endl;
        cout << "Enter Surname: ";
        string Surname;
        cin >> Surname;
        cout << endl;
        INSERT_INTO_registration_data(Name, Surname, email);
        cout << "Enter Password: ";
        cin >> Password;
        cout << endl;
        Update_INTO_authorization_DATA(email, Password);
        Send_Message(Password);

        GetLogAndPass(A);//Receiving data from the Server stage
    }
    catch (const char* exception)
    {
        std::cout << std::endl;
        std::cout << exception << std::endl;
        std::cout << std::endl;
    }

}