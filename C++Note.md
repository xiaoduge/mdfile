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













