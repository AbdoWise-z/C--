
#include "common.h"

namespace Cmm {
    ValueObject ValueObject::Void() {
        return {
            V_Void,
            nullptr
        };
    }
}
