### 条款1：视C++为一个语言联邦：C、Object-Oriented C++、Template C++、STL

C++高效编程守则视情况而变化，取决于使用C++的哪一个部分

### 条款2：尽量以const，enum，inline替换#define

1. 对于单纯的常量，最好以const对象或enums替代#define
2. 对于形似函数的宏，最好用inline函数替代#define

### 条款3：尽可能使用const

1. 尽量使用const，将某些东西声明为const可以帮助编译器侦测出错误的用法。const可被施加与任何作用域内的对象、函数参数、函数返回类型、成员函数本体。
2. 编译器强制实施bitwise constness， 但编写程序时应该使用“概念上的常量性”
3. 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。

### 条款4：确定对象使用前已被初始化。

1. 对内置类的对象进行手工初始化，因为C++不保证初始化它们。

2. 构造函数最好使用成员初值列，而不要在构造函数内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在class中声明的次序相同。
3. 为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-local static对象。

### 条款5：了解C++默默编写并调用哪些函数。

1. 编译器可以暗自为class创建default构造函数、copy构造函数、copy assignment操作符，以及析构函数。
2. 当手工创建一个构造函数后，编译不会再创建default构造函数。
3. 内含引用或const成员，编译器不会创建copy assignment操作符。

### 条款6：若不想使用编译器自动生成的函数，应该明确拒绝。

1. 为驳回编译器自动提供的技能，可将相应的成员函数声明为private并且不予实现。

### 条款7：为多态基类声明virtual析构函数。

1. polymorphic带有多态性质的base classes 应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥有一个virtual析构函数。但子类以父类指针的形式被析构时，子类对象的成分没有被销毁，故需要将父类的析构函数需要为virtual。
2. Classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不应该声明virtual析构函数
3. 若想实现一个抽象的class，但是没有pure virtual函数，可以将class的析构函数声明为pure virtual函数。但是若父类带有pure virtual（纯虚函数）析构函数，子类的析构函数中会有对父类析构函数的调用，因此必须为父类的纯虚函数提供一份定义。

```c++
#include <iostream>

template<typename T>
inline void delete_ptr(T** ptr)
{
	if(*ptr)
	{
		delete *ptr;
		*ptr = nullptr;
	}
}

class Object
{
public:
	virtual ~Object() = 0;
};
//必须为纯虚析构函数提供一份定义
Object::~Object()
{
	std::cout << "~Object()" << std::endl;
}

class ChildA : public Object
{
public:
	~ChildA(){ std::cout << "~A()" << std::endl;}
};

int main()
{
	//Object* p = new Object; //错误，不能实例化
	ChildA* a = new ChildA;

	delete_ptr(&a);

	return 0;
}
```

4. 析构函数的运作方式是最深层那个派生类的析构函数最先被调用，然后调用每一个base class 的析构函数。

### 条款8：别让异常逃离析构函数。

1. 析构函数绝对不要吐出异常，如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不再传播）或结束程序。
2. 如果客户需要对某些操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数（而非析构函数）执行该操作。

### 条款9：绝不在构造和析构过程中调用virtual函数。

1. 子类构造时，先调用base class，此时子类被认为是一个base class。析构时先调用自身的析构函数，再调用base class的析构函数。

### 条款10：令operator= 返回一个reference to *this。

1.

```c++
Widget& operator=(const Widget& rhs)
{
	...
	return* this;
}
```



### 条款11：在operator=中处理“自我赋值”

1. 确保当对象自我赋值时operator=有良好的行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy-and-swap。
2. 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

### 条款12：复制对象时勿忘其每一成分。

1. （1）复制所有local成员变量，（2）调用所有base classes内适当的copying函数。
2. copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”。
3. 不要尝试以某个copying函数实现另一个copying函数。应将共同机能放进第三个函数中，并有两个copying函数共同调用。

