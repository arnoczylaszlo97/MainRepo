#include "Node.h"

Node::Node()
{
	mPointers.resize(27);	//helyfoglal�s a 26db bet�nek
	mIsWord = false;		//sz� v�gek false-ra l�trehoz�skor
	for (size_t i = 0; i < mPointers.size(); i++) //nullpointerekkel felt�lt�s
	{
		mPointers[i] = shared_ptr<Node>(nullptr);
	}
}