// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

#define _RICHEDIT_VER	0x0500

#define _CRT_SECURE_NO_WARNINGS


#include <atlbase.h>
#include <atlwin.h>

#include<stdio.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef offsetof
#define offsetof(s, m) (size_t)&(((s*)0)->m)
#endif // !offsetof