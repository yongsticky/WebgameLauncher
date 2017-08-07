#pragma once

#include <vector>
using namespace std;

#include "Application.h"

#include "WindowMessageDispatcher.h"
#include "LayoutControl.h"
#include "ImageControl.h"
#include "ButtonControl.h"
#include "TextControl.h"
#include "WebBrowserControl.h"
#include "EditControl.h"

#include "Win32TrayIcon.h"
#include "Win32ContextMenu.h"
#include "Win32MenuItem.h"

#include "FrameHostWindow.h"
#include "PopupHostDialog.h"
#include "Win32ComponentHostWindow.h"

#include "XmlAttribute.h"
#include "BitmapLoader.h"
#include "LayoutLoader.h"

#include "QuitApplicationAction.h"
#include "ShellOpenUrlAction.h"
#include "ShowWindowAction.h"
#include "ShowControlAction.h"
#include "ShowComponentAction.h"
#include "WBNavigateAction.h"
#include "WBCommandAction.h"
#include "ConditionAction.h"
#include "SendMessageAction.h"
#include "CreateTimerAction.h"
#include "KillTimerAction.h"



bool SimpleDirectUI_Init(HINSTANCE hInstance, SDUI::Application** ppApp);
void SimpleDirectUI_Uninit();