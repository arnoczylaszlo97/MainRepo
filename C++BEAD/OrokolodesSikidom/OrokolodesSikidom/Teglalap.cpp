#include "Teglalap.h"
#include <sstream>

Teglalap::Teglalap(const Szin szin,
	const double magassag, const double szelesseg)
	:Sikidom(szin),
	_magassag(magassag),
	_szelesseg(szelesseg)
{}

double Teglalap::magassag() const
{
	return _magassag;
}
double Teglalap::szelessge() const
{
	return _szelesseg;
}
Teglalap& Teglalap::setMagassag(const double ujMagassag)
{
	if (ujMagassag >= 0) {
		_magassag = ujMagassag;
	}
	return *this;
}
Teglalap& Teglalap::setSzelesseg(const double ujSzelesseg)
{
	if (ujSzelesseg >= 0) {
		_szelesseg = ujSzelesseg;
	}
	return *this;
}

double Teglalap::Kerulet() const
{
	return (2*_magassag)+ (2*_szelesseg);
}

double Teglalap::Terulet() const
{
	return _magassag * _szelesseg;
}

Teglalap::operator std::string() const
{
	std::ostringstream oss;
	oss<<"Teglalap az objektum"<<std::endl;
	oss << "Magassag: " << _magassag << 
		", szelesseg: " << _szelesseg << std::endl;
	oss << Sikidom::operator std::string() << std::endl;
	return oss.str();
}