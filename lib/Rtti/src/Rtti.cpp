#include "rtti.h"

#include <cassert>
#include <cstdint>
#include <vector>

#include "common.h"

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

void testRTTI(uint64_t times = 1000000) {
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
