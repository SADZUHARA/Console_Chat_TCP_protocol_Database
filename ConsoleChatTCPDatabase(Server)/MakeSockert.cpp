#include "User.h"
#include "MakeSockert.h"
int MakeSockert()
{
    // Create a socket
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        return socket_file_descriptor;
    }

    // Set the server address
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");//Enter the ip of the server, in this case the local one
    // Set the port number
    serveraddress.sin_port = htons(PORT);
    // Use IPv4
    serveraddress.sin_family = AF_INET;
    // Establish a connection to the server
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Connection with the server failed.!" << endl;
        return connection;
    }
};
void GetLogAndPass(vector<Person>& A) // Receiving registration data from Server
{
    string email;
    string Password;
    cout << "Client is waiting email and Password from Server" << endl;
    std::string output_Log(MESSAGE_LENGTH, 0);// MESSAGE_LENGTH buffer variable to get the Login from Server
    read(socket_file_descriptor, &output_Log[0], MESSAGE_LENGTH - 1); //read calculates a string of size MESSAGE_LENGTH, starting from zero

    string Buffer_Log;// a buffer variable to get Login
    for (int i = 0; i < MESSAGE_LENGTH; i++) //removes the extra 0 from the string and assigns a value to the string email_
    {

        if ((int)output_Log[i] != 0) {
            cout << output_Log[i] << " ";
            email.push_back((char)output_Log[i]);
        }
        else {
            break;
        };
    }; 

    cout << "email received from client: " << email_ << endl;

    std::string output_Pass(MESSAGE_LENGTH, 0);// MESSAGE_LENGTH buffer variable to get Password from Server
    read(socket_file_descriptor, &output_Pass[0], MESSAGE_LENGTH - 1);


    
    for (int i = 0; i < MESSAGE_LENGTH; i++) //removes the extra 0 from the string and assigns a value to the string email_
    {

        if ((int)output_Pass[i] != 0) {
            cout << output_Pass[i] << " ";
            Password.push_back((char)output_Pass[i]);
        }
        else {
            break;
        };
    }; 

    cout << "Password received from client: " << Password << endl;


    A.emplace_back(email, Password); // record of the registered client on Server
};
void GetMessage(vector<Person::Chat>& B)
{
    cout << "Wait message" << endl;
    string Sender;// a buffer variable to get Login
    string Receiver;// a buffer variable to get Password
    string Message;// a buffer variable to receive Message
    std::string output_Sender(MESSAGE_LENGTH, 0);// MESSAGE_LENGTH buffer variable to get Login from Server
    read(socket_file_descriptor, &output_Sender[0], MESSAGE_LENGTH - 1); //read calculates a string of size MESSAGE_LENGTH, starting from zero

    for (int i = 0; i < MESSAGE_LENGTH; i++) //removes the extra 0 from the string and assigns a value to the string email_
    {

        if ((int)output_Sender[i] != 0) {
           
            Sender.push_back((char)output_Sender[i]);
        }
        else
        {
            break;
        };
    };

    cout << "Sender received from client: " << Sender << endl;

    std::string output_Receiver(MESSAGE_LENGTH, 0);// MESSAGE_LENGTH buffer variable to get Password from Server
    read(socket_file_descriptor, &output_Receiver[0], MESSAGE_LENGTH - 1);

    for (int i = 0; i < MESSAGE_LENGTH; i++) //removes the extra 0 from the string and assigns a value to the string email_
    {

        if ((int)output_Receiver[i] != 0) {
            
            Receiver.push_back((char)output_Receiver[i]);
        }
        else {
            break;
        };
    };
    
    cout << "Receiver received from client: " << Receiver << endl;

    std::string output_Message(MESSAGE_LENGTH, 0);// MESSAGE_LENGTH buffer variable to get Password from Server
    read(socket_file_descriptor, &output_Message[0], MESSAGE_LENGTH - 1);

    for (int i = 0; i < MESSAGE_LENGTH; i++) //removes the extra 0 from the string and assigns a value to the string email_
    {

        if ((int)output_Message[i] != 0) {
            
            Message.push_back((char)output_Message[i]);
        }
        else {
            break;
        };
    }; 
    
    cout << "Message received from client: " << Message << endl;

    B.emplace_back(Sender, Receiver, Message); // record of the registered client on Server
};
void Send_Message(string message)
{
    ssize_t bytes = write(socket_file_descriptor, message.c_str(), message.size());//c_str() converts string to const char*

    if (bytes >= 0) {
        //cout << "Message send to the server successfully.!" << message << endl;
    };
    cout << endl;
};

