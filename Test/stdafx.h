// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

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

