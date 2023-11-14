#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpPart>
#include <QtNetwork/QHttpMultiPart>

class network_manager : public QObject
{
public:
    network_manager();
    ~network_manager();
    void get_user(std::string username, std::string pass);
    void create_user(std::string email, std::string username, std::string pass);

private:
    QNetworkAccessManager *qnam;
    std::string network_response;
    void get(const char* URL);
    void post(const char* URL, std::string query_str);

private slots:
    void reply_finished(QNetworkReply *reply);
    void network_error();
    void ssl_error();
};

#endif // NETWORK_MANAGER_H
