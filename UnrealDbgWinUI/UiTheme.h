#pragma once

// 统一设计令牌（Design Tokens）。
//
// 界面层所有颜色、字号、间距、圆角、控件尺寸都必须来自本文件，页面代码里
// 不允许再出现写死的颜色值或魔法数字。这样后续换肤或调整密度时只需要改一处。

#include <cstdint>
#include <string>
#include <unordered_map>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace unrealdbg_ui
{
    namespace token
    {
        using winrt::Microsoft::UI::Xaml::Controls::Border;
        using winrt::Microsoft::UI::Xaml::Controls::FontIcon;
        using winrt::Microsoft::UI::Xaml::Controls::TextBlock;
        using winrt::Microsoft::UI::Xaml::Media::FontFamily;
        using winrt::Microsoft::UI::Xaml::Media::SolidColorBrush;
        using winrt::Windows::UI::Color;
        using winrt::Windows::UI::Text::FontWeight;

        inline Color Rgb(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255) noexcept
        {
            return Color{ alpha, red, green, blue };
        }

        // 与 tint 同色相的全透明色。凡是会被 BrushTransition 动画过渡到某个颜色的
        // "透明"底色都应该用它，而不是 (0,0,0,0)，避免过渡中间帧发灰闪烁。
        inline Color Transparent(const Color tint) noexcept
        {
            return Color{ 0, tint.R, tint.G, tint.B };
        }

        // ---------------------------------------------------------------- 颜色
        // Claude 风格调色板：明亮主题为暖米白纸面 + 白色卡片，暗黑主题为暖炭灰；
        // 唯一的强调色是陶土橙（clay），只用于主操作与选中态，其余语义色都做了降饱和。
        inline bool UseDarkTheme{ false };
        inline Color kWindowTop{ Rgb(0xFA, 0xF9, 0xF5) };
        inline Color kWindowBottom{ Rgb(0xF5, 0xF4, 0xEE) };
        inline Color kTitleBar{ Rgb(0xF0, 0xEE, 0xE6) };
        inline Color kSidebar{ Rgb(0xF0, 0xEE, 0xE6) };
        inline Color kCard{ Rgb(0xFF, 0xFF, 0xFF) };
        inline Color kCardInset{ Rgb(0xF7, 0xF6, 0xF1) };
        inline Color kCardHover{ Rgb(0xE8, 0xE6, 0xDC) };
        inline Color kSunken{ Rgb(0xEE, 0xEC, 0xE3) };
        inline Color kBorder{ Rgb(0xE5, 0xE2, 0xD7) };
        inline Color kBorderStrong{ Rgb(0xD3, 0xCF, 0xC2) };
        inline Color kTextPrimary{ Rgb(0x1F, 0x1E, 0x1C) };
        inline Color kTextSecondary{ Rgb(0x4D, 0x4B, 0x45) };
        inline Color kTextMuted{ Rgb(0x85, 0x83, 0x7B) };
        inline Color kTextOnAccent{ Rgb(0xFF, 0xFF, 0xFF) };
        inline Color kAccent{ Rgb(0xC9, 0x64, 0x42) };
        inline Color kAccentHover{ Rgb(0xB9, 0x5A, 0x3A) };
        inline Color kAccentPressed{ Rgb(0xA4, 0x4F, 0x33) };
        inline Color kAccentSoft{ Rgb(0xF6, 0xE7, 0xDF) };
        inline Color kAccentText{ Rgb(0xA4, 0x49, 0x2B) };
        inline Color kCinnabar{ Rgb(0xD9, 0x77, 0x57) };
        inline Color kCinnabarSoft{ Rgb(0xF8, 0xE5, 0xDC) };
        inline Color kGold{ Rgb(0xA2, 0x7B, 0x36) };
        inline Color kGoldSoft{ Rgb(0xF3, 0xEA, 0xD6) };
        inline Color kSuccess{ Rgb(0x4C, 0x8A, 0x5A) };
        inline Color kSuccessSoft{ Rgb(0xE3, 0xEE, 0xE2) };
        inline Color kWarning{ Rgb(0xA5, 0x77, 0x28) };
        inline Color kWarningSoft{ Rgb(0xF5, 0xEB, 0xD5) };
        inline Color kDanger{ Rgb(0xB5, 0x46, 0x3C) };
        inline Color kDangerSoft{ Rgb(0xF6, 0xE2, 0xDE) };
        inline Color kDangerHover{ Rgb(0xEF, 0xD4, 0xCF) };
        inline Color kDangerPressed{ Rgb(0xE6, 0xC4, 0xBE) };
        inline Color kInfo{ Rgb(0x4F, 0x75, 0x93) };
        inline Color kInfoSoft{ Rgb(0xE3, 0xEA, 0xF0) };
        inline Color kDebug{ Rgb(0x6E, 0x6C, 0x65) };
        inline Color kDebugSoft{ Rgb(0xEE, 0xED, 0xE6) };

        inline void SetTheme(const bool dark)
        {
            UseDarkTheme = dark;
            if (dark)
            {
                kWindowTop = Rgb(0x26, 0x26, 0x24);
                kWindowBottom = Rgb(0x22, 0x22, 0x20);
                kTitleBar = Rgb(0x1F, 0x1E, 0x1D);
                kSidebar = Rgb(0x1F, 0x1E, 0x1D);
                kCard = Rgb(0x30, 0x30, 0x2E);
                kCardInset = Rgb(0x2B, 0x2A, 0x28);
                kCardHover = Rgb(0x3A, 0x39, 0x36);
                kSunken = Rgb(0x1A, 0x19, 0x18);
                kBorder = Rgb(0x3B, 0x3A, 0x36);
                kBorderStrong = Rgb(0x4D, 0x4C, 0x47);
                kTextPrimary = Rgb(0xF5, 0xF4, 0xEE);
                kTextSecondary = Rgb(0xC3, 0xC1, 0xB7);
                kTextMuted = Rgb(0x95, 0x93, 0x89);
                kTextOnAccent = Rgb(0xFF, 0xFF, 0xFF);
                kAccent = Rgb(0xC9, 0x64, 0x42);
                kAccentHover = Rgb(0xD5, 0x71, 0x4F);
                kAccentPressed = Rgb(0xB0, 0x56, 0x37);
                kAccentSoft = Rgb(0x3D, 0x2A, 0x22);
                kAccentText = Rgb(0xE8, 0x95, 0x7A);
                kCinnabar = Rgb(0xE0, 0x85, 0x66);
                kCinnabarSoft = Rgb(0x3B, 0x2A, 0x23);
                kGold = Rgb(0xD4, 0xA7, 0x62);
                kGoldSoft = Rgb(0x3A, 0x31, 0x22);
                kSuccess = Rgb(0x7D, 0xB8, 0x8A);
                kSuccessSoft = Rgb(0x25, 0x32, 0x28);
                kWarning = Rgb(0xD9, 0xAE, 0x62);
                kWarningSoft = Rgb(0x3A, 0x31, 0x22);
                kDanger = Rgb(0xE3, 0x79, 0x6B);
                kDangerSoft = Rgb(0x3D, 0x25, 0x23);
                kDangerHover = Rgb(0x4A, 0x2C, 0x29);
                kDangerPressed = Rgb(0x2F, 0x1D, 0x1B);
                kInfo = Rgb(0x8A, 0xB0, 0xCF);
                kInfoSoft = Rgb(0x25, 0x30, 0x3A);
                kDebug = Rgb(0xA8, 0xA6, 0x9D);
                kDebugSoft = Rgb(0x2E, 0x2E, 0x2B);
            }
            else
            {
                kWindowTop = Rgb(0xFA, 0xF9, 0xF5);
                kWindowBottom = Rgb(0xF5, 0xF4, 0xEE);
                kTitleBar = Rgb(0xF0, 0xEE, 0xE6);
                kSidebar = Rgb(0xF0, 0xEE, 0xE6);
                kCard = Rgb(0xFF, 0xFF, 0xFF);
                kCardInset = Rgb(0xF7, 0xF6, 0xF1);
                kCardHover = Rgb(0xE8, 0xE6, 0xDC);
                kSunken = Rgb(0xEE, 0xEC, 0xE3);
                kBorder = Rgb(0xE5, 0xE2, 0xD7);
                kBorderStrong = Rgb(0xD3, 0xCF, 0xC2);
                kTextPrimary = Rgb(0x1F, 0x1E, 0x1C);
                kTextSecondary = Rgb(0x4D, 0x4B, 0x45);
                kTextMuted = Rgb(0x85, 0x83, 0x7B);
                kTextOnAccent = Rgb(0xFF, 0xFF, 0xFF);
                kAccent = Rgb(0xC9, 0x64, 0x42);
                kAccentHover = Rgb(0xB9, 0x5A, 0x3A);
                kAccentPressed = Rgb(0xA4, 0x4F, 0x33);
                kAccentSoft = Rgb(0xF6, 0xE7, 0xDF);
                kAccentText = Rgb(0xA4, 0x49, 0x2B);
                kCinnabar = Rgb(0xD9, 0x77, 0x57);
                kCinnabarSoft = Rgb(0xF8, 0xE5, 0xDC);
                kGold = Rgb(0xA2, 0x7B, 0x36);
                kGoldSoft = Rgb(0xF3, 0xEA, 0xD6);
                kSuccess = Rgb(0x4C, 0x8A, 0x5A);
                kSuccessSoft = Rgb(0xE3, 0xEE, 0xE2);
                kWarning = Rgb(0xA5, 0x77, 0x28);
                kWarningSoft = Rgb(0xF5, 0xEB, 0xD5);
                kDanger = Rgb(0xB5, 0x46, 0x3C);
                kDangerSoft = Rgb(0xF6, 0xE2, 0xDE);
                kDangerHover = Rgb(0xEF, 0xD4, 0xCF);
                kDangerPressed = Rgb(0xE6, 0xC4, 0xBE);
                kInfo = Rgb(0x4F, 0x75, 0x93);
                kInfoSoft = Rgb(0xE3, 0xEA, 0xF0);
                kDebug = Rgb(0x6E, 0x6C, 0x65);
                kDebugSoft = Rgb(0xEE, 0xED, 0xE6);
            }
        }

        // -------------------------------------------------------------- 字号
        // 中文界面优先保证字形清楚：正文不低于 12px，说明文字不低于 10.5px。
        inline constexpr double kFontMicro{ 10.5 };      // 徽标、极小提示
        inline constexpr double kFontCaption{ 12.0 };    // 说明文字、副标题
        inline constexpr double kFontBody{ 13.0 };       // 正文、行标题
        inline constexpr double kFontSubtitle{ 15.0 };   // 区块标题
        inline constexpr double kFontTitle{ 22.0 };      // 页面标题、磁贴主数值
        inline constexpr double kFontHero{ 26.0 };       // 总览状态大标题
        inline constexpr double kFontMono{ 12.0 };       // 等宽文本（路径、日志）

        // 只有两档字重，且必须对应字体里真实存在的字面：Microsoft YaHei UI 只有
        // Light(290) / Regular(400) / Bold(700)。请求 500、600 这类不存在的字重时，
        // WinUI 的匹配结果随字号变化（实测 600 在 15px 落到 Bold、22px 落到 Regular），
        // 同为"SemiBold"的标题有的粗有的细。所以不提供 Medium / SemiBold。
        inline constexpr FontWeight kWeightRegular{ 400 };
        inline constexpr FontWeight kWeightBold{ 700 };

        // -------------------------------------------------------------- 行高
        // 行高规范：单行文本 1.30 倍字号，多行文本 1.50 倍字号。所有文本工厂
        // （Text / TextWrapped / Mono）统一套用，页面代码不得再各自设置 LineHeight。
        inline constexpr double kLineHeightTight{ 1.3 };
        inline constexpr double kLineHeightRelaxed{ 1.5 };
        inline constexpr double kLineHeightMono{ 1.38 };

        // -------------------------------------------------------------- 间距
        // 紧凑窗口下间距阶梯整体收紧一档，保持留白节奏但不浪费纵向空间。
        inline constexpr double kSpaceXs{ 4.0 };
        inline constexpr double kSpaceSm{ 8.0 };
        inline constexpr double kSpaceMd{ 12.0 };
        inline constexpr double kSpaceLg{ 15.0 };
        inline constexpr double kSpaceXl{ 18.0 };
        inline constexpr double kSpaceXxl{ 22.0 };

        // -------------------------------------------------------------- 圆角
        // 全界面只有两档圆角 + 两种全圆，不允许出现其它数值：
        //   kRadiusMd（8） 控件与小块：按钮、输入框、下拉框、导航项、列表项、
        //                  工具条、卡片内嵌块、≤32px 的图标底片 / 品牌标记；
        //   kRadiusLg（12）容器与大块：卡片、面板、底部状态卡、内容区外框、
        //                  弹出层（下拉列表、提示框）、≥40px 的印章；
        //   全圆：状态圆点、序号徽标用 尺寸/2；胶囊标签用 MakeCapsule()。
        // 原生控件（TextBox、ComboBox 等）默认 4 / 8，由 ApplyAccentResources
        // 统一改写成上面两档。
        inline constexpr double kRadiusMd{ 8.0 };
        inline constexpr double kRadiusLg{ 12.0 };
        // 胶囊（全圆两端）没有常量半径，统一用 MakeCapsule()，按实际高度取一半。

        // -------------------------------------------------------------- 尺寸
        // 与系统标题栏按钮的 Tall 高度（48）一致，自绘内容和最小化/最大化/关闭
        // 按钮共用同一条垂直中线。
        inline constexpr double kTitleBarHeight{ 48.0 };
        // 右侧为系统标题栏按钮（3 × 46）预留的宽度，外加 10px 与自绘工具按钮的间隙。
        inline constexpr double kTitleBarCaptionInset{ 148.0 };
        // 侧栏宽度按内容推算：最长导航项"诊断与文件"约 133px；底部状态卡需要
        // 标签（约 24px）+ 取值上限 kNavValueMaxWidth，再加外边距/内边距/边框 46px。
        // 180 让两者都有余量，右侧留白又不显空。
        inline constexpr double kNavWidth{ 180.0 };
        inline constexpr double kNavValueMaxWidth{ 96.0 };
        inline constexpr double kNavCollapsedWidth{ 56.0 };
        inline constexpr double kNavItemHeight{ 36.0 };
        // 侧栏左右留白（导航列表、底部状态卡的外边距）与内容对齐线（分组标题、
        // 导航图标、状态卡文字的统一起点）。
        inline constexpr double kSidebarGutter{ 10.0 };
        inline constexpr double kSidebarInset{ 22.0 };
        inline constexpr double kSplitterHeight{ 5.0 };
        inline constexpr double kLogHeaderHeight{ 34.0 };
        inline constexpr double kLogDefaultHeight{ 218.0 };
        inline constexpr double kLogMinHeight{ 128.0 };
        inline constexpr double kLogMaxRatio{ 0.6 };
        inline constexpr double kWindowDefaultWidth{ 1180.0 };
        inline constexpr double kWindowDefaultHeight{ 790.0 };
        inline constexpr double kWindowMinWidth{ 1020.0 };
        inline constexpr double kWindowMinHeight{ 680.0 };

        // ------------------------------------------------------------ 图标字形
        // 全部取自 Segoe MDL2 Assets / Segoe Fluent Icons 的常用码位。
        inline const wchar_t* const kGlyphOverview{ L"\uE80F" };   // Home
        inline const wchar_t* const kGlyphProcess{ L"\uE7B8" };    // Devices
        inline const wchar_t* const kGlyphShield{ L"\uE72E" };     // Lock
        inline const wchar_t* const kGlyphAbout{ L"\uE946" };      // Info
        inline const wchar_t* const kGlyphLog{ L"\uE756" };        // CommandPrompt
        inline const wchar_t* const kGlyphAdd{ L"\uE710" };        // Add
        inline const wchar_t* const kGlyphPlay{ L"\uE768" };       // Play
        inline const wchar_t* const kGlyphPause{ L"\uE769" };      // Pause
        inline const wchar_t* const kGlyphRemove{ L"\uE74D" };     // Delete
        inline const wchar_t* const kGlyphCopy{ L"\uE8C8" };       // Copy
        inline const wchar_t* const kGlyphClear{ L"\uE74D" };      // Delete
        inline const wchar_t* const kGlyphRefresh{ L"\uE72C" };    // Refresh
        inline const wchar_t* const kGlyphPin{ L"\uE718" };        // Pin
        inline const wchar_t* const kGlyphChevronDown{ L"\uE70D" };
        inline const wchar_t* const kGlyphChevronUp{ L"\uE70E" };
        inline const wchar_t* const kGlyphChevronLeft{ L"\uE76B" };
        inline const wchar_t* const kGlyphChevronRight{ L"\uE76C" };
        // OpenFolderHorizontal\uFF1A\u6A2A\u5411\u6587\u4EF6\u5939\uFF0CWin10 \u7684 MDL2 \u4E0E Win11 \u7684 Fluent \u4E0B\u90FD\u6E05\u695A\uFF1B
        // E8B7/E838 \u5728 MDL2 \u91CC\u662F\u7AD6\u7248\u8F6E\u5ED3\uFF0C14px \u4E0B\u50CF\u5E73\u677F\u6216\u95E8\uFF0C\u8FA8\u8BC6\u5EA6\u5DEE\u3002
        inline const wchar_t* const kGlyphFolder{ L"\uED25" };
        inline const wchar_t* const kGlyphCheck{ L"\uE73E" };      // CheckMark
        inline const wchar_t* const kGlyphWarning{ L"\uE7BA" };    // Warning
        inline const wchar_t* const kGlyphError{ L"\uEA39" };      // StatusErrorFull
        inline const wchar_t* const kGlyphTimer{ L"\uE916" };      // Stopwatch
        inline const wchar_t* const kGlyphServer{ L"\uE968" };     // Server
        inline const wchar_t* const kGlyphSymbols{ L"\uE943" };    // Code
        inline const wchar_t* const kGlyphDownload{ L"\uE896" };   // Download
        inline const wchar_t* const kGlyphLink{ L"\uE71B" };       // Link
        inline const wchar_t* const kGlyphSun{ L"\uE706" };        // Brightness
        inline const wchar_t* const kGlyphMoon{ L"\uE708" };       // QuietHours
        inline const wchar_t* const kGlyphFilter{ L"\uE71C" };     // Filter

        inline const wchar_t* const kIconFontFamily{ L"Segoe Fluent Icons,Segoe MDL2 Assets" };

        // -------------------------------------------------------------- 字体族
        // 全界面只用三组字体，不允许在页面代码里另写字体名：
        //   kUiFontFamily   所有文字（正文、标题、数值），中英文都由 YaHei UI 渲染；
        //   kMonoFontFamily 路径、日志、版本号等等宽文本；
        //   kIconFontFamily 图标（上方定义）。
        // 不再使用衬线标题：衬线中文（思源宋体等）是否安装、装了哪些字重因机器而异，
        // 同一界面会在宋体/黑体之间漂移，且只装 Heavy 时标题会异常粗。
        // 原先按字号区分的 Display 变体也去掉——YaHei UI 排在首位，Display/Text
        // 两组实际渲染结果一致。
        inline const wchar_t* const kUiFontFamily{
            L"Microsoft YaHei UI, Microsoft YaHei, Segoe UI" };
        // 末尾显式接 YaHei UI：等宽字体不含中文，日志里的中文统一回退到它，
        // 而不是由系统随机挑选。
        inline const wchar_t* const kMonoFontFamily{
            L"Cascadia Mono, Consolas, Courier New, Microsoft YaHei UI" };

        // 字号 -> 行高（像素）换算，供文本工厂统一套用。
        inline double LineHeightFor(const double size, const double ratio) noexcept
        {
            const double value = size * ratio;
            return static_cast<double>(static_cast<int>(value * 2.0 + 0.5)) / 2.0;  // 取 0.5 的整数倍
        }

        // ------------------------------------------------------------ 基础图元
        inline SolidColorBrush Brush(const Color color)
        {
            static std::unordered_map<std::uint32_t, SolidColorBrush> cache;
            const std::uint32_t key =
                (static_cast<std::uint32_t>(color.A) << 24) |
                (static_cast<std::uint32_t>(color.R) << 16) |
                (static_cast<std::uint32_t>(color.G) << 8) |
                static_cast<std::uint32_t>(color.B);
            const auto existing = cache.find(key);
            if (existing != cache.end())
            {
                return existing->second;
            }
            SolidColorBrush brush(color);
            cache.emplace(key, brush);
            return brush;
        }

        // 所有文本统一走这里：字号、字重（外部传入）+ 字体族（固定 kUiFontFamily）
        // + 行高（按行高规范换算），页面代码不再重复设置字体属性。
        inline TextBlock Text(const winrt::hstring& value, const double size, const Color color,
            const FontWeight weight = kWeightRegular)
        {
            TextBlock block;
            block.Text(value);
            block.FontSize(size);
            block.FontFamily(FontFamily(kUiFontFamily));
            block.Foreground(Brush(color));
            block.FontWeight(weight);
            block.TextWrapping(winrt::Microsoft::UI::Xaml::TextWrapping::NoWrap);
            block.LineStackingStrategy(winrt::Microsoft::UI::Xaml::LineStackingStrategy::BlockLineHeight);
            block.LineHeight(LineHeightFor(size, kLineHeightTight));
            return block;
        }

        // 多行正文走彻底放宽的行高（1.55），这是"读得舒服"的关键。
        inline TextBlock TextWrapped(const winrt::hstring& value, const double size, const Color color,
            const FontWeight weight = kWeightRegular)
        {
            TextBlock block = Text(value, size, color, weight);
            block.TextWrapping(winrt::Microsoft::UI::Xaml::TextWrapping::Wrap);
            block.LineHeight(LineHeightFor(size, kLineHeightRelaxed));
            return block;
        }

        inline TextBlock Mono(const winrt::hstring& value, const double size, const Color color)
        {
            TextBlock block = Text(value, size, color);
            block.FontFamily(FontFamily(kMonoFontFamily));
            block.LineHeight(LineHeightFor(size, kLineHeightMono));
            return block;
        }

        inline FontIcon Icon(const winrt::hstring& glyph, const double size, const Color color)
        {
            FontIcon icon;
            icon.Glyph(glyph);
            icon.FontSize(size);
            icon.Foreground(Brush(color));
            icon.FontFamily(FontFamily(kIconFontFamily));
            icon.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Center);
            icon.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Center);
            icon.IsHitTestVisible(false);
            return icon;
        }

        // 圆角 + 边框的矩形块，界面里所有"面"都由它拼装。
        inline Border Surface(const Color background, const Color border, const double radius = kRadiusLg,
            const double padding = kSpaceLg, const double borderThickness = 1.0)
        {
            Border surface;
            surface.Background(Brush(background));
            surface.BorderBrush(Brush(border));
            surface.BorderThickness(winrt::Microsoft::UI::Xaml::Thickness{ borderThickness, borderThickness, borderThickness, borderThickness });
            surface.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius{ radius, radius, radius, radius });
            surface.Padding(winrt::Microsoft::UI::Xaml::Thickness{ padding, padding, padding, padding });
            return surface;
        }

        // 带底色的小圆点，用于状态指示。
        inline Border Dot(const Color color, const double size = 8.0)
        {
            Border dot;
            dot.Width(size);
            dot.Height(size);
            dot.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius{ size / 2, size / 2, size / 2, size / 2 });
            dot.Background(Brush(color));
            dot.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Center);
            return dot;
        }

        // 把 Border 变成真正的胶囊（两端是正半圆）。
        //
        // 不能直接写 CornerRadius = 999：WinUI 在圆角超过尺寸时按横、纵两个方向
        // 各自压缩半径，横向被压到 宽/2、纵向被压到 高/2，两端就成了椭圆弧，
        // 整体像个橄榄。这里按实际高度取 高/2，尺寸变化（文字更新、DPI 变化）时重算。
        inline void MakeCapsule(const Border& border)
        {
            border.SizeChanged([](const winrt::Windows::Foundation::IInspectable& sender,
                const winrt::Microsoft::UI::Xaml::SizeChangedEventArgs& args)
            {
                const Border self = sender.try_as<Border>();
                if (self == nullptr)
                {
                    return;
                }
                const double radius = args.NewSize().Height / 2.0;
                if (self.CornerRadius().TopLeft != radius)
                {
                    self.CornerRadius(winrt::Microsoft::UI::Xaml::CornerRadius{ radius, radius, radius, radius });
                }
            });
        }

        // 胶囊标签：状态、计数、分级都用它。
        inline Border Pill(const winrt::hstring& value, const Color foreground, const Color background,
            const double fontSize = kFontMicro)
        {
            Border pill;
            pill.Background(Brush(background));
            MakeCapsule(pill);
            pill.Padding(winrt::Microsoft::UI::Xaml::Thickness{ 10, 3, 10, 3 });
            pill.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Center);
            TextBlock label = Text(value, fontSize, foreground);
            label.TextAlignment(winrt::Microsoft::UI::Xaml::TextAlignment::Center);
            pill.Child(label);
            return pill;
        }

        inline Border Separator(const Color color, const double thickness = 1.0)
        {
            Border line;
            line.Height(thickness);
            line.Background(Brush(color));
            line.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Stretch);
            return line;
        }

        inline winrt::Microsoft::UI::Xaml::Thickness Insets(const double left, const double top,
            const double right, const double bottom)
        {
            return winrt::Microsoft::UI::Xaml::Thickness{ left, top, right, bottom };
        }

        // 把系统强调色替换成 Claude 陶土橙：ToggleSwitch、CheckBox、ProgressBar/Ring、
        // ListView 选中指示条、输入框焦点线等原生控件都从这些键取色。挂到根元素的
        // Resources 上即可覆盖整棵可视树（主题切换会重建根元素，随之刷新）。
        inline void ApplyAccentResources(const winrt::Microsoft::UI::Xaml::ResourceDictionary& resources)
        {
            const auto put = [&](const wchar_t* key, const Color color)
            {
                resources.Insert(winrt::box_value(winrt::hstring(key)), winrt::box_value(SolidColorBrush(color)));
            };
            const auto putColor = [&](const wchar_t* key, const Color color)
            {
                resources.Insert(winrt::box_value(winrt::hstring(key)), winrt::box_value(color));
            };

            // 原生控件圆角：WinUI 默认 ControlCornerRadius=4、OverlayCornerRadius=8，
            // 与自绘按钮（8）、卡片（12）对不上，统一改到两档令牌。
            resources.Insert(winrt::box_value(winrt::hstring(L"ControlCornerRadius")),
                winrt::box_value(winrt::Microsoft::UI::Xaml::CornerRadius{ kRadiusMd, kRadiusMd, kRadiusMd, kRadiusMd }));
            resources.Insert(winrt::box_value(winrt::hstring(L"OverlayCornerRadius")),
                winrt::box_value(winrt::Microsoft::UI::Xaml::CornerRadius{ kRadiusLg, kRadiusLg, kRadiusLg, kRadiusLg }));

            // 原生控件（TextBox、ComboBox、ToggleSwitch、ToolTip 等）不走 Text()，
            // 默认字体是 XamlAutoFontFamily，英文会落到 Segoe UI；统一到 kUiFontFamily。
            resources.Insert(winrt::box_value(winrt::hstring(L"ContentControlThemeFontFamily")),
                FontFamily(kUiFontFamily));

            putColor(L"SystemAccentColor", kAccent);
            putColor(L"SystemAccentColorLight1", kAccentHover);
            putColor(L"SystemAccentColorLight2", kAccentHover);
            putColor(L"SystemAccentColorLight3", kAccentText);
            putColor(L"SystemAccentColorDark1", kAccentPressed);
            putColor(L"SystemAccentColorDark2", kAccentPressed);
            putColor(L"SystemAccentColorDark3", kAccentPressed);

            const Color secondary = Rgb(kAccent.R, kAccent.G, kAccent.B, 0xE6);
            const Color tertiary = Rgb(kAccent.R, kAccent.G, kAccent.B, 0xCC);
            put(L"AccentFillColorDefaultBrush", kAccent);
            put(L"AccentFillColorSecondaryBrush", secondary);
            put(L"AccentFillColorTertiaryBrush", tertiary);
            put(L"AccentTextFillColorPrimaryBrush", kAccentText);
            put(L"AccentTextFillColorSecondaryBrush", kAccentText);
            put(L"AccentTextFillColorTertiaryBrush", kAccentText);

            put(L"ToggleSwitchFillOn", kAccent);
            put(L"ToggleSwitchFillOnPointerOver", kAccentHover);
            put(L"ToggleSwitchFillOnPressed", kAccentPressed);
            put(L"ToggleSwitchStrokeOn", kAccent);
            put(L"ToggleSwitchStrokeOnPointerOver", kAccentHover);
            put(L"ToggleSwitchStrokeOnPressed", kAccentPressed);

            put(L"CheckBoxCheckBackgroundFillChecked", kAccent);
            put(L"CheckBoxCheckBackgroundFillCheckedPointerOver", kAccentHover);
            put(L"CheckBoxCheckBackgroundFillCheckedPressed", kAccentPressed);
            put(L"CheckBoxCheckBackgroundStrokeChecked", kAccent);
            put(L"CheckBoxCheckBackgroundStrokeCheckedPointerOver", kAccentHover);
            put(L"CheckBoxCheckBackgroundStrokeCheckedPressed", kAccentPressed);

            put(L"ProgressBarForeground", kAccent);
            put(L"ProgressRingForegroundThemeBrush", kAccent);

            put(L"ListViewItemSelectionIndicatorBrush", kAccent);
            put(L"ListViewItemSelectionIndicatorPointerOverBrush", kAccentHover);
            put(L"ListViewItemSelectionIndicatorPressedBrush", kAccentPressed);
            // 列表项：静止 → 悬停 → 按下/选中 单调加深；按下态也要覆盖，否则点击时
            // 会闪出系统默认的冷灰色。
            put(L"ListViewItemBackgroundPointerOver", kCardInset);
            put(L"ListViewItemBackgroundPressed", kCardHover);
            put(L"ListViewItemBackgroundSelected", kCardHover);
            put(L"ListViewItemBackgroundSelectedPointerOver", kCardHover);
            put(L"ListViewItemBackgroundSelectedPressed", kCardHover);

            put(L"TextControlBorderBrushFocused", kAccent);
            put(L"TextControlSelectionHighlightColor", kAccent);
            put(L"HyperlinkButtonForeground", kAccentText);
            put(L"HyperlinkButtonForegroundPointerOver", kAccent);
        }

        // 内容未变时不重设：每次 SetToolTip 都会替换 ToolTip 对象，若鼠标正停在
        // 元素上，已弹出的提示会被关闭再重新弹出（定时刷新时表现为悬停闪烁）。
        inline void SetToolTip(const winrt::Microsoft::UI::Xaml::DependencyObject& element, const winrt::hstring& value)
        {
            using winrt::Microsoft::UI::Xaml::Controls::ToolTipService;
            const winrt::Windows::Foundation::IInspectable current = ToolTipService::GetToolTip(element);
            if (current != nullptr)
            {
                const auto existing = current.try_as<winrt::Windows::Foundation::IReference<winrt::hstring>>();
                if (existing != nullptr && existing.Value() == value)
                {
                    return;
                }
            }
            ToolTipService::SetToolTip(element, winrt::box_value(value));
        }
    }

    // 兼容简写：页面代码里用 ui::Text(...) 而不是 token::Text(...)。
    namespace ui = token;
}
