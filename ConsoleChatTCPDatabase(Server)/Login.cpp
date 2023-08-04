#include "User.h"
void Login(vector<Person>& A, string email_, vector<Person::Chat>& B)
{
    string email;
    string Password;
    int n = 0;
    int k;
    cout << "logging in" << endl;
    cout << "Enter email: ";
    cin >> email;
    cout << endl;
    cout << "Enter Password: ";
    cin >> Password;
    cout << endl;
   
    try
    {
        if (check_password(email, Password) == 0) { throw bad_sing(); }
        else 
        {
            ChatMenu(A, B, email);
        }

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}