

# 设计模式

## 1、工厂模式

在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。工厂模式作为一种创建模式，一般在创建复杂对象时，考虑使用；在创建简单对象时，建议直接new完成一个实例对象的创建。

### 1.1、简单工厂模式

主要特点是需要在工厂类中做判断，从而创造相应的产品，当增加新产品时，需要修改工厂类。使用简单工厂模式，我们只需要知道具体的产品型号就可以创建一个产品。

缺点：工厂类集中了所有产品类的创建逻辑，如果产品量较大，会使得工厂类变的非常臃肿。

```c++
/*
关键代码：创建过程在工厂类中完成。
*/

#include <iostream>

using namespace std;

//定义产品类型信息
typedef enum
{
	Tank_Type_56,
	Tank_Type_96,
	Tank_Type_Num
}Tank_Type;

//抽象产品类
class Tank
{
public:
	virtual const string& type() = 0;
};

//具体的产品类
class Tank56 : public Tank
{
public:
	Tank56():Tank(),m_strType("Tank56")
	{
	}

	const string& type() override
	{
		cout << m_strType.data() << endl;
		return m_strType;
	}
private:
	string m_strType;
};

//具体的产品类
class Tank96 : public Tank
{
public:
	Tank96():Tank(),m_strType("Tank96")
	{
	}
	const string& type() override
	{
		cout << m_strType.data() << endl;
		return m_strType;
	}

private:
	string m_strType;
}; 

//工厂类
class TankFactory
{
public:
    //根据产品信息创建具体的产品类实例，返回一个抽象产品类
	Tank* createTank(Tank_Type type)
	{
		switch(type)
		{
		case Tank_Type_56:
			return new Tank56();
		case Tank_Type_96:
			return new Tank96();
		default:
			return nullptr;
		}
	}
};


int main()
{
	TankFactory* factory = new TankFactory();
	Tank* tank56 = factory->createTank(Tank_Type_56);
	tank56->type();
	Tank* tank96 = factory->createTank(Tank_Type_96);
	tank96->type();

	delete tank96;
	tank96 = nullptr;
	delete tank56;
	tank56 = nullptr;
	delete factory;
	factory = nullptr;

	return 0;
}
```

### 1.2、工厂方法模式

定义一个创建对象的接口，其子类去具体现实这个接口以完成具体的创建工作。如果需要增加新的产品类，只需要扩展一个相应的工厂类即可。

缺点：产品类数据较多时，需要实现大量的工厂类，这无疑增加了代码量。

```c++
/*
关键代码：创建过程在其子类执行。
*/

#include <iostream>

using namespace std;

//产品抽象类
class Tank
{
public:
	virtual const string& type() = 0;
};

//具体的产品类
class Tank56 : public Tank
{
public:
	Tank56():Tank(),m_strType("Tank56")
	{
	}

	const string& type() override
	{
		cout << m_strType.data() << endl;
		return m_strType;
	}
private:
	string m_strType;
};

//具体的产品类
class Tank96 : public Tank
{
public:
	Tank96():Tank(),m_strType("Tank96")
	{
	}
	const string& type() override
	{
		cout << m_strType.data() << endl;
		return m_strType;
	}

private:
	string m_strType;
}; 

//抽象工厂类，提供一个创建接口
class TankFactory
{
public:
    //提供创建产品实例的接口，返回抽象产品类
	virtual Tank* createTank() = 0;
};

//具体的创建工厂类，使用抽象工厂类提供的接口，去创建具体的产品实例
class Tank56Factory : public TankFactory
{
public:
	Tank* createTank() override
	{
		return new Tank56();
	}
};

//具体的创建工厂类，使用抽象工厂类提供的接口，去创建具体的产品实例
class Tank96Factory : public TankFactory
{
public:
	Tank* createTank() override
	{
		return new Tank96();
	}
};


int main()
{
	TankFactory* factory56 = new Tank56Factory();
	Tank* tank56 = factory56->createTank();
	tank56->type();
	
	TankFactory* factory96 = new Tank96Factory();
	Tank* tank96 = factory96->createTank();
	tank96->type();

	delete tank96;
	tank96 = nullptr;
	delete factory96;
	factory96 = nullptr;

	delete tank56;
	tank56 = nullptr;
	delete factory56;
	factory56 = nullptr;

	return 0;
}
```

### 1.3、抽象工厂模式

抽象工厂模式提供创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。

