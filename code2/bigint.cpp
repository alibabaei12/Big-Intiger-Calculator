// $Id: bigint.cpp,v 1.76 2016-06-14 16:34:24-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
    
    DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {

   return *this;
}

bigint bigint::operator- () const {

   //return {uvalue, not is_negative};
   return *this;
}

bigint bigint::operator+ (const bigint& that) const {
    
    if(is_negative && that.is_negative)
    {
      
      return bigint (uvalue + that.uvalue, true);
    }

    else if (!is_negative && !that.is_negative)
    {
        
       return bigint (uvalue + that.uvalue, false);
    }

    //if first one is positive and the second is negative
    else if(!is_negative && that.is_negative)
    {
        if(uvalue < that.uvalue)
        {
            return bigint(that.uvalue - uvalue , true);
        }
        else if (that.uvalue < uvalue)
        {
            return bigint(uvalue - that.uvalue , false);
        }
        else
        {
            // they have the same value then its zero
            return bigint( uvalue - that.uvalue, false);
        }
    }
    
    //if first is negative and second is positive

    else if(is_negative && !that.is_negative)
    {
        if(uvalue < that.uvalue)
        {
            return bigint(that.uvalue - uvalue , false);
        }
        else if (that.uvalue < uvalue)
        {
            return bigint(uvalue - that.uvalue , true);
        }
        else
        {
            // they have the same value then its zero
            return bigint( uvalue - that.uvalue, false);
        }
    }

    
}

bigint bigint::operator- (const bigint& that) const {
   
    if(*this == that)
    {
        return bigint("0");
    }
    if(is_negative && !that.is_negative)
    {
      
      return bigint (uvalue + that.uvalue, true);
    }

    else if (!is_negative && that.is_negative)
    {
        
       return bigint (uvalue + that.uvalue, false);
    }

    else if(!is_negative && !that.is_negative)
    {
        if(uvalue < that.uvalue)
        {
            return bigint(that.uvalue - uvalue , true);
        }
        else if (that.uvalue < uvalue)
        {
            return bigint(uvalue - that.uvalue , false);
        }
        else
        {
            // they have the same value then its zero
            return bigint( uvalue - that.uvalue, false);
        }
    }
    

    else if(is_negative && that.is_negative)
    {
        if(uvalue < that.uvalue)
        {
            return bigint(that.uvalue - uvalue , false);
        }
        else if (that.uvalue < uvalue)
        {
            return bigint(uvalue - that.uvalue , true);
        }
        else
        {
            // they have the same value then its zero
            return bigint( uvalue - that.uvalue, false);
        }
    }

   
}

bigint bigint::operator* (const bigint& that) const {
    
    if(is_negative && !that.is_negative || !is_negative && that.is_negative )
    {
      
      return bigint (uvalue * that.uvalue, true);
    }

    else if(!is_negative && !that.is_negative || is_negative && that.is_negative)
    {
            return bigint(that.uvalue * uvalue , false);
    }
    
}

bigint bigint::operator/ (const bigint& that) const {
   
    if(is_negative && !that.is_negative || !is_negative && that.is_negative )
    {
      
      return bigint (uvalue / that.uvalue, true);
    }

    else if(!is_negative && !that.is_negative || is_negative && that.is_negative)
    {
            return bigint(uvalue / that.uvalue , false);
    }
  // bigint result = uvalue / that.uvalue;
  // return result;
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const {
    
    if(is_negative != that.is_negative)
    {
      return false;
    }
    
    else
    {
        if(uvalue == that.uvalue)
        return true;
        else return false;
    }
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? that.uvalue < uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
        
   
  return  out << "bigint(" << (that.is_negative ? "-" : "+") << "," << that.uvalue << ")";

}

