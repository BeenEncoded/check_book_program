#include <iostream>
#include <QString>
#include <string>

#include "account.hpp"
#include "utility/stream_operations.hpp"

//stream operators:
namespace data
{
    std::ostream& operator<<(std::ostream& out, const transaction_data& t)
    {
        using utility::out_mem;
        using utility::write_string;
        
        if(out.good())
        {
            out_mem(out, t.value);
            out<< t.date;
            write_string(out, t.name.toStdString());
            write_string(out, t.description.toStdString());
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, transaction_data& t)
    {
        using utility::in_mem;
        using utility::read_string;
        
        t = transaction_data{(decltype(t.value))0, tdata::time_class{}, "", ""};
        std::string temps;
        
        in.peek();
        if(in.good())
        {
            in_mem(in, t.value);
            in>> t.date;
            
            read_string(in, temps);
            t.name = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}, it != temps.end(); ++it) (*it) = 0; 
            
            read_string(in, temps);
            t.description = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}, it != temps.end(); ++it) (*it) = 0;
        }
        return in;
    }
    
    std::ostream& operator<<(std::ostream& out, const account_data& account)
    {
        using utility::out_mem;
        using utility::write_string;
        using utility::write_vector;
        
        if(out.good())
        {
            out_mem(out, account.id);
            write_string(out, account.name.toStdString());
            write_vector<transaction_data>(out, account.transactions);
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, account_data& account)
    {
        using utility::in_mem;
        using utility::read_string;
        using utility::read_vector;
        
        std::string temps;
        
        in.peek();
        if(in.good())
        {
            in_mem(in, account.id);
            read_string(in, temps);
            
            account.name = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}; it != temps.end(); ++it) (*it) = 0;
            
            read_vector<transaction_data>(in, account.transactions);
        }
        return in;
    }
    
    
}