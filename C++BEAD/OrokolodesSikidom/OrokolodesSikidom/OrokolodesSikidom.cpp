#include <iostream>
#include<vector>
#include "Sikidom.h"
#include "Kor.h"
#include "Teglalap.h"
#include "Negyzet.h"

std::shared_ptr<Teglalap> TeglalapotVagyNegyzetetLetrehoz(const double a, const double b)
{
	if (a == b) {
		return std::make_shared<Negyzet>(Szin::Feher, a);
	}
	else {
		return std::make_shared<Teglalap>(Szin::Feher, a, b);
	}
}

std::shared_ptr<Sikidom> LegnagyobbTerulet(const std::vector<std::shared_ptr<Sikidom>>& v)
{
	size_t max = 0;
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i]->Terulet() > v[max]->Terulet())
		{
			max = i;
		}
	}
	return v[max];
}
int main()
{
	//Kor k(Szin::Kek, 4);
	//std::cout << std::string(k) << std::endl;

	//Teglalap t(Szin::Piros, 6, 4);
	//std::cout << std::string(t) << std::endl;

	//Negyzet n(Szin::Zold, 12);
	//std::cout << std::string(n) << std::endl;
	//return 0;

	std::vector<std::shared_ptr<Sikidom>> sikidomVector;

	sikidomVector.push_back(std::make_shared<Kor>(Szin::Sarga, 2));
	sikidomVector.push_back(std::make_shared<Teglalap>(Szin::Kek, 2, 18));
	sikidomVector.push_back(std::make_shared<Negyzet>(Szin::Szurke, 13));
	sikidomVector.push_back(std::make_shared<Kor>(Szin::Piros, 4));
	sikidomVector.push_back(TeglalapotVagyNegyzetetLetrehoz(3.14, 3.4));

	for (const auto& curr : sikidomVector) {
		curr->Kilyukaszt();
	}

	for (const auto& curr : sikidomVector) {
		std::cout << std::string(*curr) << std::endl;
	}

	std::cout << std::string(*LegnagyobbTerulet(sikidomVector)) << std::endl;
	return 0;
}