```c++
class Customer
{
public;
	...
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);

private:
	std::string name;
};

Customer::Customer(const Customer& rhs);
{
	...
}

Customer& Customer::operator=(const Customer& rhs)
{
	...
	name = rhs.name;
	return *this;
}

class PriorityCustomer : public Customer
{
public:
	PriorityCustomer(const PriotyCustomer& rhs);
	priorityCustomer& operator=(const PriotyCustomer& rhs);

private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs):Customer(rhs), priority(rhs.priority)
{
	...
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	...
	Customer::operator=(rhs);
	priority = rhs.priority;
	return *this;
}
```



### 条款13：以对象管理资源。

1. 以对象管理资源的两个关键想法：
   * 获得资源后立刻放进管理对象。资源获取时机便是初始化时机。
   * 管理对象运用析构函数确保资源被释放。
2. 使用shared_ptr智能指针。

### 条款14：在资源管理类中小心copying行为。

1. 复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为。
2. 普遍而常见的RAII class copying行为是：抑制copying、施行引用计数法。不过其他行为也都可能被实习。

### 条款15、在资源管理类中提供对原始资源的访问。

1. APIs往往要求访问原始资源，所以每一个RAII class应该提供一个“取得其所管理资源”的方法。
2. 对原始资源的访问可能经由显示转换或隐式转换。一般而言显示转换更安全，隐式转换比较方便。

### 条款16、成对使用new和delete时要采取相同形式。

1. 如果在new表达式中使用了[]，则在对应delete中也必须使用[]。若在new表达式中没有使用[]，则在delete表达式中也不能使用[]。

### 条款17：以独立语句将newed对象置入智能指针。

1. 以独立语句将newed对象置入智能指针，否则，一旦有异常抛出，就可以造成难以察觉的内存泄漏。

### 条款18：让接口容易被正确使用，不易被误用。

1. 好的接口容易被正确使用，不容易被误用。
2. “促进正确使用”的方法包括接口的一致性，以及与内置类型的行为兼容。
3. “阻止误用”的方法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任。
4. tr1::shared_ptr支持定制型删除器。可以方法DLL问题，可被用来自动解除互斥锁等。
   std::tr1::shared_ptr<className> ptr(static_cast<calsssName*>(0), deletebyself);//deletebyself为自定义的删除器。

### 条款19、设计class犹如设计type。

1. 设计一个class需要考虑一下：
   * 新type的对象应如何被创建和销毁？
   * 对象的初始化和对象的赋值该有什么样的差别？
   * 新type对象如果被passed by value，意味着什么？copy构造函数用来定义一个type by value该如何实现。
   * 什么是新type的合法值？
   * 新的type需要配合某些继承图系吗？
   * 新type需要什么样的转换？
   * 什么样的操作符和函数对新type时合理的？
   * 什么样的函数应该驳回？那些正式必须声明为private者。
   * 谁该取用新type的成员？
   * 什么时新type的“未声明接口”？
   * 新type有多么一般化？
   * 真的需要一个新type吗？

###  条款20、宁以pass-by-reference-to-const 替换 pass-by-value

1. 尽量以pass-by-reference-to-const 替代 pass-by-value。前者比较高效，并可避免切割问题。
2. 以上规则并不适用于内置类型、以及STL的迭代器和函数对象。对它们而言，pass-by-value往往比较适当。

###  条款21、必须返回对象时，别妄想返回其reference。

1. 一个“必须返回新对象”的函数的正确写法是：就让那个函数返回一个新对象。
2. 绝不要返回pointer或reference指向一个local stack对象，或返回refercence指向一个heap-allcoated对象，或返回pointer或reference指向local static对象而言有可能同时需要多个这样的对象。

###  条款22、将成员变量声明为private。

1. 切记将成员变量声明为private，可赋予客户访问数据的一致性、可细微划分访问控制、允许约束条件得以保证，并提供class作者以充分的实现弹性。
2. protected并不比public更具封装性。

###  条款23、宁以non-member, non-friend替换member函数。

1. 以non-member,non-friend函数替换member函数，这样可以增加封装性、包裹弹性和机能扩充型。

