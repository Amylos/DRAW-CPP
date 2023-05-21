/*
 * CTcolorChart.cpp
 *
 *  Created on: 2 nov. 2022
 *      Author: andre
 */

#include <CTcolorChart.h>
#include <SDL2/SDL_image.h>

CTcolorChart::CTcolorChart(): CTool(),m_toolType(0),
	m_pRenderer(nullptr),
	m_colorChartFileStr(nullptr),
	m_pTexture(nullptr),
	m_pSurface(nullptr){}

CTcolorChart::~CTcolorChart(){}

CTcolorChart::CTcolorChart(SDL_Color color,...): CTool(),m_toolType(TOOL_COLORCHART){

	va_list optList;
	va_start(optList, color);

	m_pRenderer=va_arg(optList, SDL_Renderer*);
	m_colorChartFileStr=va_arg(optList, const char*);

	m_pSurface = IMG_Load(m_colorChartFileStr);
	if(m_pSurface == NULL)	SDL_Log("Failed to load surface : %s \n", SDL_GetError());

	m_pTexture=IMG_LoadTexture(m_pRenderer, m_colorChartFileStr);
	if(m_pTexture==NULL)	SDL_Log("Failed to load the color chart png: %s\n", SDL_GetError());

	/* only for use of TOOL_COLORCHART: DO NOT MODIFY */
	va_end(optList);

}

int CTcolorChart::GetType(){
	 return m_toolType;
}

void CTcolorChart::Draw(SDL_Renderer*pRenderer)const{
	SDL_Rect frame = SDL_Rect{
		m_rFrame.x,
		 m_rFrame.y,
		 m_rFrame.w,
		 150};

	 if(m_pTexture){
		SDL_RenderCopy(
			pRenderer,
			m_pTexture,
			NULL,
			&frame);
	}
	else{
		SDL_SetRenderDrawColor(pRenderer, 100, 100, 100, 255);
		SDL_RenderFillRect(
			pRenderer
			,&frame);
	}
}

void*CTcolorChart::IsAt(SDL_Point*Point){

	 m_rFrame.h = 150;
	 if(SDL_PointInRect(Point, &m_rFrame)) return this;
	 return nullptr;
}

SDL_Color CTcolorChart::GetColorChart(SDL_Point Point){
	Point.x -= m_rFrame.x;
	Point.y -= m_rFrame.y;

	Point.x *= (double)m_pSurface->w/m_rFrame.w;
	Point.y *= (double)m_pSurface->h/m_rFrame.h;

	m_color =*(SDL_Color*)((Uint8*)m_pSurface->pixels + Point.y*m_pSurface->pitch + Point.x*m_pSurface->format->BytesPerPixel);

	return m_color;
}

