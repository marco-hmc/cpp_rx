## RTTI Benchmark

用于比较 `std::dynamic_cast` 与自定义 RTTI 实现性能的 C++ 基准测试项目。

### 1. 自定义 RTTI 能比 std::dynamic_cast 更快的原因与权衡

#### 1.1 性能优势

- **类型检查更快**：自定义 RTTI 通常通过整数或指针直接比较类型 ID，避免了标准 RTTI 复杂的类型层次遍历。
- **编译期优化**：类型信息和 ID 可在编译期生成，运行时只需简单判断。
- **缓存友好**：结构更简单，减少多余的内存访问，提高缓存命中率。
- **无虚表查找**：避免标准 RTTI 的虚表查找和复杂的继承关系解析。

#### 1.2 Trade-off（权衡）

- **类型安全性降低**：失去编译器的类型安全检查，易出错。
- **可移植性差**：类型 ID 不能跨动态库或编译器，模块间类型不一致。
- **维护复杂度高**：需要手动注册类型、分配 ID，代码易出错。
- **标准兼容性问题**：不遵循 C++ 标准，可能与第三方库冲突。
- **调试困难**：类型错误不易追踪，调试成本高。
- **多重/虚继承支持有限**：复杂继承场景下自定义 RTTI 可能失效。

### 2. 自定义 RTTI 的核心实现要点

#### 2.1 类型唯一标识（Type ID）

为每个类型分配唯一的类型 ID，通常用静态成员变量实现：

```cpp
template<typename T>
struct TypeID {
    static const int value;
};
```

#### 2.2 类型注册与基类信息

每个类型在定义时注册自己的类型 ID，并记录其基类类型 ID：

```cpp
class RTTIBase {
protected:
    int type_id_;
public:
    virtual int getTypeID() const = 0;
};
```

#### 2.3 快速类型转换接口

通过类型 ID 判断是否可以安全转换，避免标准 RTTI 的层次遍历：

```cpp
template<typename To, typename From>
To* fast_cast(From* obj) {
    return (obj && obj->getTypeID() == TypeID<To>::value)
           ? static_cast<To*>(obj) : nullptr;
}
```

#### 2.4 多继承支持（可选）

如需支持多继承，可在类型注册时记录所有基类的类型 ID，并在转换时遍历所有基类 ID。

### 3. 限制与最佳实践

- **跨模块/动态库问题**：类型 ID 仅在同一编译单元有效。
- **复杂继承场景需谨慎**：多重继承、虚继承需额外处理。
- **仅在性能关键路径使用**：普通场景建议用标准 RTTI。
- **保持类型层次结构简单**：减少维护成本。
- **充分测试类型转换正确性**。

### 4. 结论

```
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_testDynamicCast/1000000       86.0 ms         86.0 ms            9
BM_testDynamicCast/10000        0.769 ms        0.769 ms          895
BM_testRTTI/1000000              1348 ms         1348 ms            1
BM_testRTTI/10000                11.8 ms         11.8 ms           57
BM_testKCLRttiCast/1000000       84.2 ms         84.2 ms            9
BM_testKCLRttiCast/10000        0.751 ms        0.751 ms          927
```

在本文的测试中，自定义 RTTI 实现（KCLRttiCast）仅仅轻微优于 `std::dynamic_cast`，另一个自定义实现（RTTI）性能较差。我认为std::dynamic_cast实现已经非常优化，且现代编译器对其进行了大量优化，因此自定义 RTTI 的优势并不明显。

而自定义 RTTI 带来的类型安全性降低、维护复杂度增加等问题，使得在大多数情况下，除非在极端性能要求的场景下，否则不建议使用自定义 RTTI。