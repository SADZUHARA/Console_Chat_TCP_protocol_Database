#include "User.h"

void PostgreSQL_conn() {
    // Establish a connection to the database
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");

    // Check the connection status
    if (PQstatus(conn) != CONNECTION_OK) {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
    }
    else
        cout << "Connection to database success: " << PQerrorMessage(conn) << std::endl;

};

int find_email(string email) {
    int i = 1;
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    string query = "SELECT * FROM registration_data WHERE email = '" + email + "'";//create a query string and insert the variable value into the query
    PGresult* res = PQexec(conn, query.c_str());//we execute the query using the PQexec() function

    int rows = PQntuples(res);// if the query is correct, but the email value is not in the database, the number of lines = 0
    if (rows != 0) { i = 0; };
    PQclear(res);
    return i;
};

void INSERT_INTO_registration_data(string Name, string Surname, string email)
{
    std::vector<char> chars_Name(Name.begin(), Name.end());//convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_Name.push_back('\0');

    char* Name_char = &chars_Name[0];

    std::vector<char> chars_Surname(Surname.begin(), Surname.end());//convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_Surname.push_back('\0');

    char* Surname_char = &chars_Surname[0];

    std::vector<char> chars_email(email.begin(), email.end());//convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_email.push_back('\0');

    char* email_char = &chars_email[0];

    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    // Inserting several values into a table
    const char* sql = "INSERT INTO registration_data (name, surname, email) VALUES (v1, v2, v3)";
    const char* params[3] = { Name_char, Surname_char, email_char };
    int lengths[3] = { 255, 255, 255 };
    int formats[3] = { 0, 0, 0 };
    PGresult* res = PQexecParams(conn, sql, 3, NULL, params, lengths, formats, 0);
};

void Update_INTO_authorization_DATA(string email, string password)
{
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    std::string query = "UPDATE authorization_data SET password = '" + password + "' WHERE id_user IN (SELECT registration_data.id_user FROM registration_data WHERE registration_data.email = '" + email + "')";

    //Executing an UPDATE query
    PGresult* res = PQexec(conn, query.c_str());
    PQclear(res);
};
int check_password(string email, string password) {
    int i = 1;
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    std::string query = "select * from registration_data join authorization_data on registration_data.id_user = authorization_data.id_user where registration_data.email = '" + email + "' and authorization_data.password = '" + password + "'";//create a query string and insert the variable value into the query
    PGresult* res = PQexec(conn, query.c_str());//Execute the query using the PQexec() function

    int rows = PQntuples(res);// if the query is correct, but the email value is not in the database, the number of lines = 0
    if (rows == 0) { i = 0; };
    PQclear(res);
    return i;
};

char* get_id(string email)
{
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    string query = "SELECT id_user FROM registration_data WHERE email = '"+email+"'";
    PGresult* res = PQexec(conn, query.c_str());
    char* id_user = PQgetvalue(res, 0, 0);
    PQclear(res);
    return id_user;
};// get user id in the original char* for further use

void INSERT_INTO_history_data(string sender, string receiver, string message)
{
    std::vector<char> chars_message(message.begin(), message.end());// convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_message.push_back('\0');

    char* message_char = &chars_message[0];
    cout << "Sender" << sender << endl << "Receiver" << receiver << endl;
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    string id_sender = get_id(sender);
    string id_receiver = get_id(receiver);
    std::vector<char> chars_id_sender(id_sender.begin(), id_sender.end());// convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_id_sender.push_back('\0');
    char* id_sender_char = &chars_id_sender[0];
    std::vector<char> chars_id_receiver(id_receiver.begin(), id_receiver.end());// convert to Char*, because PQexecParams only accepts Char* in the params graph
    chars_id_receiver.push_back('\0');
    char* id_receiver_char = &chars_id_receiver[0];

    
    const char* sql = "INSERT INTO history_data (id_sender, id_receiver, message) VALUES (v1, v2, v3)";
    const char* params[3] = { id_sender_char, id_receiver_char, message_char };
    int lengths[3] = { 255, 255, 255 };
    int formats[3] = { 0, 0, 0 };
    PGresult* res = PQexecParams(conn, sql, 3, NULL, params, lengths, formats, 0);
    PQclear(res);
};

void show_history(string sender, string receiver)
{
    PGconn* conn = PQconnectdb("user=zinovyse password=9999999999 dbname= postgres");
    string id_sender = get_id(sender);
    string id_receiver = get_id(receiver);
    string query = "SELECT message, send_on FROM history_data WHERE id_sender = '" + id_sender + "' and id_receiver = '" + id_receiver + "'";
    PGresult* res = PQexec(conn, query.c_str());
    int rows = PQntuples(res);
    if (rows == 0) { cout << "you didn't send messages" << endl; }
    else {
        cout << "you are sender:" << endl;
        for (int i = 0; i < rows; ++i) {
            std::cout << "Message: " << PQgetvalue(res, i, 0) << std::endl;
            std::cout << "Date: " << PQgetvalue(res, i, 1) << std::endl;
        };
    };
    string query2 = "SELECT message, send_on FROM history_data WHERE id_sender = '" + id_receiver + "' and id_receiver = '" + id_sender + "'";
    PGresult* res2 = PQexec(conn, query2.c_str());
    int rows2 = PQntuples(res2);
    if (rows2 == 0) { cout << "you didn't receive messages" << endl; }
    else {
        cout << "you are receiver:" << endl;
        for (int i = 0; i < rows2; ++i) {
            std::cout << "Message: " << PQgetvalue(res2, i, 0) << std::endl;
            std::cout << "Date: " << PQgetvalue(res2, i, 1) << std::endl;
        };
    };
};