### 条款24、若所有参数皆需类型转换，请为此采用non-member函数。

1. 如果需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。

### 条款25、考虑写出一个不抛异常的swap函数。

1. 

```C++
class WidgetImp1
{
public:
private:
	int a, b, c;
	std::vector<double> v;
}
class Widget  //使用pimpl手法
{
public:
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs);
	{
		*pImpl = *(rhs.pImpl);
	}
	class swap(Widget& other)
	{
		using std::swap;    //
		swap(pImpl, other.pImpl); //
	}
	...
private:
	WidgetImpl* pImpl;
}

namespact std{
	    template<> //表示它是std::的一个全特化版本
		void swap<Widget>(Widget& a, Widget& b)  //<Widget>表示这一特化版本
		{                                        //针对T是Widget而设计
			a.swap(b);
		}
}
```



2. 当std::swap对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常。
3. 如果你提供一个member swap，也该提供一个non-member swap用来调用前者。对于classes，而非templates，也请特化std::swap.
4. 调用swap时应针对std::swap使用using声明式，然后调用swap并且不带任何命名空间资格修饰。
5. 为用户定义类型进行std templates全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西

### 条款26、尽可能延后变量定义式的出现时间。

### 条款27、尽量少做转型动作。

1. 如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast,如果有个设计需要转型动作，试着发展无需转型的替代设计。
2. 如果转型是必要的，试着将它隐藏于某个函数背后码，客户随后可以调用该函数，而不需要将转型放进他们自己的代码内。
3. 宁可使用C++新式转型，不要使用旧式转型。前者容易辨识出来，而且比较有着分门别类的职称。

### 条款28、避免返回handles指向对象内部成分。

1. 避免返回handles（包括references、pointer、迭代器）指向对象内部。遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码牌”的可能性降至最低。

### 条款29、为“异常安全”而努力是值得的

1. 异常安全函数即使发生异常也不会泄漏资源或允许任何数据结构败坏。这样的函数区分为三种可能的保证：基本型、强烈型、不抛异常型。
2. “强烈保证”往往能够以copy-and-swap实现，但并非对所有函数都可实现或具备现实意义。
3. 函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的最弱者。

### 条款30、透彻了解inlining的里里外外。

1. 将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化。
2. 不要只因为function templates出现在头文件，就将它们声明为inline。

### 条款31、将文件间的编译依赖关系降至最低

1. 如果使用object references或object pointers可以完成任务，就不要使用objects。
   	如果能够，尽量以class声明式替换class定义式。
   	为声明式和定义式提供不同的头文件。
2. 支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依于定义式。基于此构想的两个手段时Handle classes和Interface classes。

```c++
class Person
{
public:
    virtual ~Person(){}
    virtual string name() const = 0;
    virtual string birthDate() const = 0;
    virtual string address() const = 0;


	static shared_ptr<Person> create(const string& name, const string& birthDate,
                                 	string& address);
};

class RealPerson:public Person
{
public:
    RealPerson(const string& name, const string& birthDate, const string& address)
              :m_name(name), m_birthDate(birthDate), m_address(address)
    {

   	}
	virtual ~RealPerson()
	{

	}

	string name() const
	{
    	return m_name;
	}

	string birthDate() const
	{
    	return m_birthDate;
	}

	string address() const
	{
    	return m_address;
	}

private:
    string m_name;
    string m_birthDate;
    string m_address;
};

shared_ptr<Person> Person::create(const string& name, const string& birthDate,
                                 string& address)
{
    return shared_ptr<Person>(new RealPerson(name, birthDate, address));
}

void doSomething()
{
    string name = "hei";
    string birthDate = "12";
    string address = "China";
    shared_ptr<Person>ptr(Person::create(name, birthDate, address));
    cout << ptr.get()->name().data() << endl;
    cout << ptr.get()->birthDate().data() << endl;
    cout << ptr.get()->address().data() << endl;
}
```



3. 程序库头文件应该以“完全且仅有声明式”的形式存在。这种做法不论是否设计templates都适用。

