#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include "main.h"
#include "image.h"
#include "Font.h"
#include <D3DX11tex.h>
#include "skStr.h"
#include "auth.hpp"
#pragma comment(lib, "D3DX11.lib")

static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };

using namespace KeyAuth;

auto name = skCrypt("Test");
auto ownerid = skCrypt("jBdWwxRDrF");
auto secret = skCrypt("b2b343aca0f92ee08a9550256e2c9281d01e221cb0b20f5f773b08fb6beb43ba");
auto version = skCrypt("1.0");
auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());
int main(int, char**)
{
    name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();

    KeyAuthApp.init();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_POPUP, 0, 0, 1920, 1080, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
 
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    Medium_Font = io.Fonts->AddFontFromMemoryTTF(&Medium, sizeof Medium, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Main_Font = io.Fonts->AddFontFromMemoryTTF(&Heavy, sizeof Heavy, 29.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico_Font = io.Fonts->AddFontFromMemoryTTF(&icons, sizeof icons, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico_Font1 = io.Fonts->AddFontFromMemoryTTF(&IcoSettings, sizeof IcoSettings, 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Cyrcle_Font = io.Fonts->AddFontFromMemoryTTF(&ico_button, sizeof ico_button, 52.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while (!done)
    {    
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();   
        {
            CustomStyleColor();

            if (bg8 == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, BackGround, sizeof(BackGround), &info, pump, &bg8, 0);
            ImGui::GetBackgroundDrawList()->AddImage(bg8, ImVec2(0, 0), ImVec2(1920, 1080), ImVec2(0, 0), ImVec2(1, 1), ImColor(150, 150, 150, 255));

            ImGui::SetNextWindowSize(ImVec2(size));
            ImGui::Begin("menu DirectX11", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollWithMouse);
            {
                const auto& p = ImGui::GetWindowPos();

                ImGui::SetCursorPos(ImVec2(33, 400));
                if (ImGui::ButtonIcons("S", ImVec2(20, 20),0));

                if (tab == 0)
                {
                    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 65, p.y + 450), ImColor(15, 15, 15, 255), 18.f, ImDrawCornerFlags_Left);
                    if (Logot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Logo, sizeof(Logo), &info, pump, &Logot, 0); ImGui::GetWindowDrawList()->AddImageRounded(Logot, ImVec2(p.x + 15, p.y + 20), ImVec2(p.x + 50, p.y + 60), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);

                    if (Image == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, image, sizeof(image), &info, pump, &Image, 0); ImGui::GetWindowDrawList()->AddImageRounded(Image, ImVec2(p.x + 285, p.y + 31), ImVec2(p.x + 331, p.y + 77), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);

                    ImGui::GetForegroundDrawList()->AddText(Main_Font, 28.0f, ImVec2(p.x + 255, p.y + 27), ImColor(175, 126, 164, 255), "Welcome");

                    ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 218, p.y + 73), ImColor(222, 225, 230, 255), "Glad to see you here again!");

                    ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 203, p.y + 88), ImColor(222, 225, 230, 255), "Log in to see available products.");

                    ImGui::SetCursorPos(ImVec2(168, 140));
                    ImGui::InputTextWithHint("Login", "", "2", username, 64);

                    ImGui::SetCursorPos(ImVec2(168, 220));
                    ImGui::InputTextWithHint("Password", "", "1", password, 64);

                    ImGui::SetCursorPos(ImVec2(235, 310));
                    if (ImGui::ButtonSellect("Dont have an account? Register", ImVec2(210, 25), 0)) tab = 6;
                    
                    ImGui::SetCursorPos(ImVec2(470, 300));

                    // Set a flag to track login status
                    bool loginSuccessful = false;

                    if (ImGui::ButtonCyrcle("Inject", "1", ImVec2(350, 350))) {
                        // Call KeyAuthApp.login() to login
                        KeyAuthApp.login(username, password);
                        isLoggedIn = true; // Assume login is successful for simplicity
                        tab = 1; // Switch to the software tab after login
                    }

                }
                if (tab == 6)
                {
                    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 65, p.y + 450), ImColor(15, 15, 15, 255), 18.f, ImDrawCornerFlags_Left);
                    if (Logot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Logo, sizeof(Logo), &info, pump, &Logot, 0); ImGui::GetWindowDrawList()->AddImageRounded(Logot, ImVec2(p.x + 15, p.y + 20), ImVec2(p.x + 50, p.y + 60), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);

                    if (Image == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, image, sizeof(image), &info, pump, &Image, 0); ImGui::GetWindowDrawList()->AddImageRounded(Image, ImVec2(p.x + 285, p.y + 31), ImVec2(p.x + 331, p.y + 77), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);

                    ImGui::GetForegroundDrawList()->AddText(Main_Font, 28.0f, ImVec2(p.x + 255, p.y + 27), ImColor(175, 126, 164, 255), "Welcome");

                    ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 218, p.y + 73), ImColor(222, 225, 230, 255), "Glad to see you here again!");

                    ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 200, p.y + 88), ImColor(222, 225, 230, 255), "Register to see available products.");

                    ImGui::SetCursorPos(ImVec2(168, 140));
                    ImGui::InputTextWithHint("Login", "", "2", username, 64);

                    ImGui::SetCursorPos(ImVec2(168, 220));
                    ImGui::InputTextWithHint("Password", "", "1", password, 64);

                    ImGui::SetCursorPos(ImVec2(168, 300));
                    ImGui::InputTextWithHint("Key", "", "1", key, 64);
              
                    ImGui::SetCursorPos(ImVec2(470, 300));

                    // Set a flag to track registration status
                    bool registrationSuccessful = false;

                    if (ImGui::ButtonCyrcle("Inject1", "1", ImVec2(350, 350))) {
                        // Call KeyAuthApp.regstr() to register
                        KeyAuthApp.regstr(username, password, key);
                        
                        // If registration is successful, set tab to 0
                        if (registrationSuccessful) {
                            tab = 0;
                        }
                    }

                }
                if (tab == 1)
                {
                    if (isLoggedIn) {
                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 65, p.y + 450), ImColor(15, 15, 15, 255), 18.f, ImDrawCornerFlags_Left);
                        if (Logot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Logo, sizeof(Logo), &info, pump, &Logot, 0); ImGui::GetWindowDrawList()->AddImageRounded(Logot, ImVec2(p.x + 15, p.y + 20), ImVec2(p.x + 50, p.y + 60), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), 0);

                        if (tabs == 0)
                        {
                            ImGui::GetForegroundDrawList()->AddText(Main_Font, 29.0f, ImVec2(p.x + 155, p.y + 40), ImColor(175, 126, 164, 255), "Velo.cc | Permanent Spoofer ");
                            ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 243, p.y + 73), ImColor(222, 225, 230, 255), "Subscription till: 20.08.2023");
                            ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 196, p.y + 88), ImColor(222, 225, 230, 255), "To renew your subscription visit our");  ImGui::GetForegroundDrawList()->AddText(Medium_Font, 17.0f, ImVec2(p.x + 448, p.y + 88), ImColor(175, 126, 164, 255), "website.");

                            ImGui::SetCursorPos(ImVec2(200, 350));
                            if (ImGui::Button("Asus Users", ImVec2(100, 25)));

                            ImGui::SetCursorPos(ImVec2(310, 350));
                            if (ImGui::Button("Option 2", ImVec2(100, 25)));

                            ImGui::SetCursorPos(ImVec2(200, 385));
                            if (ImGui::Button("Launch", ImVec2(210, 25)));

                            ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 130, p.y + 115), ImVec2(p.x + 500, p.y + 330), ImColor(175, 126, 164, 255), 4.f);

                            if (downl == 1)
                            {
                                static float range = 0.0f;
                                range = ImLerp(range, downl == 1 ? 240.f : 0.f, ImGui::GetIO().DeltaTime * 4.f);

                                static float loading_test = 0.00f;
                                loading_test += 0.0075f;

                                if (loading_test < 2.f)
                                {
                                    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 625, p.y + 450), ImColor(10, 10, 10, (int)range), 8.f);

                                    ImGuiWindow* window = ImGui::GetCurrentWindow();
                                    if (window->SkipItems)
                                        return false;
                                    ImGuiContext& g = *GImGui;
                                    const ImGuiStyle& style = g.Style;
                                    ImVec2 pos = window->DC.CursorPos;
                                    const auto& CurrentWindowPos = ImGui::GetWindowPos();
                                    const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                                    char label;
                                    const ImGuiID id = window->GetID(label);
                                    static std::map<ImGuiID, float> alpha_anim;
                                    auto it_alpha = alpha_anim.find(id);
                                    if (it_alpha == alpha_anim.end())
                                    {
                                        alpha_anim.insert({ id, 255 });
                                        it_alpha = alpha_anim.find(id);
                                    }
                                    if (it_alpha->second <= 255)
                                    {
                                        it_alpha->second += 0.6 / ImGui::GetIO().Framerate * 80.f;
                                    }
                                    else
                                    {

                                    }
                                    int animantion = (int)it_alpha->second;
                                    auto front = ImGui::GetForegroundDrawList(); // also you can use GetWindowDrawList() or GetBackgroundDrawList()
                                    const ImVec2 centre = ImVec2(pos.x + 313.f, pos.y - 200.f + style.FramePadding.y);
                                    static ImColor fore_color(163, 118, 153, animantion);
                                    static ImColor back_color(163, 118, 153, 170);
                                    static float arc_size = 0.45f; // 0.f < x < 2.f
                                    static float radiusss = 35.f;
                                    static float thicknessss = 4.f;
                                    int tim = g.Time;
                                    int secod = 7;
                                    static float position = 0.f;
                                    position = ImLerp(position, IM_PI * 2.f, ImGui::GetIO().DeltaTime * 2.3f);
                                    front->PathClear();
                                    front->PathArcTo(centre, 10.f, 0.f, 2.f * IM_PI, 40.f);
                                    front->PathStroke(ImGui::GetColorU32(back_color.Value), 0, 5);
                                    front->PathClear();
                                    front->PathArcTo(centre, 10.f, IM_PI * 1.5f + position, IM_PI * (1.5f + arc_size) + position, 40.f);
                                    front->PathStroke(ImGui::GetColorU32(fore_color.Value), 0, 5);
                                    if (position >= IM_PI * 1.90f)
                                        position = 0.f;
                                }
                                else
                                {

                                }
                            }
                            ImGui::SetCursorPos(ImVec2(470, 300));
                            if (ImGui::ButtonCyrcle("Inject1", "1", ImVec2(350, 350)))downl = 1;
                        }
                    }
                    //else {
                    //    // If not logged in, display a message box
                    //    ImGui::OpenPopup("InvalidLoginPopup");
                    //    if (ImGui::BeginPopupModal("InvalidLoginPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                    //        ImGui::Text("Invalid login. Please try again.");
                    //        if (ImGui::Button("OK", ImVec2(120, 0))) {
                    //            ImGui::CloseCurrentPopup();
                    //        }
                    //        ImGui::EndPopup();
                    //    }
                    //}
                }
            }ImGui::End();
        }
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
