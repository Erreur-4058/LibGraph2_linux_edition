// Copyright 2010-2024 Benjamin ALBOUY-KISSI - Ported to Linux/SFML
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
#pragma once
#ifdef LIBGRAPH2_USE_SFML

#include "LibGraph2.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <map>
#include <string>

#define LG_WINDOWTITLE "LibGraph 2"

using namespace LibGraph2;

class CLibGraph2 : public ILibGraph2_Adv, public ILibGraph2_Exp {
private:
  static CLibGraph2 *s_pInstance;

  // Fenêtre SFML
  sf::RenderWindow *m_pWindow;

  // Attributs de dessin actuels
  sf::Color m_outlineColor;
  float m_outlineThickness;
  sf::Color m_fillColor;
  pen_DashStyles m_penStyle;

  // Police de caractères
  sf::Font m_font;
  float m_fontSize;
  font_styles m_fontStyle;

  // Cache d'images
  std::map<std::string, sf::Texture> m_textureCache;

  // Système de coordonnées normalisées
  int m_nNormalisedSizeX;
  int m_nNormalisedSizeY;
  double m_dScale;
  int m_nOffsetX;
  int m_nOffsetY;

  // Backbuffer
  bool m_bBackBuffered;
  sf::RenderTexture m_backBuffer;

  // Dernier événement
  evt m_lastEvent;

private:
  CLibGraph2(void);
  ~CLibGraph2(void);

  // Fonctions de conversion de coordonnées
  float MapCoordinateX(float nPixelX) {
    return (float)((nPixelX - m_nOffsetX) / m_dScale);
  }
  float MapCoordinateY(float nPixelY) {
    return (float)((nPixelY - m_nOffsetY) / m_dScale);
  }
  float UnmapCoordinateX(float fNormalisedX) {
    return (float)(fNormalisedX * m_dScale + m_nOffsetX);
  }
  float UnmapCoordinateY(float fNormalisedY) {
    return (float)(fNormalisedY * m_dScale + m_nOffsetY);
  }
  float MapWidth(float nPixelWidth) { return (float)(nPixelWidth / m_dScale); }
  float MapHeight(float nPixelHeight) {
    return (float)(nPixelHeight / m_dScale);
  }
  float UnmapWidth(float fNormalisedWidth) {
    return (float)(fNormalisedWidth * m_dScale);
  }
  float UnmapHeight(float fNormalisedHeight) {
    return (float)(fNormalisedHeight * m_dScale);
  }

  int getPixelWidth();
  int getPixelHeight();
  void ComputeScaleAndOffset();
  bool NeedToFill();

  // Fonction de dessin de pie (complexe)
  void drawPieInternal(const CRectangle &bounds, float startAngle,
                       float sweepAngle);

public:
  static CLibGraph2 *GetInstance();
  static void ReleaseInstance();

  // Implémentation de ILibGraph2_Com
  virtual void show(const CSize &szWndSize = CSize(), bool bFullScreen = false);
  virtual void hide();
  virtual CSize getSize();
  virtual void showConsole();
  virtual void hideConsole();
  virtual void askForRefresh();
  virtual void beginPaint();
  virtual void endPaint();
  virtual const evt &getLastEvent() const override { return m_lastEvent; }

  // Fonctions de dessin
  virtual void setPen(ARGB color, float fWidth,
                      pen_DashStyles style = pen_DashStyles::Solid);
  virtual void setSolidBrush(ARGB color);
  virtual void drawArc(const CRectangle &rectBounds, float startAngle,
                       float sweepAngle);
  virtual void drawEllipse(const CRectangle &rectBounds);
  virtual void drawLine(const CPoint &ptP1, const CPoint &ptP2);
  virtual void drawPie(const CRectangle &rectBounds, float startAngle,
                       float sweepAngle);
  virtual void drawRectangle(const CRectangle &rectBounds);
  virtual void setPixel(const CPoint &ptPos, ARGB color);
  virtual void drawPolylines(const std::vector<CPoint> &vPoints,
                             bool bAutoClose = false);

  // Fonctions avancées
  virtual bool waitForEvent(evt &e);
  virtual void drawBitmap(const CString &sFileName, const CPoint &ptPos,
                          double dScaleFactor = 1.0, double dAngleDeg = 0,
                          bool bXYIsCenter = false);
  virtual void drawBitmap(const CString &sFileName, const CPoint &ptPos,
                          const CPoint &ptPosPivot, double dScaleFactor,
                          double dAngleDeg);
  virtual void setTextureBrush(const CString &sFileName);
  virtual void setFont(const CString &strFontName, float fPointSize,
                       font_styles nStyleFlags);
  virtual void drawString(const CString &text, const CPoint &ptPos);
  virtual void getStringDimension(const CString &text, const CPoint &ptPos,
                                  CRectangle &rectBounds);

  // Boîtes de dialogue
  virtual bool guiGetFileName(
      CString &sFileName, bool bOpen = true,
      const std::vector<CString> &vstrFileTypes = std::vector<CString>());
  virtual bool guiGetColor(ARGB &color);
  virtual bool guiGetPenStyle(ARGB &color, float &fWidth,
                              pen_DashStyles &style);
  virtual bool guiGetFont(CString &strFontName, float &fPointSize,
                          font_styles &nStyleFlags);
  virtual bool guiGetValue(CString &strVal, const CString &strTitle = L"",
                           const CString &strLabel = L"");
  virtual bool guiGetValue(int &nVal, const CString &strTitle = L"",
                           const CString &strLabel = L"");
  virtual bool guiGetValue(double &dVal, const CString &strTitle = L"",
                           const CString &strLabel = L"");
  virtual msgbtn_answer
  guiMessageBox(const CString &strTitle = L"", const CString &strText = L"",
                msgbtn_types btns = msgbtn_types::MsgBtnOK,
                msgicon_types icon = msgicon_types::MsgIcnNone,
                msgdefbtn_vals defbtn = msgdefbtn_vals::MsgDefBtn1);

  // Fonctions de compatibilité pour pointeurs
  virtual void drawPolylines(CPoint *pPoints, int nNbPoints,
                             bool bAutoClose = false) {
    drawPolylines(std::vector<CPoint>(pPoints, pPoints + nNbPoints),
                  bAutoClose);
  }
  virtual bool guiGetFileName(CString &sFileName, bool bOpen = true,
                              CString *pstrFileTypes = NULL,
                              int nNbFileTypes = 0) {
    return guiGetFileName(
        sFileName, bOpen,
        std::vector<CString>(pstrFileTypes, pstrFileTypes + nNbFileTypes));
  }
};

#endif // LIBGRAPH2_USE_SFML
