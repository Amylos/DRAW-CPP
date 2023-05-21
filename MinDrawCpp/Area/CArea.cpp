/*
 * CArea.cpp
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */

#include "CArea.h"

CArea::CArea():
	m_rFrame(SDL_Rect{}),
	m_color(SDL_Color{})
{}

CArea::~CArea(){}

CArea::CArea(int iLocX,int iLocY,int iWidth, int iHeight, SDL_Color color):
	m_rFrame(SDL_Rect{iLocX,iLocY,iWidth,iHeight}),
	m_color(color)
{}

void CArea::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer,m_color.r,m_color.g,m_color.b,m_color.a);
	SDL_RenderFillRect(pRenderer, &m_rFrame);
}

