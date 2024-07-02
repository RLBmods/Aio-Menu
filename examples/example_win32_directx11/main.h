#pragma once
#include "imgui_internal.h"
#include <map>
ImVec2 size = ImVec2(625, 450);
void CustomStyleColor() // Отрисовка цветов
{
    ImGuiStyle& s = ImGui::GetStyle();
    ImGuiContext& g = *GImGui;

    s.Colors[ImGuiCol_WindowBg] = ImColor(11, 11, 11, 255);
    s.Colors[ImGuiCol_ChildBg] = ImColor(255, 255, 255, 255);
    //    s.Colors[ImGuiCol_ChildBg] = ImColor(165, 175, 185, 0);
    s.Colors[ImGuiCol_PopupBg] = ImColor(17, 16, 21, 255);
    s.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
    s.Colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, 255);
    //    s.Colors[ImGuiCol_FrameBg] = ImColor(11, 11, 16, 160);
    s.Colors[ImGuiCol_Border] = ImColor(14, 13, 19, 0);
    s.Colors[ImGuiCol_TextSelectedBg] = ImColor(35, 32, 43, 160);

    s.WindowPadding = ImVec2(0, 0);
    s.ChildRounding = 4.f;
    s.WindowRounding = 18.f;
    s.ItemSpacing = ImVec2(20, 15);
}

ImFont* Main_Font = nullptr;
ImFont* Medium_Font = nullptr;
ImFont* ico_Font = nullptr;
ImFont* ico_Font1 = nullptr;
ImFont* Cyrcle_Font = nullptr;

ID3D11ShaderResourceView* Logot = nullptr;
ID3D11ShaderResourceView* Image = nullptr;
ID3D11ShaderResourceView* CSGO = nullptr;
ID3D11ShaderResourceView* Terraria = nullptr;
ID3D11ShaderResourceView* Dota = nullptr;
ID3D11ShaderResourceView* Unterned = nullptr;

ID3D11ShaderResourceView* bg = nullptr;
ID3D11ShaderResourceView* bg1 = nullptr;
ID3D11ShaderResourceView* bg2 = nullptr;
ID3D11ShaderResourceView* bg3 = nullptr;
ID3D11ShaderResourceView* bg4 = nullptr;
ID3D11ShaderResourceView* bg5 = nullptr;
ID3D11ShaderResourceView* bg6 = nullptr;
ID3D11ShaderResourceView* bg7 = nullptr;
ID3D11ShaderResourceView* bg8 = nullptr;

char username[64] = { "" };
char password[64] = { "" };
char key[64] = { "" };
int tab = 1;
int tabs = 0;
int downl = 0;
bool isLoggedIn = false;
