## rtti benchmark

### 1. concepts

#### 1. 自己实现的 rtti 比 std 实现快的的 trade off 是什么？

#### 2. 自己实现 rtti 的关键是什么？

The problem with Dynamic Cast and RTTI is that it can't cross module boundaries, or different compilers. Hence why Windows COM objects all implement a QueryInterface method, which provides a consistent ABI for a task very similar to dynamic casting.

In Windows, different compilers have different ideas about how to do things. A program (main module) can load a DLL (another module) built with a completely different compiler, which has its own way of looking at the world.

For instance, new and delete operators will not match. So if one module called new, you can't use delete from the other module. Likewise, even malloc and free can't be called across module boundaries. One compiler may have a simple malloc that just redirects to Win32 HeapAlloc, but another compiler may allocate entire pages, and hand out memory from within the pages. Can't call free from a different module than was used to allocate the memory.

Even the standard libraries won't work as expected between modules. You could printf from one module, then printf from another module, and they won't share the same output buffer, so they could flush in any order and unexpectedly print some old text .

Dynamic Cast and RTTI require compiler support, and get different implementations based on which compiler you are using. So if you pass a pointer from one module to another, you can't necessarily guarantee that dynamic cast or RTTI will work correctly.

https://kahncode.com/2019/09/24/c-tricks-fast-rtti-and-dynamic-cast/

https://github.com/elohim-meth/rtti