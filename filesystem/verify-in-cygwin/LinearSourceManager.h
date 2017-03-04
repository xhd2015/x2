

#ifndef LinearSourceManager_h__
#define LinearSourceManager_h__



/*
//it's just a policy class,not all method are need.

class LinearSourceDescriptor{
public:
	int getStart();
	size_t getLimit();
};
*/

/**
*	What this manager manages must provide a way to get start and limit.
*		There are two types of LinearSourceManager
*		1.All are equal among the free nodes and used nodes themselves.
*			If the allocated nodes have specific use,they are different from each other
*		2.
*/
class LinearSourceManager{
public:
	LinearSourceManager(int start,size_t );
	~LinearSourceManager();

	int getNew();
	void withdraw(int pos);
	


protected:

};

#endif //LinearSourceManager_h__