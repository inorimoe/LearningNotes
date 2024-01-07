##资源links
|名称|链接|
|:-|:-|
|Dear ImGui|https://github.com/ocornut/imgui|
|ImGui wiki|https://github.com/ocornut/imgui/wiki|
|Getting Started guide|https://github.com/ocornut/imgui/wiki/Getting-Started|
|SyFrom视频教程|https://www.bilibili.com/video/BV1F34y1F7Rd|

### 安装
安装 master 和 docking 分支：
```sh
git clone https://github.com/ocornut/imgui.git  #master
git clone https://github.com/ocornut/imgui.git -b docking <file_name>  #docking
```

### 运行example
使用 Visual Studio 运行 ` ./ImGui/examples/imgui_examples.sln`

### 头文件依赖
```c++
#pragma once
#include <tchar.h>

//Imgui 接口
#include "Imgui/imconfig.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imstb_rectpack.h"
#include "Imgui/imstb_textedit.h"
#include "Imgui/imstb_truetype.h"
#include "Imgui/imgui_impl_dx12.h"
#include "Imgui/imgui_impl_win32.h"

//d12 头文件接口
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_4.h>

//链接d12库
#pragma comment(lib, "d3d12.lib") 
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
```