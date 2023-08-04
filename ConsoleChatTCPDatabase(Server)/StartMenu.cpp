#include "User.h"
void StartMenu(vector<Person>& A, string email_, vector<Person::Chat>& B)
{
    
    char operat = '0';
    while (operat != '3')
    {
        cout << "Registered users: ";
        for (int i = 0; i < A.size(); i++)
        {
            cout << A[i].email << " " << A[i].password << endl;
        };
        cout << "Good day!" << endl << "Choose number: " << endl << "1 - Register" << endl << "2 - Personal account" << endl << "3 - Exit" << endl;

        cin >> operat;
        switch (operat)
        {
        case '1':

            Registration(A);
            break;
        case '2':
            Login(A,email_,B);

            break;
        default:

            std::cout << "You entered wrong number!" << std::endl;
            std::cout << std::endl;
            break;

        };
    }
}