### 条款32、确定你的public继承塑模出is-a关系

1. “public继承”意味着is-a。适用于base classes身上的每一件事情一定适用于derived classes身上，因为每一个derived class对象也是一个base class对象。

### 条款33、避免遮掩继承而来的名称

1. derived classes内的名称会遮掩base classes内的名称。在public继承下从来没人希望如此。

2. 为了让被遮掩的名称再见天日，可以使用using声明式或转交函数。

   ```c++
   class Base1
      {
      public:
          virtual void mf1() = 0;
          virtual void mf1(int)
          {
              cout << "base mf1(int)" << endl;
          }
          virtual void mf2()
          {
              cout << "base mf2()" << endl;
          }
          void mf3()
          {
              cout << "base mf3()" << endl;
          }
          void mf3(double)
          {
              cout << "base mf3(double)" << endl;
          }
      };
   
   class Derived1:public Base1
   {
   public:
       using Base1::mf1;
       using Base1::mf3;
       virtual void mf1()
       {
           cout << "Derived1 mf1()" << endl;
       }
       void mf3()
       {
           cout << "Derived1 mf3()" << endl;
       }
   };
   
   void doSomething()
   {
       Derived1 d1;
       d1.mf1();
       d1.mf2();
       d1.mf3();
       d1.mf1(2);    //不加using Base1::mf1,则错误，Derived的mf1()，会遮掩掉父类的mf1();
       d1.mf3(2.0);  //不见using Base1::mf3,则错误
   }
   ```

   

### 条款34、区分接口继承和实现继承

1. 可以为pure virtual函数提供定义（提供实现代码），但调用它的唯一途径是“调用时明确指出class名称”
2. 接口继承和实现继承不同。在public继承之下，derived classes总是继承base class的接口。
3. pure virtual（纯虚函数）只具体指定接口继承。
4. impure virtual（非纯虚函数）具体指定接口继承及缺省实现继承。
5. non-virtual函数具体指定接口继承以及强制实现继承。

### 条款35、考虑virtual函数外的其他选择

1. 由Non-virtual Interface手法实现Template Method模式。

   ```c++
   class GameCharacter
   {
   public:
   	int healthValue() const
   	{
   		...    //  事前工作：可锁定互斥器、制作运转日志记录项、验证class约
   			   //束条件、验证函数的先决条件等等
   		int retVal = doHealthValue(); //真正做些事
   		...   //   事后工作：
   		return retVal;
   	}
   private:
   	virtual int doHealthValue() const  //derived classes 可重新定义
   	{
   		...     // 缺省算法
   	}
   };
   ```

   

2. 由Function Pointers现实Strategy模式

```c++
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter
{
public:
	typedef int (*HealthCalcFunc)(const GameCharacter&);
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc):healthFunc(hcf)
	{
	
	}
	int healthValue() const
	{
		return healthFunc(*this);
	}

private:
	HealthCalcFunc healthFunc;
};

class EvilBadGuy:public GameCharacter
{
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc):GameCharacter(hcf)
	{

	}
};
int loseHealthQuickly(const GameCharacter&);
int loseHealthSlowly(const GameCharacter&);

EvilBadGuy ebg1(loseHealthQuickly);
EvilBadGuy ebg2(loseHealthSlowly);
```



3. 由std::function完成Strategy模式。

```c++
class GameCharacter;
int defaultHealthCalc(cosnt GameCharacter& gc);
class GameCharacter
{
public:
	typedef std::function<int(const GameCharacter&)> HealthCalcFunc;
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc):healthFunc(hcf)
	{
	}
	int healthValue() const
	{
		return healthFunc(*this);
	}

private:
	HealthCalcFunc healthFunc;
};
```



4. 古典的Strategy模式。
   GameCharacter是某个继承体系的根类， EvilBadGuy和EyeCandyCharacter都是其derived classes;
   HealthCalcFunc是另一个继承体系的根类，SlowHealthLoser和FaseHealthLoser都是其derived classes;

