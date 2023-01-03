#pragma once
#include "Sikidom.h"
class Kor :public Sikidom{ //leszarmazott a Sikidomból
public:
	Kor(const Szin szin, const double sugar); //constructor
	double sugar() const; //sugarGetter
	Kor& setSugar(const double ujSugar); //sugarSetter

	//pure virtual metodusok megvalósítása
	double Terulet() const override;
	double Kerulet() const override;

	operator std::string() const override;
private:
	double _sugar;
};

