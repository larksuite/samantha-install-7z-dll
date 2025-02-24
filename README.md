# 7z DLL 改造项目 README

## 一、项目概述

本项目基于 7z 2201 版本进行开发，旨在将原项目主要生成的 exe 编译产物改造为 dll，以方便在其他项目中集成使用。通过创建 `Extract7z` 类并提供 `Unzip7zPath` 导出函数，实现了对 7z 文件的解压功能，并能够回调解压进度信息，让使用者可以实时掌握解压状态。

## 二、功能介绍

**解压函数**：

`bool Extract7z::Unzip7zPath(const WCHAR* dllPath, const WCHAR* zipPath, const WCHAR* destDir, const CProgressCallback* callback, std::vector<std::wstring>* pFileList, int fromProgress, int toProgres)`

参数说明：

`dllPath`：指向当前 dll 文件路径的宽字符指针，用于加载相关依赖等。

`zipPath`：待解压的 7z 文件的路径，以宽字符形式传入。

`destDir`：解压目标目录路径，指定解压后的文件存放位置。

`callback`：指向进度回调函数的指针，用于向调用者反馈解压进度。回调函数应遵循 `CProgressCallback` 定义的规范，以便准确接收和处理进度数据。

`pFileList`：一个指向 `std::vector<std::wstring>` 的指针，用于存储解压过程中文件列表信息，方便后续操作知晓解压出的文件详情。

`fromProgress`：进度区间起始值，用于设定进度反馈的起始点，可灵活配合整体进度逻辑。

`toProgres`：进度区间结束值，界定解压进度反馈的终点。

返回值：成功解压返回 `true`，否则返回 `false`。

## 三、使用方法

引入头文件：在使用本 dll 的项目中，需引入包含 `Extract7z` 类声明的头文件，确保编译器能够识别相关类型和函数签名。

链接 dll：将生成的 dll 文件与项目进行链接，不同开发环境有不同的链接配置方式，例如在 Visual Studio 中，需在项目属性的链接器设置里指定 dll 的路径。

调用解压函数：按照 `Unzip7zPath` 函数参数要求，准备好相应的路径、回调函数等，即可发起解压操作。示例代码如下：



```
#include "Extract7z.h"

// 假设已经实现了合适的进度回调函数 CProgressCallback myCallback;

int main() {

   const WCHAR* dllPath = L"path/to/your/dll";

   const WCHAR* zipPath = L"path/to/your/7z/file.7z";

   const WCHAR* destDir = L"destination/directory";

   std::vector<std::wstring> fileList;

   bool result = Extract7z::Unzip7zPath(dllPath, zipPath, destDir, &myCallback, &fileList, 10, 98);

   if (result) {

       // 解压成功后的处理逻辑

   } else {

       // 解压失败处理

   }

   return 0;

}
```

## 四、注意事项

兼容性：由于本项目基于 7z 2201 版本改造，在使用时需确保目标环境与该版本的兼容性，尤其是涉及到系统底层依赖和其他库的协同工作时。

回调函数稳定性：使用者提供的进度回调函数应保证稳定性，避免在回调过程中出现异常导致解压中断或程序崩溃，建议在回调函数内部进行充分的错误处理。

路径正确性：传入的 dll 路径、7z 文件路径和目标解压目录路径务必准确，否则将导致解压失败或文件存放错误等问题。

## 五、后续计划

进一步优化解压性能，可能探索多线程解压等技术，提高大型 7z 文件的解压速度。

完善错误处理机制，提供更详细的错误码或错误信息，方便使用者精准定位问题根源。

欢迎各位开发者使用本项目，如果遇到问题或有改进建议，请随时在项目仓库提交 issue 或 pull request。

## 六、许可证信息（License）
本项目遵循 7z 的许可证协议。7z 使用的是 GNU LGPL（Lesser General Public License）许可证，其核心要点如下：

1. 您可以自由使用、修改和分发本软件，无论是以源代码形式还是二进制形式。但如果您对软件进行了修改，并且分发修改后的版本，您必须公开修改后的源代码，以保证其他人也能够受益于这些修改，并能够继续自由地对软件进行改进。
2. 对于使用本软件开发的应用程序，如果应用程序只是静态链接或者动态链接到本软件库，那么该应用程序可以选择遵循 LGPL 许可证，或者采用更宽松的许可证分发。但如果您对本软件库进行了修改，并且将修改后的版本作为应用程序的一部分进行分发，那么整个应用程序必须遵循 LGPL 许可证，并且公开修改后的源代码。

详细的许可证文本可参考 [官方 7z 许可证文档](https://www.7-zip.org/license.txt)，请确保在使用本项目时，您的行为符合相关的许可规定，以避免潜在的法律问题。