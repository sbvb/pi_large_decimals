// pi_calc_gen.cpp
// by sbVB (www.sbvb.com.br, sbvillasboas@gmail.com)

// install libraries gmp, gmpxx, mpfr, mpreal
// compile using line command below
// g++ -std=c++11 -I /usr/local/include -L/usr/local/lib/ pi_calc_gen.cpp -lgmp -lgmpxx -lmpfr -o pi_calc_gen

/* 

value of pi, to chech result

 3.14159265358979323846264338327950288419716939937510
   58209749445923078164062862089986280348253421170679
   82148086513282306647093844609550582231725359408128
   48111745028410270193852110555964462294895493038196
   44288109756659334461284756482337867831652712019091
   45648566923460348610454326648213393607260249141273
   72458700660631558817488152092096282925409171536436
   78925903600113305305488204665213841469519415116094
   33057270365759591953092186117381932611793105118548
   07446237996274956735188575272489122793818301194912
   98336733624406566430860213949463952247371907021798
   60943702770539217176293176752384674818467669405132
   00056812714526356082778577134275778960917363717872
   14684409012249534301465495853710507922796892589235
   42019956112129021960864034418159813629774771309960
   51870721134999999837297804995105973173281609631859
   50244594553469083026425223082533446850352619311881
   71010003137838752886587533208381420617177669147303
   59825349042875546873115956286388235378759375195778
   18577805321712268066130019278766111959092164201989
*/



#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include "gmpxx.h"
#include "mpfr.h"
#include "mpreal.h"
using namespace std;
using namespace mpfr;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// atan
// atan(x) =  x - x^3/3 + x^5/5 - x^7/7 + x^9/9 - x^11/11 ...

template <typename T>
T my_atan_gen2(const T & x, const T & eps) {
// static T my_atan_gen2(const T & x) {
	// T eps = T("1e-20");
	T signal = T(-1.0);
	T ret = x;
	// mpreal eps = mpreal("1e-20");
	T num = x * x * x;
	T den = T(3.0);

	T factor = num/den;
	int iterace = 0;

    while (fabs(factor) > fabs(eps * x)) {
        ret += signal * factor;
        num = num * x * x;
        den += T(2.0);
        factor = num/den;
        signal *= T(-1.0);
        iterace++;
	    // cout << "DEBUG iterace=" << iterace << ", factor=" << factor << ", den=" << den << ", num=" << num << endl;
    }
    return ret;
};

template <typename T>
struct MyTrait
{
	static T str2real(const char *epsStr) {
		return T(epsStr);
	}
}; // end of MyTrait

template <>
struct MyTrait<double>
{
	static double str2real(const char *epsStr) {
		ostringstream oss;
		oss << epsStr;
		double ret = atof(oss.str().c_str());
		return ret;
	}
}; // end of MyTrait

template<typename T>
T my_atan_gen(const T & x, const char *epsStr = "1e-50")
{
	T eps = MyTrait<T>::str2real(epsStr);
	// return MyTrait<T>::my_atan_gen2(x,eps);
	return my_atan_gen2(x,eps);
};


void test_my_atan_gen() {
	cout << "=== test_my_atan_gen()" << endl;
	mpreal::set_default_prec(1660);

    for (mpreal x = mpreal("0.0"); x < mpreal("0.5"); x += mpreal("0.1")) {
    	double ax = atan(x.toDouble());
    	double maxd = my_atan_gen<double>(x.toDouble(),"1e-50");
    	mpreal max = my_atan_gen<mpreal>(x,"1e-50");
    	// double maxd = my_atan_gen<double>(x.toDouble());
    	// mpreal max = my_atan_gen<mpreal>(x);
    	cout << setprecision(20) << "x=" << x << ", atan(x)=" << ax << ", my_atan_gen<double>(x)=" << maxd << ", my_atan_gen<mpreal>(x)=" << max << ", diff=" << ax-max << endl;
    }

}

// decs = number of decimals of precision
void my_pi(int decs = 5500) {
	cout << "=== my_pi()" << endl;
  mpreal::set_default_prec(4*decs);

	mpreal x = sqrt(mpreal("2.0"))-mpreal("1.0");
	ostringstream eps_oss;
	eps_oss << "1e-" << decs;
	cout << "pi shown with " << decs << " decimals" << endl;
	mpreal my_pi = mpreal("8.0")*my_atan_gen<mpreal>(x,eps_oss.str().c_str());
    cout << setprecision(decs) << my_pi << endl;
}


int main() {
	cout << "====== sbVB pi calc" << endl;
	my_pi(1000);

  return 0;
}


