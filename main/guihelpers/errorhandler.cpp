#include "errorhandler.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "popupscreen.h"

namespace bicycle::gui
{
void BicycleErrorHandler::errorOccurred(std::string &&error)
{
    espgui::changeScreenCallback = [error_ = std::move(error)](espgui::TftInterface &tft) {
        auto newDisplay =
            std::make_unique<BicyclePopupDisplay>(std::string { error_ }, std::move(espgui::currentDisplay));
        newDisplay->initOverlay(tft);
        espgui::currentDisplay = std::move(newDisplay);
    };
}
} // namespace bicycle::gui