#include "ShimCacheParser.h"
#include "ShimQuery.h"
#include <fstream>
#include <locale>
#include <algorithm>

bool compare_date(const pair<wstring, wstring> a, const pair<wstring, wstring> b)
{
    if (a.first == L"N/A" || b.first == L"N/A")
    {
        return (a.first > b.first);
    }
    else
    {
        return (a.first < b.first);
    }
}

int main()
{
    std::string buf = "";
    query_shimcache(buf);
    if (buf != "")
    {
        vector<pair<wstring, wstring>> result;
        auto parser = ShimCacheParser();
        parser.parse(buf, result);
        auto fs = std::wofstream(L"shimcache_parse_result.txt", std::wofstream::out | std::wofstream::binary);
        if (!fs.fail())
        {
            fs.imbue(locale("", locale::all ^ locale::numeric));
            vector<pair<wstring, wstring>>::iterator it = result.begin();
            if (result.size() > 0)
            {
                std::stable_sort(result.begin(), result.end(), compare_date);
            }
            wstring data;
            for (; it != result.end(); ++it)
            {
                if (it->first != L"N/A")
                {
                    data = it->first + L" " + it->second + L"\n";
                }
                else
                {
                    data = it->first + L"                 " + it->second + L"\n";
                }
                fs.write(data.c_str(), data.size());
            }
        }
        fs.close();
    }
    return 0;
}