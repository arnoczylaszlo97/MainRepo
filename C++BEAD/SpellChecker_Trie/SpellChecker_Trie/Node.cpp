#include "Node.h"

Node::Node()
{
	mPointers.resize(27);	//helyfoglalás a 26db betûnek
	mIsWord = false;		//szó végek false-ra létrehozáskor
	for (size_t i = 0; i < mPointers.size(); i++) //nullpointerekkel feltöltés
	{
		mPointers[i] = shared_ptr<Node>(nullptr);
	}
}