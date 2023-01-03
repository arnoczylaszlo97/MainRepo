#include "Kor.h"
#include<cmath>
#include<sstream>

Kor::Kor(const Szin szin, const double sugar)
	:Sikidom(szin)
	, _sugar(sugar)
{}

double Kor::sugar() const
{
	return _sugar;
}
Kor& Kor::setSugar(const double ujSugar)
{
	if (ujSugar >= 0) {
		_sugar = ujSugar;
	}

	return *this;
}

double Kor::Terulet() const
{
	return _sugar * _sugar * std::atan(1) * 4;
}
double Kor::Kerulet() const
{
	return 2*_sugar * std::atan(1) * 4;
}
Kor::operator std::string() const
{
	std::ostringstream oss;
	oss << "Kor az objektum" << std::endl;
	oss << "Sugar: " << _sugar << std::endl;
	oss << Sikidom::operator std::string() << std::endl;
	return oss.str();
}
