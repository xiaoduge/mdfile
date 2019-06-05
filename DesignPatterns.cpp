
/***********1������ģʽ���򵥹���ģʽ����������ģʽ�����󹤳�ģʽ**************/
/*
	1)���򵥹���ģʽ����Ҫ�ص�����Ҫ�ڹ����������жϣ��Ӷ�������Ӧ�Ĳ�Ʒ���������²�Ʒʱ����Ҫ�޸Ĺ����ࡣ
*/
typedef enum
{
	T80 = 1,
	T99
}TankType;

class Tank
{
public:
	virtual void message() = 0;
};

class Tank80:public Tank
{
public:
	void message()
	{
		cout << "Tank80" << endl;
	}
};

class Tank99:public Tank
{
public:
	void message()
	{
		cout << "Tank99" << endl;
	}
};

class TankFactory
{
public:
	Tank* createTank(TankType type)
	{
		switch(type)
		{
		case 1:
			return new Tank80();
		case 2:
			return new Tank99();
		default:
			return NULL;
		}
	}
};


/*
	2)����������ģʽ����ָ����һ����������Ľӿڣ����������ʵ������һ���࣬Factory Methodʹһ�����ʵ�����ӳٵ������ࡣ
	��ͼ������һ����������Ľӿڣ����������Լ�����ʵ������һ�������࣬����ģʽʹ�䴴�������ӳٵ�������С�
    ��Ҫ�������Ҫ����ӿ�ѡ������⡣
    ��ʱʹ�ã�������ȷ�ؼƻ���ͬ�����´�����ͬʵ��ʱ��
	��ν������������ʵ�ֹ����ӿڣ����ص�Ҳ��һ������Ĳ�Ʒ��
    �ؼ����룺����������������ִ�С�
	ȱ�㣺ÿ����һ�ֲ�Ʒ������Ҫ����һ�����󹤳�����ȼ򵥹���ģʽ����������ģʽ��Ҫ���������ࡣ
*/

class Tank
{
public:
	virtual void message() = 0;
};

class Tank80:public Tank
{
public:
	void message()
	{
		cout << "Tank80" << endl;
	}
};

class Tank99:public Tank
{
public:
	void message()
	{
		cout << "Tank99" << endl;
	}
};

class TankFactory
{
public:
	virtual Tank* createTank() = 0;
};

class Tank80Factory:public TankFactory
{
public:
	Tank* createTank()
	{
		return new Tank80();
	}
};

class Tank99Factory:public TankFactory
{
public:
	Tank* createTank()
	{
		return new Tank99();
	}
};

/*
	3)�����󹤳�ģʽ���ṩһ������һϵ����ػ��໥�����Ķ���ӿڣ�������ָ�����ǵľ����ࡣ
	��ͼ���ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ
	��Ҫ�������Ҫ����ӿ�ѡ������⡣
	��ʱʹ�ã�ϵͳ�Ĳ�Ʒ�ж���һ���Ĳ�Ʒ�壬��ϵͳֻ��������ĳһ��Ĳ�Ʒ��
	��ν������һ����Ʒ�����棬��������Ʒ��
	�ؼ����룺��һ��������ۺ϶��ͬ���Ʒ��
	ȱ�㣺��Ʒ����չ�ǳ����ѣ�Ҫ����һ��ϵ�е�ĳһ��Ʒ����Ҫ�ڳ���� Creator ��Ӵ��룬��Ҫ�ھ��������Ӵ��롣
*/
class Tank
{
public:
	virtual void message() = 0;
};

class Tank80:public Tank
{
public:
	void message()
	{
		cout << "Tank80" << endl;
	}
};

class Tank99:public Tank
{
public:
	void message()
	{
		cout << "Tank99" << endl;
	}
};

class Plain
{
public:
	virtual void message() = 0;
};

class Plain80: public Plain
{
public:
	void message()
	{
		cout << "Plain80" << endl;
	}
};

class Plain99: public Plain
{
public:
	void message()
	{
		cout << "Plain99" << endl;
	}
};

class Factory
{
public:
	virtual Tank* createTank() = 0;
	virtual Plain* createPlain() = 0;
};

class Factory80:public Factory
{
public:
	Tank* createTank()
	{
		return new Tank80();
	}
	Plain* createPlain()
	{
		return new Plain80();
	}
};

class Factory99:public Factory
{
public:
	Tank* createTank()
	{
		return new Tank99();
	}
	Plain* createPlain()
	{
		return new Plain99();
	}
};


/***********************************2������ģʽ********************************/
/*
	����ģʽ:��ָ����һϵ�е��㷨��������һ������װ����������ʹ���ǿ��Ի����滻��ʹ���㷨���Զ�����ʹ�����Ŀͻ����仯��Ҳ����˵��Щ�㷨����ɵĹ�����һ���ģ�����ӿ���һ���ģ�ֻ�Ǹ�����ʵ�ϴ��ڲ��졣
	��ͼ������һϵ�е��㷨,������һ������װ����, ����ʹ���ǿ��໥�滻��
	��Ҫ��������ж����㷨���Ƶ�����£�ʹ�� if...else �������ĸ��Ӻ�����ά����
	��ʱʹ�ã�һ��ϵͳ���������࣬���������ǵ�ֻ������ֱ�ӵ���Ϊ��
	��ν��������Щ�㷨��װ��һ��һ�����࣬������滻��
	�ؼ����룺ʵ��ͬһ���ӿڡ�
	ȱ�㣺 1������������ࡣ 2�����в����඼��Ҫ���Ⱪ¶��
*/

//��ͳ����ģʽʵ��
class Hurt
{
public:
	virtual void redBuff() = 0;
};

class AdcHurt:public Hurt
{
public:
	void redBuff()
	{
		cout << "Adc hurt" << endl;
	}
};

