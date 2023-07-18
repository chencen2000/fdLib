# fdLib

提供一个DLL供调用，主要解决在一个进程中的内存指针的传递和使用。

## fdLib项目

fdLib可以export一个或多个API接口，BZ进程中的代码可以加载这个DLL，并调用API接口来传递内存指针。

## testlib项目

testlib是一个测试exe项目，目的是演示如何加载fdLib.dll和获得API接口，并调用API接口。

## 集成

在BZ的代码内，可以加载fdLib.dll，等到需要保存图片的时候，可以调用API接口，将图片传递给DLL。DLL可以将图片保存在硬盘上。


