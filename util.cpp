#include "util.h"
#include <QCryptographicHash>

void util::sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string util::hash_string(std::string data)
{
    QCryptographicHash hashfunc(QCryptographicHash::Sha256);
    QByteArray hashed = hashfunc.hash(QByteArrayView(data.c_str()), QCryptographicHash::Sha256);
    hashed = hashed.toBase64();
    std::string new_data = hashed.toStdString();

    return new_data;
}