当存在多个产品系列，而客户端只使用一个系列的产品时，可以考虑使用抽象工厂模式。

缺点：当增加一个新系列的产品时，不仅需要现实具体的产品类，还需要增加一个新的创建接口，扩展相对困难。

```c++
/*
* 关键代码：在一个工厂里聚合多个同类产品。

* 以下代码以白色衣服和黑色衣服为例，白色衣服为一个产品系列，黑色衣服为一个产品系列。白色上衣搭配白色裤子，   黑色上衣搭配黑色裤字。每个系列的衣服由一个对应的工厂创建，这样一个工厂创建的衣服能保证衣服为同一个系列。
*/

//抽象上衣类
class Coat
{
public:
	virtual const string& color() = 0;
};

//黑色上衣类
class BlackCoat : public Coat
{
public:
	BlackCoat():Coat(),m_strColor("Black Coat")
	{
	}

	const string& color() override
	{
		cout << m_strColor.data() << endl;
		return m_strColor;
	}
private:
	string m_strColor;
};

//白色上衣类
class WhiteCoat : public Coat
{
public:
	WhiteCoat():Coat(),m_strColor("White Coat")
	{
	}
	const string& color() override
	{
		cout << m_strColor.data() << endl;
		return m_strColor;
	}

private:
	string m_strColor;
}; 

//抽象裤子类
class Pants
{
public:
	virtual const string& color() = 0;
};

//黑色裤子类
class BlackPants : public Pants
{
public:
	BlackPants():Pants(),m_strColor("Black Pants")
	{
	}
	const string& color() override
	{
		cout << m_strColor.data() << endl;
		return m_strColor;
	}

private:
	string m_strColor;
};

//白色裤子类
class WhitePants : public Pants
{
public:
	WhitePants():Pants(),m_strColor("White Pants")
	{
	}
	const string& color() override
	{
		cout << m_strColor.data() << endl;
		return m_strColor;
	}

private:
	string m_strColor;
};

//抽象工厂类，提供衣服创建接口
class Factory
{
public:
    //上衣创建接口，返回抽象上衣类
	virtual Coat* createCoat() = 0;
    //裤子创建接口，返回抽象裤子类
	virtual Pants* createPants() = 0;
};

//创建白色衣服的工厂类，具体实现创建白色上衣和白色裤子的接口
class WhiteFactory : public Factory
{
public:
	Coat* createCoat() override
	{
		return new WhiteCoat();
	}

	Pants* createPants() override
	{
		return new WhitePants();
	}
};

//创建黑色衣服的工厂类，具体实现创建黑色上衣和白色裤子的接口
class BlackFactory : public Factory
{
	Coat* createCoat() override
	{
		return new BlackCoat();
	}

	Pants* createPants() override
	{
		return new BlackPants();
	}
};
```



## 2、策略模式

策略模式是指定义一系列的算法，把它们单独封装起来，并且使它们可以互相替换，使得算法可以独立于使用它的客户端而变化，也是说这些算法所完成的功能类型是一样的，对外接口也是一样的，只是不同的策略为引起环境角色[^环境角色]表现出不同的行为。

相比于使用大量的if...else，使用策略模式可以降低复杂度，使得代码更容易维护。

缺点：可能需要定义大量的策略类，并且这些策略类都要提供给客户端。

[^环境角色]:持有一个策略类的引用，最终给客户端调用。

### 2.1、传统的策略模式实现

