## 1、C++使用不同的方案来存储数据：

* 自动存储持续性：在函数定义中声明的变量（包括函数参数）的存储持续性为自动的。它们在程序开始执行起所属的函数或代码块时被创建，在执行完函数或代码块时，它们使用的内存被释放。C++用两种存储持续性为自动的变量。
* 静态存储持续性：在函数定义外定义的变量和使用关键字static定义的变量的存储持续性都为静态，它们在程序整个运行过程中都存在。C++有3种存储持续性为静态的变量。
* 线程存储性（C++11）:当前多核处理器很常见，这些CPU可同时处理多个执行任务，这让程序能够将计算放在可并行处理的不同线程中。如果变量是使用关键字thread_local声明的，则其声明周期与所属线程一样长。
* 动态存储持续性：用new运算符分配的内存将一直存在，直到使用delete运算符将其释放或程序结束。这种内存的存储持续性为动态，有时称其为自由存储（free store）或堆（heap）。
123
## 2、定位new运算符

通常new负责在堆（heap）中找到一个足以满足需求的内存块。new运算符还有一种变体，被称为定位new运算符，它可以指定要使用的位置。可以使用这种特性来设置其内存管理的规程、处理需要通过特定地址进行访问的硬件或在特定位置创建对象。

要是用定位new特性，需要包含文件new，它提供了这种版本的new运算符的原型，然后将new运算符用于提供了所需地址的参数。除需要指定参数外，语法与常规的new运算符相同。具体的说，使用定位new运算符时，变量后面可以有方括号，也可以没有。

```c++
#include <iostream>
#include <new>


class Object
{
public:
	~Object(){ std::cout <<  "~Object()" << std::endl;}
protected:

private:
	char m_msg[24];
	int m_id;
};


char buf[1024];

int main()
{
	Object* obj1 = new Object;
	Object* obj2 = new Object[10];

	delete obj1;
	delete[] obj2;

	std::cout << "__________________" << std::endl;

	Object* obj3 = new(buf) Object;

	std::cout << "buf: " << (void*)buf << std::endl;
	std::cout << "obj3:" << obj3 << std::endl;

	//使用new定位运算符的对象不需要delete，要手动调用析构函数。
	obj3->~Object();

	return 0;
}
```



## 3、数组的动态内存分配

```c++
#include <iostream>

//一维数组
void oneDimensionalArray()
{
    //定义一个长度为10的数组
	int* array = new int[10];
    //赋值
	for(int i = 0; i < 10; i++)
	{
		array[i] = i*2;
	}
	//打印
	for(int i = 0; i < 10; i++)
	{
		std::cout << i << " : " << array[i] << std::endl;
	}
	//释放内存
	delete[] array;
}

//二维数组
void twoDimensionalArray()
{
	//定义一个2*10的二维数组
	int** array = new int*[2];
	for(int i = 0; i < 2; i++)
	{
		array[i] = new int[10];
	}
	//赋值
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			array[i][j] = i*10 + j;
		}
	}
	//打印
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			std::cout << "(" << i << ", " << j << ")" << array[i][j] << std::endl;
		}
	}
	//释放内存
	for(int i = 0; i < 2; i++)
	{
		delete[] array[i];
	}
	
	delete[] array;
}

//三维数组
void threeDimensionalArray()
{
	//定义一个3*10*20的数组
	int*** array = new int** [3];

	for(int i = 0; i < 3; i++)
	{
		array[i] = new int*[10];
		for(int j = 0; j < 10; j++)
		{
			array[i][j] = new int[20];
		}
	}
	//赋值
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			for(int k = 0; k < 20; k++)
			{
				array[i][j][k] = i*100 + j*10 + k;
			}
		}
	} 
	//打印
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			for(int k = 0; k < 20; k++)
			{
				char str[64];
				sprintf(str, "(%d, %d, %d): ", i, j, k);
				std::cout << str << array[i][j][k] <<std::endl;
			}
		}
	} 
	//释放内存
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			delete[] array[i][j];
		}
	} 
	for (int i = 0; i < 3; i++)
	{
		delete[] array[i];
	}
	
	delete[] array;

}

int main()
{
	threeDimensionalArray();
	return 0;
}
```



