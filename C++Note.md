### 1、constexpr

#### 1、const与constexpr：

```c++
//使用const定义常量
const int x = 7; //
const string s = "hello"; //
const int y = sqrt(x);

//使用constexpr定义常量
constexpr int xx = x; //OK
constexpr string ss = s; //错误：string不是字面值常量类型
constexpr int yy = y;   //错误：sqrt(x)不是constexpr函数
```

以常量表达式初始化的const可以用在常量表达式中，与constexpr不同的是，const可以用非常量表达式初始化，但此时该const将不能用作常量表达式。

通常情况下，当定义简单的常量时，***constexpr比const要好***。



#### 2、字面值常量类型

```c++
struct Point
{
    int x, y, z;
    constexpr Point up(int d)
    {
        return {x, y, z + d};
    }
    constexpr Point move(int dx, int dy)
    {
        return {x + dx, y + dy};
    }
};
```

含有constexpr构造函数的类称为***字面值常量类型***。构造函数必须足够简单才能声明为constexpr，即它的函数体必须为空且所有成员都是用潜在的常量表达式初始化的。

对于成员函数来说，constexpr隐含了const的意思。所以下面这种写入是没有必须要的：

```
constexpr Point move(int dx, int dy) const
{
	return {x + dx, y + dy};
}
```

通过使用字面值类型， 我们可以令constexpr函数适应用户自定义的类型。



#### 3、constexpr 函数

在函数定义中出现constexpr时，它的含义：如果给定了常量表达式作为实参，则该函数应该能用在常量表达式中。

在对象定义中出现constexpr时，它的含义：在编译时对初始化器求值。

```C++
constexpr int fac(int n)
{
    return (n > 1) ? n * fac(n - 1) : 1;
}

void f(n)
{
    int f5 = fac(5); //可能在编译期求值
    int fn = fac(n); //在运行时求值（n是变量）
    
    constexpr int f6 = fac(6); //必须在编译期求值
    constexpr int fnn = fac(n); //错误：无法在编译期求值
    
    char a[fac(4)];  //数组的尺寸必须是常量，fac（4）是常量
    char a2[fac(n)]; //错误：数组的尺寸必须是常量，而n是变量
}
```

函数必须足够简单才能在编译期求值：

1. constexpr函数必须包含一条独立的return语句。
2. constexpr不能有循环，也不能有局部变量。
3. constexpr函数不能有副作用，constexpr函数应该是一个纯函数。

以下是一些错误的示例：

```c++
int glob;
constexpr void bad1(int a) //错误： constexpr函数不能使void
{
    glob = a;   //错误： constexpr函数有副作用
}

constexpr int bad2(int a) 
{
    if( a > 0) return a;   //错误： constexpr有if语句
    else return -a;
}

constexpr int bad3(int a)
{
    int sum = 0;   //错误： 有局部变量
    for(int i = 0; i < a; ++i) //错误： 有for循环
        sum += fac(i);
    return sum;
}
```



#### 4、constexpr与引用

constexpr函数不允许有副作用，因此我们不能向非局部对象写入内容，反过来说，只要我们不向非局部对象写入内容，就能使用它。

示例：

```c++
constexpr int ftb[]{1, 2, 3, 5,8, 13};
constexpr int fib(int n)
{
    return (n < sizeof(ftb)/sizeof(*ftb)) ? ftb[n] : ftb[sizeof(ftb)/sizeof(*ftb) - 1];
}
```

constexpr 函数可以接收引用实参，尽管它不能通过这些引用写入内容，但是const引用参数同样有用。

```c++
template<>
class complex<float>
{
public:
//...
	explicit constexpr complex(const complex<double> &);
//...
}
//
constexpr complex<float> z{2.0};
//其中逻辑上用于存储const引用实参的临时变量成了编译器内部可用的一个值
```



#### 5、条件求值

constexpr函数之外的条件表达式不会在编译期求值。

```c{{
constexpr int check(int i)
{
    return (low <= i && i < high) ? i : throw out_of_range();
}

//其中我们假设low和high值是设计时未知，而编译时已知的参数。
constexpr int low = 0;
constexpr int high = 99;

```



//补充



## 模板

#### 模板别名

可以使用using或typedef为一个类型定义别名，using语法更常用，一个重要的原因是它能用来为模板定义别名。

以std::vector为例：

