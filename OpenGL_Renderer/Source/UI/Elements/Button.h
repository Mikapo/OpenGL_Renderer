#pragma once

#include "UI_element_notify.h"

class Button : public UI_element_notify<>
{
public:
    Button(const std::string& name)
        : UI_element_notify(name)
    {
    }

    void render() override;
    void check_for_events() override;

private:

    bool m_clicked = false;
    bool m_last_checked_status = false;
};
