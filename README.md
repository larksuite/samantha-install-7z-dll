# 7z DLL Modification Project README
## I. Project Overview
This project is developed based on the 7z 2201 version. Its goal is to transform the main compilation product of the original project from an exe into a dll, facilitating integration into other projects. By creating the `Extract7z` class and providing the `Unzip7zPath` export function, it enables the extraction of 7z files and can callback the extraction progress information, allowing users to monitor the extraction status in real - time.

## II. Function Introduction
### Extraction Function
`bool Extract7z::Unzip7zPath(const WCHAR* dllPath, const WCHAR* zipPath, const WCHAR* destDir, const CProgressCallback* callback, std::vector<std::wstring>* pFileList, int fromProgress, int toProgres)`
#### Parameter Explanation
- `dllPath`: A wide - character pointer pointing to the current dll file path, used for loading related dependencies, etc.
- `zipPath`: The path of the 7z file to be extracted, passed in as a wide - character string.
- `destDir`: The path of the extraction target directory, specifying the location where the extracted files will be stored.
- `callback`: A pointer to the progress callback function, used to feedback the extraction progress to the caller. The callback function should follow the specifications defined by `CProgressCallback` to accurately receive and process progress data.
- `pFileList`: A pointer to `std::vector<std::wstring>`, used to store the file list information during the extraction process, facilitating subsequent operations to know the details of the extracted files.
- `fromProgress`: The starting value of the progress range, used to set the starting point of the progress feedback, which can be flexibly coordinated with the overall progress logic.
- `toProgres`: The ending value of the progress range, defining the end point of the extraction progress feedback.
#### Return Value
Returns `true` if the extraction is successful, otherwise `false`.

## III. Usage Instructions
1. **Include the Header File**: In the project using this dll, you need to include the header file containing the declaration of the `Extract7z` class to ensure that the compiler can recognize the relevant types and function signatures.
2. **Link the DLL**: Link the generated dll file with the project. Different development environments have different link configuration methods. For example, in Visual Studio, you need to specify the dll path in the linker settings of the project properties.
3. **Call the Extraction Function**: Prepare the corresponding paths, callback functions, etc. according to the parameter requirements of the `Unzip7zPath` function, and then you can initiate the extraction operation. The sample code is as follows:
```cpp
#include "Extract7z.h"
// Assume that a suitable progress callback function CProgressCallback myCallback has been implemented;
int main() {
    const WCHAR* dllPath = L"path/to/your/dll";
    const WCHAR* zipPath = L"path/to/your/7z/file.7z";
    const WCHAR* destDir = L"destination/directory";
    std::vector<std::wstring> fileList;
    bool result = Extract7z::Unzip7zPath(dllPath, zipPath, destDir, &myCallback, &fileList, 10, 98);
    if (result) {
        // Processing logic after successful extraction
    } else {
        // Processing for extraction failure
    }
    return 0;
}
```

## IV. Precautions
1. **Compatibility**: Since this project is modified based on the 7z 2201 version, when using it, ensure the compatibility of the target environment with this version, especially when it comes to the collaborative work of system - level dependencies and other libraries.
2. **Callback Function Stability**: The progress callback function provided by the user should be stable. Avoid exceptions during the callback process that may cause the extraction to be interrupted or the program to crash. It is recommended to conduct sufficient error handling inside the callback function.
3. **Path Correctness**: The dll path, 7z file path, and target extraction directory path passed in must be accurate. Otherwise, it will lead to problems such as extraction failure or incorrect file storage.

## V. Future Plans
1. Further optimize the extraction performance. We may explore multi - thread extraction and other technologies to improve the extraction speed of large 7z files.
2. Improve the error - handling mechanism, provide more detailed error codes or error messages to help users accurately locate the root cause of problems.

We welcome all developers to use this project. If you encounter problems or have improvement suggestions, please feel free to submit issues or pull requests in the project repository.

## VI. License Information
This project follows the 7z license agreement. 7z uses the GNU LGPL (Lesser General Public License). The core points are as follows:
1. You can freely use, modify, and distribute this software, whether in source code form or binary form. However, if you modify the software and distribute the modified version, you must disclose the modified source code to ensure that others can also benefit from these modifications and can continue to freely improve the software.
2. For applications developed using this software, if the application only statically or dynamically links to this software library, the application can choose to follow the LGPL license or use a more permissive license for distribution. But if you modify this software library and distribute the modified version as part of the application, the entire application must follow the LGPL license and disclose the modified source code.

For the detailed license text, please refer to the [official 7z license document](https://www.7-zip.org/license.txt). Please ensure that your actions comply with the relevant license regulations when using this project to avoid potential legal issues. 