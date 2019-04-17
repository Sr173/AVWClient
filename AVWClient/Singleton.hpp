#pragma once

template <class T>
class Singleton {
public:
	static T* getPtr() {
		static T* ptr = new T;
		return ptr;
	}
};