class ApcHurt:public Hurt
{
public:
	void redBuff()
	{
		cout << "Apc hurt" << endl;
	}
};

//����1������һ��ָ�����
class Soldier
{
public:
	Soldier(Hurt* hurt):m_hurt(hurt)
	{
	}
	~Soldier()
	{
	}
	void beInjured()
	{
		m_hurt->redBuff();
	}
private:
	Hurt* m_hurt;
};

//����2������һ��������ǩ
typedef enum
{
	adc,
	apc
}HurtType;

class Master
{
public:
	Master(HurtType type)
	{
		switch(type)
		{
		case adc:
			m_hurt = new AdcHurt;
			break;
		case apc:
			m_hurt = new ApcHurt;
			break;
		default:
			m_hurt = NULL;
			break;
		}
	}
	~Master()
	{
	}
	void beInjured()
	{
		if(m_hurt != NULL)
		{
			m_hurt->redBuff();
		}
		else
		{
			cout << "Not hurt" << endl;
		}
	}
private:
	Hurt* m_hurt;
};

//����3��ʹ��ģ����
template <typename T>
class Tank
{
public:
	void beInjured()
	{
		m_hurt.redBuff();
	}
private:
	T m_hurt;
};
//END

//ʹ�ú���ָ��ʵ�ֲ���ģʽ
void adcHurt(int num)
{
	cout << "adc hurt:" << num << endl;
}

void apcHurt(int num)
{
	cout << "apc hurt:" << num << endl;
}

//��ͨ����ָ��
class Aid
{
public:
	typedef void (*HurtFun)(int);
	
	Aid(HurtFun fun):m_fun(fun)
	{
	}
	void beInjured(int num)
	{
		m_fun(num);
	}
private:
	HurtFun m_fun;
};

//ʹ��std::function , ͷ�ļ���#include<functional>
class Bowman
{
public:
	typedef std::function<void(int)> HurtFunc;

	Bowman(HurtFunc fun):m_fun(fun)
	{
	}
	void beInjured(int num)
	{
		m_fun(num);
	}

private:
	HurtFunc m_fun;
};
//END


/***********************************3��������ģʽ********************************/
/*
	������ģʽ����һ����Ľӿ�ת���ɿͻ�ϣ������һ���ӿڣ�ʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������
	��Ҫ�������Ҫ��������ϵͳ�У�����Ҫ��һЩ"�ִ�Ķ���"�ŵ��µĻ����У����»���Ҫ��Ľӿ����ֶ���������ġ�
	��ʱʹ�ã� 1��ϵͳ��Ҫʹ�����е��࣬������Ľӿڲ�����ϵͳ����Ҫ�� 2����Ҫ����һ�������ظ�ʹ�õ��࣬������һЩ�˴�֮��û��̫�������һЩ�࣬����һЩ�����ڽ�����������һ��������ЩԴ�಻һ����һ�µĽӿڡ� 3��ͨ���ӿ�ת������һ���������һ����ϵ�С��������ϻ��ͷ��ݣ����ڶ���һ���ɻ����ڲ�����ʵ��������£�����һ�������������������һ��������ʵ�ַɵĽӿڡ���
	��ν�����̳л��������Ƽ�����
	�ؼ����룺�������̳л��������еĶ���ʵ����Ҫ��Ŀ��ӿڡ�
	ȱ�㣺1�������ʹ��������������ϵͳ�ǳ����ң�����������а��ա����磬�����������õ��� A �ӿڣ���ʵ�ڲ���������� B �ӿڵ�ʵ�֣�һ��ϵͳ���̫��������������������һ�����ѡ����������Ǻ��б�Ҫ�����Բ�ʹ��������������ֱ�Ӷ�ϵͳ�����ع���
*/

//ʹ�ø��ϣ�����ģʽ
class Deque  //˫�˶��У���������
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

class Sequence  //˳���࣬Ŀ����
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

class Stack:public Sequence   //ջ, ������
{
public:
	void push(int x)
	{
		m_deque.push_back(x);
	}
	void pop()
	{
		m_deque.pop_back();
	}
private:
	Deque m_deque;
};

class Queue:public Sequence  //���У�������
{
public:
	void push(int x)
	{
		m_deque.push_back(x);
	}
	void pop()
	{
		m_deque.pop_front();
	}
private:
	Deque m_deque;
};
//END

//ʹ�ü̳�,��ģʽ
class Deque  //˫�˶��У���������
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

class Sequence  //˳���࣬Ŀ����
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

class Stack:public Sequence, private Deque   //ջ, ������
{
public:
	void push(int x)
	{
		push_back(x);
	}
	void pop()
	{
		pop_back();
	}
};

class Queue:public Sequence, private Deque  //���У�������
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
//END