```c++
/*
* 关键代码：实现同一个接口。

* 以下代码实例中，以游戏角色不同的攻击方式为不同的策略，游戏角色即为执行不同策略的环境角色。
*/

#include <iostream>

using namespace std;

//抽象策略类，提供一个接口
class Hurt
{
public:
	virtual void blood() = 0;
};

//具体的策略实现类，具体实现接口， Adc持续普通攻击
class AdcHurt : public Hurt
{
public:
	void blood() override
	{
		cout << "Adc hurt, Blood loss" << endl;
	}
};

//具体的策略实现类，具体实现接口， Apc技能攻击
class ApcHurt : public Hurt
{
public:
	void blood() override
	{
		cout << "Apc Hurt, Blood loss" << endl;
	}
};

//环境角色类， 游戏角色战士，传入一个策略类指针参数。
class Soldier
{
public:
	Soldier(Hurt* hurt):m_pHurt(hurt)
	{
	}
    //在不同的策略下，该游戏角色表现出不同的攻击
	void attack()
	{
		m_pHurt->blood();
	}
private:
	Hurt* m_pHurt;
};

//定义策略标签
typedef enum
{
	Hurt_Type_Adc,
	Hurt_Type_Apc,
	Hurt_Type_Num
}HurtType;

//环境角色类， 游戏角色法师，传入一个策略标签参数。
class Mage
{
public:
	Mage(HurtType type)
	{
		switch(type)
		{
		case Hurt_Type_Adc:
			m_pHurt = new AdcHurt();
			break;
		case Hurt_Type_Apc:
			m_pHurt = new ApcHurt();
			break;
		default:
			break;
		}
	}
	~Mage()
	{
		delete m_pHurt;
		m_pHurt = nullptr;
		cout << "~Mage()" << endl;
	}

	void attack()
	{
		m_pHurt->blood();
	}
private:
	Hurt* m_pHurt;
};

//环境角色类， 游戏角色弓箭手，实现模板传递策略。
template<typename T>
class Archer
{
public:
	void attack()
	{
		m_hurt.blood();
	}
private:
	T m_hurt;
};

int main()
{
	Archer<ApcHurt>* arc = new Archer<ApcHurt>;
	arc->attack();

	delete arc;
	arc = nullptr;
	
	return 0;
}
```

### 2.2、使用函数指针实现策略模式

```c++
#include <iostream>
#include <functional> 

void adcHurt()
{
	std::cout << "Adc Hurt" << std::endl;
}

void apcHurt()
{
	std::cout << "Apc Hurt" << std::endl;
}

//环境角色类， 使用传统的函数指针
class Soldier
{
public:
	typedef void (*Function)();
	Soldier(Function fun): m_fun(fun)
	{
	}
	void attack()
	{
		m_fun();
	}
private:
	Function m_fun;
};

//环境角色类， 使用std::function<>
class Mage
{
public:
	typedef std::function<void()> Function;

	Mage(Function fun): m_fun(fun)
	{
	}
	void attack()
	{
		m_fun();
	}
private:
	Function m_fun;
};

int main()
{
	Soldier* soldier = new Soldier(apcHurt);
	soldier->attack();
	delete soldier;
	soldier = nullptr;
	return 0;
}
```

## 3、适配器模式

适配器模式可以将一个类的接口转换成客户端希望的另一个接口，使得原来由于接口不兼容而不能在一起工作的那些类可以在一起工作。通俗的讲就是当我们已经有了一些类，而这些类不能满足新的需求，此时就可以考虑是否能将现有的类适配成可以满足新需求的类。适配器类需要继承或依赖已有的类，实现想要的目标接口。

缺点：过多地使用适配器，会让系统非常零乱，不易整体进行把握。比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现，一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，可以不使用适配器，而是直接对系统进行重构。

### 3.1、使用复合实现适配器模式

```c++
/*
* 关键代码：适配器继承或依赖已有的对象，实现想要的目标接口。

* 以下示例中，假设我们之前有了一个双端队列，新的需求要求使用栈和队列来完成。
  双端队列可以在头尾删减或增加元素。而栈是一种先进后出的数据结构，添加数据时添加到栈的顶部，删除数据时先删   除栈顶部的数据。因此我们完全可以将一个现有的双端队列适配成一个栈。
*/

//双端队列， 被适配类
class Deque
{
public:
	void push_back(int x)
	{
		cout << "Deque push_back:" << x << endl;
	}
	void push_front(int x)
	{
		cout << "Deque push_front:" << x << endl;
	}
	void pop_back()
	{
		cout << "Deque pop_back" << endl;
	}
	void pop_front()
	{
		cout << "Deque pop_front" << endl;
	}
};

//顺序类，抽象目标类
class Sequence  
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//栈,后进先出, 适配类
class Stack:public Sequence   
{
public:
	//将元素添加到堆栈的顶部。
	void push(int x) override
	{
		m_deque.push_front(x);
	}
	//从堆栈中删除顶部元素
	void pop() override
	{
		m_deque.pop_front();
	}
private:
	Deque m_deque;
};

//队列，先进先出，适配类
class Queue:public Sequence  
{
public:
	//将元素添加到队列尾部
	void push(int x) override
	{
		m_deque.push_back(x);
	}
	//从队列中删除顶部元素
	void pop() override
	{
		m_deque.pop_front();
	}
private:
	Deque m_deque;
};
```

### 3.2、使用继承实现适配器模式