```c++
class GameCharacter;
class HealthClacFunc
{
public:
	virtual int calc(const GameCharacter& gc) const
	{
	}
};
HealthCalcFunc defaultHealthCalc;
class GameCharacter
{
public:
	explicit GameCharacter(HealthCalcFunc* phcf = &defaultHealthCalc):pHealthCalc(phcf)
	{
	}
	int healthValue() const 
	{
		return pHealthCalc->calc(*this);
	}

private:
	HealthCalcFunc* pHealthCalc;
}
```



### 条款36、绝不重新定义继承而来的non-virtual函数

### 条款37、绝不重新定义继承而来的缺省参数值。

1. 绝不重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数唯一应该覆写的东西却是动态绑定。

### 条款38、通过复合塑模出has-a或“根据某物实现出”

1. 复合（composition）的意义和public继承完全不同。
2. 在应用域（application domain）复合意味has-a（有一个）。在现实域（implementation domain）复合意味is-impllemented-in-terms-of（根据某物实现出）。

### 条款39、明智而审慎地使用private继承。

1. private继承意味is-implemented-in-terms-of(根据某物实现出)。它通常比复合（composition）的级别低。但当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计是合理的。换句化说，当面对“并不存在is-a关系”的两个classes，其中一个需要访问另一个的protected成员，或需要重新定义其一或多个virtual函数，private继承极有可能成为正确的设计策略。
2. 和复合不同，private继承可能造成empty base最优化。这对致力于“对象尺寸最小化”的程序库开发者而言可能很重要。

### 条款40、明智而审慎地使用多重继承。

1. 多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual继承的需要。
2. virtua继承会增加大小、速度、初始化复杂度等等成本。如果virtual base classes不带任何数据，将是最具适用价值的情况。
3. 多重继承的确有正当用途。其中一个情节设计“public继承某个Interface class”和“private继承某个协助实现的class”的两相组合。

### 条款41、了解隐式接口和编译器多态

1. classes和templates都支持接口（interfaces）和多态（polymorphism）。
2. 对classes而言接口是显式的（explicit），以函数签名为中心。多态是通过virtual函数发生在运行期。
3. 对template参数而言，接口是隐式的，基于有效表达式。多态则通过template具现化和函数重载解析发生于编译器。

### 条款42、了解typename的双重意义。

1. 声明template参数时，前缀关键字class和typename可互换。
2. 请使用关键字typename表示嵌套从属类型名称；但不得在base class lists（基类列）或member initalization list（成员初值列）内以它作为base class修饰符。

```c++
//嵌套从属类型名称示例：
template<typename C>
void print2nd(const C& container)
{
    if(container.size() >= 2)
    {
    //在缺省的情况下C::const_iterator不被认为是类型，在嵌套从属关系C::const_iterator前加typename说  明C::const_iterator为类型(使用vs2015，和最新的g++编译，不加typename貌似也能正常工作)
	typename C::const_iterator iter(container.begin());
    }
}
//一般性规则：任何时候想要在template中指涉一个嵌套从属类型名，就必须在紧邻它的前一个位置放上typename。

//不能使用typename示例
template<typename T>
class Derived::public Base<T>::Nested //base class list中不允许typename
{
public:
    explicit Derived(int x):Base<T>::Nested(x) //mem.init.list中不允许typename
    {
        typename Base<T>::Nested temp; //嵌套从属名称，需要加typename；
    }
};

//接手一个迭代器，为迭代器所指的对象做一份local副本temp；
template<typename IterT>
void workWithIterator(IterT iter)
{
    typename std::iterator_traits<IterT>::value_type temp(*iter)
}
```

std::iterator_traits<IterT>::value_type   :类型为ItetT对象所指之物的类型

### 条款43、学习处理模板化基类内的名称。