/***********************************4������ģʽ********************************/
/*
	����ģʽ����֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣
	��Ҫ�����һ��ȫ��ʹ�õ���Ƶ���ش��������١�
	��ʱʹ�ã������ʵ����Ŀ����ʡϵͳ��Դ��ʱ��
	��ν�����ж�ϵͳ�Ƿ��Ѵ��ڵ�����������򷵻أ�û���򴴽���
	�ؼ����룺���캯����˽�еġ�
	ȱ�㣺
*/
/*
����������Լ������ʵ�ַ����������������
        ����������˼�壬�����򲻵��ѾͲ���ȥʵ�����࣬Ҳ����˵�ڵ�һ���õ���ʵ����ʱ��Ż�ȥʵ�����������ϱߵľ��䷽������Ϊ����ʵ�֣�
        ���������˿϶�Ҫ������ʳ�������ڵ����ඨ���ʱ��ͽ���ʵ������
�����ص���ѡ��
        ����Ҫ�����߳�ͬ���������ڷ������Ƚϴ󣬻��߿��ܷ��ʵ��̱߳Ƚ϶�ʱ�����ö���ʵ�֣�����ʵ�ָ��õ����ܡ������Կռ任ʱ�䡣
        �ڷ�������Сʱ����������ʵ�֡�������ʱ�任�ռ䡣
*/
//����ʽһ��ʵ�֣����̰߳�ȫ��getInstance���ص�ʵ��ָ����Ҫdelete
class Singleton
{
public:
	static Singleton* getInstance();
	~Singleton(){}

private:
	static Singleton* m_pSingleton;
	Singleton(){}	
	Singleton(const Singleton& obj) = delete;  //��ȷ�ܾ�
	Singleton& operator=(const Singleton& obj) = delete; //��ȷ�ܾ�
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
//END

//����ʽ����lock���̰߳�ȫ
std::mutex mt;

class Singleton
{
public:
	static Singleton* getInstance();
private:
	Singleton(){}
	Singleton(const Singleton&) = delete;  //��ȷ�ܾ�
	Singleton& operator=(const Singleton&) = delete; //��ȷ�ܾ�

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
//END

//����һ��referenceָ��local static����
//���߳̿��ܴ��ڲ�ȷ���ԣ��κ�һ��non-const static���󣬲�������local��non-local,�ڶ��̻߳����¡��ȴ�ĳ�·������������鷳������ķ������ڳ���ĵ��߳������׶��ֹ���������reference-returning������
class Singleton
{
public:
	static Singleton& getInstance();
private:
	Singleton(){}
	Singleton(const Singleton&) = delete;  //��ȷ�ܾ�
	Singleton& operator=(const Singleton&) = delete; //��ȷ�ܾ�
};


Singleton& Singleton::getInstance()
{
	static Singleton singleton;
	return singleton;
}
//END

//����ʽ���̰߳�ȫ��ע��delete
class Singleton
{
public:
	static Singleton* getInstance();
private:
	Singleton(){}
	Singleton(const Singleton&) = delete;  //��ȷ�ܾ�
	Singleton& operator=(const Singleton&) = delete; //��ȷ�ܾ�

	static Singleton* m_pSingleton;
};

Singleton* Singleton::m_pSingleton = new Singleton();

Singleton* Singleton::getInstance()
{
	return m_pSingleton;
}
//END


/***********************************5��ԭ��ģʽ********************************/
/*
	ԭ��ģʽ����ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���
	��Ҫ������������ڽ�����ɾ������
	��ʱʹ�ã�1).�����ǵĶ������Ͳ��ǿ�ʼ����ȷ���ģ��������������������ȷ���Ļ�����ô����ͨ��������͵Ķ����¡��һ���µĶ���Ƚ�����һЩ��2).�е�ʱ��������Ҫһ��������ĳ��״̬�µĸ�������ʱ������ʹ��ԭ��ģʽ����õ�ѡ�����磺һ�����󣬾���һ�δ���֮�����ڲ���״̬�����˱仯�����ʱ��������Ҫһ�����״̬�ĸ��������ֱ��newһ���µĶ���Ļ�,��������״̬�ǲ��Եģ���ʱ������ʹ��ԭ��ģʽ����ԭ���Ķ��󿽱�һ���������������ͺ�֮ǰ�Ķ�������ȫһ�µ��ˣ�3).�����Ǵ���һЩ�Ƚϼ򵥵Ķ���ʱ�����Ҷ���֮��������С�����ܾͼ������Բ�ͬ���ѣ���ô�Ϳ���ʹ��ԭ��ģʽ����ɣ�ʡȥ�˴�������ʱ���鷳�ˣ�4).�е�ʱ�򣬴�������ʱ�����캯���Ĳ����ܶ࣬���Լ��ֲ���ȫ��֪��ÿ�����������壬�Ϳ���ʹ��ԭ��ģʽ������һ���µĶ��󣬲���ȥ��ᴴ���Ĺ��̡�

	->�ʵ���ʱ����һ��ԭ��ģʽ���ܼ��ٶ�Ӧ�Ĺ����������ٳ���ĸ��Ӷȣ����Ч��
	��ν�����������е�һ��ԭ�Ͷ��󣬿��ٵ����ɺ�ԭ�Ͷ���һ����ʵ����
	�ؼ����룺������return new className(*this);
*/
class Clone
{
public:
	Clone()
	{
	}
	virtual ~Clone()
	{
	}
	virtual Clone* clone() = 0;
	virtual void show() = 0;
};

class Sheep:public Clone
{
public:
	Sheep(int id, string name):Clone(),m_id(id),m_name(name)
	{
		cout << "Sheep() id add:" << &m_id << endl;
		cout << "Sheep() name add:" << &m_name << endl;
	}
	~Sheep()
	{
	}

	Sheep(const Sheep& obj)
	{
		this->m_id = obj.m_id;
		this->m_name = obj.m_name;
		cout << "Sheep(const Sheep& obj) id add:" << &m_id << endl;
		cout << "Sheep(const Sheep& obj) name add:" << &m_name << endl;
	}

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
	delete s2;
	return 0;
}


/***********************************6��ģ��ģʽ********************************/
/*
	ģ��ģʽ������һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ������С�ģ�巽��ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض����衣
	��Ҫ����������������ͬ�ķ����������߼���ͬ��ϸ���в��졣
	��ν��������Ҫ�����ӵ��㷨���������㷨���Ϊģ�巽�����ܱ�ϸ��������ʵ�֣��ع�ʱ������ʹ�õķ���������ͬ�Ĵ�����󵽸��࣬ͨ�����Ӻ���Լ����Ϊ��
	�ؼ����룺�ڳ�����ʵ��ͨ�ýӿڣ�ϸ�ڱ仯������ʵ�֡�
	ȱ�㣺ÿһ����ͬ��ʵ�ֶ���Ҫһ��������ʵ�֣�������ĸ������ӣ�ʹ��ϵͳ�����Ӵ�
*/
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

class ComputerA:public Computer
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

class ComputerB:public Computer
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


/***********************************7��������ģʽ********************************/
/*
	������ģʽ�������Ӷ���Ĺ��������ʾ���룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
	��Ҫ�����һ�����Ӷ���Ĵ����������ɸ������ֵ��Ӷ�����һ�����㷨���ɣ���������仯��������Ӷ���ĸ������־������ٱ仯���������������һ����㷨ȴ����ȶ���
	��ν���������벻��ֿ�
	�ؼ����룺�����ߣ��������ṩʵ����Director�������������ʵ����������ϵ����
	ȱ�㣺1����Ʒ�����й�ͬ�㣬��Χ�����ơ� 2�����ڲ��仯���ӣ����кܶ�Ľ����ࡣ
*/

typedef enum
{
	type1,
	type2
}ProductType;

class Product   //��Ʒ
{
public:
	void setNum(int num);
	void setColor(string color);
	void setType(ProductType type);

