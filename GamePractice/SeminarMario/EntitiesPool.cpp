#include "EntitiesPool.h"

EntitiesPool::EntitiesPool()
{

}

void EntitiesPool::insert(EntityPtr whom)
{
	_pool.push_back(whom);
	_isInUse.push_back(false);
}

EntityPtr EntitiesPool::getNext()
{
	int i = 0;
	while (i < _isInUse.size() && _isInUse[i]) {
		i++;
	}
	if (i == _isInUse.size())
		throw "all cells are in use";
	return _pool[i];
	
}

void EntitiesPool::returnEntity(EntityPtr toFree)
{
	int i = 0;
	for(;i< _pool.size();i++){
		if (toFree==_pool[i]){
			_isInUse[i] = false;
			break;
		}
	}
}