1. 可以在derived class templates内通过“this->”指涉base class templates内的成员名称，或由一个明白写出的“base class资格修饰符完成”。

   ```c++
   class CompanyA
   {
   public:
       void sendCleartext(const std::string& msg);
       void sendEncrypted(const std::string& msg);
   };
   class CompanyB
   {
   public:
       void sendCleartext(const std::string& msg);
       void sendEncrypted(const std::string& msg);
   };
   class CompanyZ
   {
   public:
       void sendEncrypted(const std::string& msg);
   };
   class MsgInfo
   {
   };
   template<typename Company>
   class MsgSender
   {
   public:
       void sendClear(const MsgInfo& info)
       {
   	std::string msg;
   	//info->msg
   	Company c;
   	c.sendCleartext(msg);
       }
       void sendSecret(const MsgInfo& info)
       {
       }
   };
   //提供一个针对CompanyZ的MsgSender特化版
   template<>
   class MsgSender<CompanyZ> //
   {
   public:
       void sendSecret(const MsgInfo& info)
       {
       }
   };
   template<typename Company>
   class LoggingMsgSender:public MsgSender<Company>
   {
   public:
       void sendClearMsg(const MsgInfo& info)
       {
           //logging begin
   	sendClear(info); //不能通过编译，编译器知道base class templates有可能被特化。
   	//logging end;
       }
   };
   template<typename Company>
   class LoggingMsgSender:public MsgSender<Company>
   {
   public:
       void sendClearMsg(const MsgInfo& info)
       {
           //logging begin
   	this->sendClear(info); //成立，假设sendClear将被继承
   	//logging end;
       }
   };
   template<typename Company>
   class LoggingMsgSender:public MsgSender<Company>
   {
   public:
       using MsgSender<Company>::sendClear; //告诉编译器，请假设sendClear位于base class内
       void sendClearMsg(const MsgInfo& info)
       {
           //logging begin
   	sendClear(info); //成立
   	//logging end;
       }
   };
   template<typename Company>
   class LoggingMsgSender:public MsgSender<Company>
   {
   public:
       void sendClearMsg(const MsgInfo& info)
       {
           //logging begin
   	MsgSender<Company>::sendClear(info); //成立，假设sendClear将被继承下来
   	//logging end;
       }
   };
   ```

   

### 条款44、将与参数无关的代码抽离templates。

1. Templates生产多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系。
2. 因非类型模板而造成的代码膨胀，往往可以消除，做法是以函数参数或class成员变量替换template参数。
3. 因类型参数而造成的代码膨胀，往往可以降低，做法是让带有完全相同二进制表述的具现类型共享现实码。

### 条款45、运用成员函数模板接受所有兼容类型。

1. 使用member function templates生产“可接受所有兼容类型”的函数。
2. 如果声明member templates用于“泛化copy构造”或“泛化assignment操作”，还是需要生命正常的copy构造函数和copy assignment操作符。

```c++
template<class T>
class shared_ptr
{
public:
    shared_ptr(shared_ptr const& r);
    template<class Y>
    shared_ptr(shared_ptr<Y> const& r); //声明泛化copy构造函数，并不会阻止编译器生产默认的copy构造函数。
    shared_ptr& operator=(shared_ptr const& r);
    template<class Y>
    shared_ptr& operator=(shared_ptr<Y> const& r);
};
```



### 条款46、需要类型转换时为模板定义非成员函数

1. 当编写一个class template，而它所提供的与此template相关的函数支持所有参数之隐式类型转换时，将那些函数定义为class template内部的friend函数。

```c++
template<typename T>
class Rational
{
public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs)
    {
    	return Rational(lhs.numerator()*rhs.numerator(),
   	                    lhs.denominator()*rhs.denominator());
    }
};

//对于复杂的函数
template<typename T> class Rational; //声明
template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs,
                             const Rational<T>& rhs);
template<typename T>
class Rational
{
public:
    friend const Rational<T> operator*(const Rational<T>& lhs,
                                       const Rational<T>& rhs)
    {
	return doMultiply(lhs, rhs);
    }
};
```



### 条款47、使用traits classes表现类型信息

1. Traits classes 使得类型相关信息在编译器可用。它们以template和templates特化完成实现。
2. 整合重载技术后，traits classes有可能在编译器对类型执行if...else测试(if...else在运行期检测)

