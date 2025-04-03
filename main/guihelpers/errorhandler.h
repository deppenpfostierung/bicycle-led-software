#pragma once

// 3rdparty lib includes
#include <errorhandlerinterface.h>

namespace bicycle::gui
{

struct BicycleErrorHandler : public virtual espgui::ErrorHandlerInterface
{
    void errorOccurred(std::string &&error) override;
};

} // namespace bicycle::gui