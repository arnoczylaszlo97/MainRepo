#pragma once
#include<string>
#include "Teglalap.h"

class Negyzet : public Teglalap{
public:
	Negyzet(const Szin szin,const double oldalHossz);

	Teglalap& setMagassag(const double ujMagassag) override;
	Teglalap& setSzelesseg(const double ujMagassag) override;

	operator std::string()const override;
};

