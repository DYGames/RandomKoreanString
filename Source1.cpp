#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <locale>
#include <codecvt>
#include <vector>

const std::codecvt_mode le_bom =
static_cast<std::codecvt_mode>(std::little_endian |
	std::generate_header |
	std::consume_header);

typedef std::codecvt_utf16<wchar_t, 0x10ffff, le_bom> wcvt_utf16le_bom;

std::wostream& wendl(std::wostream& out)
{
	return out.put(L'\r').put(L'\n').flush();
}

int main()
{
	wchar_t start = 44032;
	wchar_t end = 55203;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distNum(1, 3);

	wcvt_utf16le_bom cvt(1);
	std::wofstream input;
	std::locale wloc(input.getloc(), &cvt);
	input.imbue(wloc);
	input.open("input.txt", std::ios::binary | std::ios::out);

	std::vector<std::wstring> wvector;
	std::wstring s;
	for (int i = 0; i < end - start; i++)
	{
		int n = distNum(generator);
		s.append({ static_cast<wchar_t>(start + i) });
		for (int j = 0; j < n; j++)
		{
			std::uniform_int_distribution<int> distU(start + i, (int)end);
			s.append({ static_cast<wchar_t>(distU(generator)) });
		}
		wvector.push_back(s);
		s.clear();
	}

	for (int i = 0; i < 1000; i++)
	{
		std::uniform_int_distribution<int> distRn(0, wvector.size() - 1);
		int  t = distRn(generator);
		input << wvector.at(t);
		input << wendl;
		//wvector.erase(wvector.begin() + t);
	}
	input.close();
	return 0;
}