	void showProduct();
private:
	int m_num;
	string m_color;
	ProductType m_type;

};

void Product::setNum(int num)
{
	m_num = num;
}

void Product::setColor(string color)
{
	m_color = color;
}

void Product::setType(ProductType type)
{
	m_type = type;
}

void Product::showProduct()
{
	cout << "Product: " << endl;
	cout << "       num  : " << m_num << endl;
	cout << "       color: " << m_color.data() << endl;
	cout << "       type : " << m_type << endl;
}

//�����߸��࣬����ӿ�
class Builder
{
public:
	Builder(){}
	virtual ~Builder(){}
	virtual void buildNum(int num) = 0;
	virtual void buildColor(string color) = 0;
	virtual void buildType(ProductType type) = 0;
	virtual void createProduct() = 0;
	virtual Product* getProduct() = 0;
	virtual void show() = 0;
};

//������A
class BuilderA:public Builder
{
public:
	BuilderA(){}
	 ~BuilderA(){}
	void buildNum(int num) override;
	void buildColor(string color) override;
	void buildType(ProductType type) override;
	void createProduct() override;
	Product* getProduct() override;
	void show() override;
private:
	Product* m_product;
};

void BuilderA::buildNum(int num)
{
	cout << "BuilderA build Num: " << num << endl;
	m_product->setNum(num);
}

void BuilderA::buildColor(string color)
{
	cout << "BuilderA build color: " << color.data() << endl;
	m_product->setColor(color);
}

void BuilderA::buildType(ProductType type)
{
	cout << "BuilderA build type: " << type << endl;
	m_product->setType(type);
}

void BuilderA::createProduct()
{
	cout << "BuilderA CreateProduct: " << endl;
	m_product = new Product();
}

Product* BuilderA::getProduct()
{
	return m_product;
}
void BuilderA::show()
{
	m_product->showProduct();
}

//������B
class BuilderB:public Builder
{
public:
	BuilderB(){}
	 ~BuilderB(){}
	void buildNum(int num) override;
	void buildColor(string color) override;
	void buildType(ProductType type) override;
	void createProduct() override;
	Product* getProduct() override;
	void show() override;
private:
	Product* m_product;
};

void BuilderB::buildNum(int num)
{
	cout << "BuilderB build Num: " << num << endl;
	m_product->setNum(num);
}

void BuilderB::buildColor(string color)
{
	cout << "BuilderB build color: " << color.data() << endl;
	m_product->setColor(color);
}

void BuilderB::buildType(ProductType type)
{
	cout << "BuilderB build type: " << type << endl;
	m_product->setType(type);
}

void BuilderB::createProduct()
{
	cout << "BuilderB CreateProduct: " << endl;
	m_product = new Product();
}

Product* BuilderB::getProduct()
{
	return m_product;
}
void BuilderB::show()
{
	m_product->showProduct();
}

//�����࣬�����Ź���ľ������
class Director
{
public:
	Director(Builder* builder):m_builder(builder)
	{
	}
	void construct(int num, string color, ProductType type)
	{
		m_builder->createProduct();
		m_builder->buildNum(num);
		m_builder->buildColor(color);
		m_builder->buildType(type);
	}

private:
	Builder* m_builder;
};


/***********************************8�����ģʽ********************************/
/*
	���ģʽ��Ϊ��ϵͳ�е�һ��ӿڶ���һ��һ�µĽ��棬���ģʽ�ṩ��һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ�������ױ�ʹ�ã����ڸ��ӵ�ϵͳ��ϵͳΪ�ͻ��ṩһ���򵥵Ľӿڣ��Ѹ��ӵ�ʵ�ֹ��̷�װ�������ͻ�����Ҫ�˽�ϵͳ�ڲ���ϸ�ڡ�
	��Ҫ������ͻ�����Ҫ�˽�ϵͳ�ڲ����ӵ�ϸ�ڣ�ֻ��Ҫһ���ӿڣ�ϵͳ��ڡ�
	��ν�����ͻ���ֱ����ϵͳ��ϣ�����ͨ���������ϵͳ��ϡ�
	�ؼ����룺�ͻ���ϵͳ֮���һ����۲㣬��۲㴦��ϵͳ�ĵ��ù�ϵ��������ϵ�ȡ�
	ȱ�㣺��Ҫ�޸�ʱ���׼̳С������޸ġ�
*/
//
class Cpu
{
public:
	void productCpu()
	{
		cout << "Product Cpu" << endl;
	}
};

class Ram
{
public:
	void productRam()
	{
		cout << "Product Ram" << endl;
	}
};

class Graphics
{
public:
	void productGraphics()
	{
		cout << "Product Graphics" << endl;
	}
};

class Computer
{
public:
	void productComputer()
	{
		Cpu cpu;
		cpu.productCpu();
		Ram ram;
		ram.productRam();
		Graphics graphics;
		graphics.productGraphics();
	}
};

int main()
{
	//�ͻ�ֱ�ӵ���computer����������������ľ��岿�����������̡�Ҳ��ֱ�ӵ�����������
	Computer computer;   
	computer.productComputer();

	Cpu cpu;
	cpu.productCpu();

	return 0;
}

/***********************************9�����ģʽ********************************/
/*
	���ģʽ����������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ�����ģʽʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
	��Ҫ����������������ͽṹ�������У�ģ���˼�Ԫ�غ͸���Ԫ�صĸ���ͻ�������������Ԫ��һ��������Ԫ�أ��Ӷ�ʹ�ÿͻ������븴��Ԫ�ص��ڲ��ṹ���
	��ν������֦����Ҷʵ��ͳһ�ӿڣ���֦�ڲ���ϸýӿڡ�
	�ؼ����룺��֦�ڲ���ϸýӿڣ����Һ����ڲ�����list�������Component��
	ȱ�㣺��
*/
//
class Company
{
public:
    Company(string name):m_name(name)
    {}
    virtual ~Company(){}
    virtual void add(Company* company) = 0;
    virtual void remove(string name) = 0;
    virtual void display(int depth) = 0;
    string getName()
    {
        return m_name;
    }

protected:
    string m_name;
};

//����Ĺ�˾
class ConcreteCompany:public Company   //��֦
{
public:
    ConcreteCompany(string name):Company(name)
    {}
    ~ConcreteCompany()
    {
        cout << "~ConcreteCompany()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;

private:
    list<shared_ptr<Company>> m_listCompany;

};

void ConcreteCompany::add(Company* company)
{
    shared_ptr<Company> temp(company);
    m_listCompany.push_back(temp);
}

void ConcreteCompany::remove(string name)
{
    list<shared_ptr<Company>>::iterator iter = m_listCompany.begin();
    for(; iter != m_listCompany.end(); iter++)
    {
        shared_ptr<Company> temp(*iter);
        string strName = temp.get()->getName();
        if(name == strName)
        {
            m_listCompany.erase(iter);
        }
    }
}

void ConcreteCompany::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
    list<shared_ptr<Company>>::iterator iter = m_listCompany.begin();
    for(; iter != m_listCompany.end(); iter++)
    {
        shared_ptr<Company> temp(*iter);
        temp.get()->display(depth + 2);
    }
}

//��˾�µĲ���
class FinanceDept:public Company    //��Ҷ
{
public:
    FinanceDept(string name):Company(name)
    {}
    ~FinanceDept()
    {
        cout << "~FinanceDept()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;
};

void FinanceDept::add(Company* company)
{
    cout << "FinanceDept add failed" << endl;
}

void FinanceDept::remove(string name)
{
    cout << "FinanceDept remove failed" << endl;
}

void FinanceDept::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
}

//��˾�µĲ���
class HRDept:public Company  //��Ҷ
{
public:
    HRDept(string name):Company(name)
    {}
    ~HRDept()
    {
        cout << "~HRDept()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;
};

void HRDept::add(Company* company)
{
    cout << "HRDept add failed" << endl;
}

void HRDept::remove(string name)
{
    cout << "HRDept remove failed" << endl;
}

void HRDept::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
}

int main(int argc, char *argv[])
{
    Company* root = new ConcreteCompany("zong");
    Company* f1 = new FinanceDept("F1");
    Company* h1 = new HRDept("H1");
    root->add(f1);
    root->add(h1);
    Company* c1 = new ConcreteCompany("fen1");
    Company* f2 = new FinanceDept("F2");
    Company* h2 = new HRDept("H2");
    c1->add(f2);
    c1->add(h2);
    root->add(c1);
    root->display(0);
    delete root;

    return 0;
}

/***********************************10������ģʽ********************************/
/*
	����ģʽ��Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ��ʡ�
	��Ҫ�������ֱ�ӷ��ʶ���ʱ���������⣬���磺Ҫ���ʵĶ�����Զ�̷������ϡ����������ϵͳ�У���Щ��������ĳЩԭ��ֱ�ӷ��ʻ��ʹ���߻�ϵͳ�����ܶ��鷳�������ڷ��ʴ˶���ʱ����һ���Դ˶���ķ��ʲ㡣
	��ν���������м����㡣
	�ؼ����룺ʵ���뱻��������ϡ�
	ȱ�㣺��
*/
//
class Gril
{
public:
    Gril(string name = "gril"):m_string(name){}
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

class YoungMan:public Profession
{
public:
    YoungMan(Gril gril):m_gril(gril){}
    void profess()
    {
        cout << "Young man love " << m_gril.getName().data() << endl;
    }
private:
    Gril m_gril;
};

class ManProxy:public Profession
{
public:
    ManProxy(Gril gril):m_man(new YoungMan(gril)){}
    void profess()
    {
        cout << "I am Proxy" << endl;
        m_man->profess();
    }
private:
    YoungMan* m_man;
};

int main(int argc, char *argv[])
{
    Gril gril("hei");
    Profession* proxy = new ManProxy(gril);
    proxy->profess();
    delete proxy;
    return 0;
}

/***********************************11����Ԫģʽ********************************/
/*
	��Ԫģʽ�����ù�������Ч��֧�ִ���ϸ���ȵĶ���
	��Ҫ��������д�������ʱ�������й�ͬ�Ĳ��ֳ���������������ͬ��ҵ������ֱ�ӷ����ڴ������еĶ��󣬱������´�����
	��ν������Ψһ��ʶ���жϣ�����ڴ����У��򷵻����Ψһ��ʶ������ʶ�Ķ���
	�ؼ����룺���ڲ�״̬��Ϊ��ʶ�����й���
	ȱ�㣺��
*/
//��Money�������Ϊ�ڲ���ʶ����ֵ��Ϊ�ⲿ״̬��
enum MoneyCategory   //������ڱ�ʶ����Ϊ��ʶ��
{
    Coin,
    bankNote
};

enum FaceValue      //��ֵ���ⲿ��ʶ����Ҫ�洢�Ķ���
{
    ValueOne = 1,
    ValueTwo
};

class Money      //������
{
public:
    Money(MoneyCategory cate):m_mCate(cate){}
    virtual ~Money(){ cout << "~Money() " << endl; }
    virtual void save() = 0;
private:
    MoneyCategory m_mCate;
};

class MoneyCoin:public Money    //��������1
{
public:
    MoneyCoin(MoneyCategory cate):Money(cate){}
    ~MoneyCoin(){ cout << "~MoneyCoin()" << endl; }
    void save()
    {
        cout << "Save Coin" << endl;
    }
};

class MoneyNote:public Money   //��������2
{
public:
    MoneyNote(MoneyCategory cate):Money(cate){}
    ~MoneyNote(){ cout << "~MoneyNote()" << endl; }
    void save()
    {
        cout << "Save BankNote" << endl;
    }
};

class Bank
{
public:
    Bank():m_coin(nullptr),m_note(nullptr),m_count(0){}
    ~Bank()
    {
        if(m_coin != nullptr)
        {
            delete m_coin;
            m_coin = nullptr;
        }
        if(m_note != nullptr)
        {
            delete m_note;
            m_note = nullptr;
        }
    }
    void saveMoney(MoneyCategory cate, FaceValue value)
    {
        switch(cate)    //�������Ϊ��ʶ��
        {
        case Coin:
        {
            if(m_coin == nullptr)  //�ڴ��д��ڱ�ʶ������ʶ�Ķ�����ֱ�ӵ��ã����ٴ���
            {
                m_coin = new MoneyCoin(Coin);
            }
            m_coin->save();
            m_vector.push_back(value);
            break;
        }
        case bankNote:
        {
            if(m_note == nullptr)
            {
                m_note = new MoneyNote(bankNote);
            }
            m_note->save();
            m_vector.push_back(value);
            break;
        }
        default:
            break;
        }
    }

