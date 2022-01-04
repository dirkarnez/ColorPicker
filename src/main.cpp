#include <SFML/Graphics.hpp>
#include <windows.h>
#include <sstream>
#include <string>
#include <iostream>
#include <wchar.h>

void Clipboard(HWND hwnd, const wchar_t *Data);

int main()
{
	wchar_t colorstr[50];

	POINT p;
	HDC hDC;
	BOOL b;
	hDC = GetDC(NULL);
	if (hDC == NULL)
		return CLR_INVALID;
	sf::RenderWindow window(sf::VideoMode(300, 300), "Color Picker", sf::Style::Titlebar | sf::Style::Close);
	sf::Color mycolor;

	while (window.isOpen())
	{
		sf::Event event;
		b = GetCursorPos(&p);
		if (!b)
			return CLR_INVALID;

		COLORREF color = GetPixel(hDC, p.x, p.y);
		mycolor.r = GetRValue(color);
		mycolor.g = GetGValue(color);
		mycolor.b = GetBValue(color);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		sf::Text text;

		sf::Font font;
		font.loadFromFile("C:\\WINDOWS\\fonts\\arial.ttf");
		text.setFont(font);
		text.setString("Press:\nLeft Arrow to copy hexadecimal RGB value\nRight Arrow to copy decimal RGB value");
		text.setCharacterSize(15);
		text.setFillColor(sf::Color::Red);
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(300, 240));
		rectangle.setFillColor(mycolor);
		rectangle.setPosition(0, 60);
		window.draw(rectangle);
		window.draw(text);
		window.display();
		HWND hwnd = GetDesktopWindow();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			wsprintfW(colorstr, L"#%02lX%02lX%02lX", mycolor.r, mycolor.g, mycolor.b);
			Clipboard(hwnd, colorstr);
			MessageBoxW(NULL, colorstr, L"Copied Hex RGB", MB_OK | MB_ICONINFORMATION);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			wsprintfW(colorstr, L"%03d, %03d, %03d", mycolor.r, mycolor.g, mycolor.b);
			Clipboard(hwnd, colorstr);
			MessageBoxW(NULL, colorstr, L"Copied Dec RGB", MB_OK | MB_ICONINFORMATION);
		}
		Sleep(10);
	}
	return 0;
}

void Clipboard(HWND hwnd, const wchar_t *Data)
{
	OpenClipboard(hwnd);
	EmptyClipboard();
	int BufferSize = (wcslen(Data) + 1) * sizeof(wchar_t);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, BufferSize);
	if (!hData) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hData), Data, BufferSize);
	GlobalUnlock(hData);
	SetClipboardData(CF_UNICODETEXT, (HANDLE)hData);
	CloseClipboard();
	GlobalFree(hData);
}