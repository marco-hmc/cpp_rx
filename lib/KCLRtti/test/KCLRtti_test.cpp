#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "KCLRttiCast.h"
#include "KCL_RTTI.h"
#include "utils.h"

#define IS_BLOOD_RELATED(obj, type) \
    (obj ? kcl_dynamic_cast<type*>(obj) : nullptr)

class Grandfather {
  public:
    KCL_RTTI_IMPL()
    virtual ~Grandfather() {}
};
KCL_RTTI_REGISTER(Grandfather)

class Father : public Grandfather {
  public:
    KCL_RTTI_IMPL()
    virtual ~Father() {}
};
KCL_RTTI_REGISTER(Father, Grandfather)

class Son : public Father {
  public:
    KCL_RTTI_IMPL()
    virtual ~Son() {}
};
KCL_RTTI_REGISTER(Son, Father)

class LaoWang {
  public:
    KCL_RTTI_IMPL()
    virtual ~LaoWang() {}
};
KCL_RTTI_REGISTER(LaoWang)

class GrandfatherA : public virtual Grandfather {
  public:
    KCL_RTTI_IMPL()
    virtual ~GrandfatherA() {}
};
KCL_RTTI_REGISTER(GrandfatherA)

class GrandfatherB : public virtual Grandfather {
  public:
    KCL_RTTI_IMPL()
    virtual ~GrandfatherB() {}
};
KCL_RTTI_REGISTER(GrandfatherB)

class MultiFather : public GrandfatherA, public GrandfatherB {
  public:
    KCL_RTTI_IMPL()
    virtual ~MultiFather() {}
};
KCL_RTTI_REGISTER(MultiFather, GrandfatherA, GrandfatherB)

class MultiSon : public MultiFather {
  public:
    KCL_RTTI_IMPL()
    virtual ~MultiSon() {}
};
KCL_RTTI_REGISTER(MultiSon, MultiFather)

TEST(KCLRttiTest, SingleInheritanceScenario) {
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

TEST(KCLRttiTest, MultipleInheritanceScenario) {
    auto multiSon = std::make_unique<MultiSon>();
    auto multiFather = std::make_unique<MultiFather>();
    auto grandfatherA = std::make_unique<GrandfatherA>();
    auto grandfatherB = std::make_unique<GrandfatherB>();

    EXPECT_TRUE(IS_BLOOD_RELATED(multiSon.get(), MultiFather));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiSon.get(), GrandfatherA));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiSon.get(), GrandfatherB));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiSon.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(multiSon.get(), LaoWang));

    EXPECT_FALSE(IS_BLOOD_RELATED(multiFather.get(), MultiSon));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiFather.get(), GrandfatherA));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiFather.get(), GrandfatherB));
    EXPECT_TRUE(IS_BLOOD_RELATED(multiFather.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(multiFather.get(), LaoWang));

    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), MultiSon));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), MultiFather));
    EXPECT_TRUE(IS_BLOOD_RELATED(grandfatherA.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherA.get(), LaoWang));

    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherB.get(), MultiSon));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherB.get(), MultiFather));
    EXPECT_TRUE(IS_BLOOD_RELATED(grandfatherB.get(), Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(grandfatherB.get(), LaoWang));
}

TEST(KCLRttiTest, NullPointerScenario) {
    Grandfather* nullPtr = nullptr;

    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, Father));
    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, Grandfather));
    EXPECT_FALSE(IS_BLOOD_RELATED(nullPtr, LaoWang));
}

TEST(KCLRttiTest, PerformanceTest) {
    const uint64_t iterations = 1000000;

    std::string timeResult =
        myUtils::measure_time([&]() { testKCLRttiCast(iterations); });

    std::cout << "KCL RTTI Performance (" << iterations
              << " iterations): " << timeResult << std::endl;

    EXPECT_TRUE(true);
}
