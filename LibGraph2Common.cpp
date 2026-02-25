// Copyright 2010-2024 Benjamin ALBOUY-KISSI - Ported to Linux
/*
    This file is part of LibGraph.

    LibGraph is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LibGraph is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LibGraph. If not, see <http://www.gnu.org/licenses/>.
*/

#include "LibGraph2.h"
#include <iostream>
#include <vector>

#ifdef LIBGRAPH2_USE_SFML
#include "LibGraph2impSFML.h"
#endif

namespace LibGraph2 {

// Fonctions utilitaires pour les couleurs

ARGB MakeARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
  return ((ARGB)(a) << 24) | ((ARGB)(r) << 16) | ((ARGB)(g) << 8) | (ARGB)(b);
}

uint8_t GetA(ARGB c) { return (uint8_t)((c >> 24) & 0xFF); }

uint8_t GetR(ARGB c) { return (uint8_t)((c >> 16) & 0xFF); }

uint8_t GetG(ARGB c) { return (uint8_t)((c >> 8) & 0xFF); }

uint8_t GetB(ARGB c) { return (uint8_t)(c & 0xFF); }

// Opérateur de sortie pour wstring
std::ostream &operator<<(std::ostream &out, const std::wstring &str) {
  // Conversion simple UTF-16 vers UTF-8
  for (wchar_t c : str) {
    if (c < 128) {
      out << (char)c;
    } else {
      out << '?'; // Caractère de remplacement pour les caractères non-ASCII
    }
  }
  return out;
}

// Gestion de l'instance Singleton

ILibGraph2 *GetLibGraph2(void) {
#ifdef LIBGRAPH2_USE_SFML
  return CLibGraph2::GetInstance();
#else
  return nullptr;
#endif
}

ILibGraph2_Exp *GetLibGraph2Exp() {
#ifdef LIBGRAPH2_USE_SFML
  return static_cast<ILibGraph2_Exp *>(CLibGraph2::GetInstance());
#else
  return nullptr;
#endif
}

ILibGraph2_Adv *GetLibGraph2Adv() {
#ifdef LIBGRAPH2_USE_SFML
  return static_cast<ILibGraph2_Adv *>(CLibGraph2::GetInstance());
#else
  return nullptr;
#endif
}

void ReleaseLibGraph2(void) {
#ifdef LIBGRAPH2_USE_SFML
  CLibGraph2::ReleaseInstance();
#endif
}

// Wrappers globaux pour le Niveau 0 et compatibilité Niveau 1/2

bool waitForEvent() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return false;
  evt e;
  return pLib->waitForEvent(e);
}

evt_type getLastEventType() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return (
        evt_type)0; // Default to first enum value (usually None or MouseDown)
  return pLib->getLastEvent().type;
}

int getLastEventKeyCode() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return 0;
  return (int)pLib->getLastEvent().vkKeyCode;
}

int getLastEventMouseX() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return 0;
  return (int)pLib->getLastEvent().x;
}

int getLastEventMouseY() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return 0;
  return (int)pLib->getLastEvent().y;
}

void show(float fWidth, float fHeight, bool bFullScreen) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->show(CSize(fWidth, fHeight), bFullScreen);
}

void hide() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->hide();
}

float getWidth() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    return pLib->getSize().m_fWidth;
  return 0;
}

float getHeight() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    return pLib->getSize().m_fHeight;
  return 0;
}

void showConsole() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->showConsole();
}

void hideConsole() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->hideConsole();
}

void askForRefresh() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->askForRefresh();
}

void beginPaint() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->beginPaint();
}

void endPaint() {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->endPaint();
}

void setPen(ARGB color, float fWidth, pen_DashStyles style) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->setPen(color, fWidth, style);
}

void setSolidBrush(ARGB color) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->setSolidBrush(color);
}

void drawEllipse(float x, float y, float fWidth, float fHeight) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawEllipse(CRectangle(CPoint(x, y), CSize(fWidth, fHeight)));
}

void drawArc(float x, float y, float fWidth, float fHeight, float startAngle,
             float sweepAngle) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawArc(CRectangle(CPoint(x, y), CSize(fWidth, fHeight)), startAngle,
                  sweepAngle);
}

void drawPie(float x, float y, float fWidth, float fHeight, float startAngle,
             float sweepAngle) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawPie(CRectangle(CPoint(x, y), CSize(fWidth, fHeight)), startAngle,
                  sweepAngle);
}

void drawLine(float x1, float y1, float x2, float y2) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawLine(CPoint(x1, y1), CPoint(x2, y2));
}

void drawRectangle(float x, float y, float fWidth, float fHeight) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawRectangle(CRectangle(CPoint(x, y), CSize(fWidth, fHeight)));
}

void setPixel(float x, float y, ARGB color) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->setPixel(CPoint(x, y), color);
}

void drawBitmap(const char *sFileName, float fPosX, float fPosY,
                double dScaleFactor, double dAngleDeg, bool bXYIsCenter) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawBitmap(sFileName, CPoint(fPosX, fPosY), dScaleFactor, dAngleDeg,
                     bXYIsCenter);
}

void drawBitmap(const char *sFileName, float fPosX, float fPosY,
                float fPosPivotX, float fPosPivotY, double dScaleFactor,
                double dAngleDeg) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (pLib)
    pLib->drawBitmap(sFileName, CPoint(fPosX, fPosY),
                     CPoint(fPosPivotX, fPosPivotY), dScaleFactor, dAngleDeg);
}

// Niveau 1/2
bool waitForEvent(evt_type &evtType, int &evtKeyCode, int &evtMouseX,
                  int &evtMouseY) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return false;
  evt e;
  bool ret = pLib->waitForEvent(e);
  evtType = e.type;
  evtKeyCode = (int)e.vkKeyCode;
  evtMouseX = (int)e.x;
  evtMouseY = (int)e.y;
  return ret;
}

bool guiGetColor(ARGB &color) {
  ILibGraph2 *pLib = GetLibGraph2();
  return pLib ? pLib->guiGetColor(color) : false;
}

bool guiGetPenStyle(ARGB &color, float &fWidth, pen_DashStyles &style) {
  ILibGraph2 *pLib = GetLibGraph2();
  return pLib ? pLib->guiGetPenStyle(color, fWidth, style) : false;
}

bool guiGetValue(int &nVal, const char *strTitle, const char *strLabel) {
  ILibGraph2 *pLib = GetLibGraph2();
  return pLib ? pLib->guiGetValue(nVal, strTitle, strLabel) : false;
}

bool guiGetValue(double &dVal, const char *strTitle, const char *strLabel) {
  ILibGraph2 *pLib = GetLibGraph2();
  return pLib ? pLib->guiGetValue(dVal, strTitle, strLabel) : false;
}

msgbtn_answer guiMessageBox(const char *strTitle, const char *strText,
                            msgbtn_types btns, msgicon_types icon,
                            msgdefbtn_vals defbtn) {
  ILibGraph2 *pLib = GetLibGraph2();
  return pLib ? pLib->guiMessageBox(strTitle, strText, btns, icon, defbtn)
              : msgbtn_answer::MsgAnsError;
}

void drawPolylines(const float *pXs, const float *pYs, int nNbPoints,
                   bool bAutoClose) {
  ILibGraph2 *pLib = GetLibGraph2();
  if (!pLib)
    return;
  std::vector<CPoint> vPts;
  for (int i = 0; i < nNbPoints; ++i)
    vPts.push_back(CPoint(pXs[i], pYs[i]));
  pLib->drawPolylines(vPts, bAutoClose);
}

} // namespace LibGraph2