```C++
//双端队列，被适配类
class Deque  
{
public:
	void push_back(int x)
	{
		cout << "Deque push_back:" << x << endl;
	}
	void push_front(int x)
	{
		cout << "Deque push_front:" << x << endl;
	}
	void pop_back()
	{
		cout << "Deque pop_back" << endl;
	}
	void pop_front()
	{
		cout << "Deque pop_front" << endl;
	}
};

//顺序类，抽象目标类
class Sequence  
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//栈,后进先出, 适配类
class Stack:public Sequence, private Deque   
{
public:
	void push(int x)
	{
		push_front(x);
	}
	void pop()
	{
		pop_front();
	}
};

//队列，先进先出，适配类
class Queue:public Sequence, private Deque 
{
public:
	void push(int x)
	{
		push_back(x);
	}
	void pop()
	{
		pop_front();
	}
};
```

## 4、单例模式

单例模式顾名思义，保证一个类仅可以有一个实例化对象，并且提供一个可以访问它的全局接口。实现单例模式必须注意一下几点：

* 单例类只能由一个实例化对象。
* 单例类必须自己提供一个实例化对象。
* 单例类必须提供一个可以访问唯一实例化对象的接口。

单例模式分为懒汉和饿汉两种实现方式。

### 4.1、懒汉单例模式

懒汉：故名思义，不到万不得已就不会去实例化类，也就是说在第一次用到类实例的时候才会去实例化一个对象。在访问量较小，甚至可能不会去访问的情况下，采用懒汉实现，这是以时间换空间。

#### 4.1.1、非线程安全的懒汉单例模式

```C++
/*
* 关键代码：构造函数是私有的，不能通过赋值运算，拷贝构造等方式实例化对象。
*/

//懒汉式一般实现：非线程安全，getInstance返回的实例指针需要delete
class Singleton
{
public:
	static Singleton* getInstance();
	~Singleton(){}

private:
	Singleton(){}	                                     //构造函数私有
	Singleton(const Singleton& obj) = delete;            //明确拒绝
	Singleton& operator=(const Singleton& obj) = delete; //明确拒绝
    
    static Singleton* m_pSingleton;
};

Singleton* Singleton::m_pSingleton = NULL;

Singleton* Singleton::getInstance()
{
	if(m_pSingleton == NULL)
	{
		m_pSingleton = new Singleton;
	}
	return m_pSingleton;
}
```

#### 4.1.2、线程安全的懒汉单例模式

```c++
//懒汉式：加lock，线程安全
std::mutex mt;

class Singleton
{
public:
	static Singleton* getInstance();
private:
	Singleton(){}                                    //构造函数私有
	Singleton(const Singleton&) = delete;            //明确拒绝
	Singleton& operator=(const Singleton&) = delete; //明确拒绝

	static Singleton* m_pSingleton;
	
};
Singleton* Singleton::m_pSingleton = NULL;

Singleton* Singleton::getInstance()
{
	if(m_pSingleton == NULL)
	{
		mt.lock();
		m_pSingleton = new Singleton();
		mt.unlock();
	}
	return m_pSingleton;
}
```

#### 4.1.3、返回一个reference指向local static对象

这种单例模式实现方式多线程可能存在不确定性：任何一种non-const static对象，不论它是local或non-local,在多线程环境下“等待某事发生”都会有麻烦。解决的方法：在程序的单线程启动阶段手工调用所有reference-returning函数。这种实现方式的好处是不需要去delete它。

```c++
class Singleton
{
public:
	static Singleton& getInstance();
private:
	Singleton(){}
	Singleton(const Singleton&) = delete;  //明确拒绝
	Singleton& operator=(const Singleton&) = delete; //明确拒绝
};


Singleton& Singleton::getInstance()
{
	static Singleton singleton;
	return singleton;
}
```



### 4.2、饿汉单例模式

饿汉：饿了肯定要饥不择食。所以在单例类定义的时候就进行实例化。在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。

```c++
//饿汉式：线程安全，注意一定要在合适的地方去delete它
class Singleton
{
public:
	static Singleton* getInstance();
private:
	Singleton(){}                                    //构造函数私有
	Singleton(const Singleton&) = delete;            //明确拒绝
	Singleton& operator=(const Singleton&) = delete; //明确拒绝

	static Singleton* m_pSingleton;
};

Singleton* Singleton::m_pSingleton = new Singleton();

Singleton* Singleton::getInstance()
{
	return m_pSingleton;
}
```

## 5、原型模式