```c++
template<...>
class deque
{
public:
	class iterator
    {
    public:
    	typedef random_access_iterator_tag iterator_category;
   		...
    };
};

template<...>
class list
{
public:
	class iterator
    {
   	public:
    	typedef bidirectional_iterator_tag iterator_category;
   		...
    };
};

//iterator_traits响应iterator class的嵌套式typedef
template<typename IterT>
struct iterator_traits
{
    typedef typename IterT::iterator_category iterator_category;
    ...
};

//对于指针（也是一种迭代器）需要提供一个偏特化版本
template<typename IterT>
struct iterator_traits<IterT*>
{
    typedef random_access_iterator_tag iterator_category;
    ...
};

//利用重载在编译器检查类型
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)
{
    iter += d;
}

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag)
{
    if(d >= 0)
    {
	while(d--)
	{
	    ++iter;
	}
    }
    else
    {
	while(d++)
	{
	    --iter;
	}
    }
}

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)
{
    iter += d;
}

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::inputs_iterator_tag)
{
    if(d < 0)
    {
        throw std::out_of_range("Negative distance");
    }
    while(d--)
    {
	++iter;
    }
}

//调用“劳工函数”
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
    doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
}
```



### 条款48、认识template元编程

1. Template metaprogramming(TMP，模板元编程)是编写template-based C++程序并执行于编译器的过
2. Template metaprogramming(TMP，模板元编程)可以将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率。
3. TMP可被用来生成“基于政策选择组合”的客户定制代码，也可用来避免生成某些特殊类型并不合适的代码
4. TMP并没有真正的循环结构，因此循环由递归完成，“递归模板具现化”

```c++
template<unsigned n>
struct Factorial
{
    enum {value = n * Factorial<n-1>::value};
};
template<>
struct Factorial<0>   //特殊情况：Factorial<0>; 结束递归的条件
{
    enum {value = 1};
};
```



### 条款49、了解new-handler的行为

1. 一个良好设计的new-handler函数必须做以下的事情：
       让更多内存可被使用
       安装另一个new-handler
       卸载new-handler
       抛出bad_alloc（或派生自bad_alloc）的异常
       不返回，通常调用abort或exit。

```c++
//令class提供自己的set_new_handler和operator new
//需要声明一个类型为new_handler的static成员，用以指向class Widget的new-handler。
class Widget
{
public:
    static std::new_handler set_new_handler(std::new_handler p) throw();
    static void* operator new(std::size_t size) throw(std::bad_alloc);
private:
    static std::new_handler currentHandler;//static成员必须在class定义式以外被定义（除非是const而且是整型）
};
std::new_handler Widget::currentHandler = 0;//在class实现文件内初始化为null

std::new_handler Widget::set_new_handler(std::new_handler p) throw()
{
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}
//资源管理类
class NewHandlerHolder
{
    explicit NewHandlerHolder(std::new_handler nh):handler(nh)
    {}
    ~NewHandlerHolder()
    {
        std::set_new_handler(handler);
    }
private:
    std::new_handler handler;
    NewHandlerHolder(const NewHandlerHolder&); //阻止copying
    NewHandlerHolder& operator=(const NewHandlerHolder&):
};

void* Widget::operator new(std::size_t size) throw(bad_alloc)
{
    NewHandlerHolder h(std::set_new_handler(currentHandler));//安装Widget的new-handler
    return ::operator new(size); //分配内存或抛出异常，恢复global new-handler.
}
//使用new-handling
void outOfMem();  //函数声明，此函数在Widget对象分配失败时调用
Widget::set_new_handler(outOfMen);  //设定outOfMem为Widget的new-handling函数
Widget* pw1 = new Widget;  // 如果内存分配失败，调用outOfMem
std::string* ps = new std::string; //若内存分配失败，调用global new-handling函数（若有）
Widget::set_new_handler(0); //设定Widget专属的new-handling函数为null
Widget* pw2 = new Widget;  //若内存分配失败，立刻抛出异常（class Widget并没有专属的new-handling函数）
```



