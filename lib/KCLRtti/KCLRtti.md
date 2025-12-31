# KCLRtti 库设计说明

## 设计目标

- 提供高性能的类型识别和转换机制，替代 `std::dynamic_cast`
- 支持多态类型安全转换
- 适用于性能敏感场景

## 核心设计

1. **类型唯一标识（TypeID）**

   - 每个类型分配唯一的类型 ID
   - 类型 ID 用于快速判断类型关系

2. **类型注册机制**

   - 类型在程序启动时自动注册
   - 支持记录基类信息，实现继承关系判断

3. **转换接口**

   - 提供 `kcl_dynamic_cast<T>()` 方法，内部通过类型 ID 判断是否可转换
   - 转换效率远高于标准 RTTI

4. **多继承支持**
   - 可记录多个基类类型 ID，支持多重继承场景

## 性能与权衡

- **优势**：类型判断快，运行时开销低，适合高频转换场景
- **劣势**：类型安全性略低，跨模块/动态库类型 ID 不一致，复杂继承需额外处理

## 典型用法

```cpp
class Base {
    KCL_RTTI_IMPL()
    virtual ~Base() {}
};
KCL_RTTI_REGISTER(Base)

class Derived : public Base {
    KCL_RTTI_IMPL()
    virtual ~Derived() {}
};
KCL_RTTI_REGISTER(Derived, Base)

Base* obj = new Derived();
Derived* d = kcl_dynamic_cast<Derived*>(obj);
```

## 最佳实践

- 仅在性能关键路径使用
- 保持类型层次结构简单
- 充分测试类型转换正确性
