# UnrealDbgWinUI

`UnrealDbgWinUI` 是 `UnrealDbg.sln` 中新增的原生 WinUI 3 前端，用于替代旧版 Delphi VCL GUI。Delphi 源码保留在仓库中作为兼容参考，不参与新前端构建。

## 设计边界

- 纯 WinUI 3 / C++/WinRT，不使用 WebView。
- `RunTime.cpp` 只通过 `UnrealDbgDll.dll` 现有的四个稳定导出访问后端。
- 新进程继续导出 `PrintLog`，兼容后端现有的日志回调契约。
- `DebuggerList.ini` 与 `Config.ini` 保持旧版节名、键名和 `名称&路径` 格式。
- 设计令牌集中在 `UiTheme.h`，页面不直接散落颜色和尺寸。
- 旧 `Loader` 的符号准备职责已并入 WinUI；新界面不再启动 `Loader.exe` 或旧调试器。
- 支持暗黑与明亮主题，切换后整个界面即时重建并写入 `Config.ini` 的 `[UI] Theme`。
- 首次运行默认使用明亮主题；未显式配置 `Theme=dark` 时保持明亮。

## 界面结构

- **总览**：VT 初始化状态、后端状态、外部调试器、目标进程与本机环境。
- **调试器**：添加、移除、启动外部调试器和路径定位。
- **目标与防护**：前台进程捕获、目标生命周期展示、TL 开关和线程恢复阻塞。
- **驱动 Hook**：逐项控制 DbgkSys EPT Hook；说明每项作用，进入 VT 初始化后由界面锁定。
- **诊断与文件**：运行文件检查、系统信息、后端路径与日志入口。
- **日志中心**：实时切换界面运行日志、DbgkSys10/11、VTLoad、Hook64/Hook 日志。
- **系统详情**：展示系统版本、CPU、内存、固件、安全启动、主板、GPU、磁盘和运行环境。
- **系统符号**：进入页面时不自动解析；点击“初始化”后才递归解析 `C:\Symbols` 下全部 PDB，列出函数、变量、RVA、当前已加载模块地址，以及 `_ETHREAD.CrossThreadFlags` 等结构字段偏移；支持全局搜索、PDB/类型切换、仅项目使用过滤、自定义 PDB，并默认隐藏编译器 lambda 与 `??` 内部符号。
- **符号缓存**：自动校验 `ntoskrnl`、`win32kbase`、`win32kfull` PDB，支持缓存复用和重新检查。

界面采用 Claude 风格：明亮主题为暖米白纸面 + 白色卡片，暗黑主题为暖炭灰；陶土橙（#C96442）是唯一强调色，只用于主操作、选中态与原生控件（开关、进度条、复选框等，经 `ApplyAccentResources` 覆盖系统强调色），其余语义色均降饱和。标题栏与侧栏共用一块底色，内容区作为左上圆角面板嵌入。圆角只有两档：容器（卡片、面板、弹出层）12、控件（按钮、输入框、下拉框、导航项）8，状态标签为按实际高度计算的全圆胶囊；原生控件经 `ControlCornerRadius` / `OverlayCornerRadius` 统一到这两档。全界面只用三组字体：文字一律 Microsoft YaHei UI（含原生控件），字重只有 Regular / Bold 两档（雅黑没有 Medium/SemiBold 字面）；路径、日志等等宽文本用 Cascadia Mono / Consolas 回退链；图标用 Segoe Fluent Icons / MDL2 Assets。Windows 10 上标题栏顶部系统留下的 1px 白线会重画为标题栏色；左右的深灰细线是 DWM 系统边框，Win10 无法在应用内修改，Win11 下设为主题边框色。

日志中心对内核与 Hook 日志使用 UTF-8、CP936/GBK、GB18030 和系统代码页联合判定，避免在 UTF-8 活动代码页进程中把 GBK 中文误读为乱码。
WinUI 引导、启动异常、冒烟测试与压力测试诊断统一追加到 `程序目录\Log\WinUI.log`，不再写入系统临时目录。

## Loader 融合

旧的 `Loader.exe` 会在独立启动画面中下载符号，再拉起旧 GUI。新前端保留其核心职责，但移除独立进程和启动画面：

1. WinUI 首帧出现后，后台读取系统模块的 PE RSDS 签名。
2. 使用 `DbgHelp::SymFindFileInPathW` 按 GUID + Age 校验 `C:\Symbols`。
3. 缓存缺失时从配置的符号服务器下载，并在写入后再次校验。
4. 点击“进入 VT 调试模式”时，等待符号准备完成后再调用后端初始化。

符号服务器配置优先读取 `SymbolTool\Config.ini`；不存在时创建 `[Symbol] Server=200`，默认使用 Microsoft Symbol Server。

## 构建

工程固定使用当前稳定版：

- Windows App SDK 2.5.1
- C++/WinRT 3.0.260818.1
- 目标系统最低版本 Windows 10 2004（Build 19041）

构建依赖位于 `_artifacts\winui_251_packages`。使用 Visual Studio 2022 的 MSBuild 构建 Release：

```powershell
& 'D:\Microsoft Visual Studio2022\Community\MSBuild\Current\Bin\MSBuild.exe' `
  'UnrealDbgWinUI\UnrealDbgWinUI.vcxproj' `
  /p:Configuration=Release /p:Platform=x64 /m /v:m
```

产物位于：

```text
x64\WinUI\Release\UnrealDbgWinUI.exe
```

`UnrealDbgWinUI` 与驱动、Hook、DLL 项目已解除构建依赖：只重建 WinUI 时不会再构建其它项目。修改驱动或 DLL 时请单独构建对应项目，或者构建整个 `UnrealDbg.sln`。

目标电脑需要安装 Windows App Runtime 2.5.1 x64。运行 UI 冒烟测试：

```powershell
x64\WinUI\Release\UnrealDbgWinUI.exe --ui-smoke-test --ui-theme=light
x64\WinUI\Release\UnrealDbgWinUI.exe --ui-smoke-test --ui-theme=dark
```

## 兼容文件

新前端优先读取发布目录根部的旧版配置；如果不存在，再读取 `Config` 子目录。这样可以与旧 Delphi 构建共用已有调试器列表和 TL 设置。
