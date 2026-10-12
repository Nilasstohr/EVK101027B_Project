#include <gui/startscreen2_screen/StartScreen2View.hpp>

StartScreen2View::StartScreen2View()
{

}

void StartScreen2View::setupScreen()
{
    StartScreen2ViewBase::setupScreen();
}

void StartScreen2View::tearDownScreen()
{
    StartScreen2ViewBase::tearDownScreen();
}

void StartScreen2View::EnableKeyBoardClicked()
{
	presenter->transmitCDCData("EnableKeyBoardClicked");

}

void StartScreen2View::setReceivedUSBData(const char* data)
{
    Unicode::strncpy(textAreaUSBReceiveBuffer, data, TEXTAREAUSBRECEIVE_SIZE);
    textAreaUSBReceive.setWildcard(textAreaUSBReceiveBuffer);
    textAreaUSBReceive.resizeToCurrentText();
    textAreaUSBReceive.invalidate();
}