2. set_new_handler允许客户指定一个函数，在内存分配无法获得满足时被调用。
3. Nothrow new是一个颇为局限的工具，因为它只适用于内存分配；后继的构造函数调用还是可能抛出异常。

### 条款50、了解new和delete的合理替换时机

1. 有许多理由需要写个定义的new和delete，包括改善效能、对heap运用错误进行调试、收集heap使用信息。
        为了检测运用错误
        为了收集动态分配内存之使用统计信息
        为了增加分配和归还的速度
        为了降低缺省内存管理器带来的空间额外开销
        为了弥补缺省分配器中的非最佳齐位
        为了将相关对象成簇集中
        为了获得非传统的行为(比如自定义delete，在其中所归还内存内容覆盖为0，增加应用程序的数据安全性)

### 条款51、编写new和delete时需要固守常态

1. operator new应该内含一个无穷循环，并在其中尝试分配内存，如果它无法满足内存需求，就该调用new-handler。它也应该有能力处理0bytes申请。class专属版本则还应该处理比正确大小更大(错误)的申请。
2. operator delete应该在收到null指针时不做任何事。class专属版本则还应该处理比正确大小更大的(错误)申请。

### 条款52、写了placement new也要写placement delete

1. operator new接受的参数除了一定会有的size_t外还有其它参数，这比那时所谓的placement new。

   特别有用的一个“接受一个指针指向对象该被构造之处”

   ```c++
   void* operator new(std::size_t, void* pMemory) throw(); //标准库 #include <new>
   ```

2. 当写一个placement operator new，请确定也写出对应的placement operator delete。如果没有这样做，你的程序可能会发生隐微而时断时续的内存泄漏。

3. 当声明placement new 和 placement delete，请确定不要无意识地遮掩它们的正常版本。
   缺省情况下C++在global作用域内提供以下形式的operator new：

   ```c++
   void* operator new(std::size_t) throw(std::bad_alloc); //normal new
   void* operator new(std::size_t, void*) throw(); //placement new
   void* operator new(std::size_t, const std::nothrow_t&) throw(); //nothrow new
   ```

一个简单的做法，建立一个base class,内含所有正常形式的new和delete

```C++
class StandardNewDeleteForms
{
public:
    //normal new/delete
    static void* operator new(std::size_t size) throw(std::bad_alloc)
    {
        return ::operator new(size);
    }
    static void operator delete(void* pMemory) throw()
    {
        ::operator delete(pMemory);
    }
    //placement new/delete
    static void* operator new(std::size_t size, void* ptr) throw()
    {
	return operator new(size, ptr);
    }
    static void operator delete(void* pMemory, void* ptr) throw()
    {
	::operator delete(pMemory, ptr);
    }
    //nothrow new/delete
    static void* operator new(std::size_t size, const std::nothrow_t& nt) throw()
    {
	return ::operator new(size, nt);
    }
    static void operator delete(void* pMemory, const std::nothrow_t&) throw()
    {
	::operator delete(pMemory);
    }
};

class Widget:public StandardNewDeleteForms
{
public:
    using StandardNewDeleteForms::operator new;
    using StandaraNewDeleteForms::operator delete;
    
	//添加自定义placement new
	static void* operator new(std::size_t size, std::ostream& logStream)		throw(std::bad_alloc);

	//添加自定义placement delete
	static void operator delete(void* pMemory, std::ostream& logStream) throw();


};
```



### 条款53、不要轻易忽略编译器的警告

1. 严肃对待编译器发生的警告信息。努力在你的编译器的最高警告级别下争取“无任何警告"的荣誉。
2. 不要过度依赖编译器的报警能力，因为不同的编译器对待事情的态度并不相同。一旦移植到另一个编译器上，你原本依赖的警告信息有可能消失。

### 条款54、让自己熟悉包括TR1在内的标准程序库

### 条款55、让自己熟悉Boost




















