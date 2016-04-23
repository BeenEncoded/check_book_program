#ifndef DATA_ACCOUNT_HPP_INCLUDED
#define DATA_ACCOUNT_HPP_INCLUDED
#include <QString>
#include <vector>
#include <iostream>

#include "utility/time_class.hpp"

namespace data
{
    struct account_data;
    struct transaction_data;
    
    
    std::ostream& operator<<(std::ostream&, const account_data&);
    std::istream& operator>>(std::istream&, account_data&);
    
    std::ostream& operator<<(std::ostream&, const transaction_data&);
    std::istream& operator>>(std::istream&, transaction_data&);
    
    struct transaction_data
    {
        int_least32_t value;
        tdata::time_class date;
        QString name, description;
    };
    
    struct account_data
    {
        QString name;
        int_least16_t id; //supports 65,536 account ids... I think that will be fine.
        std::vector<transaction_data> transactions;
    };
    
    
}

#endif