原型模式：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。通俗的讲就是当需要创建一个新的实例化对象时，我们刚好有一个实例化对象，但是已经存在的实例化对象又不能直接使用。这种情况下拷贝一个现有的实例化对象来用，可能会更方便。

以下情形可以考虑使用原型模式：

* 当new一个对象，非常繁琐复杂时，可以使用原型模式来进行复制一个对象。比如创建对象时，构造函数的参数很多，而自己又不完全的知道每个参数的意义，就可以使用原型模式来创建一个新的对象，不必去理会创建的过程。
* 当需要new一个新的对象，这个对象和现有的对象区别不大，我们就可以直接复制一个已有的对象，然后稍加修改。
* 当需要一个对象副本时，比如需要提供对象的数据，同时又需要避免外部对数据对象进行修改，那就拷贝一个对象副本供外部使用。

```c++
/*
* 关键代码：拷贝，return new className(*this);
*/
#include <iostream>

using namespace std;

//提供一个抽象克隆基类。
class Clone
{
public:
	virtual Clone* clone() = 0;
	virtual void show() = 0;
};

//具体的实现类
class Sheep:public Clone
{
public:
	Sheep(int id, string name):Clone(),
	                           m_id(id),m_name(name)
	{
		cout << "Sheep() id address:" << &m_id << endl;
		cout << "Sheep() name address:" << &m_name << endl;
	}
	~Sheep()
	{
	}
	//关键代码拷贝构造函数
	Sheep(const Sheep& obj)
	{
		this->m_id = obj.m_id;
		this->m_name = obj.m_name;
		cout << "Sheep(const Sheep& obj) id address:" << &m_id << endl;
		cout << "Sheep(const Sheep& obj) name address:" << &m_name << endl;
	}
	//关键代码克隆函数，返回return new Sheep(*this)
	Clone* clone()
	{
		return new Sheep(*this);
	}
	void show()
	{
		cout << "id  :" << m_id << endl;
		cout << "name:" << m_name.data() << endl;
	}
private:
	int m_id;
	string m_name;
};

int main()
{
	Clone* s1 = new Sheep(1, "abs");
	s1->show();
	Clone* s2 = s1->clone();
	s2->show();
    
	delete s1;
    s1 = nullptr;
	delete s2;
    s2 = nullptr;
	return 0;
}

```

## 6、模板模式

模板模式：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

当多个类有相同的方法，并且逻辑相同，只是细节上有差异时，可以考虑使用模板模式。具体的实现上可以将相同的核心算法设计为模板方法，具体的实现细节有子类实现。

缺点:每一个不同的实现都需要一个子类来实现，导致类的个数增加，使得系统更加庞大。

以生产电脑为例，电脑生产的过程都是一样的，只是一些装配的器件可能不同而已。

```c++
/*
* 关键代码：在抽象类实现通用接口，细节变化在子类实现。
*/

#include <iostream>

using namespace std;

class Computer
{
public:
	void product()
	{
		installCpu();
		installRam();
		installGraphicsCard();
	}

protected:
	virtual	void installCpu() = 0;
	virtual void installRam() = 0;
	virtual void installGraphicsCard() = 0;

};

class ComputerA : public Computer
{
protected:
	void installCpu() override
	{
		cout << "ComputerA install Inter Core i5" << endl;
	}

	void installRam() override
	{
		cout << "ComputerA install 2G Ram" << endl;
	}

	void installGraphicsCard() override
	{
		cout << "ComputerA install Gtx940 GraphicsCard" << endl;
	}
};

class ComputerB : public Computer
{
protected:
	void installCpu() override
	{
		cout << "ComputerB install Inter Core i7" << endl;
	}

	void installRam() override
	{
		cout << "ComputerB install 4G Ram" << endl;
	}

	void installGraphicsCard() override
	{
		cout << "ComputerB install Gtx960 GraphicsCard" << endl;
	}
};

int main()
{
	ComputerB* c1 = new ComputerB();
	c1->product();

	delete c1;
	c1 = nullptr;

	return 0;
}

```

## 7、建造者模式

建造者模式：将复杂对象的构建和其表示分离，使得相同的构建过程可以产生不同的表示。

以下情形可以考虑使用建造者模式：

* 对象的创建复杂，但是其各个部分的子对象创建算法一定。
* 需求变化大，构造复杂对象的子对象经常变化，但将其组合在一起的算法相对稳定。

建造者模式的优点：

