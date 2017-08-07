// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料

#define _RICHEDIT_VER	0x0500

#define _CRT_SECURE_NO_WARNINGS

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <atlctrls.h>
#include <atlmisc.h>
#include<stdio.h>
#include <string>

#include "SimpleDirectUI.h"

extern SDUI::Application* _app;

#ifndef offsetof
#define offsetof(s, m) (size_t)&(((s*)0)->m)
#endif // !offsetof

