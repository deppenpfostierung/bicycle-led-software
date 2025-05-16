#pragma once

// 3rdparty lib includes
#include <iconinterface.h>

// local includes
#include "icons/radio_checked.h"
#include "icons/radio_checked_grey.h"
#include "icons/radio_unchecked.h"
#include "icons/radio_unchecked_grey.h"

template <typename TValue, typename TParent>
class ChangeValueDisplayRadioIcon : public virtual espgui::MenuItemIconInterface
{
public:
    explicit ChangeValueDisplayRadioIcon(const TValue value, TParent *parent)
        : m_value { value }
        , m_parent { parent }
    {
    }

    const espgui::Icon<24, 24> *icon(const bool selected) const override
    {
        if (m_value == m_parent->getValue())
        {
            return selected ? &icons::radio_checked_grey : &icons::radio_checked;
        }

        return selected ? &icons::radio_unchecked_grey : &icons::radio_unchecked;
    }

private:
    TValue m_value;
    TParent *m_parent;
};