* 将对象的创建和表示分离，客户端不需要了解具体的构建细节。
* 增加新的产品对象时，只需要增加其具体的建造类即可，不需要修改原来的代码，扩展方便。

产品之间差异性大，内部变化较大、较复杂时不建议使用建造者模式。

```c++
/*
*关键代码：建造者类：创建和提供实例； Director类：管理建造出来的实例的依赖关系。
*/

#include <iostream>
#include <string>

using namespace std;

//具体的产品类
class Order
{
public:
	void setFood(const string& food)
	{
		m_strFood = food;
	}

	const string& food()
	{
		cout << m_strFood.data() << endl;
		return m_strFood;
	}
	
	void setDrink(const string& drink)
	{
		m_strDrink = drink;
	}

	const string& drink()
	{
		cout << m_strDrink << endl;
		return m_strDrink;
	}

private:
	string m_strFood;
	string m_strDrink;
};

//抽象建造类，提供建造接口。
class OrderBuilder
{
public:
	virtual ~OrderBuilder()
	{
		cout << "~OrderBuilder()" << endl;
	}
	virtual void setOrderFood() = 0;
	virtual void setOrderDrink() = 0;
	virtual Order* getOrder() = 0;
};

//具体的建造类
class VegetarianOrderBuilder : public OrderBuilder 
{
public:
	VegetarianOrderBuilder()
	{
		m_pOrder = new Order;
	}

	~VegetarianOrderBuilder()
	{
		cout << "~VegetarianOrderBuilder()" << endl;
		delete m_pOrder;
		m_pOrder = nullptr;
	}

	void setOrderFood() override
	{
		m_pOrder->setFood("vegetable salad");
	}

	void setOrderDrink() override
	{
		m_pOrder->setDrink("water");
	}

	Order* getOrder() override
	{
		return m_pOrder;
	}

private:
	Order* m_pOrder;
};

//具体的建造类
class MeatOrderBuilder : public OrderBuilder
{
public:
	MeatOrderBuilder()
	{
		m_pOrder = new Order;
	}
	~MeatOrderBuilder()
	{
		cout << "~MeatOrderBuilder()" << endl;
		delete m_pOrder;
		m_pOrder = nullptr;
	}

	void setOrderFood() override
	{
		m_pOrder->setFood("beef");
	}

	void setOrderDrink() override
	{
		m_pOrder->setDrink("beer");
	}

	Order* getOrder() override
	{
		return m_pOrder;
	}

private:
	Order* m_pOrder;
};

//Director类，负责管理实例创建的依赖关系，指挥构建者类创建实例
class Director
{
public:
	Director(OrderBuilder* builder) : m_pOrderBuilder(builder)
	{
	}
	void construct()
	{
		m_pOrderBuilder->setOrderFood();
		m_pOrderBuilder->setOrderDrink();
	}

private:
	OrderBuilder* m_pOrderBuilder;
};


int main()
{
//	MeatOrderBuilder* mBuilder = new MeatOrderBuilder;
	OrderBuilder* mBuilder = new MeatOrderBuilder;  //注意抽象构建类必须有虚析构函数，解析时才会														 调用子类的析构函数
	Director* director = new Director(mBuilder);
	director->construct();
	Order* order = mBuilder->getOrder();
	order->food();
	order->drink();

	delete director;
	director = nullptr;

	delete mBuilder;
	mBuilder = nullptr;

	return 0;
}
```

## 8、外观模式

外观模式：为子系统中的一组接口定义一个一致的界面；外观模式提供一个高层的接口，这个接口使得这一子系统更加容易被使用；对于复杂的系统，系统为客户端提供一个简单的接口，把负责的实现过程封装起来，客户端不需要连接系统内部的细节。

以下情形建议考虑外观模式：

* 设计初期阶段，应有意识的将不同层分离，层与层之间建立外观模式。
* 开发阶段，子系统越来越复杂，使用外观模式提供一个简单的调用接口。
* 一个系统可能已经非常难易维护和扩展，但又包含了非常重要的功能，可以为其开发一个外观类，使得新系统可以方便的与其交互。

优点：

* 实现了子系统与客户端之间的松耦合关系。
* 客户端屏蔽了子系统组件，减少了客户端所需要处理的对象数据，使得子系统使用起来更方便容易。
* 更好的划分了设计层次，对于后期维护更加的容易。

