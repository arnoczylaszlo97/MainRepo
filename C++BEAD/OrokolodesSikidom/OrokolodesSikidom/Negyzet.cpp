#include "Negyzet.h"
#include<sstream>

Negyzet::Negyzet(const Szin szin, const double oldalHossz)
	:Teglalap(szin, oldalHossz, oldalHossz)
{}

Teglalap& Negyzet::setMagassag(const double ujMagassag)
{
	Teglalap::setMagassag(ujMagassag);
	return Teglalap::setSzelesseg(ujMagassag);
}

Teglalap& Negyzet::setSzelesseg(const double ujSzelesseg)
{
	setSzelesseg(ujSzelesseg);
	return Teglalap::setMagassag(ujSzelesseg);
}

Negyzet::operator std::string() const
{
	std::ostringstream oss;
	oss << "Negyzet az objektum " << std::endl;
	oss << "Oldalhossz:  " << magassag() << std::endl;
	oss << Sikidom::operator std::string() << std::endl;
	return oss.str();
}