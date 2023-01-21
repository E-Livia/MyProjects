#include "DBLink.h"

std::unique_ptr<DBLink> DBLink::instance = nullptr;

pqxx::connection* DBLink::GetInstance()
{
    if (instance == nullptr)
    {
        instance.reset(new DBLink());
    }
    return &instance->m_connectionObject;
}
