# pi_large_decimals
Calculate pi value with very large number of decimals using C++ template code, 
based on gnu libraries of infinite precision - gmp, gmpxx, mpfr, mpreal

The pi value is calculated as pi=8.0*atan(sqrt(2)-1);

The atan function is calculated by expanding the Taylor Series
atan(x) =  x - x^3/3 + x^5/5 - x^7/7 + x^9/9 - x^11/11 ...

The code is written using C++ generic (template), where both "double" and "mpreal" can be used.
"mpreal" is a C++ class that represents a float point number with precision as large as necessary.



