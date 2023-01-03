#pragma once
#include "Sikidom.h"
class Teglalap: public Sikidom{
public:
	Teglalap(const Szin szin, const double magassag, const double szelesseg);

	double magassag() const;
	double szelessge() const;
	virtual Teglalap& setMagassag(double ujMagassag);
	virtual Teglalap& setSzelesseg(double ujSzelesseg);

	double Kerulet() const override;
	double Terulet() const override;

	operator std::string() const override;

private:
	double _magassag;
	double _szelesseg;

};

