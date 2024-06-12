#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <tchar.h>
#pragma comment(lib, "wininet.lib")

bool DownloadFile(const wchar_t* url, const wchar_t* file_path) {
    HINTERNET hInternet = InternetOpen(L"Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::wcerr << L"InternetOpen failed. Error: " << GetLastError() << std::endl;
        return false;
    }

    HINTERNET hUrl = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        std::wcerr << L"InternetOpenUrl failed. Error: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead;
    HANDLE hFile = CreateFile(file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::wcerr << L"CreateFile failed. Error: " << GetLastError() << std::endl;
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return false;
    }

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        DWORD bytesWritten;
        if (!WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL)) {
            std::wcerr << L"WriteFile failed. Error: " << GetLastError() << std::endl;
            CloseHandle(hFile);
            InternetCloseHandle(hUrl);
            InternetCloseHandle(hInternet);
            return false;
        }
    }

    CloseHandle(hFile);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return true;
}

void InstallSoftware(const wchar_t* installer_path) {
    HINSTANCE result = ShellExecute(NULL, L"open", installer_path, NULL, NULL, SW_SHOWNORMAL);
    if ((int)result <= 32) {
        std::wcerr << L"ShellExecute failed. Error: " << GetLastError() << std::endl;
    }
}

int wmain() {
    const wchar_t* chrome_url = L"https://dl.google.com/chrome/install/latest/chrome_installer.exe";
    const wchar_t* firefox_url = L"https://download.mozilla.org/?product=firefox-latest&os=win&lang=en-US";
    const wchar_t* adobe_url = L"https://get.adobe.com/reader/download/";

    const wchar_t* chrome_installer = L"chrome_installer.exe";
    const wchar_t* firefox_installer = L"firefox_installer.exe";
    const wchar_t* adobe_installer = L"adobe_installer.exe";

    std::wcout << L"Downloading Chrome installer..." << std::endl;
    if (DownloadFile(chrome_url, chrome_installer)) {
        std::wcout << L"Installing Chrome..." << std::endl;
        InstallSoftware(chrome_installer);
    }
    else {
        std::wcerr << L"Failed to download Chrome installer." << std::endl;
    }

    std::wcout << L"Downloading Firefox installer..." << std::endl;
    if (DownloadFile(firefox_url, firefox_installer)) {
        std::wcout << L"Installing Firefox..." << std::endl;
        InstallSoftware(firefox_installer);
    }
    else {
        std::wcerr << L"Failed to download Firefox installer." << std::endl;
    }

    std::wcout << L"Downloading Adobe Reader installer..." << std::endl;
    if (DownloadFile(adobe_url, adobe_installer)) {
        std::wcout << L"Installing Adobe Reader..." << std::endl;
        InstallSoftware(adobe_installer);
    }
    else {
        std::wcerr << L"Failed to download Adobe Reader installer." << std::endl;
    }

    return 0;
}