```C++
/*
* 关键代码：客户与系统之间加一个外观层，外观层处理系统的调用关系、依赖关系等。
*以下实例以电脑的启动过程为例，客户端只关心电脑开机的、关机的过程，并不需要了解电脑内部子系统的启动过程。
*/
#include <iostream>

using namespace std;

//抽象控件类，提供接口
class Control
{
public:
	virtual void start() = 0;
	virtual void shutdown() = 0;
};

//子控件， 主机
class Host : public Control
{
public:
	void start() override
	{
		cout << "Host start" << endl;
	}
	void shutdown() override
	{
		cout << "Host shutdown" << endl;
	}
};

//子控件， 显示屏
class LCDDisplay : public Control
{
public:
	void start() override
	{
		cout << "LCD Display start" << endl;
	}
	void shutdown() override
	{
		cout << "LCD Display shutdonw" << endl;
	}
};

//子控件， 外部设备
class Peripheral : public Control
{
public:
	void start() override
	{
		cout << "Peripheral start" << endl;
	}
	void shutdown() override
	{
		cout << "Peripheral shutdown" << endl;
	}
};

class Computer
{
public:
	void start()
	{
		m_host.start();
		m_display.start();
		m_peripheral.start();
		cout << "Computer start" << endl;
	}
	void shutdown()
	{
		m_host.shutdown();
		m_display.shutdown();
		m_peripheral.shutdown();
		cout << "Computer shutdown" << endl;
	}
private:
	Host   m_host;
	LCDDisplay m_display;
	Peripheral   m_peripheral;
};

int main()
{
	Computer computer;
	computer.start();

	//do something

	computer.shutdown();

	return 0;
}
```

## 9、组合模式

组合模式：将对象组合成树形结构以表示“部分-整体”的层次结构，组合模式使得客户端对单个对象和组合对象的使用具有一直性。

既然讲到以树形结构表示“部分-整体”，那可以将组合模式想象成一根大树，将大树分成树枝和树叶两部分，树枝上可以再长树枝，也可以长树叶，树叶上则不能再长出别的东西。

以下情况可以考虑使用组合模式：

* 希望表示对象的部分-整体层次结构。
* 希望客户端忽略组合对象与单个对象的不同，客户端将统一的使用组合结构中的所有对象。

