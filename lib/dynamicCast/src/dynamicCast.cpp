#include <cassert>
#include <cstdint>
#include <vector>

namespace {
    class Grandfather {
      public:
        virtual ~Grandfather(){};

        template <typename T>
        bool isDerivedFrom(T* obj) {
            return dynamic_cast<Grandfather*>(obj) != nullptr;
        }
    };

    class Father : public Grandfather {};
    class Son : public Father {};
    class LaoWang {
      public:
        virtual ~LaoWang() {}
    };

}  // namespace

#define IS_BLOOD_RELATED(obj, type) (dynamic_cast<type*>(obj))

void testDynamicCast(uint64_t times = 1000000) {
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