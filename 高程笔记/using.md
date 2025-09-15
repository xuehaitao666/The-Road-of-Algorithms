# <mark>using的作用

## 1. **命名空间引入**  
最常见的就是我们写代码时用的：  

```cpp
#include <iostream>
using namespace std;  // 引入整个命名空间
```

这样就不用写 `std::cout`，可以直接写 `cout`。  
但是⚠️缺点是可能引起命名冲突，所以更推荐写：  

```cpp
using std::cout;
using std::cin;
```

这样只引入需要的名字。

---

## 2. **类型别名**  
`using` 可以给类型起别名，等价于 `typedef`，但更直观：  

```cpp
typedef unsigned int uint1;  // 旧写法
using uint2 = unsigned int;  // 新写法（推荐）
```

还可以给模板起别名，非常强大：  

```cpp
template <typename T>
using vec = std::vector<T>;

vec<int> v; // 相当于 std::vector<int>
```

---

## 3. **继承中的 using 声明**  
当子类继承父类时，`using` 可以：  

### (1) 引入父类的成员函数  
```cpp
struct Base {
    void show(int) {}
};

struct Derived : Base {
    using Base::show; // 引入父类的 show
    void show(double) {}
};
```
**<mark>代码解析见本md结尾</mark>**

### (2) 改变访问权限  
```cpp
class Base {
protected:
    int value;
};

class Derived : public Base {
public:
    using Base::value; // 把 protected 改成 public
};
```

---

## 4. **别名模板（C++11+）**  
比 typedef 更灵活：  

```cpp
template <typename T>
using Map = std::map<T, int>;

Map<string> m;  // 等价于 std::map<string, int>
```

---

## 5. **函数重载控制**（少见但有用）  
有时候引入某个重载函数，让它和当前作用域的函数一起参与重载决议。  

---

✅ **总结**：  
`using` 在 C++ 里主要有四大用途：  
1. 引入命名空间里的名字（最常见）。  
2. 定义类型别名（比 typedef 更强大）。  
3. 在继承中引入父类成员函数或改变访问权限。  
4. 定义别名模板。  


## 代码解析

### 代码

```cpp
struct Base {
    void show(int) {}
};

struct Derived : Base {
    using Base::show; // 引入父类的 show
    void show(double) {}
};
```

---

### 1. `Base` 结构体

```cpp
struct Base {
    void show(int) {}
};
```

`Base` 有一个成员函数：

* `show(int)` —— 接受一个 `int` 参数。

---

### 2. `Derived` 继承自 `Base`

```cpp
struct Derived : Base {
    using Base::show; // 引入父类的 show
    void show(double) {}
};
```

* `Derived` 继承了 `Base`。
* 在 `Derived` 里我们又定义了一个新的函数：

  ```cpp
  void show(double) {}
  ```

  这是一个不同参数类型的重载。

⚠️ **重点问题**：如果没有 `using Base::show;`，那么 `Derived` 里的 `show(double)` 会 **隐藏（遮蔽）** `Base` 的 `show(int)`，导致 `Derived` 只能调用 `show(double)`。

---

### 3. `using Base::show`

`using Base::show;` 的作用是：

* 把 `Base` 里的所有 `show` 函数“搬”到 `Derived` 的作用域中。
* 这样 `Derived` 里就同时有：

  * `void show(int)`（来自 `Base`）
  * `void show(double)`（自己定义的）

于是 `Derived` 的对象可以调用这两个版本的函数。

---

### 4. 使用示例

```cpp
int main() {
    Derived d;
    d.show(10);     // 调用 Base::show(int)
    d.show(3.14);   // 调用 Derived::show(double)
}
```

如果把 `using Base::show;` 去掉：

```cpp
int main() {
    Derived d;
    d.show(10);     // ❌ 错误，show(int) 被 Derived::show(double) 隐藏了
}
```

---

✅ **总结**：
这段代码的关键点是 **`using Base::show;`**，它解决了 **子类新定义的函数会隐藏父类同名函数** 的问题，让子类同时拥有父类的函数重载版本。