    int sumSave()
    {
        auto iter = m_vector.begin();
        for(; iter != m_vector.end(); iter++)
        {
            m_count += *iter;
        }
        return m_count;
    }

private:
    vector<FaceValue> m_vector;
    Money* m_coin;
    Money* m_note;
    int m_count;
};

int main()
{
    Bank b1;
    b1.saveMoney(Coin, ValueOne);
    b1.saveMoney(Coin, ValueTwo);
    b1.saveMoney(Coin, ValueTwo);
    b1.saveMoney(bankNote, ValueOne);
    b1.saveMoney(bankNote, ValueTwo);
    cout << b1.sumSave() << endl;

    return 0;
}

/***********************************12���Ž�ģʽ********************************/
/*
	�Ž�ģʽ�������󲿷���ʵ�ֲ��ַ��룬ʹ���Ƕ����Զ����任��
	��Ҫ��������кܶ��п��ܻ�仯������£��ü̳л�����౬ը���⣬������չ��
	��ν�����Ѳ�ͬ�ķ�����������ʹ���Ƕ����仯����������֮�����ϡ�
	�ؼ����룺����ʵ����������������������ʵ�ࡣ
	ȱ�㣺��
*/

//������App�������ֻ�ȫ�������ֿ���ʹ����������Ž�
class App
{
public:
    virtual ~App(){ cout << "~App()" << endl; }
    virtual void run() = 0;
};

class GameApp:public App
{
public:
    void run()
    {
        cout << "GameApp Running" << endl;
    }
};

class TranslateApp:public App
{
public:
    void run()
    {
        cout << "TranslateApp Running" << endl;
    }
};

class MobilePhone
{
public:
    virtual ~MobilePhone(){ cout << "~MobilePhone()" << endl;}
    virtual void appRun(App* app) = 0;  //ʵ��App���ֻ����Ž�
};

class XiaoMi:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "XiaoMi: ";
        app->run();
    }
};

class HuaWei:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "HuaWei: ";
        app->run();
    }
};

