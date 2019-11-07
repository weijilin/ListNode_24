#define _CRT_SECURE_NO_WARNINGS 1
#if 0
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}

private:
	T1 _d1;
	T2 _d2;
};


// 偏特化另外一种方式： 对类型参数限制更加严格
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}

private:
	T1* _d1;
	T2* _d2;
};


int main()
{
	Data<int*, char*> d1;
	Data<char*, short*> d2;

	Data<int, char*> d3;
	return 0;
}
#endif

// 构造函数 拷贝构造函数  赋值运算符重载  析构函数
// 什么是浅拷贝   解决方式:深拷贝
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pStr = new char[strlen(s._str) + 1];
			strcpy(pStr, s._str);
			delete[] _str;
			_str = pStr;
		}

		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

#if 0
// 写一个通用类型的拷贝函数--->效率尽可能高
template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	// 优点：一定不会出错
	// 缺陷：效率低--->O(N)
	//for (size_t i = 0; i < size; ++i)
	//	dst[i] = src[i];

	// 优点：效率高--->O(1)
	// 缺陷：浅拷贝
	memcpy(dst, src, size*sizeof(T));
}
#endif

#if 0
// plain old data
bool IsPODType(const char* strType)
{
	const char* strTypes[] = { "char", "short", "int", "long", "double" };
	for (auto e : strTypes)
	{
		if (strcmp(e, strType) == 0)
			return true;
	}

	return false;
}
#endif

#if 0
// 类型萃取---->类模板特化的应用
// 内置类型
struct TrueType
{
	static bool Get()
	{
		return true;
	}
};

// 自定义类型
struct FalseType
{
	static bool Get()
	{
		return false;
	}
};

// T--> 内置类型  自定义类型
template<class T>
struct TypeTraits
{
	typedef FalseType PODType;
};

// 用所有的内置类型来特化TypeTraits模板
template<>
struct TypeTraits<char>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODType;
};

// ...

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	if (TypeTraits<T>::PODType::Get())
	{
		// 内置类型
		memcpy(dst, src, size*sizeof(T));
	}
	else
	{
		// 自定义类型---可能会涉及到深浅拷贝
		for (size_t i = 0; i < size; ++i)
			dst[i] = src[i];
	}
}

#endif

#if 0
// 类型萃取---->类模板特化的应用
// 内置类型
struct TrueType
{};

// 自定义类型
struct FalseType
{};

// T--> 内置类型  自定义类型
template<class T>
struct TypeTraits
{
	typedef FalseType PODType;
};

// 用所有的内置类型来特化TypeTraits模板
template<>
struct TypeTraits<char>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODType;
};

// ...

template<class T>
void _Copy(T* dst, const T* src, size_t size, TrueType)
{
	// 内置类型
	memcpy(dst, src, size*sizeof(T));
}

template<class T>
void _Copy(T* dst, const T* src, size_t size, FalseType)
{
	// 自定义类型---可能会涉及到深浅拷贝
	for (size_t i = 0; i < size; ++i)
		dst[i] = src[i];
}

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	_Copy(dst, src, size, TypeTraits<T>::PODType());
}



void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);


	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];
	Copy(s2, s1, 3);
}

int main()
{
	TestCopy();
	return 0;
}
#endif

#include "a.h"

int main()
{
	Add(10, 20);
	Sub(10, 20);

	Sub(10.0, 20.0);
	return 0;
}

