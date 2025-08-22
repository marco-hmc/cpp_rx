#include <cassert>
#include <cstdint>
#include <vector>

#include "KCL_RTTI.h"
#include "common.h"

#define IS_BLOOD_RELATED(obj, type) (kcl_dynamic_cast<type*>(obj))

class Grandfather {
  public:
    KCL_RTTI_IMPL()
    virtual ~Grandfather() = default;
};
KCL_RTTI_REGISTER(Grandfather)

class Father : public Grandfather {
  public:
    KCL_RTTI_IMPL()
    ~Father() override = default;
};
KCL_RTTI_REGISTER(Father, Grandfather)

class Son : public Father {
  public:
    KCL_RTTI_IMPL()
    ~Son() override = default;
};
KCL_RTTI_REGISTER(Son, Father)

class LaoWang {
  public:
    KCL_RTTI_IMPL()
    virtual ~LaoWang() = default;
};

KCL_RTTI_REGISTER(LaoWang)

void testKCLRttiCast(uint64_t times = 1000000) {
    std::vector<Grandfather*> objects;
    objects.reserve(times);
    for (int i = 0; i < times; ++i) {
        objects.push_back(new Son());
    }

    for (int i = 0; i < times; ++i) {
        assert(IS_BLOOD_RELATED(objects[i], Father));
        assert(IS_BLOOD_RELATED(objects[i], Grandfather));
        assert(!IS_BLOOD_RELATED(objects[i], LaoWang));
    }

    for (auto* obj : objects) {
        delete obj;
    }
}