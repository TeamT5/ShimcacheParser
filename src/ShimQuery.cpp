#include "ShimQuery.h"
#include <Windows.h>
#include <vector>
#include <stdint.h>

const std::wstring SHIMCACHE_PATH = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCompatCache";
const std::wstring SHIMCACHE_XP_PATH = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCompatibility";
const std::wstring SHIMCACHE_VALUE = L"AppCompatCache";
const size_t shim_data_size = 1024 * 1024 * 15; //15mb

bool query_shimcache(std::string &buf)
{
    HKEY hKey = NULL;
    DWORD dwResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, SHIMCACHE_PATH.c_str(), 0, KEY_QUERY_VALUE, (PHKEY)&hKey);
    if (ERROR_SUCCESS != dwResult)
    {
        dwResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, SHIMCACHE_XP_PATH.c_str(), 0, KEY_QUERY_VALUE, (PHKEY)&hKey);
        if (ERROR_SUCCESS != dwResult)
        {
            SetLastError(dwResult);
            return false;
        }
    }
    std::vector<BYTE> shim_data;
    shim_data.resize(shim_data_size);
    DWORD extract_data_size = shim_data_size;
    dwResult = RegQueryValueEx(hKey, SHIMCACHE_VALUE.c_str(), NULL, NULL, shim_data.data(), &extract_data_size);
    if (ERROR_SUCCESS == dwResult)
    {
        buf = std::string(reinterpret_cast<char*>(shim_data.data()), (size_t)extract_data_size);
        return true;
    }
    return false;
}