```c++
/*
* 关键代码：树枝内部组合该接口，并且含有内部属性list，里面放Component。
*/

#include <iostream>
#include <list>
#include <memory>

using namespace std;

//抽象类，提供组合和单个对象的一致接口
class Company
{
public:
	Company(const string& name): m_name(name){}
	virtual ~Company(){ cout << "~Company()" << endl;}

	virtual void add(Company* ) = 0;
	virtual void remove(const string&) = 0;
	virtual void display(int depth) = 0;

	virtual const string& name()
	{
		return m_name;
	}

protected:
	string m_name;
};

//具体的单个对象实现类，“树枝”类
class HeadCompany : public Company
{
public:
	HeadCompany(const string& name): Company(name){}
	virtual ~HeadCompany(){ cout << "~HeadCompany()" << endl;}

	void add(Company* company) override
	{
		shared_ptr<Company> temp(company);
		m_companyList.push_back(temp);
	}

	void remove(const string& strName) override
	{
		list<shared_ptr<Company>>::iterator iter = m_companyList.begin();
		for(; iter != m_companyList.end(); iter++)
		{
			if((*iter).get()->name() == strName)
			{
			//不应该在此处使用list<T>.erase(list<T>::iterator iter),会导致iter++错误，这里删除目               标元素之后，必须return。
				m_companyList.erase(iter);
				return;
			}
		}
	}

	void display(int depth) override
	{
		for(int i = 0; i < depth; i++)
		{
			cout << "-";
		}
		cout << this->name().data() << endl;
		list<shared_ptr<Company>>::iterator iter = m_companyList.begin();
		for(; iter!= m_companyList.end(); iter++)
		{
			(*iter).get()->display(depth + 1);
		}
	}

private:
	list<shared_ptr<Company>> m_companyList;
};

//具体的单个对象实现类，“树叶”类
class ResearchCompany : public Company
{
public:
	ResearchCompany(const string& name): Company(name){}
	virtual ~ResearchCompany(){ cout << "~ResearchCompany()" << endl;}

	void add(Company* ) override
	{
	}

	void remove(const string&) override
	{
	}

	void display(int depth) override
	{
		for(int i = 0; i < depth; i++)
		{
			cout << "-";
		}
		cout << m_name.data() << endl;
	}
};

//具体的单个对象实现类，“树叶”类
class SalesCompany : public Company
{
public:
	SalesCompany(const string& name): Company(name){}
	virtual ~SalesCompany(){ cout << "~SalesCompany()" << endl;}

	void add(Company* ) override
	{
	}

	void remove(const string&) override
	{
	}

	void display(int depth) override
	{
		for(int i = 0; i < depth; i++)
		{
			cout << "-";
		}
		cout << m_name.data() << endl;
	}
};

//具体的单个对象实现类，“树叶”类
class FinanceCompany : public Company
{
public:
	FinanceCompany(const string& name): Company(name){}
	virtual ~FinanceCompany(){ cout << "~FinanceCompany()" << endl;}

	void add(Company* ) override
	{
	}

	void remove(const string&) override
	{
	}

	void display(int depth) override
	{
		for(int i = 0; i < depth; i++)
		{
			cout << "-";
		}
		cout << m_name.data() << endl;
	}
};


int main()
{
	HeadCompany* headRoot = new HeadCompany("Head Root Company");

	HeadCompany* childRoot1 = new HeadCompany("Child Company A");
	ResearchCompany* r1 = new ResearchCompany("Research Company A");
	SalesCompany* s1 = new SalesCompany("Sales Company A");
	SalesCompany* s2 = new SalesCompany("Sales Company B");
	FinanceCompany* f1 = new FinanceCompany("FinanceCompany A");
	
	childRoot1->add(r1);
	childRoot1->add(s1);
	childRoot1->add(s2);
	childRoot1->add(f1);

	HeadCompany* childRoot2 = new HeadCompany("Child Company B");
	ResearchCompany* r2 = new ResearchCompany("Research Company B");
	SalesCompany* s3 = new SalesCompany("Sales Company C");
	SalesCompany* s4 = new SalesCompany("Sales Company D");
	FinanceCompany* f2 = new FinanceCompany("FinanceCompany B");
	
	childRoot2->add(r2);
	childRoot2->add(s3);
	childRoot2->add(s4);
	childRoot2->add(f2);

	headRoot->add(childRoot1);
	headRoot->add(childRoot2);
	headRoot->display(1);
	
	cout << "\n***************\n" << endl;

	childRoot1->remove("Sales Company B");
	headRoot->display(1);
	
	cout << "\n***************\n" << endl;

	delete headRoot;
	headRoot = nullptr;

	return 0;
}
```

## 10、代理模式

代理模式：为其它对象提供一种代理以控制这个对象的访问。在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介作用。

优点：

* 职责清晰。真实的角色只负责实现实际的业务逻辑，不用关心其它非本职责的事务，通过后期的代理完成具体的任务。这样代码会简洁清晰。
* 代理对象可以在客户端和目标对象之间起到中介的作用，这样就保护了目标对象。
* 扩展性好。

```C++
/*
* 关键代码：一个是真正的你要访问的对象(目标类)，一个是代理对象,真正对象与代理对象实现同一个接口,先访问代理*         类再访问真正要访问的对象。
*/
#include <iostream>

using namespace std;

class Gril
{
public:
    Gril(const string& name = "gril"):m_string(name){}
    string getName()
    {
        return m_string;
    }
private:
    string m_string;
};

class Profession
{
public:
    virtual ~Profession(){}
    virtual void profess() = 0;
};

class YoungMan : public Profession
{
public:
    YoungMan(const Gril& gril):m_gril(gril){}
    void profess()
    {
        cout << "Young man love " << m_gril.getName().data() << endl;
    }

private:
    Gril m_gril;
};

class ManProxy : public Profession
{
public:
    ManProxy(const Gril& gril):m_pMan(new YoungMan(gril)){}
	~ManProxy()
	{
		delete m_pMan;
		m_pMan = nullptr;
	}
    void profess()
    {
        m_pMan->profess();
    }
private:
    YoungMan* m_pMan;
};

int main(int argc, char *argv[])
{
    Gril gril("heihei");
    ManProxy* proxy = new ManProxy(gril);
    proxy->profess();

    delete proxy;
	proxy = nullptr;
    return 0;
}
```

## 11、享元模式

享元模式：运用共享技术有效地支持大量细粒度的对象。在有大量对象时，把其中共同的部分抽象出来，如果有相同的业务请求，直接返回内存中已有的对象，避免重新创建。



以下情况可以考虑使用享元模式：

* 系统中有大量的对象，这些对象消耗大量的内存，且这些对象的状态可以被外部化。















