int main()
{
    App* gameApp = new GameApp;
    App* translateApp = new TranslateApp;
    MobilePhone* mi = new XiaoMi;
    MobilePhone* hua = new HuaWei;
    mi->appRun(gameApp);
    mi->appRun(translateApp);
    hua->appRun(gameApp);
    hua->appRun(translateApp);
    delete hua;
    delete mi;
    delete gameApp;
    delete translateApp;

    return 0;
}

/***********************************13��װ��ģʽ********************************/
/*
	װ��ģʽ����̬�ظ�һ���������һЩ����Ĺ��ܣ��������ӹ�����˵��װ����ģʽ���������������
	��Ҫ�����ͨ������Ϊ����չһ���ྭ��ʹ�ü̳еķ�ʽ�����ڼ̳�Ϊ�����뾲̬����������������չ���ܵ����࣬���������͡�
	��ν����������Ĺ��ܻ��֣�ͬʱ�̳�װ�����ࡣ
	�ؼ����룺װ���ิ�Ϻͼ̳�����࣬�������չ����д����ķ�����
	ȱ�㣺��
*/

//
class Dumplings    //������   ����
{
public:
    virtual ~Dumplings(){}
    virtual void showDressing() = 0;
};

class MeatDumplings:public Dumplings    //��ʵ��  ���ڽ���
{
public:
     ~MeatDumplings(){ cout << "~MeatDumplings()" << endl; }
    void showDressing()
    {
        cout << "Add Meat" << endl;
    }
};

class DecoratorDumpling:public Dumplings    //װ����
{
public:
    DecoratorDumpling(Dumplings* d):m_dumpling(d){}
    virtual ~DecoratorDumpling(){ cout << "~DecoratorDumpling()" << endl; }
    void showDressing()
    {
        m_dumpling->showDressing();
    }
private:
    Dumplings* m_dumpling;
};

