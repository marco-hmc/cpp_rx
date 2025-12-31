#include "rtti.h"

#include <cassert>
#include <cstdint>
#include <vector>

namespace {
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

}  // namespace

#define IS_BLOOD_RELATED(obj, type) ((obj)->cast<type>())

void testRTTI(uint64_t times) {
    std::vector<Grandfather*> objects;
    objects.reserve(times);

    for (uint64_t i = 0; i < times; ++i) {
        objects.push_back(new Son());
    }

    for (uint64_t i = 0; i < times; ++i) {
        auto* obj = objects[i];
        assert(IS_BLOOD_RELATED(obj, Father));
        assert(IS_BLOOD_RELATED(obj, Grandfather));
        assert(!IS_BLOOD_RELATED(obj, LaoWang));
    }

    for (auto* obj : objects) {
        delete obj;
    }
}
