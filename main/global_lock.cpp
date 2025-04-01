#include "global_lock.h"

namespace bicycle::global {

cpputils::DelayedConstruction<espcpputils::recursive_mutex_semaphore> global_lock;

} // namespace bicycle::global