class SaltDecorator:public DecoratorDumpling   // װ����  ����
{
public:
    SaltDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~SaltDecorator(){ cout << "~SaltDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing();   //ע���
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Salt" << endl;
    }
};

class OilDecorator:public DecoratorDumpling   //װ����  ����
{
public:
    OilDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~OilDecorator(){ cout << "~OilDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing(); //ע���
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Oil" << endl;
    }
};

class CabbageDecorator:public DecoratorDumpling  //װ����   ���߲�
{
public:
    CabbageDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~CabbageDecorator(){ cout << "~CabbageDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing(); //ע���
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Cabbage" << endl;
    }
};

int main()
{
    Dumplings* d = new MeatDumplings;       //ԭʼ�������
    Dumplings* d1 = new SaltDecorator(d);   //���κ�Ľ���
    Dumplings* d2 = new OilDecorator(d1);   //���ͺ�Ľ���
    Dumplings* d3 = new CabbageDecorator(d2);  //���߲˺�Ľ���
    d3->showDressing();
    delete d;
    delete d1;
    delete d2;
    delete d3;
    return 0;
}


/***********************************14������¼ģʽ********************************/
/*
	����¼ģʽ���ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸö���֮�Ᵽ�����״̬�������Ժ�Ϳ��Խ��ö���ָ���ԭ�������״̬��
	��Ҫ�������
	��ν����ͨ��һ������¼��ר�Ŵ洢����״̬��
	�ؼ����룺����¼�ࡢ�ͻ��ࡢ����¼�����ࣻ�ͻ��಻�뱸��¼����ϣ������뱸��¼��������ϡ�
	ȱ�㣺��
*/

typedef struct  //��Ҫ�������Ϣ
{
    int grade;
    string arm;
    string corps;
}GameValue;

class Memento   //����¼��
{
public:
    Memento(){}
    Memento(GameValue value):m_gameValue(value){}
    GameValue getValue()
    {
        return m_gameValue;
    }
private:
    GameValue m_gameValue;
};

class Game     //�ͻ��� ��Ϸ
{
public:
    Game(GameValue value):m_gameValue(value)
    {}
    void addGrade()  //�ȼ�����
    {
        m_gameValue.grade++;
    }
    void replaceArm(string arm)  //��������
    {
        m_gameValue.arm = arm;
    }
    void replaceCorps(string corps)  //��������
    {
        m_gameValue.corps = corps;
    }
    Memento saveValue()    //���浱ǰ��Ϣ
    {
        Memento memento(m_gameValue);
        return memento;
    }
    void load(Memento memento) //������Ϣ
    {
        m_gameValue = memento.getValue();
    }
    void showValue()
    {
        cout << "Grade: " << m_gameValue.grade << endl;
        cout << "Arm  : " << m_gameValue.arm.data() << endl;
        cout << "Corps: " << m_gameValue.corps.data() << endl;
    }
private:
    GameValue m_gameValue;
};

class Caretake //����¼������
{
public:
    void save(Memento memento)  //������Ϣ
    {
        m_memento = memento;
    }
    Memento load()            //���ѱ������Ϣ
    {
        return m_memento;
    }
private:
    Memento m_memento;
};

int main()
{
    GameValue v1 = {0, "Ak", "3K"};
    Game game(v1);    //��ʼֵ
    game.addGrade();
    game.showValue();
    cout << "----------" << endl;
    Caretake care;
    care.save(game.saveValue());  //���浱ǰֵ
    game.addGrade();          //�޸ĵ�ǰֵ
    game.replaceArm("M16");
    game.replaceCorps("123");
    game.showValue();
    cout << "----------" << endl;
    game.load(care.load());   //�ָ���ʼֵ
    game.showValue();
    return 0;
}


/***********************************15���н���ģʽ********************************/
/*
	�н���ģʽ����һ���н��������װһϵ�еĶ��󽻻����н���ʹ��������Ҫ��ʾ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮ǰ�Ľ�����
	��Ҫ��������������֮ǰ���ڴ����Ĺ�����ϵ�������Ʊػ����ϵͳ��ø��ӣ���һ������ı䣬���ǳ�����Ҫ������֮�����Ķ��󣬲�������Ӧ�Ĵ���
	��ν��������״�ṹ����Ϊ���ͽṹ��
	�ؼ����룺����ض����ͨ�ŷ�װ��һ�����е�������
	ȱ�㣺��
*/

class Mediator;

class Person   //����ͬ����
{
public:
    virtual ~Person(){}
    virtual void setMediator(Mediator* mediator)
    {
        m_mediator = mediator;
    }
    virtual void sendMessage(const string& message) = 0;
    virtual void getMessage(const string& message) = 0;
protected:
    Mediator* m_mediator;
};

class Mediator    //�����н���
{
public:
    virtual ~Mediator(){}
    virtual void setBuyer(Person* buyer) = 0;
    virtual void setSeller(Person* seller) = 0;
    virtual void send(const string& message, Person* person) = 0;
};

class Buyer:public Person   //�����
{
public:
    void sendMessage(const string& message)
    {
        m_mediator->send(message, this);
    }
    void getMessage(const string& message)
    {
        cout << "Buyer Get: " << message.data() << endl;
    }
};

class Seller:public Person  //������
{
public:
    void sendMessage(const string& message)
    {
        m_mediator->send(message, this);
    }
    void getMessage(const string& message)
    {
        cout << "Seller Get: " << message.data() << endl;
    }
};

