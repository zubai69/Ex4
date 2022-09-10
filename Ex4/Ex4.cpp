#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <clocale>

WCHAR szTitle[] = L"Sin";
WCHAR szWindowClass[] = L"SinWndClass";

const int WND_X = 300;
const int WND_Y = 0;
const int WND_W = 733;
const int WND_H = 720;

ATOM MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Draw(HDC hdc);

DWORD WINAPI Run(LPVOID lpThreadParameter)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND hCon = GetConsoleWindow();
	RECT rc;

	MyRegisterClass(hInstance);
	GetWindowRect(hCon, &rc);  

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_BORDER, rc.left + WND_X, rc.top + WND_Y, WND_W, WND_H, hCon,
		nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	_getch();

	return 0;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		Draw(hdc);
		EndPaint(hWnd, &ps);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI Draw(HDC hdc) {

	float x, y, x0, y0;
	float h = M_PI / 180;
	SelectObject(hdc, GetStockObject(WHITE_PEN));
	MoveToEx(hdc, 0, 360, NULL);
	LineTo(hdc, 1000, 360);
	MoveToEx(hdc, 360, 0, NULL);
	LineTo(hdc, 360, 1000);
	for (x = 0.0f; x <= 720.0f; x += 0.01f)
	{
		MoveToEx(hdc, x, -100*sin(x*h)+360, NULL);
		LineTo(hdc, x, -100*sin(x*h)+361);
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sinus() {
	DWORD dwStream = 1;
	HANDLE drawStream;
	drawStream = CreateThread(NULL, 0, Run, &dwStream, 0, &dwStream);
	_getch();
}

void file() {
	std::ofstream f1;
	std::ifstream f2;
	f1.open("zubai.txt");
	int i = 0;
	int m;
	std::cout << "Введите 10 чисел:" << std::endl;
	while (i < 10) {
		std::cin >> m;
		f1 << m << "\n";
		i++;
	}
	f1.close();
	f2.open("zubai.txt");
	std::string str;
	int sum = 0;
	while (std::getline(f2, str)) {
		sum += atoi(str.c_str());
	}
	std::cout << "Сумма: " << sum << std::endl;
	f2.close();
}

int main() {
	setlocale(LC_ALL, "");
	sinus();
	return 0;
}