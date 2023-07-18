# fdLib

提供一个DLL供调用，主要解决在一个进程中的内存指针的传递和使用。

## fdLib项目

fdLib可以export一个或多个API接口，代码可以加载这个DLL，并调用API接口来传递内存指针。

如下的例子，

```
extern "C" __declspec(dllexport) int func1(DWORD param1) {
	return 42;
}
```

演示了一个名为func1的API会导出，这个API有一个DWORD类型的输入参数，这个API的返回一个int，42.


## testlib项目

testlib是一个测试exe项目，目的是演示如何加载fdLib.dll和获得API接口，并调用API接口。

如下的例子，

```
    HINSTANCE hDLL = LoadLibrary(L"fdLib.dll");
    if (hDLL != NULL)
    {
        func1 p = (func1)GetProcAddress(hDLL, "func1");
        if (p != NULL) {
            std::cout << "Load DLL successfully, and func1 return " << p(1) << std::endl;
        }
    }
```

演示了加载fdLib.dll和获得名字为func1的API，并且进行调用，获得返回值。


## 集成

在BZ的代码内，可以加载fdLib.dll，等到需要保存图片的时候，可以调用API接口，将图片传递给DLL。DLL可以将图片保存在硬盘上。


