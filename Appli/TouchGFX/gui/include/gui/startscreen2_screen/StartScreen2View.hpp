#ifndef STARTSCREEN2VIEW_HPP
#define STARTSCREEN2VIEW_HPP

#include <gui_generated/startscreen2_screen/StartScreen2ViewBase.hpp>
#include <gui/startscreen2_screen/StartScreen2Presenter.hpp>
//#include <touchgfx/widgets/Keyboard.hpp>
//#include <gui/common/CustomKeyboard.hpp>

class StartScreen2View : public StartScreen2ViewBase
{
public:
    StartScreen2View();
    virtual ~StartScreen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void EnableKeyBoardClicked();
protected:
};

#endif // STARTSCREEN2VIEW_HPP
