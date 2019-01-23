// $Id: ubigint.cpp,v 1.14 2016-06-23 17:21:26-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iterator> 
#include <sstream>
#include <algorithm>

using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (long that) {
   unsigned char x;
   unsigned long y;
  if(that == 0)
  {
        uvalue.push_back('0');
  } 
  else{
   while(that > 0)
   {
	y = that % 10;
 	x = y + '0';
   	uvalue.push_back(x);
  	that/=10;
	 DEBUGF ('~', this << " -> " << y)
   }  
  }
   /*uvalue.push_back('1');
   uvalue.push_back('3');
   uvalue.push_back('9'); 
  *///cout << "aliiii" << endl;
  
}

ubigint::ubigint (const string& that) {
  DEBUGF ('~', "that = \"" << that << "\"");
   for (char digit: that) {
      if (not isdigit (digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
 	    uvalue.push_back(digit);
     // uvalue = uvalue * 10 + digit - '0';
   }

		reverse(uvalue.begin(), uvalue.end());
//uvalue.push_back('5');
}

ubigint ubigint::operator+ (const ubigint& that) const {
   
	 vector<unsigned char> resault;
        unsigned long remainder = 0;
        unsigned long i = 0;
        unsigned long digit= 0;
	unsigned char dig;
	unsigned long sum = 0;
        unsigned long uval;
	unsigned long that_uval;
	
	while(true)
       {
		if(i >= uvalue.size() && i >= that.uvalue.size() && remainder == 0)
		{
			break;
		}
		else if(i >= uvalue.size() && i >= that.uvalue.size() && remainder == 1)
		{
			dig = remainder + '0';
			resault.push_back(dig);
			remainder = 0;
		}
		else if(i < uvalue.size() && i < that.uvalue.size()) 
		{	
			
			uval = uvalue[i] - '0';
			that_uval = that.uvalue[i] - '0';

			sum = remainder + uval + that_uval;
			remainder = sum / 10 ;
			digit = sum % 10 ;
			dig = digit + '0';
			resault.push_back(dig);
	
  	                i++;
        	}
		else if(i >= uvalue.size())
		{
						
			uval = 0;
			that_uval = that.uvalue[i] - '0';

			sum = remainder + uval + that_uval;
			remainder = sum / 10 ;
			digit = sum % 10 ;
			dig = digit + '0';
			resault.push_back(dig);
	
  	                i++;
		}
		
		else if(i >= that.uvalue.size())
		{
						
			uval = uvalue[i] - '0';
			that_uval = 0;

			sum = remainder + uval + that_uval;
			remainder = sum / 10 ;
			digit = sum % 10 ;
			dig = digit + '0';
			resault.push_back(dig);
	
  	                i++;
		}
		else{
			//! is my error msg saying something is wrong
			resault.push_back('!');
		}	

       

	}
	
     //put it there in reverse
	string getstr (resault.rbegin(), resault.rend());

    return ubigint(getstr);
}

ubigint ubigint::operator- (const ubigint& that) const {
   	if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   
 	vector<unsigned char> res;
     long uval;
     long that_uval;
     long sub = 0;
    unsigned long digit;
     char dig;	
	 long borrow = 0;
	unsigned long i = 0;
    long dif = 0;
   if(*this == that)
    {
       // res.push_back('0');
  //   return ubigint(0);
    }
    else{
	while (true)
   	 {
 		
		if(i >= uvalue.size())
		{
			break;
		}

		else if(i < uvalue.size() && i < that.uvalue.size()) 
		{	
			uval = uvalue[i] - '0';
			that_uval = that.uvalue[i] - '0';
			dif = uval - that_uval - borrow;
			
			if (dif < 0)
			{
				dif += 10;
				borrow = 1;	
			}
			else{
				
				borrow = 0;
			}

			dig = dif + '0';
			res.push_back(dig);
	
  	                i++;
        }
	  
		else if(i >= that.uvalue.size())
		{
						
			uval = uvalue[i] - '0';
			that_uval = 0;

			dif = uval - that_uval - borrow;

			if (dif < 0)
			{
				dif += 10;
				borrow = 1;			
			}
			else{
				borrow = 0;
			}

			dig = dif + '0';
			res.push_back(dig);
	
  	                i++;
		}
		else{
			//! is my error msg saying something is wrong
			res.push_back('!');
			break;
		}	
		
	}
    }
    //vector<unsigned char> zero() = {'0'};
    while (res.size() > 0 and res.back() == '0') res.pop_back();
     //put it there in reverse
	string getstr (res.rbegin(), res.rend());
    return ubigint(getstr);

}

ubigint ubigint::operator* (const ubigint& that) const {
    
    //initializing a vector of size m+n filled with zeros
    vector<unsigned char> res (uvalue.size() + that.uvalue.size(), '0');
    
    long carry;
    long d;
    long uval;
    long tval;
    long digit;
    char dig;
    for(int i = 0 ; i < uvalue.size() ; i++)
    {
        uval = uvalue[i] - '0';
        carry = 0;
        for(int j = 0 ; j < that.uvalue.size(); j++)
        {
             tval = that.uvalue[j] - '0';
            d = (res[i+j] - '0') + (uval * tval) + carry;
             digit = d % 10; 
             dig = digit + '0';
            res[i+j] = dig;
            carry = d / 10;
        }
        res[i+(that.uvalue.size())] = carry + '0';
    }

    while (res.size() > 0 and res.back() == '0') res.pop_back();
	string getstr (res.rbegin(), res.rend());
    return ubigint(getstr);


}

void ubigint::multiply_by_2() {
    vector<unsigned char> temp = uvalue;
    vector<unsigned char> vec2{'2'};
   vector<unsigned char> res (temp.size() + vec2.size(), '0'); 
    long carry;
    long d;
    long uval;
    long tval;
    long digit;
    char dig;
    for(int i = 0 ; i < temp.size() ; i++)
    {
        uval = temp[i] - '0';
        carry = 0;
        for(int j = 0 ; j < vec2.size(); j++)
        {
             tval = vec2[j] - '0';
            d = (res[i+j] - '0') + (uval * tval) + carry;
             digit = d % 10; 
             dig = digit + '0';
            res[i+j] = dig;
            carry = d / 10;
        }
        res[i+(vec2.size())] = carry + '0';
    }

    while (res.size() > 0 and res.back() == '0') res.pop_back();
	string getstr (res.rbegin(), res.rend());
    uvalue.clear();
    uvalue = res;
}

void ubigint::divide_by_2() {
    vector<unsigned char> two {'2'};
    vector<unsigned char> res;

    long sub;
    long calc;
    long uval = uvalue.back() - '0';

    for(int i = uvalue.size() - 1; i >= 0 ; --i)
    {
        if(uval >= 2)
        {
            calc = uval / 2;
            res.push_back(calc + '0');

            if(i == 0)
                break;
            else
            {
                  sub = uval - (2 * calc);
                  uval = (sub * 10) + (uvalue[i - 1] - '0');
            }
    
        }
        else
        {
             if(uval == 0)
             {
                 res.push_back('0');
                 uval = (uvalue[i - 1] - '0');
             }
             else
             {
                 res.push_back('0');
                 uval = (uvalue[i - 1] - '0') + (uval * 10); 
             }

        }
    }

    //while (res.size() > 0 and res.back() == '0') res.pop_back();
	string getstr (res.rbegin(), res.rend());
    uvalue.clear();
    vector<unsigned char> ans (getstr.begin(), getstr.end());
    while (ans.size() > 0 and ans.back() == '0') ans.pop_back();
    uvalue = ans;
   // uvalue.clear();
    /*for(int i = res.size() - 1; i >= 0; --i)
    {
        //uvalue.push_back(res[i]);
        uvalue[i]=res[i];
    }
    
    while (uvalue.size() > 0 and uvalue.back() == '0') uvalue.pop_back();
    */
}

struct quo_rem 
{
    ubigint quotient; 
    ubigint remainder; 
};

quo_rem udivide (const ubigint& dividend, ubigint divisor) {
   // Note: divisor is modified so pass by value (copy).
   
   ubigint zero("0");
   if (divisor == zero) throw domain_error ("udivide by zero");
   
   ubigint power_of_2("1");
   ubigint quotient ("0");

  // ubigint remainder;
 // ubigint remainder;
  //remainder.uvalue = dividend.uvalue;
   // string getstr (dividend.uvalue.rbegin(), dividend.uvalue.rend());
  
    ubigint remainder = dividend;// (getstr);
  // left operand, dividend

   ubigint test("192");
   //test = test - divisor;
   ubigint one ("1");
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }

bool a = true;
   //test = remainder;
   while (zero < power_of_2) {
    
      if (divisor < remainder or (divisor == remainder)) { 
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
         
         //test = test + one;
      }
      divisor.divide_by_2();
      
      power_of_2.divide_by_2();  
   }
   //test.divide_by_2();
  // test = divisor;
  
         if(remainder < zero)
            remainder = zero;
      return {.quotient = quotient, .remainder = remainder};
    // return {.quotient = test  , .remainder = remainder};
}




ubigint ubigint::operator/ (const ubigint& that) const {
   
  return udivide (*this, that).quotient; 
 // return udivide (*this, that).remainder; 
 //   ubigint a ("24"); 
  // a.divide_by_2(); 
  // return a;
}

ubigint ubigint::operator% (const ubigint& that) const {
   
   return udivide (*this, that).remainder;
   //return that;
}

bool ubigint::operator== (const ubigint& that) const {
   //return uvalue == that.uvalue;

	long dif = 1;
	long number;
	//long i = uvalue.size()-1;
	long i = uvalue.size() - 1;
	long uval;
	long tuval;
 
	if(uvalue.size() != that.uvalue.size())
	{
		return false;	
	}
	else{
		while (i >= 0)
		{
			uval = uvalue[i] - '0';
			tuval = that.uvalue[i] - '0';
				
			if(uval != tuval)
				return false;

			i--;			
		}
	}

   return true;
}

bool ubigint::operator< (const ubigint& that) const {
  // return uvalue < that.uvalue;
	long dif = 1;
	long number;
	//long i = uvalue.size()-1;
	long i = uvalue.size() - 1;
	long uval;
	long tuval;
 
	/* for(unsigned int i = uvalue.size()-1 ; i >= 0 ; i--)
  		{
			number = uvalue[i] - '0';
			dif = dif * 10 + number;
		 { 
	*/
	if(uvalue.size() < that.uvalue.size())
	{
		return true;	
	}
	else if(uvalue.size() > that.uvalue.size())
	{
		return false;
	}
	else if(uvalue.size() == that.uvalue.size()){
		while (true)
		{
			uval = uvalue[i] - '0';
			tuval = that.uvalue[i] - '0';
				
			if(uval < tuval)
            {
				return true;
            }
                
            else if( uval > tuval || i == 0)
            {
				return false;
            }
          
			i--;			
		}
	}

    return true;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
      vector<unsigned char> temp (that.uvalue);
	   	out << "ubigint(";

copy(that.uvalue.rbegin(), that.uvalue.rend(), ostream_iterator<char>(out, ""));
//reverse_copy(that.uvalue.begin(), that.uvalue.end(), ostream_iterator<char>(out, ""));
	//reverse(temp.begin(), temp.end());
	/*for(auto i : that.uvalue)
	{
			out << i;
	}*/
 	out << ")";
	return out;
}