class HouseMediator:public Mediator  //������н���
{
public:
    HouseMediator():m_buyer(nullptr),m_seller(nullptr){}
    void setBuyer(Person* buyer)
    {
        m_buyer = buyer;
    }
    void setSeller(Person *seller)
    {
        m_seller = seller;
    }
    void send(const string& message, Person* person)
    {
        if(person == m_buyer)
        {
            m_seller->getMessage(message);
        }
        if(person == m_seller)
        {
            m_buyer->getMessage(message);
        }
    }
private:
    Person* m_buyer;
    Person* m_seller;
};

int main()
{
    Person* buyer = new Buyer;
    Person* seller = new Seller;
    Mediator* houseMediator = new HouseMediator;
    buyer->setMediator(houseMediator);
    seller->setMediator(houseMediator);
    houseMediator->setBuyer(buyer);
    houseMediator->setSeller(seller);
    buyer->sendMessage("1.5?");
    seller->sendMessage("2!!!");
    return 0;
}

/***********************************16��ְ����ģʽ********************************/
/*
	ְ����ģʽ��ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮ǰ����Ϲ�ϵ������Щ��������һ��������������������������ֱ����һ����������Ϊֹ��
	��Ҫ�����ְ�����ϵĴ����߸��������󣬿ͻ�ֻ��Ҫ�������͵�ְ�����ϼ��ɣ������������Ĵ���ϸ�ں�����Ĵ��ݣ�����ְ����������ķ����ߺ�����Ĵ����߽����ˡ�
	��ν����ְ���������඼��ʵͳһ�Ľӿڡ�
	�ؼ����룺Handler��ָ�����ϼ���handleRequest()���ж��Ƿ���ʣ��������򴫵ݸ��ϼ���
	ȱ�㣺��
*/
//
enum RequestLevel
{
    One = 1,
    Two,
    Three
};

class Leader
{
public:
    Leader(Leader* leader):m_leader(leader){}
    virtual ~Leader(){}
    virtual void handleRequest(RequestLevel level) = 0;
protected:
    Leader* m_leader;
};

class Monitor:public Leader   //����1
{
public:
    Monitor(Leader* leader):Leader(leader){}
    void handleRequest(RequestLevel level)
    {
        if(level < Two)
        {
            cout << "Mointor handle request : " << level << endl;
        }
        else
        {
            m_leader->handleRequest(level);
        }
    }
};

class Captain:public Leader    //����2
{
public:
    Captain(Leader* leader):Leader(leader){}
    void handleRequest(RequestLevel level)
    {
        if(level < Three)
        {
            cout << "Captain handle request : " << level << endl;
        }
        else
        {
            m_leader->handleRequest(level);
        }
    }
};

class General:public Leader   //����3
{
public:
    General(Leader* leader):Leader(leader){}
    void handleRequest(RequestLevel level)
    {
        cout << "General handle request : " << level << endl;
    }
};

int main()
{
    Leader* general = new General(nullptr);
    Leader* captain = new Captain(general);
    Leader* monitor = new Monitor(captain);
    monitor->handleRequest(Three);
    return 0;
}

/***********************************17���۲���ģʽ********************************/
/*
	�۲���ģʽ�����������һ��һ�Զ��������ϵ����һ�������״̬�����ı�ʱ���������������Ķ���Ҫ�õ�֪ͨ���Զ����¡�
	��Ҫ�����һ��������£���������ҲҪ���¡�
	��ν����Ŀ����֪ͨ����֪ͨ���й۲����Զ����¡�
	�ؼ����룺��Ŀ����������һ��ArrayList����Ź۲����ǡ�
	ȱ�㣺��
*/
//����ģ��ΪĿ���࣬��ͼΪ�۲����ࡣ������ģ�ͷ����ı�ʱ��֪ͨ��ͼ�����
class View;

class DataModel   //Ŀ�������   ����ģ��
{
public:
    virtual ~DataModel(){}
    virtual void add(View* view) = 0;
    virtual void remove(View* view) = 0;
    virtual void notify() = 0;   //֪ͨ����
};

class View      //�۲��߳�����   ��ͼ
{
public:
    virtual ~View(){ cout << "~View()" << endl; }
    virtual void update() = 0;
};

class IntModel:public DataModel   //�����Ŀ���࣬ ����ģ��
{
public:
    ~IntModel()
    {
        clear();
    }
    void add(View* view)
    {
        auto iter = std::find(m_list.begin(), m_list.end(), view); //�ж��Ƿ��ظ����
        if(iter == m_list.end())
        {
            m_list.push_back(view);
        }
    }
    void remove(View* view)
    {
        auto iter = m_list.begin();
        for(;iter != m_list.end(); iter++)
        {
            if(*iter == view)
            {
                delete *iter;        //�ͷ��ڴ�
                m_list.erase(iter);  //ɾ��Ԫ��
                break;
            }
        }
    }
    void notify()  //֪ͨ�۲��߸���
    {
        auto iter = m_list.begin();
        for(; iter != m_list.end(); iter++)
        {
            (*iter)->update();
        }
    }
private:
    void clear()
    {
        if(!m_list.empty())
        {
            auto iter = m_list.begin();
            for(;iter != m_list.end(); iter++)  //�ͷ��ڴ�
            {
                delete *iter;
            }
        }
    }
private:
    list<View*> m_list;
};

class TreeView:public View  //����Ĺ۲�����   ��ͼ
{
public:
    TreeView(string name):m_name(name),View(){}
    ~TreeView(){ cout << "~TreeView()" << endl; }
    void update()
    {
        cout << m_name.data() << " : Update" << endl;
    }
private:
    string m_name;
};

int main()
{
    View* v1 = new TreeView("view1");
    View* v2 = new TreeView("view2");
    View* v3 = new TreeView("view3");
    View* v4 = new TreeView("view4");
    DataModel* model = new IntModel;
    model->add(v1);
    model->add(v2);
    model->add(v3);
    model->add(v2);
    model->add(v4);
    model->notify();
    cout << "----------" << endl;
    model->remove(v2);
    model->notify();
    delete model;
    return 0;
}

