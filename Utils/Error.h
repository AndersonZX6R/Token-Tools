/***
 * Error.h
 *
 * Copyright(c) 2013 - Eng.º Anderson Marques Ribeiro.
 *
 * 06 de Janeiro de 2013.
 */

#ifndef __ERROR
#define __ERROR

#include <string>

using namespace std;

namespace UTILS
{

#define DECLARE_ERROR_CODE( name ) const UTILS::ErrorCodeType name = UTILS::LAST_ERROR_CODE++

#define BEGIN_DECLARE_ERROR( name ) \
class name : public UTILS::Error \
{ \
public: \
    name (UTILS::ErrorCodeType ec) : UTILS::Error(ec) \
    {}; \
protected: \
    char *getErrorMessage(UTILS::ErrorCodeType ec) const \
    { \

#define DECLARE_ERROR( name, message ) \
        if (name == getError()) return message;

#define END_DECLARE_ERROR \
        return UTILS::Error::getErrorMessage(ec); \
    }; \
}

#define RAISE( errorName, errorCode ) throw errorName( errorCode )

typedef long ErrorCodeType;

class Error
{
public:

    Error(ErrorCodeType err) :
        m_ec(err)
    {};

private:

    ErrorCodeType m_ec;

protected:

    virtual char *getErrorMessage(ErrorCodeType ec) const
    {
        return "Unknown error";
    };

public:

    ErrorCodeType getError() const
    {
        return m_ec;
    };
    virtual char *getMessage() const
    {
        return getErrorMessage(getError());
    };

}; // class Error

extern ErrorCodeType LAST_ERROR_CODE;

DECLARE_ERROR_CODE(ERR_MEMORY_ALLOCATION);

BEGIN_DECLARE_ERROR(EMemory)
    DECLARE_ERROR(ERR_MEMORY_ALLOCATION, "Tentativa de alocação de memória falhou");
END_DECLARE_ERROR;

}; // namespace UTILS

#endif // ifndef __ERROR
