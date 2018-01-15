#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <QString>


class Exception
{
public:
    Exception(QString const &message);
    ~Exception() = default;
    QString what() const;
private:
    QString m_message;
};


#endif // EXCEPTION_H