```c++
/*
template<class _Ty, class _Alloc = allocator<_Ty> >
class vector
{

};
*/

using CVec = std::vector<char>; //两个参数都固定了

CVec vc = {'a', 'b', 'c'}; //vc的类型std::vector<char, allocator<char>>
```

如果绑定一个模板的所有参数，就会得到一个类型。如果只是绑定了一部分，得到的还是一个模板。

注意在别名定义中从using得到的永远是一个别名，即当使用别名时与使用原始模板是完全一样的。

```c++
template<typename T>
using Vec = vector<T, My_alloc<T>>; //Vec只是绑定了第二个参数，得到的还是一个模板

Vec<int> fib = {1, 2, 3, 4, 5}; 
```



别名和原始模板的等价性意味着：在使用别名时，如果用到了模板特例化，就会正确得到特例化版本。

```c++
template<int>
struct int_exact_traits
{
    using type = int;
};

template<>
struct int_exact_traits<8>
{
    using type = char;
};

template<>
struct int_exact_traits<16>
{
    using type = short;
};

template<int N>
using int_exact = typename int_exact_traits<N>::type; //定义简便的别名

//测试
int_exact<8> a = 8;
cout << "type: " << typeid(a).name() << endl; //type: char

int_exact<16> a = 16;
cout << "type: " << typeid(a).name() << endl; //type: short

```



#### 模板使用建议

1. 使用模板表示用于很多实参类型的算法。*23.1*

2. 使用模板表示容器。*23.2*

3. 注意template<class T>和template<typename T>含义相同。*23.2*

4. 当设计一个模板时，首先设计并调试非模板版本；随后通过添加参数将其泛化。*23.2.1*

5. 模板时类型安全的，但类型检查的时机太晚了。*23.3*

6. 当设计一个模板时，仔细思考概念（它对模板实参的要求）。*23.3*

7. 如果一个类模板必须是可以拷贝的，为它定义一个非模板拷贝构造函数和一个非模板拷贝复制运算符。*23.4.6.1*

8. 如果一个类模板必须是可以移动的，为它定义一个非模板移动构造函数和一个非模板移动复制运算符。*23.4.6.1*

9. 虚函数成员不能是模板成员函数。*23.4.6.2*

   ```c++
   class Shape
   {
       template<typename T>
       virtual bool intersect(const T&) const = 0; //错误，这段代码不合法
   };
   ```

10. 只有当一个类型依赖类模板的所有实参时才将其定义为模板成员。*23.4.6.3*

11. 使用函数模板推断类模板实参类型。*23.5.1*

12. 对多种不同实参类型。重载函数模板来获得相同的语义。*23.5.3*

13. 借助实参带入失败机制为程序提供正确的候选函数集。*23.5.3.2*

14. 使用模板别名简化符号、隐藏实现细节。*23.6*

15. C++不支持模板分别编译：在每个用到模板的编译单元中都#include模板定义。*23.7*

16. 使用普通函数作为接口编写不能使用模板处理的代码。*23.7.1*

17. 将大的模板和较严重依赖上下文的模板分开编译。*23.7*



## 泛型程序设计

#### 算法和提升

***算法***：所谓算法就是一个求解问题的过程或公式，即，通过一个有穷的计算序列生成结果。  

函数模板就是普通函数的泛化：它能对多种数据类型执行动作，并且能用以参数方式传递来的各种操作实现要执行的工作，函数模板通常也称为算法。  

***提升***：从一个（多个可能更好）具体的实例中泛化出一个算法，使之能适用于最大（但合理）范围的实参类型，即，限制一个算法(或一个类)只依赖必要的属性。

提升算法是一个由具体到抽象的过程，最重要的一点是保持性能并注意如何做才是合理的，如果试图覆盖所有可能的类型和操作，可能会把泛化推到一个不合理的程度。因此试图在缺乏具体实例的情况下直接从基本原理进行抽象，通常会使代码臃肿不堪，难以使用。

以下展示从一个具体实例提升出算法的过程：

```c++
//计算实参数组中double值的和
double add_double(double *array, int n)
{
    double sum{0};
    for(int i = 0; i < n; ++i)
    {
        sum = sum + array[i];
    }
    return sum;
}
//计算vector<int>中所有int值的和
int add_vector(const std::vector<int> &vec)
{
    int sum{0};
    for(auto iter = vec.cbegin(); iter != vec.cend(); ++iter)
    {
        sum += *iter;
    }
    return sum;
}
```

以上代码给出了两个具体的算法，现在以这两个具体的算法未起点，逐步设计出一个通用的算法。

