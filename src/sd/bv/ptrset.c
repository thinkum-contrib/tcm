#include "ptrset.h"
#include "ktransition.h"
#include "klocation.h"
#include "lstring.h"

#include <stdio.h>

template class PtrSet<KTransition>;
template class PtrSet<KLocation>;

template class PtrSetEl<KTransition>;
template class PtrSetEl<KLocation>;

template <class T> PtrSetEl<T>::PtrSetEl(T *newitem, const PtrSetEl<T> *f /* = NULL */)
{
	item = newitem;
	child[0] = child[1] = NULL;
	father = f;
}

template <class T> PtrSetEl<T>::~PtrSetEl() {
	if ( NULL != child[0] )
		delete child[0];
	if ( NULL != child[1] )
		delete child[1];
	if ( NULL != item )
		delete item;
}

template <class T> PtrSetEl<T>::PtrSetEl(const PtrSetEl<T> &copy, const PtrSetEl<T> *f /* = NULL */)
{
	item = new T(*copy.item);
	if ( NULL == copy.child[0] )
		child[0] = NULL;
	else
		child[0] = new PtrSetEl<T>(*copy.child[0], this);
	if ( NULL == copy.child[1] )
		child[1] = NULL;
	else
		child[1] = new PtrSetEl<T>(*copy.child[1], this);
	father = f;
}

template <class T> T *PtrSetEl<T>::search(T *key, mode notfound) {
	if ( *key == *item )
		return item;
	int i = *item < *key;
	T *result = NULL;
	if ( NULL != child[i] )
		result = child[i]->search(key, notfound);
	else if ( SInsert == notfound )
		child[i] = new PtrSetEl<T>(key, this);
	return NULL != result || i != notfound ? result : item;
}

template <class T> void PtrSetEl<T>::print(int depth) {
	if ( NULL != child[0] )
		child[0]->print(depth + 1);
	printf("%*c%s:\n", depth, ':', ((string *)item)->getstr());
	if ( NULL != child[1] )
		child[1]->print(depth + 1);
}


/*--------------------------------------------------------------------------*/


template <class T> PtrSet<T>::PtrSet()
:root(NULL) {
}

template <class T> PtrSet<T>::~PtrSet() {
	if ( NULL != root )
		delete root;
}

template <class T> PtrSet<T>::PtrSet(const PtrSet<T> &copy)
{
	if ( NULL == copy.root )
		root = (PtrSetEl<T> *) NULL;
	else
		root = new PtrSetEl<T>(*copy.root);
}

template <class T> T *PtrSet<T>::search(T *key, mode notfound) {
	if ( NULL != root )
		return root->search(key, notfound);
	if ( SInsert == notfound )
		root = new PtrSetEl<T>(key);
	return NULL;
}

template <class T> bool PtrSet<T>::first(mode dir /* = SNext */) {
	current = root;
	if ( NULL == current )
		return False;
	while ( NULL != current->child[dir] )
		current = current->child[dir];
	return True;
}

template <class T> bool PtrSet<T>::next(mode dir /* = SNext */) {
	if ( NULL == current )
		return False;
	register const PtrSetEl<T> *temp = current->child[1 - dir];
	if ( NULL != temp ) {
		do
			current = temp;
		while ( NULL != (temp = temp->child[dir]) );
		return True;
	}
	do {
		temp = current;
		if ( NULL == (current = temp->father) )
			return False;
	} while (current->child[dir] != temp);
	return True;
}

template <class T> void PtrSet<T>::print() {
	if ( NULL != root )
		root->print(0);
}
