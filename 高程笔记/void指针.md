# **<mark>void*</mark>**
---
![alt text](image-2.png)
---

## 1. 什么是 `void *`

* `void *` 叫做 **通用指针（generic pointer）**。
* 它表示“指向某种未知类型的内存地址”。
* 在 C/C++ 里，**任何类型的指针都能隐式转换成 `void*`**，但反过来要显式转换回来。

举例：

```cpp
int a = 10;
double b = 3.14;

void* p1 = &a;  // int* → void*
void* p2 = &b;  // double* → void*
```

<mark>此时 `p1`、`p2` 只是存了地址，但不知道地址里的数据类型。


---

## 2. 为什么需要 `void *`

因为它能用来表示 **<mark>任意数据的地址**，常见用途：

### (1) 通用函数参数

标准库里的 `malloc` 就是返回 `void*`：

```cpp
void* p = malloc(100); // 分配100字节
```

原因：malloc 不知道你要存 `int` 还是 `double`，所以返回 `void*`，用户自己决定怎么用。

### (2) 需要传递不同类型指针的地方

比如 C 语言的 `qsort` 比较函数参数：

```c
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
```

---

## 3. 使用 `void *` 的注意点

* **<mark>不能直接解引用**

  ```cpp
  void* p;
  *p = 10; // ❌ 错误：不知道类型，没法解引用
  ```

* 必须 **<mark>强制类型转换** 回去

  ```cpp
  int a = 10;
  void* p = &a;
  int* pa = (int*)p; // 转回 int*
  cout << *pa << endl; // 输出 10
  ```

* 在 C++ 里，通常更推荐用 **模板 (template)** 或 **`std::any` / `std::variant`** 来实现类型无关，而不是 `void*`。

---

## 4. 举个完整例子

```cpp
#include <iostream>
using namespace std;

void print(void* data, char type) {
    if (type == 'i') cout << *(int*)data << endl;
    else if (type == 'd') cout << *(double*)data << endl;
}

int main() {
    int a = 42;
    double b = 3.14;

    print(&a, 'i');  // 输出 42
    print(&b, 'd');  // 输出 3.14
}
```

---

✅ **<mark>总结**

* `void*` 是 **万能指针**，能存储任何类型变量的地址。
* 不能直接操作数据，必须强制转换回来。
* 在 C 中用得多（`malloc`, `qsort`），在 C++ 中一般用模板和泛型来替代。

---
![alt text](image-1.png)