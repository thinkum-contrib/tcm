#ifndef _PTRSET_H
#define _PTRSET_H

#include "bool.h"
#include <stddef.h>

enum mode { SNext = 0, SPrevious = 1, SExact, SInsert };

template <class T> class PtrSet;

template <class T> class PtrSetEl {
	private:
		PtrSetEl<T> *child[2];
		const PtrSetEl<T> *father;
		T *item;
		PtrSetEl(T *newitem, const PtrSetEl<T> *f =
			(const PtrSetEl<T> *) NULL);
		PtrSetEl(const PtrSetEl<T> &copy, const PtrSetEl<T> *f =
			(const PtrSetEl<T> *) NULL);
		~PtrSetEl();
		T *search(T *key, mode notfound);
		void print(int depth);
	friend class PtrSet<T>;
};

template <class T> class PtrSet {
	private:
		PtrSetEl<T> *root;
		const PtrSetEl<T> *current;
	public:
		PtrSet();
		~PtrSet();
		PtrSet(const PtrSet<T> &copy);
		T *search(T *key, mode notfound);
		bool contains(T *key) {
			return NULL != search(key, SExact);
		};
		void clear() {
			if ( NULL != root ) {
				delete root;
				root = (PtrSetEl<T> *) NULL;
				current = (const PtrSetEl<T> *) NULL;
			}
		};
		bool first(mode dir = SNext);
		bool last() {
			return first(SPrevious);
		};
		bool next(mode dir = SNext);
		bool prev() {
			return next(SPrevious);
		};
		T *cur() const {
			return NULL != current ? current->item : (T *) NULL;
		};
		void print();
};

#endif