先确定一个抽象的目标：

* 不再明确说明元素是double还是int。
* 不再明确说明是数组还是向量。

以下为第一个抽象版本：

```c++
template<typename Iter, typename Val = double>
Val sum_v1(Iter first, Iter last) noexcept
{
    Val sum = 0;
    while(first != last)
    {
        sum = sum + (*first);
        ++first;
    }
    return sum;
}

//测试
vector<int> vec = {200, 2, 3, 4};
int sum1 = sum_v1<vector<int>::iterator, int>(vec.begin(), vec.end()); //sum1 = 209

double ad[] = {100.0, 2, 3, 4};
double sum2 = sum_v1(ad, ad + 4); //sum2 = 109
```

以上抽象出了一个通用版本, 但是类型参数Val不能自动推到获得，显示的指定Val有点不友好。

下面针对Val类型参数和加、减、乘、除做进一步抽象

```c++
template<typename Iter, typename Val, typename Operator>
Val sum_v2(Iter first, Iter last, Val sum, Operator opr) noexcept
{
    while(first != last)
    {
        sum = opr(sum, *first);
        ++first;
    }
    return sum;
}
//测试
vector<int> vec = {200, 2, 3, 4};
int sum = sum_v2(vec.begin(), vec.end(), 0, std::plus<int>());

double ad[] = {100.0, 2, 3, 4};
double product = sum_v2(ad, ad + 4, 1.0, std::multiplies<double>());
```

标准库对一些常见的运算，如plus、minus、multiplies，提供了对应的函数对象，可以作为实参。

设计算法最重要的指导原则是：在从具体实例提升算法的过程中，增加的特性（符号或运行时开销）不能损害算法的使用。

以下是标准库提供的plus函数对象

```c++
template<class _Ty = void>
struct plus
{   
    // functor for operator+
    typedef _Ty first_argument_type;
    typedef _Ty second_argument_type;
    typedef _Ty result_type;

    constexpr _Ty operator()(const _Ty& _Left, const _Ty& _Right) const
    {   
        // apply operator+ to operands
        return (_Left + _Right);
    }

};

template<>
struct plus<void>
{  
    // transparent functor for operator+
    typedef int is_transparent;

    template<class _Ty1, class _Ty2>
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const 
    -> decltype(static_cast<_Ty1&&>(_Left) + static_cast<_Ty2&&>(_Right))
    { 
        // transparently apply operator+ to operands
        return (static_cast<_Ty1&&>(_Left) + static_cast<_Ty2&&>(_Right));
    }
};
```



#### 概念

***概念***：周密且严谨地说明一个算法(或一个类)对其实参的要求。





#### 泛型程序设计建议

1. 模板可传递实参类型而不丢失信息。*24.1*
2. 模板提供了一种编译时编程的通用机制。*24.1*
3. 模板提供了编译时“鸭子类型”[^鸭子类型]。*24.1*
4. 通过“提升”具体实例来设计泛型算法。*24.2*
5. 用概念说明模板实参的要求来泛化算法。*24.3*
6. 不要赋予常规符号非常规的含义。*24.3*
7. 将概念用作设计工具。*24.3*
8. 使用常用且规范的模板实参要求来追求算法与实参类型间的“插头兼容性”模板。*24.3*
9. 发现概念的方法：最小化一个算法对其模板实参的要求，然后推广至更广用途。*24.3.1*
10. 一个概念不仅是一个特定算法实现需求的描述。*24.3.1*
11. 尽量从众所周知的概念列表中选择概念。*24.3.1*和*24.4.4*
12. 模板实参的默认概念是Regular。*24.3.1*
13. 并非所有模板实参类型都满足Regular。*24.3.1*
14. 一个概念不仅是一些语法上的要求，还有语义方面的要求。*24.3.1* 、*24.3.2*、*24.4.1*
15. 用代码具体化概念。 *24.4*
16. 将概念表达为编译时谓词(constexpr函数)，并用static_assert()或enable_if<>测试它们。*24.4*
17. 将公理用作设计工具。*24.4.1*
18. 将公理作为测试的指导。*24.4.1* 
19. 某些概念涉及两个或更多模板实参。 *24.4.2*
20. 概念不仅是类型的类型。*24.4.2*
21. 概念可能涉及数值实参。*24.4.3*
22. 将概念作为测试模板定义的指导。*24.4.5*

[^鸭子类型]: 如果它走路像鸭子，叫起来也像鸭子，那么它就是一只鸭子。









































