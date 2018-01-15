#include "exception.h"


Exception::Exception(QString const &message)
:
    m_message(message)
{}


QString Exception::what() const {
    return m_message;
}
