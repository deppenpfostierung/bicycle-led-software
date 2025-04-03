#include "sdkconfig.h"

#include "configutils_bicycle.h"
#define CONFIGWRAPPER_TOSTRING_USINGS using ::toString;
#include <configwrapper_priv.h>

// local includes
#include "enums.h"

INSTANTIATE_CONFIGWRAPPER_TEMPLATES(ButtonAction)
