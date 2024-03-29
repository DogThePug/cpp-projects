// Casting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


class Parent {
public:
	virtual void speak()
	{
		std::cout << "parent" << std::endl;
	}
};
class Brother :public Parent {
public:
	void speak()
	{
		std::cout << "brother" << std::endl;
	}
};
class Sister :public Parent {
public:
	void speak()
	{
		std::cout << "sister" << std::endl;
	}
};
int main()
{
	Parent parent;
	Brother brother;

	Parent *ppb = &brother;

	Brother *pbb = static_cast<Brother *> (ppb);

	Brother *pb = static_cast<Brother *> (&parent);

	Parent && p = static_cast <Parent &&>(parent);

	p.speak();
	pb->speak();
	
	Parent *bp = &parent;

	Brother *bpp = dynamic_cast<Brother *>(bp);

	if (bpp == nullptr) {
		std::cout << "invalid cast" << std::endl;
	}
	else {
		bpp->speak();
	}

	Sister *sbb = dynamic_cast<Sister *>(pbb);
	if (sbb == nullptr) {
		std::cout << "invalid cast" << std::endl;
	}
	else {
		bpp->speak();
	}

	system("pause");
    return 0;
}

