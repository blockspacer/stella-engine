/*
MIT License

Copyright (c) 2019-2020 Stephane Cuillerdier (aka aiekick)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __IMGUI_FILE_DIALOG_H_
#define __IMGUI_FILE_DIALOG_H_

#include "../../lib/imgui/imgui.h"

#include <vector>
#include <string>
#include <map>

#include <future>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include <list>

#define MAX_FILE_DIALOG_NAME_BUFFER 1024

struct FileInfoStruct
{
	char type = ' ';
	std::string filePath;
	std::string fileName;
	std::string ext;
};

class ImGuiFileDialog
{
private:
	std::vector<FileInfoStruct> m_FileList;
	std::map<std::string, ImVec4> m_FilterColor;
	std::string m_SelectedFileName;
	std::string m_SelectedExt;
	std::string m_CurrentPath;
	std::vector<std::string> m_CurrentPath_Decomposition;
	std::string m_Name;
	bool m_ShowDialog = false;
	bool m_ShowDrives = false;

public:
	static char FileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static char DirectoryNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static char SearchBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static int FilterIndex;
	bool IsOk = false;
	bool m_AnyWindowsHovered = false;
	bool m_CreateDirectoryMode = false;

private:
	std::string dlg_key;
	std::string dlg_name;
	const char *dlg_filters{};
	std::string dlg_path;
	std::string dlg_defaultFileName;
	std::string dlg_defaultExt;
	std::function<void(std::string, bool*)> dlg_optionsPane;
	size_t dlg_optionsPaneWidth = 0;
	std::string searchTag;
	std::string dlg_userString;

public:
	static ImGuiFileDialog* Instance()
	{
		static auto *_instance = new ImGuiFileDialog();
		return _instance;
	}

protected:
	ImGuiFileDialog(); // Prevent construction
	ImGuiFileDialog(const ImGuiFileDialog&) {}; // Prevent construction by copying
	ImGuiFileDialog& operator =(const ImGuiFileDialog&) { return *this; }; // Prevent assignment
	~ImGuiFileDialog(); // Prevent unwanted destruction

public:
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName,
		const std::function<void(std::string, bool*)>& vOptionsPane, size_t vOptionsPaneWidth = 250, const std::string& vUserString = "");
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vDefaultFileName,
		const std::function<void(std::string, bool*)>& vOptionsPane, size_t vOptionsPaneWidth = 250, const std::string& vUserString = "");
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vPath, const std::string& vDefaultFileName, const std::string& vUserString = "");
	void OpenDialog(const std::string& vKey, const char* vName, const char* vFilters,
		const std::string& vFilePathName, const std::string& vUserString = "");

	void CloseDialog(const std::string& vKey);
	bool FileDialog(const std::string& vKey, ImGuiWindowFlags vFlags = ImGuiWindowFlags_NoCollapse);
	std::string GetFilepathName();
	std::string GetCurrentPath();
	std::string GetCurrentFileName();
	std::string GetCurrentFilter();
	std::string GetUserString();

	void SetFilterColor(const std::string& vFilter, ImVec4 vColor);
    bool GetFilterColor(const std::string& vFilter, ImVec4 *vColor);
    void ClearFilterColor();

private:
	void SetPath(const std::string& vPath);
	void ScanDir(const std::string& vPath);
	void SetCurrentDir(const std::string& vPath);
	bool CreateDir(const std::string& vPath);
	void ComposeNewPath(std::vector<std::string>::iterator vIter);
	void GetDrives();
};


#endif // __IMGUI_FILE_DIALOG_H_