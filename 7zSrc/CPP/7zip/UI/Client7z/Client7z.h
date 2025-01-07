// Copyright (c) 2022 Lark Technologies Pte. Ltd.
#pragma once

#include <vector>
#include <string>
#include <functional>

typedef std::function<void(int progress, const std::wstring& message)> CProgressCallback;

namespace Extract7z {

//解压7z文件到文件夹
bool Unzip7zPath(const WCHAR* dllPath,
                 const WCHAR* zipPath,
                 const WCHAR* destDir,
                 const CProgressCallback* callback,
                 std::vector<std::wstring>* pFileList,
                 int fromProgress = 0,
                 int toProgres = 100);
}  // namespace Extract7z
