/*
 * CTcolorChart.h
 *
 *  Created on: 2 nov. 2022
 *      Author: andre
 */

#ifndef CTCOLORCHART_H_
#define CTCOLORCHART_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CTool.h>
#include<CUtil.h>
#include <stdarg.h>
#include <SDL2/SDL_image.h>

class CTcolorChart : public CTool {
private:
	int 		  	m_toolType;
	SDL_Renderer*	m_pRenderer;
	const char*		m_colorChartFileStr;
	SDL_Texture*    m_pTexture;
	SDL_Surface*	m_pSurface;
private:
	CTcolorChart();
public:
	CTcolorChart(SDL_Color color,...);
	virtual ~CTcolorChart();
	virtual int GetType();
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual SDL_Color GetColorChart(SDL_Point Point);
	virtual void*IsAt(SDL_Point*Point);
};

#endif /* CTCOLORCHART_H_ */
