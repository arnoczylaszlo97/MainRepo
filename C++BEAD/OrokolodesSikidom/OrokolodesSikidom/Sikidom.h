#pragma once
#include<string>
#include <unordered_map>

enum class Szin{
	Feher,
	Fekete,
	Kek,
	Piros,
	Sarga,
	Szurke,
	Zold,

};

class Sikidom //abstract class
{
public:
	Sikidom(const Szin szin); //constructor

	Szin szin() const;	//szin getter
	Sikidom& setSzin(const Szin szin);//szin setter

	virtual double Kerulet() const = 0; //pure virtual->nem kell megvalósítani cpp-ben
	virtual double Terulet() const = 0;

	Sikidom& Kilyukaszt(); 

	virtual operator std::string() const; //virutal->meg kell valosítani cppben

private:
	bool _lyukas;
	Szin _szin;
};

