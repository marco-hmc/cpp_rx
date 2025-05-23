#include "rtti.h"

#include <gtest/gtest.h>

#include <memory>

#define IS_BLOOD_RELATED(obj, type) ((obj)->cast<type>())

class Grandfather : public RTTI::Enable {
    RTTI_DECLARE_TYPEINFO(Grandfather);
};

class Father : public Grandfather {
    RTTI_DECLARE_TYPEINFO(Father, Grandfather);
};

class Son : public Father {
    RTTI_DECLARE_TYPEINFO(Son, Father);
};

class LaoWang : public RTTI::Enable {
    RTTI_DECLARE_TYPEINFO(LaoWang);
};

class GrandfatherA : public virtual RTTI::Enable {
    RTTI_DECLARE_TYPEINFO(GrandfatherA);
};

class GrandfatherB : public virtual RTTI::Enable {
    RTTI_DECLARE_TYPEINFO(GrandfatherB);
};

class MultiFather : public GrandfatherA, public GrandfatherB {
    RTTI_DECLARE_TYPEINFO(MultiFather, GrandfatherA, GrandfatherB);
};

class MultiSon : public MultiFather {
    RTTI_DECLARE_TYPEINFO(MultiSon, MultiFather);
};

TEST(RttiTest, SingleInheritanceScenario) {
    auto son = std::make_unique<Son>();
    auto father = std::make_unique<Father>();
    auto grandfather = std::make_unique<Grandfather>();
    auto laowang = std::make_unique<LaoWang>();

    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), Father));
    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(son.get(), LaoWang));
    EXPECT_FALSE(IS_BLOOD_RELATED(father.get(), Son));
    EXPECT_TRUE(IS_BLOOD_RELATED(father.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(father.get(), LaoWang));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfather.get(), Son));
}

TEST(RttiTest, MultiInheritanceScenario) {
    auto son = std::make_unique<MultiSon>();
    auto father = std::make_unique<MultiFather>();
    auto grandfatherA = std::make_unique<GrandfatherA>();
    auto grandfatherB = std::make_unique<GrandfatherB>();
    auto laowang = std::make_unique<LaoWang>();

    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), MultiFather));
    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), GrandfatherA));
    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), GrandfatherB));
    EXPECT_FALSE(IS_BLOOD_RELATED(son.get(), LaoWang));
    EXPECT_FALSE(IS_BLOOD_RELATED(father.get(), MultiSon));
    EXPECT_TRUE(IS_BLOOD_RELATED(father.get(), GrandfatherA));
    EXPECT_TRUE(IS_BLOOD_RELATED(father.get(), GrandfatherB));
    EXPECT_FALSE(IS_BLOOD_RELATED(father.get(), LaoWang));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), MultiSon));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), MultiFather));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), LaoWang));
}

TEST(RttiTest, NullPointerScenario) {
    Grandfather* nullPtr = nullptr;

    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, Father));
    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, LaoWang));
}

TEST(RttiTest, NonRttiTypeScenario) {
    struct NonRttiType {};

    NonRttiType nonRttiObj;
    auto* grandfather = reinterpret_cast<Grandfather*>(&nonRttiObj);

    // 非 RTTI 类型的对象，cast 应该返回 nullptr
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfather, Father));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfather, Grandfather));
}

TEST(RttiTest, DeepInheritanceScenario) {
    class GreatGrandfather : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(GreatGrandfather);
    };

    class Grandfather : public GreatGrandfather {
        RTTI_DECLARE_TYPEINFO(Grandfather, GreatGrandfather);
    };

    class Father : public Grandfather {
        RTTI_DECLARE_TYPEINFO(Father, Grandfather);
    };

    class Son : public Father {
        RTTI_DECLARE_TYPEINFO(Son, Father);
    };

    auto son = std::make_unique<Son>();
    auto father = std::make_unique<Father>();
    auto grandfather = std::make_unique<Grandfather>();
    auto greatGrandfather = std::make_unique<GreatGrandfather>();

    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), Father));
    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), Grandfather));
    EXPECT_TRUE(IS_BLOOD_RELATED(son.get(), GreatGrandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(son.get(), LaoWang));

    EXPECT_FALSE(IS_BLOOD_RELATED(father.get(), Son));
    EXPECT_TRUE(IS_BLOOD_RELATED(father.get(), Grandfather));
    EXPECT_TRUE(IS_BLOOD_RELATED(father.get(), GreatGrandfather));

    EXPECT_FALSE(IS_BLOOD_RELATED(grandfather.get(), Son));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfather.get(), Father));
    EXPECT_TRUE(IS_BLOOD_RELATED(grandfather.get(), GreatGrandfather));
}

TEST(RttiTest, CrossInheritanceScenario) {
    class InterfaceA : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(InterfaceA);
    };

    class InterfaceB : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(InterfaceB);
    };

    class CrossDerived : public InterfaceA, public InterfaceB {
        RTTI_DECLARE_TYPEINFO(CrossDerived, InterfaceA, InterfaceB);
    };

    auto crossDerived = std::make_unique<CrossDerived>();
    auto* interfaceA = static_cast<InterfaceA*>(crossDerived.get());
    auto* interfaceB = static_cast<InterfaceB*>(crossDerived.get());

    EXPECT_TRUE(IS_BLOOD_RELATED(interfaceA, CrossDerived));
    EXPECT_TRUE(IS_BLOOD_RELATED(interfaceB, CrossDerived));
    EXPECT_FALSE(IS_BLOOD_RELATED(interfaceA, InterfaceB));
    EXPECT_FALSE(IS_BLOOD_RELATED(interfaceB, InterfaceA));
}

TEST(RttiTest, PolymorphicScenario) {
    class Base : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(Base);
    };

    class DerivedA : public Base {
        RTTI_DECLARE_TYPEINFO(DerivedA, Base);
    };

    class DerivedB : public Base {
        RTTI_DECLARE_TYPEINFO(DerivedB, Base);
    };

    auto derivedA = std::make_unique<DerivedA>();
    auto derivedB = std::make_unique<DerivedB>();
    auto* baseA = static_cast<Base*>(derivedA.get());
    auto* baseB = static_cast<Base*>(derivedB.get());

    EXPECT_TRUE(IS_BLOOD_RELATED(baseA, DerivedA));
    EXPECT_FALSE(IS_BLOOD_RELATED(baseA, DerivedB));
    EXPECT_TRUE(IS_BLOOD_RELATED(baseB, DerivedB));
    EXPECT_FALSE(IS_BLOOD_RELATED(baseB, DerivedA));
}