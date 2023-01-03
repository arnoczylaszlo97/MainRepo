#include "Sikidom.h"
#include <sstream>


//seged dict a toStringhezs
std::unordered_map<Szin, std::string> szinToString = {
	{Szin::Feher,"Feher"},
	{Szin::Fekete,"Fekete"},
	{Szin::Kek,"Kek"},
	{Szin::Piros,"Piros"},
	{Szin::Sarga,"Sarga"},
	{Szin::Szurke,"Szurke"},
	{Szin::Zold,"Zold"}
};

Sikidom::Sikidom(const Szin szin) //constructor
	:_lyukas(false)
	, _szin(szin)
{}
Szin Sikidom::szin() const // szin getter
{
	return _szin;
}
Sikidom& Sikidom::setSzin(const Szin szin) //Sikidom& - Sikidom referencia
{
	_szin = szin;
	return *this; //éppen aktuális példány visszaadása
}

Sikidom& Sikidom::Kilyukaszt()
{
	if (Terulet() > Kerulet()) {
		_lyukas = true;
	}

	return *this;
}

Sikidom::operator std::string() const
{
	std::ostringstream oss;
	oss << (_lyukas ? "lyukas" : "teli") << std::endl;
	oss << szinToString[_szin] << std::endl;
	oss << "Terulet: " << Terulet() << std::endl;
	oss << "Kerulet: " << Kerulet() << std::endl;
	return oss.str();
}
